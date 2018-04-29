/*
    Copyright (C) 2018  Alexander Roper

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
#include "models/resourcesmodel.h"
#include "docks/resourcestreedock.h"
#include <QDebug>
#include <QAction>
#include "gamesettings.h"
#include <QLabel>
#include "resources/allresourceitems.h"
#include "editors/alleditors.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    resourcesModel(new ResourcesModel),
    resourcesTreeDock(new ResourcesTreeDock)
{
    ui->setupUi(this);

    // DOCKS
    resourcesTreeDock->setModel(resourcesModel);
    addDockWidget(Qt::RightDockWidgetArea, resourcesTreeDock);

    // CENTRAL WIDGET
    tabWidget = new QTabWidget;
    tabWidget->setTabsClosable(true);
    setCentralWidget(tabWidget);

    // CONNECT
    connect(ui->action_Open_project, &QAction::triggered, this, &MainWindow::openProject);
    connect(ui->action_Resources, &QAction::toggled, resourcesTreeDock, &ResourcesTreeDock::setVisible);

    connect(resourcesTreeDock, &ResourcesTreeDock::openAmazonFireOptions, this, &MainWindow::openAmazonFireOptions);
    connect(resourcesTreeDock, &ResourcesTreeDock::openAndroidOptions, this, &MainWindow::openAndroidOptions);
    connect(resourcesTreeDock, &ResourcesTreeDock::openIncludedFile, this, &MainWindow::openIncludedFile);
    connect(resourcesTreeDock, &ResourcesTreeDock::openiOsOptions, this, &MainWindow::openiOsOptions);
    connect(resourcesTreeDock, &ResourcesTreeDock::openLinuxOptions, this, &MainWindow::openLinuxOptions);
    connect(resourcesTreeDock, &ResourcesTreeDock::openMacOptions, this, &MainWindow::openMacOptions);
    connect(resourcesTreeDock, &ResourcesTreeDock::openMainOptions, this, &MainWindow::openMainOptions);
    connect(resourcesTreeDock, &ResourcesTreeDock::openObject, this, &MainWindow::openObject);
    connect(resourcesTreeDock, &ResourcesTreeDock::openRoom, this, &MainWindow::openRoom);
    connect(resourcesTreeDock, &ResourcesTreeDock::openScript, this, &MainWindow::openScript);
    connect(resourcesTreeDock, &ResourcesTreeDock::openSprite, this, &MainWindow::openSprite);
    connect(resourcesTreeDock, &ResourcesTreeDock::openWindowsOptions, this, &MainWindow::openWindowsOptions);
    connect(resourcesTreeDock, &ResourcesTreeDock::visibilityChanged, ui->action_Resources, &QAction::setChecked);

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);

    // // // // // // //
    loadProject("/home/minirop/GameMaker Projects/shoot the notes/shoot the notes.yyp");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openProject()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open project", "/home/minirop/GameMaker Projects/shoot the notes", "GameMaker Studio project (*.yyp)");
    if (!filename.isEmpty())
    {
        loadProject(filename);
    }
}

void MainWindow::openRoom(RoomResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    auto editor = new RoomEditor(item);
    int pos = tabWidget->addTab(editor, item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openSprite(SpriteResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("sprite"), item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openScript(ScriptResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    auto editor = new ScriptEditor(item);
    int pos = tabWidget->addTab(editor, item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openAndroidOptions(AndroidOptionsResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("android"), item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openAmazonFireOptions(AmazonFireOptionsResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("amazon fire"), item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openWindowsOptions(WindowsOptionsResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("windows"), item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openLinuxOptions(LinuxOptionsResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("linux"), item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openMacOptions(MacOptionsResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("mac"), item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openiOsOptions(iOSOptionsResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("ios"), item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openIncludedFile(IncludedFileResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("included files"), item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openMainOptions(MainOptionsResourceItem * item)
{
    if (checkTab(item->id))
    {
        return;
    }

    int pos = tabWidget->addTab(new QLabel("main options"), item->name());

    idOfOpenedTabs.push_back(item->id);

    tabWidget->setCurrentIndex(pos);
}

void MainWindow::openObject(ObjectResourceItem * item)
{
    auto id = item->id;
    if (checkTab(id))
    {
        return;
    }

    auto editor = new ObjectEditor(item);

    int pos = tabWidget->addTab(editor, item->name());

    idOfOpenedTabs.push_back(id);

    tabWidget->setCurrentIndex(pos);

    connect(item, &ObjectResourceItem::nameChanged, [this, item]() {
        int index = idOfOpenedTabs.indexOf(item->id);
        tabWidget->setTabText(index, item->name());
    });
}

void MainWindow::loadProject(QString filename)
{
    QFileInfo fi(filename);
    GameSettings::setRootPath(fi.absolutePath());

    auto json = Utils::readFileToJSON(filename);
    if (json.isEmpty())
    {
        return;
    }

    auto resourcesJson = json["resources"].toArray();
    for (const auto & value : resourcesJson)
    {
        auto obj = value.toObject();
        auto data = obj["Value"].toObject();
        auto id = obj["Key"].toString();
        auto filenameYY = data["resourcePath"].toString().replace("\\", "/").replace("//", "/");

        auto type = ResourceStringToType(data["resourceType"].toString());
        auto item = ResourceItem::create(type, id);
        item->filename = GameSettings::rootPath() + "/" + filenameYY;

        resources[id] = item;
    }

    // main options FIX
    {
        auto obj = json["parentProject"].toObject()["alteredResources"].toArray().first().toObject();
        auto data = obj["Value"].toObject();
        auto id = obj["Key"].toString();
        auto filenameYY = data["resourcePath"].toString().replace("\\", "/").replace("//", "/");
        filenameYY.replace("options_main", "inherited/options_main.inherited");
        auto type = ResourceStringToType(data["resourceType"].toString());
        auto item = ResourceItem::create(type, id);
        item->filename = GameSettings::rootPath() + "/" + filenameYY;

        resources[id] = item;
    }


    resourcesModel->fill(resources);
}

bool MainWindow::checkTab(QString id)
{
    if (idOfOpenedTabs.contains(id))
    {
        int pos = idOfOpenedTabs.indexOf(id);
        tabWidget->setCurrentIndex(pos);
        return true;
    }

    return false;
}

void MainWindow::closeTab(int pos)
{
    auto editor = qobject_cast<MainEditor*>(tabWidget->widget(pos));
    if (editor && editor->isDirty())
    {
        auto btn = QMessageBox::warning(this, "Unsaved changes", "You have unsaved changes, do you really want to close this editor?", QMessageBox::Yes, QMessageBox::No);
        if (btn == QMessageBox::No)
        {
            return;
        }
    }

    idOfOpenedTabs.remove(pos);
    tabWidget->removeTab(pos);
}
