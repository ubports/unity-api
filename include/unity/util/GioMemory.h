/*
 * Copyright (C) 2013-2017 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Pete Woods <pete.woods@canonical.com>
 */

#ifndef UNITY_UTIL_GIOMEMORY_H
#define UNITY_UTIL_GIOMEMORY_H

#include <gio/gio.h>

#include <unity/util/GObjectMemory.h>

namespace unity
{

namespace util
{

namespace internal
{
struct GDBusSignalUnsubscriber
{
public:
    void operator()(guint handle) noexcept
    {
        if (handle != 0 && G_IS_OBJECT(bus_.get()))
        {
            g_dbus_connection_signal_unsubscribe(bus_.get(), handle);
        }
    }

    GObjectSPtr<GDBusConnection> bus_;
};

}

typedef ResourcePtr<guint, internal::GDBusSignalUnsubscriber> GDBusSignalConnection;

inline GDBusSignalConnection gdbus_signal_connection(guint id, GObjectSPtr<GDBusConnection> bus) noexcept
{
    return GDBusSignalConnection(id, internal::GDBusSignalUnsubscriber{bus});
}

}  // namespace until

}  // namespace unity

#endif
