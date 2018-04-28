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

#include "gmlhighlighter.h"
#include <QDebug>
#include <set>
#include <string>
#include <Qsci/qsciscintilla.h>
#include <QStringView>

static std::set<std::string> keywords = {
    "for",
    "if",
    "var",
    "while",
};

static std::set<std::string> builtin_variables = {
    "argument0", "argument1", "argument2", "argument3", "argument4",
    "arguments",
    "image_angle",
    "speed",
    "x",
    "y",
};

static std::set<std::string> local_variables;

enum StyleType {
    Normal,
    Strings,
    Globals,
    Locals,
    Keywords,
    BuiltinVariables
};

GMLHighlighter::GMLHighlighter()
{/*
    setColor(Qt::black, Normal);
    setColor(Qt::darkRed, Strings);
    setColor(Qt::darkBlue, Globals);
    setColor(Qt::darkBlue, Locals);
    setColor(Qt::darkYellow, Keywords);
    setColor(Qt::darkGreen, BuiltinVariables);*/
}
/*
const char * GMLHighlighter::language() const
{
    return "GML";
}

QString GMLHighlighter::description(int style) const
{
    return QString("style %1").arg(style);
}

void GMLHighlighter::styleText(int start, int end)
{
    startStyling(true);

    QStringView str = editor()->text();

    int position = start;
    while (position < end)
    {
        if (str[position] == '"')
        {
            int begin_position = position;
            position++;
            while (position < end && str[position] != '"')
            {
                position++;
                if (position < end && str[position] == '\\')
                {
                    position++;
                }
            }
            position++;

            int length = position - begin_position;
            qDebug() << "string from" << begin_position << "to" << position;
            setStyling(length, Strings);
        }
        else
        {
            if (position + 1 < end)
                setStyling(1, Normal);
            position++;
        }
    }
}
*/
