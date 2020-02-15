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

#ifndef FORMEDIT_H
#define FORMEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class FormEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FormEdit(QWidget *parent = nullptr);

    void setLabel(QString label);
    void setText(QString text);
    QString text() const;
    void setLineEditWidth(int width);
    void setValidator(QValidator * validator);

    bool eventFilter(QObject * watched, QEvent * event) override;

signals:
    void editingFinished();

private:
    void checkLineEditContents();

    QLabel * m_label;
    QLineEdit * m_lineEdit;
    QString m_cachedValue;
};

#endif // FORMEDIT_H
