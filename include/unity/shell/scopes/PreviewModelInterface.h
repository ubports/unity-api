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

#ifndef UNITY_SHELL_SCOPES_PREVIEWMODELINTERFACE_H
#define UNITY_SHELL_SCOPES_PREVIEWMODELINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API PreviewModelInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

    Q_PROPERTY(int widgetColumnCount READ widgetColumnCount WRITE setWidgetColumnCount NOTIFY widgetColumnCountChanged)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)
    Q_PROPERTY(bool processingAction READ processingAction NOTIFY processingActionChanged)

public:
    enum Roles {
        RoleColumnModel
    };

    // @cond
    virtual void setWidgetColumnCount(int count) = 0;
    virtual int widgetColumnCount() const = 0;
    virtual bool loaded() const = 0;
    virtual bool processingAction() const = 0;
    // @endcond

Q_SIGNALS:
    // @cond
    void widgetColumnCountChanged();
    void loadedChanged();
    void processingActionChanged();
    // @endcond

    void triggered(QString const&, QString const&, QVariantMap const&);
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::PreviewModelInterface*)

#endif
