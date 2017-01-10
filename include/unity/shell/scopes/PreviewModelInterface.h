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

/**
 * @brief A list of PreviewWidgetModelInterface instances.
 *
 * This model exposes a number of PreviewWidgetModelInterface instances based on
 * the value of widgetColumnCount property.
 */
class UNITY_API PreviewModelInterface : public QAbstractListModel
{
    Q_OBJECT

    /**
     * @brief Number of column models this preview should expose.
     *
     * Previews can be laid out in a different number of columns - for example the number
     * of desired columns can change when changing orientation of the display and
     * therefore there's more horizontal space available.
     */
    Q_PROPERTY(int widgetColumnCount READ widgetColumnCount WRITE setWidgetColumnCount NOTIFY widgetColumnCountChanged)

    /**
     * @brief Boolean specifying whether loading this preview finished.
     */
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)

    /**
     * @brief Boolean specifying whether an action is currently being performed.
     *
     * Performing an action in a preview often involves communicating to a scope and
     * as such can take a while. It's safer to disable all actions while value of this
     * property is true.
     */
    Q_PROPERTY(bool processingAction READ processingAction NOTIFY processingActionChanged)

protected:
    /// @cond
    explicit PreviewModelInterface(QObject* parent = 0) : QAbstractListModel(parent) { }
    /// @endcond

public:
    /**
     * @brief The roles supported by this model.
     */
    enum Roles {
        RoleColumnModel
    };
    Q_ENUM(Roles)

    // @cond
    virtual void setWidgetColumnCount(int count) = 0;
    virtual int widgetColumnCount() const = 0;
    virtual bool loaded() const = 0;
    virtual bool processingAction() const = 0;
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RoleColumnModel] = "columnModel";
        return roles;
    }
    // @endcond

Q_SIGNALS:
    // @cond
    void widgetColumnCountChanged();
    void loadedChanged();
    void processingActionChanged();
    // @endcond

    /**
     * @brief Signal emitted when user triggers an action.
     *
     * This signal is emitted when user triggers an action - the parameters are widget
     * id, action id and properties of the widget/action.
     */
    void triggered(QString const&, QString const&, QVariantMap const&);
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::PreviewModelInterface*)

#endif
