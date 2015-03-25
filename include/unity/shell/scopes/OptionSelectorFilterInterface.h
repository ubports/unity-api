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

#ifndef UNITY_SHELL_SCOPES_OPTIONSELECTORFILTERINTERFACE_H
#define UNITY_SHELL_SCOPES_OPTIONSELECTORFILTERINTERFACE_H

#include <unity/SymbolExport.h>

#include "FilterBaseInterface.h"
#include "OptionSelectorOptionsInterface.h"

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API OptionSelectorFilterInterface : public FilterBaseInterface
{
    Q_OBJECT

public:
    Q_PROPERTY(QString label READ label NOTIFY labelChanged)
    Q_PROPERTY(bool multiSelect READ multiSelect NOTIFY multiSelectChanged)
    Q_PROPERTY(OptionSelectorOptionsInterface* options READ options)

    FiltersInterface::FilterType filterType() const override
    {
        return FiltersInterface::OptionSelectorFilter;
    }

    virtual QString label() const = 0;
    virtual bool multiSelect() const = 0;
    virtual OptionSelectorOptionsInterface* options() const = 0;

Q_SIGNALS:
    void labelChanged(const QString&);
    void multiSelectChanged(bool);

protected:
    /// @cond
    explicit OptionSelectorFilterInterface(QObject* parent = 0) : FilterBaseInterface(parent) {}
    /// @endcond
};

}

}
}

Q_DECLARE_METATYPE(unity::shell::scopes::OptionSelectorFilterInterface*)

#endif
