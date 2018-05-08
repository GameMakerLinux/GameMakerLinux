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

#ifndef PROJECTRESOURCE_H
#define PROJECTRESOURCE_H

#include "resourceitem.h"

class ProjectResource : public ResourceItem
{
public:
    ProjectResource();

public:
    void load(QJsonObject object) override;
    QJsonObject save() override;

    QString filename() const override;

private:
    QJsonObject m_cachedProjectFile;
};

#endif // PROJECTRESOURCE_H
