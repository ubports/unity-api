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

#ifndef OPTIONSELECTOROPTIONSINTERFACE_H
#define OPTIONSELECTOROPTIONSINTERFACE_H

#include <unity/SymbolExport.h>
#include <QAbstractListModel>
#include <unity/scopes/FilterOption.h>
#include <unity/scopes/FilterState.h>
#include <list>

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API OptionSelectorOptionInterface : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString id READ id)
    Q_PROPERTY(QString label READ label NOTIFY labelChanged)
    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)

    virtual QString id() const = 0;
    virtual QString label() const = 0;
    virtual bool checked() const = 0;

public Q_SLOTS:
    virtual void setChecked(bool) = 0;

Q_SIGNALS:
    void checkedChanged(bool);
    void labelChanged(const QString&);
};

class UNITY_API OptionSelectorOptionsInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(OptionRoles)

public:
    enum Roles {
        RoleOption = Qt::UserRole + 1
    };

protected:
    /// @cond
    explicit OptionSelectorOptionsInterface(QObject* parent = 0) : QAbstractListModel(parent) {}
    /// @endcond
};

}

}
}

Q_DECLARE_METATYPE(unity::shell::scopes::OptionSelectorOptionInterface*)
Q_DECLARE_METATYPE(unity::shell::scopes::OptionSelectorOptionsInterface*)

#endif
