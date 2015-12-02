/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranties of MERCHANTABILITY,
 * SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIR_MOUSE_POINTER_INTERFACE_H
#define MIR_MOUSE_POINTER_INTERFACE_H

#include <QQuickItem>

/**
 * @brief The QML mouse pointer
 *
 * FIXME: Get this out of unity-api
 *
 * This QML item drives the position of the Mir mouse pointer on the scene
 */
class MirMousePointerInterface : public QQuickItem {
    Q_OBJECT

    /**
     * @brief Name of the cursor
     * Defines the look of the mouse pointer along with themeName
     */
    Q_PROPERTY(QString cursorName READ cursorName NOTIFY cursorNameChanged)

    /**
     * @brief Name of the cursor theme
     * Defines the look of the mouse pointer along with cursorName
     * Its default value is "default".
     */
    Q_PROPERTY(QString themeName READ themeName NOTIFY themeNameChanged)

    /**
     * @brief X coordinate of the cursor hotspot
     * Is value depends on the current cursor name and theme
     */
    Q_PROPERTY(qreal hotspotX READ hotspotX NOTIFY hotspotXChanged)

    /**
     * @brief Y coordinate of the cursor hotspot
     * Is value depends on the current cursor name and theme
     */
    Q_PROPERTY(qreal hotspotY READ hotspotY NOTIFY hotspotYChanged)
public:
    /**
     * @brief The constructor
     */
    MirMousePointerInterface(QQuickItem *parent = nullptr) : QQuickItem(parent) {}

    /// @cond
    virtual void setCursorName(const QString &cursorName) = 0;
    virtual QString cursorName() const = 0;

    virtual void setThemeName(const QString &themeName) = 0;
    virtual QString themeName() const = 0;

    virtual qreal hotspotX() const = 0;
    virtual qreal hotspotY() const = 0;
    /// @endcond

    /**
     * @brief Sets the custom cursor
     *
     * If it's not a pixmap cursor it will be ignored.
     *
     * To use it, cursorName must be set to "custom". themeName is ignored in this case.
     */
    virtual void setCustomCursor(const QCursor &) = 0;

Q_SIGNALS:
    /// @cond
    void cursorNameChanged(QString name);
    void themeNameChanged(QString name);
    void hotspotXChanged(qreal value);
    void hotspotYChanged(qreal value);
    /// @endcond

public Q_SLOTS:
    /**
     * @brief Handler for Mir mouse events
     * The implementation should respond to Mir mouse events by moving itself along its parent
     * area.
     * This is called by Mir's platform cursor.
     *
     * Note that we get only relative mouse movement, since the mouse pointer position is defined
     * by this very item. Ie., it's up to this class to decide whether or not it (the mouse pointer)
     * should move (and how much) due to movement in a mouse device.
     *
     * @param movement Movement vector
     */
    virtual void handleMouseEvent(ulong timestamp, QPointF movement, Qt::MouseButtons buttons,
            Qt::KeyboardModifiers modifiers) = 0;

    /**
     * @brief Handler for Mir mouse wheel events
     * This is called by Mir's platform cursor.
     */
    virtual void handleWheelEvent(ulong timestamp, QPoint angleDelta, Qt::KeyboardModifiers modifiers) = 0;

};

#endif // MIR_MOUSE_POINTER_INTERFACE_H
