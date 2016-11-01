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

#ifndef UNITY_SHELL_APPLICATION_WINDOW_H
#define UNITY_SHELL_APPLICATION_WINDOW_H

#include <QObject>
#include <QPoint>

#include "Mir.h"

namespace unity
{
namespace shell
{
namespace application
{

class MirSurfaceInterface;

/**
   @brief A slightly higher concept than MirSurface

   A Window exists before its MirSurface gets created (for splashscreen purposes)
   and might also hang around after the backing surface is gone (In case the application
   was killed to free up memory, as it should still remain in the window list since the user
   did not explicitly close it).
 */
class WindowInterface : public QObject
{
    Q_OBJECT

    /**
     * @brief Position of the current surface buffer, in pixels.
     */
    Q_PROPERTY(QPoint position READ position NOTIFY positionChanged)

    /**
     * @brief Requested position of the current surface buffer, in pixels.
     */
    Q_PROPERTY(QPoint requestedPosition READ requestedPosition WRITE setRequestedPosition NOTIFY requestedPositionChanged)

    /**
     * @brief State of the surface
     */
    Q_PROPERTY(Mir::State state READ state NOTIFY stateChanged)

    /**
     * @brief Whether the surface is focused
     *
     * It will be true if this surface is MirFocusControllerInterface::focusedSurface
     */
    Q_PROPERTY(bool focused READ focused NOTIFY focusedChanged)

    /**
     * @brief Whether the surface wants to confine the mouse pointer within its boundaries
     *
     * If true, the surface doesn't want the mouse pointer to leave its boundaries while it's focused.
     */
    Q_PROPERTY(bool confinesMousePointer READ confinesMousePointer NOTIFY confinesMousePointerChanged)

    /**
     * @brief A unique identifier for this window.
     * Useful for telling windows apart in a list model as they get moved around
     */
    Q_PROPERTY(int id READ id CONSTANT)

    /**
     * @brief Surface backing up this window
     * It might be null if a surface hasn't been created yet (application is starting up) or if
     * the corresponding application has been killed (but can still get restarted to continue from
     * where it left)
     */
    Q_PROPERTY(unity::shell::application::MirSurfaceInterface* surface READ surface NOTIFY surfaceChanged)

public:
    /// @cond
    WindowInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual QPoint position() const = 0;
    virtual QPoint requestedPosition() const = 0;
    virtual void setRequestedPosition(const QPoint &) = 0;
    virtual Mir::State state() const = 0;
    virtual bool focused() const = 0;
    virtual bool confinesMousePointer() const = 0;
    virtual int id() const = 0;
    virtual MirSurfaceInterface* surface() const = 0;
    /// @endcond

public Q_SLOTS:
    /**
     * @brief Requests a change to the specified state
     */
    virtual void requestState(Mir::State state) = 0;

    /**
     * @brief Requests focus for this surface
     *
     * Causes the emission of focusRequested()
     */
    virtual void requestFocus() = 0;

    /**
     * @brief Sends a close request
     *
     */
    virtual void close() = 0;

Q_SIGNALS:
    /// @cond
    void positionChanged(QPoint position);
    void requestedPositionChanged(QPoint position);
    void stateChanged(Mir::State value);
    void focusedChanged(bool value);
    void confinesMousePointerChanged(bool value);
    void surfaceChanged(unity::shell::application::MirSurfaceInterface *surface);
    /// @endcond

    /**
     * @brief Emitted in response to a requestFocus() call
     */
    void focusRequested();
};


} // namespace application
} // namespace shell
} // namespace unity

Q_DECLARE_METATYPE(unity::shell::application::WindowInterface*)

#endif // UNITY_SHELL_APPLICATION_WINDOw_H
