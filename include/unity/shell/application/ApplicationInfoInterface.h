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

#ifndef UNITY_SHELL_APPLICATION_APPLICATIONINFOINTERFACE_H
#define UNITY_SHELL_APPLICATION_APPLICATIONINFOINTERFACE_H

#include <unity/SymbolExport.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace unity
{
namespace shell
{
namespace application
{

/**
 * @brief A class that holds information about applications
 *
 * The items hold all the information required for the visual representation
 * in the launcher.
 */

class UNITY_API ApplicationInfoInterface: public QObject
{
    Q_OBJECT

    Q_ENUMS(Stage)
    Q_ENUMS(State)

    /**
     * @brief The appId of the application.
     *
     * Holds the appId for the application. For example (com.ubuntu.camera-app).
     * The appId is derived from the filename of the .desktop file.
     */
    Q_PROPERTY(QString appId READ appId CONSTANT)

    /**
     * @brief The name of the application.
     *
     * Holds the name of the application. Localized to current language.
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

    /**
     * @brief The comment for the application.
     *
     * Holds the comment of the application as obtained from the .desktop file. Localized
     * to current language.
     */
    Q_PROPERTY(QString comment READ comment NOTIFY commentChanged)

    /**
     * @brief The application's icon.
     *
     * Holds a path to the icon for the application. Can be a file or a gicon url.
     */
    Q_PROPERTY(QUrl icon READ icon NOTIFY iconChanged)

    /**
     * @brief The application's stage.
     *
     * Holds the stage where this application is currently located.
     */
    Q_PROPERTY(Stage stage READ stage NOTIFY stageChanged)

    /**
     * @brief The application's state.
     *
     * Holds the current application state.
     */
    Q_PROPERTY(State state READ state NOTIFY stateChanged)

    /**
     * @brief The application's focus state.
     *
     * Holds the current application focus state. True if focused, false otherwise.
     */
    Q_PROPERTY(bool focused READ focused NOTIFY focusedChanged)

    /**
     * @brief The URL of the app's screenshot to be used with the image provider.
     *
     * Holds the URL for the app's screenshot. This URL will change whenever the screenshot updates.
     */
    Q_PROPERTY(QUrl screenshot READ screenshot NOTIFY screenshotChanged)

protected:
    /// @cond
    ApplicationInfoInterface(const QString &appId, QObject* parent = 0): QObject(parent) { Q_UNUSED(appId) }
    /// @endcond

public:
    /**
     * @brief A enum that defines a stage.
     *
     * MainStage: The main stage, which is the normal place for applications in
     * traditional desktop environments.
     * SideStage: The side stage, a panel on the right to place phone form factor
     * applications.
     */
    enum Stage {
        MainStage,
        SideStage
    };

    /**
     * @brief An application's state.
     *
     * Starting: The application was launched and is currently starting up.
     * Running: The application is running and ready to be used.
     * Suspended: The application is in the background and has been suspended by
     * the system in order to save resources.
     * Stopped: The application is in the background and has been stopped by
     * the system in order to save resources. From a programmers point of view,
     * the application is closed, but it's state has been stored to disk and
     * can be restored upon next launch.
     */
    enum State {
        Starting,
        Running,
        Suspended,
        Stopped
    };

    /// @cond
    virtual ~ApplicationInfoInterface() {}

    virtual QString appId() const = 0;
    virtual QString name() const = 0;
    virtual QString comment() const = 0;
    virtual QUrl icon() const = 0;
    virtual Stage stage() const = 0;
    virtual State state() const = 0;
    virtual bool focused() const = 0;
    virtual QUrl screenshot() const = 0;
    /// @endcond

Q_SIGNALS:
    /// @cond
    void nameChanged(const QString &name);
    void commentChanged(const QString &comment);
    void iconChanged(const QUrl &icon);
    void stageChanged(Stage stage);
    void stateChanged(State state);
    void focusedChanged(bool focused);
    void screenshotChanged(const QUrl &screenshot);
    /// @endcond
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATIONMANAGER_APPLICATIONINFOINTERFACE_H
