/*
 * Copyright (C) 2014 Canonical, Ltd.
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

#ifndef UNITY_SHELL_SCOPES_PREVIEWSTACKINTERFACE_H
#define UNITY_SHELL_SCOPES_PREVIEWSTACKINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

class PreviewModelInterface;

class UNITY_API PreviewStackInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

    Q_PROPERTY(int widgetColumnCount READ widgetColumnCount WRITE setWidgetColumnCount NOTIFY widgetColumnCountChanged)

public:
    enum Roles {
        RolePreviewModel
    };

    Q_INVOKABLE virtual unity::shell::scopes::PreviewModelInterface* get(int index) const = 0;

    // @cond
    virtual void setWidgetColumnCount(int columnCount) = 0;
    virtual int widgetColumnCount() const = 0;
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RolePreviewModel] = "previewModel";
        return roles;
    }
    // @endcond

Q_SIGNALS:
    // @cond
    void widgetColumnCountChanged();
    // @endcond
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::PreviewStackInterface*)

#endif
