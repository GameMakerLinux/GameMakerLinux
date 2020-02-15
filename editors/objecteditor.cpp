/*
    Copyright (C) Alexander Roper

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "objecteditor.h"
#include "gamesettings.h"
#include "utils/utils.h"
#include "widgets/codeeditor.h"
#include "widgets/selectitem.h"
#include "resources/spriteresourceitem.h"
#include "models/sortedeventsmodel.h"
#include "utils/flowlayout.h"
#include <QDir>
#include <QDebug>

struct EventTypeAndNumber {
    ObjectEvent::EventType type;
    int number = 0;
};
Q_DECLARE_METATYPE(EventTypeAndNumber)

ObjectEditor::ObjectEditor(ObjectResourceItem* item)
    : MainEditor { item }
    , ui { new Ui::ObjectEditor }
{
    QTabWidget * tabWidget = new QTabWidget;
    ui->setupUi(tabWidget);
    setWidget(tabWidget);

    tabWidget->setCurrentIndex(0);

    // remove the widgets to put them in a FlowLayout
    ui->checkboxLayout->removeWidget(ui->visibleCheckBox);
    ui->checkboxLayout->removeWidget(ui->solidCheckBox);
    ui->checkboxLayout->removeWidget(ui->persistentCheckBox);
    ui->checkboxLayout->removeWidget(ui->usesPhysicsCheckBox);

    ui->physicsOptions->layout()->removeWidget(ui->sensorCheckBox);
    ui->physicsOptions->layout()->removeWidget(ui->startAwakeCheckBox);
    ui->physicsOptions->layout()->removeWidget(ui->kinematicCheckBox);

    auto flow = new FlowLayout;
    ui->checkboxLayout->addLayout(flow);
    flow->addWidget(ui->visibleCheckBox);
    flow->addWidget(ui->solidCheckBox);
    flow->addWidget(ui->persistentCheckBox);
    flow->addWidget(ui->usesPhysicsCheckBox);

    flow = new FlowLayout;
    ui->physicsVerticalLayout->addLayout(flow);
    std::vector<QString> labels {
        "Density",
        "Restitution",
        "Collision Group",
        "Linear Damping",
        "Angular Damping",
        "Friction"
    };
    std::vector<FormEdit**> edits {
        &m_density,
        &m_restitution,
        &m_collisionGroup,
        &m_linearDamping,
        &m_angularDamping,
        &m_friction
    };
    for (unsigned int i = 0; i < labels.size(); i++)
    {
        *(edits[i]) = new FormEdit;
        (*(edits[i]))->setLineEditWidth(50);
        (*(edits[i]))->setLabel(labels[i]);
        if (edits[i] == &m_collisionGroup)
        {
            (*(edits[i]))->setValidator(new QIntValidator(0, 100));
        }
        else
        {
            (*(edits[i]))->setValidator(new QDoubleValidator(0.0, 100.0, 1));
        }
        flow->addWidget(*(edits[i]));
    }

    flow = new FlowLayout;
    flow->addWidget(ui->sensorCheckBox);
    flow->addWidget(ui->startAwakeCheckBox);
    flow->addWidget(ui->kinematicCheckBox);
    ui->physicsVerticalLayout->addLayout(flow);
    // FlowLayout end

    auto setParentAction = ui->parentLineEdit->addAction(QIcon::fromTheme("edit-undo"), QLineEdit::TrailingPosition);
    connect(setParentAction, &QAction::triggered, this, &ObjectEditor::chooseParent);

    auto setMaskAction = ui->maskLineEdit->addAction(QIcon::fromTheme("edit-undo"), QLineEdit::TrailingPosition);
    connect(setMaskAction, &QAction::triggered, this, &ObjectEditor::chooseMask);

    auto * sortedModel = new SortedEventsModel;
    sortedModel->setSourceModel(&eventsModel);
    ui->eventsListView->setModel(sortedModel);
    ui->eventsListView->selectionModel()->select(sortedModel->index(0, 0), QItemSelectionModel::ClearAndSelect);
    ui->eventsListView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(&eventsModel, &EventsModel::rowsInserted, this, &ObjectEditor::onEventsAdded);
    connect(&eventsModel, &EventsModel::rowsRemoved, this, &ObjectEditor::onEventsRemoved);
    connect(&eventsModel, &EventsModel::modelReset, this, &ObjectEditor::onEventsCleared);

    connect(ui->spriteViewer, &QPushButton::clicked, this, &ObjectEditor::chooseSprite);

    connect(ui->eventsListView, &QListView::pressed, [this](const QModelIndex & index) {
        ui->stackedCodeEditorWidget->setCurrentIndex(index.row());
    });
    connect(ui->eventsListView, &QListView::customContextMenuRequested, this, &ObjectEditor::showEventsContextMenu);

    connect(ui->nameLineEdit, &QLineEdit::textChanged, [item](QString text) {
        item->setName(text);
    });
    connect(ui->maskLineEdit, &QLineEdit::textChanged, [this, item](QString) {
        item->setMaskSprite(m_maskSprite);
    });
    connect(ui->visibleCheckBox, &QCheckBox::toggled, [item](bool toggled) {
        item->setVisible(toggled);
    });
    connect(ui->solidCheckBox, &QCheckBox::toggled, [item](bool toggled) {
        item->setSolid(toggled);
    });
    connect(ui->persistentCheckBox, &QCheckBox::toggled, [item](bool toggled) {
        item->setPersistent(toggled);
    });
    connect(ui->usesPhysicsCheckBox, &QCheckBox::toggled, [item](bool toggled) {
        item->setPhysics(toggled);
    });
    connect(ui->parentLineEdit, &QLineEdit::textChanged, [this, item](QString) {
        item->setParentObject(m_parentObject);
    });

    connect(m_density, &FormEdit::editingFinished, [this, item]() {
        item->setDensity(m_density->text().toDouble());
    });
    connect(m_restitution, &FormEdit::editingFinished, [this, item]() {
        item->setRestitution(m_restitution->text().toDouble());
    });
    connect(m_collisionGroup, &FormEdit::editingFinished, [this, item]() {
        item->setGroup(m_collisionGroup->text().toInt());
    });
    connect(m_linearDamping, &FormEdit::editingFinished, [this, item]() {
        item->setLinearDamping(m_linearDamping->text().toDouble());
    });
    connect(m_angularDamping, &FormEdit::editingFinished, [this, item]() {
        item->setAngularDamping(m_angularDamping->text().toDouble());
    });
    connect(m_friction, &FormEdit::editingFinished, [this, item]() {
        item->setFriction(m_friction->text().toDouble());
    });

    connect(ui->kinematicCheckBox, &QCheckBox::toggled, [item](bool toggled) {
        item->setKinematic(toggled);
    });
    connect(ui->sensorCheckBox, &QCheckBox::toggled, [item](bool toggled) {
        item->setSensor(toggled);
    });
    connect(ui->startAwakeCheckBox, &QCheckBox::toggled, [item](bool toggled) {
        item->startAwake(toggled);
    });

    load();

    createEventsMenu();
}

void ObjectEditor::refreshChildren()
{
    auto pItem = item<ObjectResourceItem>();

    ui->childrenTextEdit->clear();

    auto objectItems = ResourceItem::findAll(ResourceType::Object);
    for (auto & childId : objectItems)
    {
        auto pChildItem = ResourceItem::get<ObjectResourceItem>(childId);
        auto pParent = pChildItem->parentObject();
        if (pParent && pParent->id() == pItem->id())
            ui->childrenTextEdit->appendPlainText(pChildItem->name());
    }
}

void ObjectEditor::save()
{
    auto pItem = item<ObjectResourceItem>();
    auto oldName = pItem->name();

    // GENERAL SETTINGS
    auto name = ui->nameLineEdit->text();
    pItem->setName(name);
    pItem->setSprite(m_sprite);
    pItem->setMaskSprite(m_maskSprite);

    // Rename directory/file when name changes
    if (oldName != name)
    {
        QDir(GameSettings::rootPath() + "/objects").rename(oldName, name);
        QFile(GameSettings::rootPath() + "/objects/" + name + "/" + oldName + ".yy").rename(name + ".yy");
    }

    // EVENTS (TODO: improve?)
    for (int i = 0; i < ui->stackedCodeEditorWidget->count(); i++)
    {
        auto editor = qobject_cast<CodeEditor*>(ui->stackedCodeEditorWidget->widget(i));
        if (editor)
        {
            QString filename = QString("%1/%2").arg(GameSettings::rootPath(), eventsModel.getFilename(i));
            Utils::writeFile(filename, editor->getCode().toLocal8Bit());
        }
    }

    pItem->clearEvents();
    for (int i = 0; i < eventsModel.rowCount(); i++)
    {
        auto ev = eventsModel.getEvent(i);
        pItem->addEvent(ev);
    }

    // HIERARCHY
    auto previousParent = pItem->parentObject();
    pItem->setParentObject(m_parentObject);
    if (previousParent != m_parentObject)
    {
        // update children when an object has it's parent changed
        if (previousParent)
            emit childrenChanged(previousParent);
        if (m_parentObject)
            emit childrenChanged(pItem->parentObject());
    }

    // PHYSICS
    pItem->setVisible(ui->visibleCheckBox->isChecked());
    pItem->setSolid(ui->solidCheckBox->isChecked());
    pItem->setPersistent(ui->persistentCheckBox->isChecked());
    pItem->setPhysics(ui->usesPhysicsCheckBox->isChecked());

    pItem->setDensity(m_density->text().toDouble());
    pItem->setRestitution(m_restitution->text().toDouble());
    pItem->setGroup(m_collisionGroup->text().toInt());
    pItem->setLinearDamping(m_linearDamping->text().toDouble());
    pItem->setAngularDamping(m_angularDamping->text().toDouble());
    pItem->setFriction(m_friction->text().toDouble());

    pItem->setSensor(ui->sensorCheckBox->isChecked());
    pItem->startAwake(ui->startAwakeCheckBox->isChecked());
    pItem->setKinematic(ui->kinematicCheckBox->isChecked());

    // SAVE FILE
    auto json = pItem->save();
    QString filename = QString("%1/%2").arg(GameSettings::rootPath(), pItem->filename());
    Utils::writeFile(filename, json);

    emit saved();
}

void ObjectEditor::load()
{
    auto pItem = item<ObjectResourceItem>();

    // GENERAL SETTINGS
    ui->nameLineEdit->setText(pItem->name());

    if (auto sprite = pItem->sprite())
    {
        auto pix = sprite->thumbnail();
        ui->spriteViewer->setIcon(pix);
    }
    else
    {
        ui->spriteViewer->setIcon({});
    }

    // EVENTS
    eventsModel.clear();

    auto pCurrentItemInHierarchy = pItem;
    while (pCurrentItemInHierarchy)
    {
        for (int i = 0; i < pCurrentItemInHierarchy->eventsCount(); i++)
        {
            auto event = pCurrentItemInHierarchy->getEvent(i);
            eventsModel.addEvent(event, pCurrentItemInHierarchy != pItem);
        }

        pCurrentItemInHierarchy = nullptr; //pCurrentItemInHierarchy->parentObject();
    }

    // HIERARCHY
    if (pItem->parentObject() != nullptr)
    {
        m_parentObject = pItem->parentObject();
        ui->parentLineEdit->setText(m_parentObject->name());
    }
    else
    {
        m_parentObject = nullptr;
        ui->parentLineEdit->setText({});
    }

    refreshChildren();

    // PHYSICS
    ui->visibleCheckBox->setChecked(pItem->isVisible());
    ui->solidCheckBox->setChecked(pItem->isSolid());
    ui->persistentCheckBox->setChecked(pItem->isPersistent());
    ui->usesPhysicsCheckBox->setChecked(pItem->usesPhysics());

    m_density->setText(QString::number(pItem->getDensity()));
    m_restitution->setText(QString::number(pItem->getRestitution()));
    m_collisionGroup->setText(QString::number(pItem->getGroup()));
    m_linearDamping->setText(QString::number(pItem->getLinearDamping()));
    m_angularDamping->setText(QString::number(pItem->getAngularDamping()));
    m_friction->setText(QString::number(pItem->getFriction()));

    ui->sensorCheckBox->setChecked(pItem->isSensor());
    ui->startAwakeCheckBox->setChecked(pItem->startsAwake());
    ui->kinematicCheckBox->setChecked(pItem->isKinematic());
}

void ObjectEditor::onEventsAdded(const QModelIndex & parent, int first, int last)
{
    Q_UNUSED(parent)
    for (int i = first; i <= last; i++)
    {
        auto editor = new CodeEditor;
        ui->stackedCodeEditorWidget->insertWidget(i, editor);

        auto inherited = eventsModel.isInherited(i);
        if (inherited)
        {
            editor->setReadOnly(true);
        }
        else
        {
            auto item = eventsModel.getEvent(i);
            editor->setCode(item->code());
            connect(editor, &CodeEditor::textChanged, [editor, item]() {
                item->setCode(editor->getCode());
            });
        }
    }
}

void ObjectEditor::onEventsRemoved(const QModelIndex & parent, int first, int last)
{
    Q_UNUSED(parent)
    for (int i = first; i <= last; i++)
    {
        ui->stackedCodeEditorWidget->removeWidget(ui->stackedCodeEditorWidget->widget(first));
    }
}

void ObjectEditor::onEventsCleared()
{
    while (ui->stackedCodeEditorWidget->count() > 0)
    {
        ui->stackedCodeEditorWidget->removeWidget(ui->stackedCodeEditorWidget->widget(0));
    }
}

void ObjectEditor::chooseParent()
{
    ResourceItem * pItem = ResourceItem::findFolder(ResourceType::Object);
    SelectItem selectParent("Select parent", pItem, item<ObjectResourceItem>());
    if (selectParent.exec())
    {
        auto parentItem = selectParent.choice();
        if (m_parentObject != parentItem)
        {
            if (parentItem)
            {
                m_parentObject = qobject_cast<ObjectResourceItem*>(parentItem);
                ui->parentLineEdit->setText(parentItem->name());
            }
            else
            {
                m_parentObject = nullptr;
                ui->parentLineEdit->setText({});
            }
        }
    }
}

void ObjectEditor::chooseMask()
{
    ResourceItem * pItem = ResourceItem::findFolder(ResourceType::Sprite);
    SelectItem selectMask("Select sprite mask", pItem);
    if (selectMask.exec())
    {
        auto maskItem = selectMask.choice();

        if (maskItem)
        {
            m_maskSprite = qobject_cast<SpriteResourceItem*>(maskItem);
            ui->maskLineEdit->setText(maskItem->name());
        }
        else
        {
            m_maskSprite = nullptr;
            ui->maskLineEdit->setText({});
        }
    }
}

void ObjectEditor::chooseSprite()
{
    ResourceItem * pItem = ResourceItem::findFolder(ResourceType::Sprite);
    SelectItem selectMask("Select sprite", pItem);
    if (selectMask.exec())
    {
        auto spriteItem = selectMask.choice();

        if (spriteItem)
        {
            m_sprite = qobject_cast<SpriteResourceItem*>(spriteItem);
            ui->spriteViewer->setIcon(m_sprite->thumbnail());
        }
        else
        {
            m_sprite = nullptr;
            ui->spriteViewer->setIcon(QIcon());
        }

        item<ObjectResourceItem>()->setSprite(m_sprite);
    }
}

void ObjectEditor::showEventsContextMenu(const QPoint & pos)
{
    auto index = ui->eventsListView->indexAt(pos);
    QMenu menu;
    menu.addAction("Add new event", this, &ObjectEditor::addEvent);
    if (index.isValid())
    {
        int row = index.row();
        bool inherited = eventsModel.isInherited(row);
        auto event = eventsModel.getEvent(row);
        if (inherited)
        {
            auto act = menu.addAction("Override event", this, &ObjectEditor::overrideEvent);
            act->setData(QVariant::fromValue(event));
        }
        else
        {
            auto act = menu.addAction("Change event", this, qOverload<>(&ObjectEditor::changeEvent));
            act->setData(QVariant::fromValue(event));
            act = menu.addAction("Delete event", this, &ObjectEditor::deleteEvent);
            act->setData(QVariant::fromValue(event));
        }
    }
    menu.exec(QCursor::pos());
}

void ObjectEditor::addEvent()
{
    menuTriggeredType = MenuTriggeredType::Create;
    auto menu = getEventsMenu();
    connect(menu, &QMenu::triggered, this, &ObjectEditor::menuTriggered);
    menu->exec(QCursor::pos());
    menuTriggeredType = MenuTriggeredType::Nothing;
}

void ObjectEditor::overrideEvent()
{
    auto action = qobject_cast<QAction*>(sender());
    auto event = action->data().value<ObjectEvent*>();
    Q_UNUSED(event)
}

void ObjectEditor::changeEvent()
{
    auto action = qobject_cast<QAction*>(sender());
    auto event = action->data().value<ObjectEvent*>();
    Q_UNUSED(event)
}

void ObjectEditor::deleteEvent()
{
    auto action = qobject_cast<QAction*>(sender());
    auto event = action->data().value<ObjectEvent*>();

    eventsModel.deleteEvent(event);
}

void ObjectEditor::menuTriggered(QAction * action)
{
    if (menuTriggeredType == MenuTriggeredType::Nothing)
        return;

    auto pItem = item<ObjectResourceItem>();
    auto eventTypeAndNumber = action->data().value<EventTypeAndNumber>();
    auto newEvent = new ObjectEvent(eventTypeAndNumber.type, eventTypeAndNumber.number);
    newEvent->setOwner(pItem->id());
    item<ObjectResourceItem>()->addEvent(newEvent);
    eventsModel.addEvent(newEvent);
}

void ObjectEditor::createEventsMenu()
{
}

QMenu * ObjectEditor::getEventsMenu()
{
    static bool init = false;
    static QMenu eventsMenu;
    if (!init)
    {
        auto act = eventsMenu.addAction("Create");
        act->setData(QVariant::fromValue(EventTypeAndNumber { ObjectEvent::CreateEvent }));
        act = eventsMenu.addAction("Step");
        act->setData(QVariant::fromValue(EventTypeAndNumber { ObjectEvent::StepEvent }));
        act = eventsMenu.addAction("Begin Step");
        act->setData(QVariant::fromValue(EventTypeAndNumber { ObjectEvent::StepEvent, 1 }));
        act = eventsMenu.addAction("End Step");
        act->setData(QVariant::fromValue(EventTypeAndNumber { ObjectEvent::StepEvent, 2 }));

        init = true;
    }
    return &eventsMenu;
}
