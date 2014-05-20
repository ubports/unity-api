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

/**
 * @brief A master model for previews.
 *
 * Each item in this model represents an individual preview, where each is stacked
 * on top of the previous one. Item on index 0 is always the one on the very bottom
 * of the stack.
 */
class UNITY_API PreviewStackInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

    /**
     * @brief Number of columns the individual previews should expose.
     *
     * Previews can be laid out in a different number of columns - for example the number
     * of desired columns can change when changing orientation of the display and
     * therefore there's more horizontal space available.
     */
    Q_PROPERTY(int widgetColumnCount READ widgetColumnCount WRITE setWidgetColumnCount NOTIFY widgetColumnCountChanged)

protected:
    /// @cond
    explicit PreviewStackInterface(QObject* parent = 0) : QAbstractListModel(parent) { }
    /// @endcond

public:
    /**
     * @brief The roles supported by this model.
     */
    enum Roles {
        RolePreviewModel
    };

    /**
     * @brief Get preview model at a particular index.
     *
     * Return PreviewModelInterface instance at a particular index or nullptr
     * if the index is out of bounds.
     */
    Q_INVOKABLE virtual unity::shell::scopes::PreviewModelInterface* getPreviewModel(int index) const = 0;

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
