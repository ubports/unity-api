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


#ifndef UNITY_SHELL_LAUNCHER_LAUNCHERINTERFACE_H
#define UNITY_SHELL_LAUNCHER_LAUNCHERINTERFACE_H

#include <QtCore/QObject>

namespace unity
{

namespace shell
{

namespace launcher
{

class QuickListModelInterface;
class ApplicationListModel;

/**
  * @brief An interface that provides all the data needed by the launcher.
  */

class UNITY_API LauncherInterface : public QObject
{
    Q_OBJECT

protected:
    /// @cond
    explicit LauncherInterface(QObject* parent = 0) : QObject(parent) { }
    /// @endcond

public:
    virtual ~LauncherInterface() { }

    /**
      * @brief Returns a list of recent applications.
      * @returns A list of application IDs.
      */
    virtual ApplicationListModel* recentApplications() const = 0;

    /**
      * @brief Returns a list of favorite applications.
      * @returns A list of application IDs.
      */
    virtual ApplicationListModel* favoriteApplications() const = 0;

    /**
      * @brief Get the user friendly name of an application.
      * @param appId The ID of the application.
      * @returns The user friendly name of the application.
      */
    virtual void QString displayName(const QString &appId) = 0;

    /**
      * @brief Get the icon of an application.
      * @param appId The ID of the application.
      * @returns The full path to the icon for the application.
      */
    virtual void QString icon(const QString &appId) = 0;

    //TODO: Fill in getters for all the other things needed from the .desktop file.

    /**
      * @brief Get the QuickList for an application.
      * @param appId The ID of the application.
      * @returns A QuickListModelInterface containing the QuickList.
      */
    virtual QuickListModelInterface* quickList(const QString &appId) = 0;

    /**
      * @brief Get the progress for the progress overlay of an application.
      * @param appId The ID of the application.
      * @returns The percentage of the overlay progress bar. -1 if no progress bar available.
      */
    virtual int progress(const QString &appId) = 0;

    /**
      * @brief Get the count of the count overlay of an application.
      * @param appId The ID of the application.
      * @returns The number to be displayed in the overlay. -1 if no count overlay is available.
      */
    virtual int count(const QStrign &appId) = 0;

Q_SIGNALS:
    void progressChanged(const QString &appId, int progress);
    void countChanged(const QString &appId, int count);
};

} // namespace launcher

} // namespace shell

} // namespace unity

#endif // UNITY_SHELL_LAUNCHER_LAUNCHERINTERFACE_H
