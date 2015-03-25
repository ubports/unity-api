/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MOCKOPTIONSELECTOROPTIONS_H
#define MOCKOPTIONSELECTOROPTIONS_H

#include <unity/shell/scopes/OptionSelectorOptionsInterface.h>

class MockSelectorOptions : public unity::shell::scopes::OptionSelectorOptionsInterface
{
    Q_OBJECT

public:
    MockSelectorOptions(int num = 2, QObject *parent = 0);
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    void setChecked(int index, bool checked) override;

private:
    int m_numOfOptions;
};

#endif
