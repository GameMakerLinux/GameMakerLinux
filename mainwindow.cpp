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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "utils/utils.h"
#include <QAction>
#include "gamesettings.h"
#include <QLabel>
#include "resources/allresourceitems.h"
#include "editors/alleditors.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow { parent },
    ui { new Ui::MainWindow }
{
    ui->setupUi(this);

    // DOCKS
    resourcesTreeDock.setModel(&resourcesModel);
    addDockWidget(Qt::RightDockWidgetArea, &resourcesTreeDock);

    // CENTRAL WIDGET
    tabWidget = new QTabWidget;
    tabWidget->setTabsClosable(true);
    setCentralWidget(tabWidget);

    // CONNECT
    connect(ui->action_Open_project, &QAction::triggered, this, &MainWindow::openProject);
    connect(ui->action_Close_project, &QAction::triggered, this, &MainWindow::closeProject);
    connect(ui->action_Resources, &QAction::toggled, &resourcesTreeDock, &ResourcesTreeDock::setVisible);

    connect(&resourcesTreeDock, &ResourcesTreeDock::openAmazonFireOptions, this, &MainWindow::openAmazonFireOptions);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openAndroidOptions, this, &MainWindow::openAndroidOptions);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openIncludedFile, this, &MainWindow::openIncludedFile);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openiOsOptions, this, &MainWindow::openiOsOptions);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openLinuxOptions, this, &MainWindow::openLinuxOptions);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openMacOptions, this, &MainWindow::openMacOptions);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openMainOptions, this, &MainWindow::openMainOptions);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openObject, this, &MainWindow::openObject);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openRoom, this, &MainWindow::openRoom);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openScript, this, &MainWindow::openScript);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openSprite, this, &MainWindow::openSprite);
    connect(&resourcesTreeDock, &ResourcesTreeDock::openWindowsOptions, this, &MainWindow::openWindowsOptions);
    connect(&resourcesTreeDock, &ResourcesTreeDock::itemRemoved, this, &MainWindow::removeTab);
    connect(&resourcesTreeDock, &ResourcesTreeDock::visibilityChanged, ui->action_Resources, &QAction::setChecked);

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);

    auto lop = GameSettings::lastOpenedProject();
    if (!lop.isEmpty())
    {
        loadProject(lop);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openProject()
{
    QString projectPath = QFileInfo(GameSettings::lastOpenedProject()).absolutePath();
    QString filename = QFileDialog::getOpenFileName(this, "Open project", projectPath, "GameMaker Studio project (*.yyp)");
    if (!filename.isEmpty())
    {
        loadProject(filename);
    }
}

void MainWindow::openRoom(RoomResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    auto editor = new RoomEditor(item);
    int pos = tabWidget->addTab(editor, item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);

    connect(editor, &RoomEditor::openObject, this, &MainWindow::openObject);
    connect(editor, &RoomEditor::openInstance, this, &MainWindow::openInstance);
}

void MainWindow::openSprite(SpriteResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    auto label = new QLabel;
    label->setPixmap(item->pixmap());
    int pos = tabWidget->addTab(label, item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openScript(ScriptResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    auto editor = new ScriptEditor(item);
    int pos = tabWidget->addTab(editor, item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openAndroidOptions(AndroidOptionsResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("android"), item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openAmazonFireOptions(AmazonFireOptionsResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("amazon fire"), item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openWindowsOptions(WindowsOptionsResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("windows"), item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openLinuxOptions(LinuxOptionsResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("linux"), item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openMacOptions(MacOptionsResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("mac"), item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openiOsOptions(iOSOptionsResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("ios"), item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openIncludedFile(IncludedFileResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("included files"), item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openMainOptions(MainOptionsResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("main options"), item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openObject(ObjectResourceItem * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    auto editor = new ObjectEditor(item);
    connect(editor, &ObjectEditor::childrenChanged, this, &MainWindow::updateChildren);

    int pos = tabWidget->addTab(editor, item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);

    connect(item, &ObjectResourceItem::nameChanged, [this, item]() {
        int index = idOfOpenedTabs.indexOf(item->id());
        tabWidget->setTabText(index, item->name());
    });
}

void MainWindow::openInstance(ObjectInstance * item)
{
    auto id = item->id();
    if (moveToTab(id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("instance"), item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::removeTab(QString id)
{
    int tab = idOfOpenedTabs.indexOf(id);
    if (tab != -1)
        closeTab(tab);
}

void MainWindow::saveProjectItem()
{
    // so the projectResource is not saved twice
    if (!m_savingProject)
    {
        auto json = projectResource.save();
        QString filename = QString("%1/%2").arg(GameSettings::rootPath(), projectResource.filename());
        Utils::writeFile(filename, json);
    }
}

void MainWindow::saveProject()
{
    m_savingProject = true;
    emit doSave();
    m_savingProject = false;

    auto json = projectResource.save();
    QString filename = QString("%1/%2").arg(GameSettings::rootPath(), projectResource.filename());
    Utils::writeFile(filename, json);
}

bool MainWindow::closeProject()
{
    bool isDirty = false;
    if (isDirty)
    {
        auto choice = QMessageBox::information(this, "Unsaved changes", "Do you want to close this project without saving?", QMessageBox::Yes, QMessageBox::No);
        if (choice == QMessageBox::No)
        {
            return false;
        }
    }

    // clear everything
    ResourceItem::clear();
    resourcesModel.clear();
    tabWidget->clear();

    return true;
}

void MainWindow::updateChildren(ObjectResourceItem * item)
{
    auto id = item->id();
    if (idOfOpenedTabs.contains(id))
    {
        int pos = idOfOpenedTabs.indexOf(id);
        auto editor = qobject_cast<ObjectEditor*>(tabWidget->widget(pos));
        editor->refreshChildren();
    }
}

void MainWindow::loadProject(QString filename)
{
    if (!closeProject())
    {
        return;
    }

    QFileInfo fi(filename);
    GameSettings::setRootPath(fi.absolutePath());

    auto json = Utils::readFileToJSON(filename);
    if (json.isEmpty())
    {
        return;
    }

    projectResource.setName(fi.baseName());
    projectResource.load(json);

    resourcesModel.fill(ResourceItem::all());

    GameSettings::setLastOpenedProject(filename);
}

bool MainWindow::moveToTab(QString id)
{
    if (idOfOpenedTabs.contains(id))
    {
        int pos = idOfOpenedTabs.indexOf(id);
        tabWidget->setCurrentIndex(pos);
        return true;
    }

    return false;
}

bool MainWindow::closeTab(int pos)
{
    idOfOpenedTabs.remove(pos);
    tabWidget->removeTab(pos);

    return true;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if (closeProject())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
