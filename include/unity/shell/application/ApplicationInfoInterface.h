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
        Running,
        Suspended,
        Stopped
    };

    virtual ~ApplicationInfo() {}

    virtual QString appId() const = 0;
    virtual QString name() const = 0;
    virtual QString comment() const = 0;
    virtual QUrl icon() const = 0;
    virtual Stage stage() const = 0;
    virtual State state() const = 0;
    virtual bool focused() const = 0;

Q_SIGNALS:
    void nameChanged(const QString &name);
    void commentChanged(const QString &comment);
    void iconChanged(const QUrl &icon);
    void stageChanged(Stage stage);
    void stateChanged(State state);
    void focusedChanged(bool focused);
    /// @endcond
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATIONMANAGER_APPLICATIONINFOINTERFACE_H
