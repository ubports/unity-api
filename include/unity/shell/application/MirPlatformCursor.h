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

#ifndef MIR_PLATFORM_CURSOR_H
#define MIR_PLATFORM_CURSOR_H

#include <qpa/qplatformcursor.h>

class MirMousePointerInterface;

/**
 * @brief Cursor interface for Mir platform
 *
 * FIXME: Get this out of unity-api
 */
class MirPlatformCursor : public QPlatformCursor
{
public:
    /**
     * @brief Set the QML mouse pointer that this platform cursor will talk to
     */
    virtual void setMousePointer(MirMousePointerInterface *mousePointer) = 0;
};

#endif // MIR_PLATFORM_CURSOR_H
