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

#include "formedit.h"
#include <QHBoxLayout>
#include <QEvent>

FormEdit::FormEdit(QWidget *parent) : QWidget(parent)
{
    m_label = new QLabel;
    m_lineEdit = new QLineEdit;
    m_lineEdit->installEventFilter(this);

    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_label);
    layout->addWidget(m_lineEdit);

    connect(m_lineEdit, &QLineEdit::editingFinished, this, &FormEdit::checkLineEditContents);
}

void FormEdit::setLabel(QString label)
{
    m_label->setText(label + ":");
}

void FormEdit::setText(QString text)
{
    m_lineEdit->setText(text);
    m_cachedValue = text;
}

QString FormEdit::text() const
{
    return m_lineEdit->text();
}

void FormEdit::setLineEditWidth(int width)
{
    m_lineEdit->setFixedWidth(width);
}

void FormEdit::setValidator(QValidator * validator)
{
    m_lineEdit->setValidator(validator);
}

void FormEdit::checkLineEditContents()
{
    if (m_lineEdit->text().isEmpty())
    {
        m_lineEdit->setText(m_cachedValue);
    }
    else
    {
        m_cachedValue = m_lineEdit->text();
    }
}

bool FormEdit::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == m_lineEdit && event->type() == QEvent::FocusOut)
    {
        checkLineEditContents();
    }

    return QWidget::eventFilter(watched, event);
}
