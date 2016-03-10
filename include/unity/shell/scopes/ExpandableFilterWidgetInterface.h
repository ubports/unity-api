/*
 * Copyright (C) 2016 Canonical, Ltd.
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

#ifndef UNITY_SHELL_SCOPES_EXPANDABLEFILTERWIDGETINTERFACE_H
#define UNITY_SHELL_SCOPES_EXPANDABLEFILTERWIDGETINTERFACE_H

#include <unity/SymbolExport.h>

#include "FilterBaseInterface.h"
#include "FiltersInterface.h"

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API ExpandableFilterWidgetInterface : public FilterBaseInterface
{
    Q_OBJECT

public:
    FiltersInterface::FilterType filterType() const override
    {
        return FiltersInterface::ExpandableFilterWidget;
    }

    virtual FiltersInterface* filters() const = 0;

protected:
    /// @cond
    explicit ExpandableFilterWidgetInterface(QObject* parent = 0) : FilterBaseInterface(parent) {}
    /// @endcond
};

}

}
}

Q_DECLARE_METATYPE(unity::shell::scopes::ExpandableFilterWidgetInterface *)

#endif
