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
        qCritical() << "Can't open file" << filename;
        return {};
    }

    QJsonParseError error;
    auto doc = QJsonDocument::fromJson(f.readAll(), &error);
    f.close();

    if (error.error != QJsonParseError::NoError)
    {
        qCritical() << "JSON error:" << error.errorString();
        return {};
    }

    return doc.object();
}

QString Utils::readFile(QString filename)
{
    QFile f(filename);
    if (!f.open(QFile::ReadOnly))
    {
        qCritical() << "Can't open file" << filename;
        return {};
    }

    auto str = f.readAll();
    f.close();

    return str;
}

bool Utils::writeFile(QString filename, QByteArray data)
{
    QFile f(filename);
    if (!f.open(QFile::WriteOnly))
    {
        qCritical() << "Can't open file" << filename;
        return false;
    }

    f.write(data);
    f.close();

    return true;
}

// RESOURCES

static QMap<QString, ResourceType> resourcesTypesStrings = {
    { "GMFolder",           ResourceType::Folder            },
    { "GMObject",           ResourceType::Object            },
    { "GMRoom",             ResourceType::Room              },
    { "GMSprite",           ResourceType::Sprite            },
    { "GMScript",           ResourceType::Script            },
    { "GMFont",             ResourceType::Font              },
    { "GMSound",            ResourceType::Sound             },
    { "GMMainOptions",      ResourceType::MainOptions,      },
    { "GMiOSOptions",       ResourceType::iOSOptions,       },
    { "GMIncludedFile",     ResourceType::IncludedFile,     },
    { "GMAmazonFireOptions",ResourceType::AmazonFireOptions,},
    { "GMLinuxOptions",     ResourceType::LinuxOptions,     },
    { "GMWindowsOptions",   ResourceType::WindowsOptions,   },
    { "GMAndroidOptions",   ResourceType::AndroidOptions,   },
    { "GMMacOptions",       ResourceType::MacOptions,       },
    { "GMConfig",           ResourceType::Config,           },
    { "GMTileSet",          ResourceType::TileSet,          },
    { "GMPath",             ResourceType::Path,             },
    { "GMNotes",            ResourceType::Notes,            },
    { "GMExtension",        ResourceType::Extension,        },
    { "GMTimeline",         ResourceType::Timeline,         },
    { "GMOptions",          ResourceType::Options,          },
    { "GMShader",           ResourceType::Shader,           },
    { "root",               ResourceType::Root,             },
    { "GMEvent",            ResourceType::Event,            },
    { "GMSpriteImage",      ResourceType::SpriteImage,      },
    { "GMSpriteFrame",      ResourceType::SpriteFrame,      },
    { "GMImageLayer",       ResourceType::ImageLayer,       },
    { "GMRInstanceLayer",   ResourceType::InstancesLayer,    },
    { "GMRBackgroundLayer", ResourceType::BackgroundLayer,  }
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
