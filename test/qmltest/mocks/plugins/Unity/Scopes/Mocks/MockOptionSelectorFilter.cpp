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

#include "MockOptionSelectorFilter.h"

MockOptionSelectorFilter::MockOptionSelectorFilter(const QString &id, const QString &label, bool multi, QObject *parent)
    : unity::shell::scopes::OptionSelectorFilterInterface(parent),
      m_id(id),
      m_label(label),
      m_multiSelect(multi),
      m_options(new MockSelectorOptions(2, this))
{
}

QString MockOptionSelectorFilter::id() const
{
    return m_id;
}

QString MockOptionSelectorFilter::label() const
{
    return m_label;
}

bool MockOptionSelectorFilter::multiSelect() const
{
    return m_multiSelect;
}

unity::shell::scopes::OptionSelectorOptionsInterface* MockOptionSelectorFilter::options() const
{
    return m_options;
}
