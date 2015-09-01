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

#ifndef UNITY_SHELL_SCOPES_FILTERBASEINTERHACE_H
#define UNITY_SHELL_SCOPES_FILTERBASEINTERHACE_H

#include "FiltersInterface.h"
#include <QObject>

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API FilterBaseInterface : public QObject
{
    Q_OBJECT

    public:

        Q_PROPERTY(QString filterId READ filterId CONSTANT)
        Q_PROPERTY(FiltersInterface::FilterType filterType READ filterType CONSTANT)

        virtual QString filterId() const = 0;
        virtual FiltersInterface::FilterType filterType() const = 0;
        virtual QString filterTag() const = 0;

    protected:
        /// @cond
        explicit FilterBaseInterface(QObject* parent = 0) : QObject(parent) {}
        /// @endcond
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::FilterBaseInterface*)

#endif
