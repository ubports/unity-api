/*
 * Copyright (C) 2017 Canonical Ltd.
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

#include <unity/util/GioMemory.h>
#include <unity/util/GlibMemory.h>
#include <libqtdbustest/DBusTestRunner.h>
#include <gtest/gtest.h>
#include <list>
#include <string>

using namespace std;
using namespace unity::util;
using namespace QtDBusTest;

namespace
{

class GioMemoryTest: public testing::Test
{
protected:
    static void SetUpTestCase()
    {
        g_log_set_always_fatal((GLogLevelFlags) (G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL));
    }

    static void on_dbus_signal(GDBusConnection *, const gchar *, const gchar *, const gchar *, const gchar *signal_name, GVariant *, gpointer user_data)
    {
        static_cast<GioMemoryTest*>(user_data)->onDbusSignal(signal_name);
    }

    void onDbusSignal(const gchar *signal_name)
    {
        signals_.emplace_back(signal_name);
        g_main_loop_quit(mainloop_.get());
    }

    static gboolean on_timeout(gpointer user_data)
    {
        return static_cast<GioMemoryTest*>(user_data)->onTimeout();
    }

    gboolean onTimeout()
    {
        g_main_loop_quit(mainloop_.get());
        return G_SOURCE_CONTINUE;
    }

    static GObjectSPtr<GDBusConnection> getSessionBus()
    {
        auto address = unique_glib(g_dbus_address_get_for_bus_sync(G_BUS_TYPE_SESSION, nullptr, nullptr));

        GError *error = nullptr;
        auto bus = unique_gobject(
                g_dbus_connection_new_for_address_sync(address.get(), (GDBusConnectionFlags) (G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT | G_DBUS_CONNECTION_FLAGS_MESSAGE_BUS_CONNECTION), nullptr,
                        nullptr, &error));
        if (!bus) {
            g_printerr ("Error connecting to D-Bus address %s: %s\n", address.get(), error->message);
            g_error_free (error);
        }


        g_dbus_connection_set_exit_on_close(bus.get(), FALSE);

        return bus;
    }

    DBusTestRunner dbusTestRunner;

    GDBusSignalConnection signalConnection_;

    GMainLoopSPtr mainloop_;

    list<string> signals_;
};


TEST_F(GioMemoryTest, signals)
{
    mainloop_ = share_glib(g_main_loop_new(nullptr, false));

    auto bus = getSessionBus();
    ASSERT_TRUE(bool(bus));

    signalConnection_ = gdbus_signal_connection(
            g_dbus_connection_signal_subscribe(bus.get(), nullptr, "org.does.not.exist", nullptr, "/does/not/exist", nullptr, G_DBUS_SIGNAL_FLAGS_NONE, on_dbus_signal, this, nullptr), bus);

    g_dbus_connection_emit_signal(bus.get(), nullptr, "/does/not/exist", "org.does.not.exist", "hello", nullptr, nullptr);
    {
        auto timer = g_source_manager(g_timeout_add(5000, on_timeout, this));
        g_main_loop_run(mainloop_.get());
        EXPECT_EQ(list<string>{"hello"}, signals_);
    }
    signals_.clear();

    signalConnection_.dealloc();

    g_dbus_connection_emit_signal(bus.get(), nullptr, "/does/not/exist", "org.does.not.exist", "hello", nullptr, nullptr);
    {
        auto timer = g_source_manager(g_timeout_add(5000, on_timeout, this));
        g_main_loop_run(mainloop_.get());
        EXPECT_TRUE(signals_.empty());
    }
}

}
