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

#ifndef UNITY_SHELL_SCOPES_VALUESLIDERFILTERINTERFACE_H
#define UNITY_SHELL_SCOPES_VALUESLIDERFILTERINTERFACE_H

#include <unity/SymbolExport.h>

#include "FilterBaseInterface.h"

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API ValueSliderFilterInterface : public FilterBaseInterface
{
    Q_OBJECT

public:
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(unity::shell::scopes::ValueSliderValuesInterface* values READ values NOTIFY valuesChanged)
    Q_PROPERTY(int minValue READ minValue NOTIFY minValueChanged);
    Q_PROPERTY(int maxValue READ maxValue NOTIFY maxValueChanged);

public:
    FiltersInterface::FilterType filterType() const override
    {
        return FiltersInterface::ValueSliderFilter;
    }

    virtual int value() const = 0;
    virtual void setValue()  = 0;
    virtual int minValue() const = 0;
    virtual int maxValue() const = 0;
    virtual ValueSliderValuesInterface* values() const = 0;

Q_SIGNALS:
    void valueChanged();
    void valuesChanged();
    void minValueChanged();
    void maxValueChanged();

protected:
    /// @cond
    explicit ValueSliderFilterInterface(QObject* parent = 0) : FilterBaseInterface(parent) {}
    /// @endcond
};

}

}
}

Q_DECLARE_METATYPE(unity::shell::scopes::ValueSliderFilterInterface*)

#endif
