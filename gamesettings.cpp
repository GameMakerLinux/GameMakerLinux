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

#include "gamesettings.h"
#include <QSettings>
#include <QCoreApplication>

QString GameSettings::rootPath()
{
    return root_path;
}

void GameSettings::setRootPath(QString root)
{
    root_path = root;
}

QString GameSettings::lastOpenedProject()
{
    return last_opened_project;
}

void GameSettings::setLastOpenedProject(QString filename)
{
    last_opened_project = filename;

    save();
}

void GameSettings::save()
{
    QSettings settings(qApp->applicationDirPath() + "/configuration.ini", QSettings::IniFormat);

    settings.setValue("last_opened_project", last_opened_project);
}

void GameSettings::load()
{
    QSettings settings(qApp->applicationDirPath() + "/configuration.ini", QSettings::IniFormat);

    last_opened_project = settings.value("last_opened_project").toString();
}

QString GameSettings::root_path;
QString GameSettings::last_opened_project;
