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

#include "utils.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

// FILES

QJsonObject Utils::readFileToJSON(QString filename)
{
    QFile f(filename);
    if (!f.open(QFile::ReadOnly))
    {
        qCritical() << __PRETTY_FUNCTION__ << "Can't open file" << filename;
        return {};
    }

    QJsonParseError error;
    auto doc = QJsonDocument::fromJson(f.readAll(), &error);
    f.close();

    if (error.error != QJsonParseError::NoError)
    {
        qCritical() << "File:" << filename << "=> JSON error:" << error.errorString();
        return {};
    }

    return doc.object();
}

QString Utils::readFile(QString filename)
{
    QFile f(filename);
    if (!f.open(QFile::ReadOnly))
    {
        qCritical() << __PRETTY_FUNCTION__ << "Can't open file" << filename;
        return {};
    }

    auto str = f.readAll();
    f.close();

    return str;
}

bool Utils::writeFile(QString filename, QJsonObject object)
{
    auto data = QJsonDocument(object).toJson();
    return Utils::writeFile(filename, data);
}

bool Utils::writeFile(QString filename, QByteArray data)
{
    QFile f(filename);
    if (!f.open(QFile::WriteOnly))
    {
        qCritical() << __PRETTY_FUNCTION__ << "Can't open file" << filename;
        return false;
    }

    f.write(data);
    f.close();

    return true;
}

// RESOURCES

static QMap<QString, ResourceType> resourcesTypesStrings = {
    { "GMAmazonFireOptions",ResourceType::AmazonFireOptions },
    { "GMAndroidOptions",   ResourceType::AndroidOptions    },
    { "GMConfig",           ResourceType::Config            },
    { "GMEvent",            ResourceType::Event             },
    { "GMExtension",        ResourceType::Extension         },
    { "GMFolder",           ResourceType::Folder            },
    { "GMFont",             ResourceType::Font              },
    { "GMHtml5Options",     ResourceType::HTML5Options      },
    { "GMImageLayer",       ResourceType::ImageLayer        },
    { "GMIncludedFile",     ResourceType::IncludedFile      },
    { "GMiOSOptions",       ResourceType::iOSOptions        },
    { "GMLinuxOptions",     ResourceType::LinuxOptions      },
    { "GMMacOptions",       ResourceType::MacOptions        },
    { "GMMainOptions",      ResourceType::MainOptions       },
    { "GMNotes",            ResourceType::Notes             },
    { "GMObject",           ResourceType::Object            },
    { "GMOptions",          ResourceType::Options           },
    { "GMPath",             ResourceType::Path              },
    { "GMProject",          ResourceType::Project           },
    { "GMRBackgroundLayer", ResourceType::BackgroundLayer   },
    { "GMRInstance",        ResourceType::ObjectInstance    },
    { "GMRInstanceLayer",   ResourceType::InstanceLayer     },
    { "GMRLayer",           ResourceType::FolderLayer       },
    { "GMRoom",             ResourceType::Room              },
    { "GMRTileLayer",       ResourceType::TileLayer         },
    { "GMRoomSettings",     ResourceType::RoomSettings      },
    { "GMScript",           ResourceType::Script            },
    { "GMShader",           ResourceType::Shader            },
    { "GMSound",            ResourceType::Sound             },
    { "GMSprite",           ResourceType::Sprite            },
    { "GMSpriteFrame",      ResourceType::SpriteFrame       },
    { "GMSpriteImage",      ResourceType::SpriteImage       },
    { "GMTileSet",          ResourceType::TileSet           },
    { "GMTileSet",          ResourceType::TileSet           },
    { "GMTimeline",         ResourceType::Timeline          },
    { "GMtvOSOptions",      ResourceType::tvOSOptions       },
    { "GMWindowsOptions",   ResourceType::WindowsOptions    },
    { "GMWindowsUAPOptions",ResourceType::WindowsUAPOptions },
    { "root",               ResourceType::Root              },
};

QString Utils::resourceTypeToString(ResourceType type)
{
    return resourcesTypesStrings.key(type, "Unknown");
}

ResourceType Utils::resourceStringToType(QString type)
{
    if (resourcesTypesStrings.contains(type))
    {
        return resourcesTypesStrings[type];
    }
    qDebug() << "Unknown resource type:" << type;
    return ResourceType::Unknown;
}
