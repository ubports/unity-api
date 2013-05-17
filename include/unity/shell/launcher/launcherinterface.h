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

namespace notifications
{

class QuickListModelInterface;

/**
\brief A source of notifications

This should feed the model with new notifications from an implementation-specific
source.
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

    //TODO: Is QString ok for app id? How does an app id look like?
    //TODO: Sync with Mir team on their understanding of an app id.
    //TODO: Instead of working on appIds in this API, should we have an Application class that wraps the apps props?
    /**
      * @brief Returns a list of recent applications.
      * @returns A list of application IDs.
      */
    virtual QStringList recentApplications() const = 0;

    /**
      * @brief Add an application to the list of recent applications.
      * @param appId The ID of the application to be added.
      */
    virtual void addRecentApplication(const QString &appId) = 0;

    /**
      * @brief Remove an application from the list of recent applications.
      * @param appId The ID of the application to be removed.
      */
    virtual void removeRecentApplication(const QString &appId) = 0;

    /**
      * @brief Returns a list of favorite applications.
      * @returns A list of application IDs.
      */
    virtual QStringList favoriteApplications() const = 0;

    /**
      * @brief Add an application to the list of favorite applications.
      * @param appId The ID of the application to be added.
      */
    virtual void addFavoriteApplication(const QString &appId) = 0;

    /**
      * @brief Remove an application from the list of favorite applications.
      * @param appId The ID of the application to be removed.
      */
    virtual void removeFavoriteApplication(const QString &appId) = 0;


    //TODO: What about translations? Translation happening in backend or in frontend?
    /**
      * @brief Get the user friendly name of an application.
      * @param appId The ID of the application.
      * @returns The user friendly name of the application.
      */
    virtual void QString displayName(const QString &appId) = 0;

    //TODO: Should we work on the full path of icons or just the identifier?
    //      Probably some icon ID our ImageProvider can work with...
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

    //TODO: Is this good enough? Should it be wrapped in something that can emit signals on its own?
    virtual int progress(const QString &appId) = 0;
    virtual int count(const QStrign &appId) = 0;

Q_SIGNALS:
    void recentApplicationAdded(const QString &appId);
    void recentApplicationRemoved(const QString &appId);

    void favoriteApplicationAdded(const QString &appId);
    void favoriteApplicationRemoved(const QString &appId);

    void progressChanged(const QString &appId, int progress);
    void countChanged(const QString &appId, int count);

    //TODO: Discuss this. Is a single signal enough or does it need to be more granular?
    //      Is it needed at all? Do .desktop files change? Is there any dynamic data at all (except the QuickList)?
    void applicationChanged(const QString &appId);
};

} // namespace notifications

} // namespace shell

} // namespace unity

#endif // UNITY_SHELL_LAUNCHER_LAUNCHERINTERFACE_H
