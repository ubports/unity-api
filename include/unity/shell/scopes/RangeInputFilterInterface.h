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
    Q_PROPERTY(double startValue READ startValue WRITE setStartValue NOTIFY startValueChanged)
    Q_PROPERTY(double endValue READ endValue WRITE setEndValue NOTIFY endValueChanged)
    Q_PROPERTY(QString startPrefixLabel READ startPrefixLabel NOTIFY startPrefixLabelChanged)
    Q_PROPERTY(QString startPostfixLabel READ startPostfixLabel NOTIFY startPostfixLabelChanged)
    Q_PROPERTY(QString centralLabel READ centralLabel NOTIFY centralLabelChanged)
    Q_PROPERTY(QString endPrefixLabel READ endPrefixLabel NOTIFY endPrefixLabelChanged)
    Q_PROPERTY(QString endPostfixLabel READ endPostfixLabel NOTIFY endPostfixLabelChanged)

    FiltersInterface::FilterType filterType() const override
    {
        return FiltersInterface::RangeInputFilter;
    }

    virtual double startValue() const = 0;
    virtual double endValue() const = 0;
    virtual void setStartValue(double value) = 0;
    virtual void setEndValue(double value)  = 0;
    virtual QString startPrefixLabel() const = 0;
    virtual QString startPostfixLabel() const = 0;
    virtual QString centralLabel() const = 0;
    virtual QString endPrefixLabel() const = 0;
    virtual QString endPostfixLabel() const = 0;

Q_SIGNALS:
    void startValueChanged(double);
    void endValueChanged(double);
    void startPrefixLabelChanged(QString);
    void startPostfixLabelChanged(QString);
    void centralLabelChanged(QString);
    void endPrefixLabelChanged(QString);
    void endPostfixLabelChanged(QString);

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
