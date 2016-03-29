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

#ifndef MOCKOPTIONSELECTORFILTER_H
#define MOCKOPTIONSELECTORFILTER_H

#include <unity/shell/scopes/OptionSelectorFilterInterface.h>
#include <unity/shell/scopes/FiltersInterface.h>
#include "MockSelectorOptions.h"

class MockOptionSelectorFilter : public unity::shell::scopes::OptionSelectorFilterInterface
{
    Q_OBJECT

public:
    MockOptionSelectorFilter(const QString &id, const QString& title, const QString &label, bool multi, QObject *parent = 0);
    QString filterId() const override;
    QString title() const override;
    QString label() const override;
    bool multiSelect() const override;
    unity::shell::scopes::OptionSelectorOptionsInterface* options() const override;
    QString filterTag() const override;

private:
    QString m_id;
    QString m_title;
    QString m_label;
    bool m_multiSelect;
    MockSelectorOptions *m_options;
};

#endif
