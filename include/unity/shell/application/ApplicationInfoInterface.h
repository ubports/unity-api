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
     * @brief The desktopFile (deprecated).
     *
     * The full path to the .desktop file. Will be dropped in favor of appId.
     */
    Q_PROPERTY(QString desktopFile READ desktopFile WRITE setDesktopFile NOTIFY desktopFileChanged)

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
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    /**
     * @brief The comment for the application.
     *
     * Holds the comment of the application as obtained from the .desktop file. Localized
     * to current language.
     */
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)

    /**
     * @brief The application's icon.
     *
     * Holds a path to the icon for the application. Can be a file or a gicon url.
     */
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)

    /**
     * @brief The command to launch this application.
     *
     * Holds the command to launch this application as obtained from the .desktop file.
     */
    Q_PROPERTY(QString exec READ exec WRITE setExec NOTIFY execChanged)

    /**
     * @brief Handle (deprecated)
     *
     * Needed for compatibility. Will be dropped.
     */
    Q_PROPERTY(qint64 handle READ handle WRITE setHandle NOTIFY handleChanged)

    /**
     * @brief The application's stage.
     *
     * Holds the stage where this application is currently located.
     */
    Q_PROPERTY(Stage stage READ stage WRITE setStage NOTIFY stageChanged)

    /**
     * @brief The application's state.
     *
     * Holds the current application state.
     */
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)

    /**
     * @brief The application's fullscreen state.
     *
     * Holds the current application fullscreen state. True if fullscreen, false otherwise.
     */
    Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen NOTIFY fullscreenChanged)

    /**
     * @brief The application's focus state.
     *
     * Holds the current application focus state. True if focused, false otherwise.
     */
    Q_PROPERTY(bool focused READ focused WRITE setFocused NOTIFY focusedChanged)

    /**
     * @brief A screenshot for the application.
     *
     * Holds a screenshot of the current application if possible. Used to keep displaying
     * stopped/killed applications.
     */
    Q_PROPERTY(QImage screenshot READ screenshot WRITE setScreenshot NOTIFY screenshotChanged)

protected:
    /// @cond
    ApplicationInfo(const QString &appId, QObject* parent = 0): QObject(parent) {}

public:
    enum Stage {
        MainStage,
        SideStage
    };

    enum State {
        Starting,
        Running
    };

    virtual ~ApplicationInfo() {}

    virtual QString desktopFile() const = 0;
    virtual QString appId() const = 0;
    virtual QString name() const = 0;
    virtual QString comment() const = 0;
    virtual QString icon() const = 0;
    virtual QString exec() const = 0;
    virtual qint64 handle() const = 0;
    virtual Stage stage() const = 0;
    virtual State state() const = 0;
    virtual bool fullscreen() const = 0;
    virtual bool focused() const = 0;
    virtual QImage screenshot() const = 0;

Q_SIGNALS:
    // FIXME: drop this once desktopFile() is dropped
    void desktopFileChanged(const QString &desktopFile);
    void nameChanged(const QString &name);
    void commentChanged(const QString &comment);
    void iconChanged(const QString &icon);
    void execChanged(const QString &exec);
    // FIXME: drop this once handle() is dropped
    void handleChanged(quing64 handle);
    void stageChanged(Stage stage);
    void stateChanged(State state);
    void fullscreenChanged(bool fullscreen);
    void focusedChanged(bool focused);
    void screenshotChanged(const QImage &image);
    /// @endcond
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATIONMANAGER_APPLICATIONINFOINTERFACE_H
