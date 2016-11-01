/*
 * Copyright (C) 2016 Canonical, Ltd.
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

#ifndef UNITY_SHELL_APPLICATION_TOPLEVELWINDOWMODELINTERFACE_H
#define UNITY_SHELL_APPLICATION_TOPLEVELWINDOWMODELINTERFACE_H

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace application
{

class ApplicationInfoInterface;
class MirSurfaceInterface;
class WindowInterface;

/**
 * @brief A model of top-level surfaces
 *
 * It's an abstraction of top-level application windows.
 *
 * When an entry first appears, it normaly doesn't have a surface yet, meaning that the application is
 * still starting up. A shell should then display a splash screen or saved screenshot of the application
 * until its surface comes up.
 *
 * As applications can have multiple surfaces and you can also have entries without surfaces at all,
 * the only way to unambiguously refer to an entry in this model is through its id.
 */
class TopLevelWindowModelInterface : public QAbstractListModel
{
    Q_OBJECT

    /**
     * @brief Number of top-level surfaces in this model
     *
     * This is the same as rowCount, added in order to keep compatibility with QML ListModels.
     */
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

    /**
     * @brief The input method surface, if any
     *
     * The surface of a onscreen keyboard (akak "virtual keyboard") would be kept here and not in the model itself.
     */
    Q_PROPERTY(unity::shell::application::MirSurfaceInterface* inputMethodSurface READ inputMethodSurface NOTIFY inputMethodSurfaceChanged)

    /**
     * @brief The currently focused window, if any
     */
    Q_PROPERTY(unity::shell::application::WindowInterface* focusedWindow READ focusedWindow
                                                                         NOTIFY focusedWindowChanged)
public:
    /**
     * @brief The Roles supported by the model
     *
     * WindowRole - A WindowInterface. It will be null if the application is still starting up
     * ApplicationRole - An ApplicationInfoInterface
     */
    enum Roles {
        WindowRole = Qt::UserRole,
        ApplicationRole = Qt::UserRole + 1,
    };

    virtual ~TopLevelWindowModelInterface() {}

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roleNames { {WindowRole, "window"},
                                           {ApplicationRole, "application"} };
        return roleNames;
    }

    /// @cond
    virtual MirSurfaceInterface* inputMethodSurface() const = 0;
    virtual WindowInterface* focusedWindow() const = 0;
    /// @endcond

public Q_SLOTS:
    /**
     * @brief Returns the surface at the given index
     *
     * It will be a nullptr if the application is still starting up and thus hasn't yet created
     * and drawn into a surface.
     *
     * Same as windowAt(index).surface()
     */
    virtual MirSurfaceInterface *surfaceAt(int index) const = 0;

    /**
     * @brief Returns the window at the given index
     *
     * Will always be valid
     */
    virtual WindowInterface *windowAt(int index) const = 0;

    /**
     * @brief Returns the application at the given index
     */
    virtual ApplicationInfoInterface *applicationAt(int index) const = 0;

    /**
     * @brief Returns the unique id of the element at the given index
     */
    virtual int idAt(int index) const = 0;

    /**
     * @brief Returns the index where the row with the given id is located
     *
     * Returns -1 if there's no row with the given id.
     */
    virtual int indexForId(int id) const = 0;

    /**
     * @brief Raises the row with the given id to the top of the window stack (index == count-1)
     */
    virtual void raiseId(int id) = 0;

Q_SIGNALS:
    /// @cond
    void countChanged();
    void inputMethodSurfaceChanged(unity::shell::application::MirSurfaceInterface* inputMethodSurface);
    void focusedWindowChanged(unity::shell::application::WindowInterface *focusedWindow);
    /// @endcond

    /**
     * @brief Emitted when the list changes
     *
     * Emitted when model gains an element, loses an element or when elements exchange positions.
     */
    void listChanged();
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_TOPLEVELWINDOWMODELINTERFACE_H
