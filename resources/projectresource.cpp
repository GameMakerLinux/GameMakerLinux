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

#include "projectresource.h"
#include "utils/utils.h"
#include "utils/uuid.h"

ProjectResource::ProjectResource()
    : ResourceItem { ResourceType::Project }
{

}

void ProjectResource::load(QJsonObject object)
{
    m_cachedProjectFile = object;

    setId(object["id"].toString());

    auto resourcesJson = object["resources"].toArray();
    for (auto value : resourcesJson)
    {
        auto obj = value.toObject();
        auto data = obj["Value"].toObject();
        auto id = obj["Key"].toString();
        auto filenameYY = data["resourcePath"].toString().replace("\\", "/").replace("//", "/");

        auto type = Utils::resourceStringToType(data["resourceType"].toString());
        auto item = ResourceItem::create(type, id);

        auto json = Utils::readFileToJSON(GameSettings::rootPath() + "/" + filenameYY);
        item->load(json);
    }

    // main options FIX
    {
        auto obj = object["parentProject"].toObject()["alteredResources"].toArray().first().toObject();
        auto data = obj["Value"].toObject();
        auto id = obj["Key"].toString();
        auto filenameYY = data["resourcePath"].toString().replace("\\", "/").replace("//", "/");
        filenameYY.replace("options_main", "inherited/options_main.inherited");

        auto type = Utils::resourceStringToType(data["resourceType"].toString());
        auto item = ResourceItem::create(type, id);
        auto json = Utils::readFileToJSON(GameSettings::rootPath() + "/" + filenameYY);
        item->load(json);
    }
}


QJsonObject ProjectResource::save()
{
    auto resources = ResourceItem::all();

    QJsonArray resourcesJson;
    for(auto & resource : resources)
    {
        switch (resource->type())
        {
        case ResourceType::AmazonFireOptions:
        case ResourceType::AndroidOptions:
        case ResourceType::Extension:
        case ResourceType::Folder:
        case ResourceType::Font:
        case ResourceType::iOSOptions:
        case ResourceType::LinuxOptions:
        case ResourceType::MacOptions:
        case ResourceType::Notes:
        case ResourceType::Object:
        case ResourceType::Path:
        case ResourceType::Room:
        case ResourceType::Root:
        case ResourceType::Script:
        case ResourceType::Shader:
        case ResourceType::Sound:
        case ResourceType::Sprite:
        case ResourceType::TileSet:
        case ResourceType::Timeline:
        case ResourceType::WindowsOptions:
            // add those to the project file
            break;
        case ResourceType::BackgroundLayer:
        case ResourceType::Config:
        case ResourceType::Event:
        case ResourceType::ImageLayer:
        case ResourceType::IncludedFile:
        case ResourceType::InstanceLayer:
        case ResourceType::MainOptions:
        case ResourceType::ObjectInstance:
        case ResourceType::Options:
        case ResourceType::Project:
        case ResourceType::RoomSettings:
        case ResourceType::SpriteFrame:
        case ResourceType::SpriteImage:
        case ResourceType::Unknown:
            // don't add those
            continue;
        default:
            // easier to find missing values
            throw 42;
        }
        QString path = resource->filename();

        QJsonObject value;
        value["id"] = Uuid::generate();
        value["resourcePath"] = path.replace("/", "\\");
        value["resourceType"] = Utils::resourceTypeToString(resource->type());

        QJsonObject object;
        object["Key"] = resource->id();
        object["Value"] = value;

        resourcesJson.append(object);
    }
    m_cachedProjectFile["resources"] = resourcesJson;

    return m_cachedProjectFile;
}


QString ProjectResource::filename() const
{
    return QString("%1.yyp").arg(name());
}
