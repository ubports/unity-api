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

#ifndef UNITY_SHELL_SCOPES_RANGEINPUTFILTERINTERFACE_H
#define UNITY_SHELL_SCOPES_RANGEINPUTFILTERINTERFACE_H

#include <unity/SymbolExport.h>

#include "FilterBaseInterface.h"

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API RangeInputFilterInterface : public FilterBaseInterface
{
    Q_OBJECT

public:
    Q_PROPERTY(QVariant startValue READ startValue WRITE setStartValue NOTIFY startValueChanged)
    Q_PROPERTY(QVariant endValue READ endValue WRITE setEndValue NOTIFY endValueChanged)

    FiltersInterface::FilterType filterType() const override
    {
        return FiltersInterface::RangeInputFilter;
    }

    virtual QVariant startValue() const = 0;
    virtual QVariant endValue() const = 0;
    virtual void setStartValue(QVariant const& value) = 0;
    virtual void setEndValue(QVariant const& value)  = 0;

Q_SIGNALS:
    void startValueChanged(QVariant const&);
    void endValueChanged(QVariant const&);

protected:
    /// @cond
    explicit RangeInputFilterInterface(QObject* parent = 0) : FilterBaseInterface(parent) {}
    /// @endcond
};

}

}
}

Q_DECLARE_METATYPE(unity::shell::scopes::RangeInputFilterInterface*)

#endif
