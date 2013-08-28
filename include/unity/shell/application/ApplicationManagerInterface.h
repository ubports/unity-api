/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Michael Zanetti <michael.zanetti@canonical.com>
 */

#ifndef UNITY_SHELL_APPLICATION_APPLICATIONMANAGERINTERFACE_H
#define UNITY_SHELL_APPLICATION_APPLICATIONMANAGERINTERFACE_H

#include <unity/SymbolExport.h>

#include <QtCore/QObject>

namespace unity
{
namespace shell
{
namespace application
{

/**
 * @brief The Application manager
 *
 * This is the main class to interact with Applications
 */

class UNITY_API ApplicationManagerInterface: public QObject
{
    Q_OBJECT

    /**
     * Holds all the applications known to the ApplicationManager.
     */
    Q_PROPERTY(ApplicationListModel* applications READ applications CONSTANT)

protected:
    /// @cond
    ApplicationManagerInterface(QObject* parent = 0): QObject(parent) {}
    /// @endcond

public:
    enum Flag {
        NoFlag = 0x0,
        ForceMainStage = 0x1,
    };
    Q_DECLARE_FLAGS(ExecFlags, Flag)

    /// @cond
    virtual ~ApplicationInfo() {}
    /// @endcond

    /**
     * @brief Focus an application.
     */
    void focusApplication(ApplicationInfoInterface *application);

    /**
     * @brief Unfocus an application.
     */
    void unfocusCurrentApplication(StageHint stageHint);

    /**
     * @brief Start a process.
     *
     * @param desktopFile // TODO: really desktopFile? Shouldn't this be appId?
     * @param flags Special Flags for the execution of this process.
     */
    Application* startProcess(QString desktopFile, ExecFlags flags, QStringList arguments)

    /**
      * @brief Stops a process.
      */
    void stopProcess(ApplicationInfoInterface* application)

Q_SIGNALS:
    // TODO: needed?
    void mainStageFocusedApplicationChanged();
    void sideStageFocusedApplicationChanged();
    void focusRequested(FavoriteApplication favoriteApplication);
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATIONMANAGER_APPLICATIONINFO_H
