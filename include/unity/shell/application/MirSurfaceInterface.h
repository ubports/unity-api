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

#ifndef UNITY_SHELL_APPLICATION_MIRSURFACE_H
#define UNITY_SHELL_APPLICATION_MIRSURFACE_H

#include <QObject>
#include <QSize>

#include "Mir.h"

namespace unity
{
namespace shell
{
namespace application
{

/**
   @brief Holds a Mir surface. Pretty much an opaque class.

   All surface manipulation is done by giving it to a MirSurfaceItem and then
   using MirSurfaceItem's properties.
 */
class MirSurfaceInterface : public QObject
{
    Q_OBJECT

    /**
     * @brief The surface type
     */
    Q_PROPERTY(Mir::Type type READ type NOTIFY typeChanged)

    /**
     * @brief Name of the surface, given by the client application
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

    /**
     * @brief Size of the current surface buffer, in pixels.
     */
    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)

    /**
     * @brief State of the surface
     */
    Q_PROPERTY(Mir::State state READ state WRITE setState NOTIFY stateChanged)

    /**
     * @brief True if it has a mir client bound to it.
     * A "zombie" (live == false) surface never becomes alive again.
     */
    Q_PROPERTY(bool live READ live NOTIFY liveChanged)

    /**
     * @brief Visibility of the surface
     */
    Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)

    /**
     * @brief Orientation angle of the surface
     *
     * How many degrees, clockwise, the UI in the surface has to rotate to match shell's UI orientation
     */
    Q_PROPERTY(Mir::OrientationAngle orientationAngle READ orientationAngle WRITE setOrientationAngle
               NOTIFY orientationAngleChanged DESIGNABLE false)

    /**
     * @brief The requested minimum width for the surface
     * Zero if not set
     */
    Q_PROPERTY(int minimumWidth READ minimumWidth NOTIFY minimumWidthChanged)

    /**
     * @brief The requested minimum height for the surface
     * Zero if not set
     */
    Q_PROPERTY(int minimumHeight READ minimumHeight NOTIFY minimumHeightChanged)

    /**
     * @brief The requested maximum width for the surface
     * Zero if not set
     */
    Q_PROPERTY(int maximumWidth READ maximumWidth NOTIFY maximumWidthChanged)

    /**
     * @brief The requested maximum height for the surface
     * Zero if not set
     */
    Q_PROPERTY(int maximumHeight READ maximumHeight NOTIFY maximumHeightChanged)

    /**
     * @brief The requested width increment for the surface
     * Zero if not set
     */
    Q_PROPERTY(int widthIncrement READ widthIncrement NOTIFY widthIncrementChanged)

    /**
     * @brief The requested height increment for the surface
     * Zero if not set
     */
    Q_PROPERTY(int heightIncrement READ heightIncrement NOTIFY heightIncrementChanged)

    /**
     * @brief The Shell crhome mode
     */
    Q_PROPERTY(Mir::ShellChrome shellChrome READ shellChrome NOTIFY shellChromeChanged)

public:
    /// @cond
    MirSurfaceInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~MirSurfaceInterface() {}

    virtual Mir::Type type() const = 0;

    virtual QString name() const = 0;

    virtual QSize size() const = 0;
    virtual void resize(int width, int height) = 0;
    virtual void resize(const QSize &size) = 0;

    virtual Mir::State state() const = 0;
    virtual void setState(Mir::State qmlState) = 0;

    virtual bool live() const = 0;

    virtual bool visible() const = 0;

    virtual Mir::OrientationAngle orientationAngle() const = 0;
    virtual void setOrientationAngle(Mir::OrientationAngle angle) = 0;

    virtual int minimumWidth() const = 0;
    virtual int minimumHeight() const = 0;
    virtual int maximumWidth() const = 0;
    virtual int maximumHeight() const = 0;
    virtual int widthIncrement() const = 0;
    virtual int heightIncrement() const = 0;
    
    virtual Mir::ShellChrome shellChrome() const = 0;
    /// @endcond

Q_SIGNALS:
    /// @cond
    void typeChanged(Mir::Type value);
    void liveChanged(bool value);
    void visibleChanged(bool visible);
    void stateChanged(Mir::State value);
    void orientationAngleChanged(Mir::OrientationAngle value);
    void sizeChanged(const QSize &value);
    void nameChanged(const QString &name);
    void minimumWidthChanged(int value);
    void minimumHeightChanged(int value);
    void maximumWidthChanged(int value);
    void maximumHeightChanged(int value);
    void widthIncrementChanged(int value);
    void heightIncrementChanged(int value);
    void shellChromeChanged(Mir::ShellChrome value);
    /// @endcond
};

} // namespace application
} // namespace shell
} // namespace unity

Q_DECLARE_METATYPE(unity::shell::application::MirSurfaceInterface*)

#endif // UNITY_SHELL_APPLICATION_MIRSURFACE_H
