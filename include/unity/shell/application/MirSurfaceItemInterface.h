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

#ifndef UNITY_SHELL_APPLICATION_MIRSURFACEITEM_H
#define UNITY_SHELL_APPLICATION_MIRSURFACEITEM_H

#include "Mir.h"

#include <QQuickItem>

namespace unity
{
namespace shell
{
namespace application
{

class MirSurfaceInterface;

/**
   @brief Renders a MirSurface in a QML scene and forwards the input events it receives to it.

   You can have multiple MirSurfaceItems displaying the same MirSurface. But care must
   be taken that only one of them feeds the MirSurface with input events and also only
   one resizes it.
 */
class MirSurfaceItemInterface : public QQuickItem
{
    Q_OBJECT

    /**
     * @brief The surface to be displayed
     */
    Q_PROPERTY(unity::shell::application::MirSurfaceInterface* surface READ surface WRITE setSurface NOTIFY surfaceChanged)

    /**
     * @brief Type of the given surface or Mir.UnknownType if no surface is set
     */
    Q_PROPERTY(Mir::Type type READ type NOTIFY typeChanged)

    /**
     * @brief State of the given surface or Mir.UnknownState if no surface is set
     */
    Q_PROPERTY(Mir::State surfaceState READ surfaceState NOTIFY surfaceStateChanged)

    /**
     * @brief Name of the given surface or an empty string if no surface is set
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

    /**
     * @brief True if the item has a surface and that surface has a mir client bound to it.
     * A "zombie" (live == false) surface never becomes alive again.
     */
    Q_PROPERTY(bool live READ live NOTIFY liveChanged)

    /**
     * @brief  Orientation angle of the given surface
     *
     * How many degrees, clockwise, the UI in the surface has to rotate to match shell's UI orientation
     */
    Q_PROPERTY(Mir::OrientationAngle orientationAngle READ orientationAngle WRITE setOrientationAngle
               NOTIFY orientationAngleChanged DESIGNABLE false)


    /**
     * @brief Whether the item will forward activeFocus, touch events, mouse events and key events to its surface.
     * It's false by default.
     * Only one item should have this property enabled for a given surface.
     */
    Q_PROPERTY(bool consumesInput READ consumesInput
                                  WRITE setConsumesInput
                                  NOTIFY consumesInputChanged)

    /**
     * @brief The desired width for the contained MirSurface.
     * It's ignored if set to zero or a negative number
     * The default value is zero
     */
    Q_PROPERTY(int surfaceWidth READ surfaceWidth
                                WRITE setSurfaceWidth
                                NOTIFY surfaceWidthChanged)

    /**
     * @brief The desired height for the contained MirSurface.
     * It's ignored if set to zero or a negative number
     * The default value is zero
     */
    Q_PROPERTY(int surfaceHeight READ surfaceHeight
                                WRITE setSurfaceHeight
                                NOTIFY surfaceHeightChanged)

    Q_PROPERTY(FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)

    /**
     * @brief The Shell chrome mode
     */
    Q_PROPERTY(Mir::ShellChrome shellChrome READ shellChrome NOTIFY shellChromeChanged)

public:

    enum FillMode {
        Stretch,
        PadOrCrop
    };
    Q_ENUM(FillMode)

    /// @cond
    MirSurfaceItemInterface(QQuickItem *parent = 0) : QQuickItem(parent) {}
    virtual ~MirSurfaceItemInterface() {}

    virtual Mir::Type type() const = 0;
    virtual QString name() const = 0;
    virtual bool live() const = 0;

    virtual Mir::State surfaceState() const = 0;

    virtual Mir::OrientationAngle orientationAngle() const = 0;
    virtual void setOrientationAngle(Mir::OrientationAngle angle) = 0;

    virtual MirSurfaceInterface* surface() const = 0;
    virtual void setSurface(MirSurfaceInterface*) = 0;

    virtual bool consumesInput() const = 0;
    virtual void setConsumesInput(bool value) = 0;

    virtual int surfaceWidth() const = 0;
    virtual void setSurfaceWidth(int value) = 0;

    virtual int surfaceHeight() const = 0;
    virtual void setSurfaceHeight(int value) = 0;

    virtual FillMode fillMode() const = 0;
    virtual void setFillMode(FillMode value) = 0;

    virtual Mir::ShellChrome shellChrome() const = 0;
    /// @endcond

Q_SIGNALS:
    /// @cond
    void typeChanged(Mir::Type);
    void surfaceStateChanged(Mir::State);
    void liveChanged(bool live);
    void orientationAngleChanged(Mir::OrientationAngle angle);
    void surfaceChanged(MirSurfaceInterface*);
    void consumesInputChanged(bool value);
    void surfaceWidthChanged(int value);
    void surfaceHeightChanged(int value);
    void nameChanged(const QString &name);
    void fillModeChanged(FillMode value);
    void shellChromeChanged(Mir::ShellChrome value);
    /// @endcond
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_MIRSURFACEITEM_H
