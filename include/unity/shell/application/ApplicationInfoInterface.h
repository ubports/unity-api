/*
 * Copyright 2013,2015,2016 Canonical Ltd.
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
 */

#ifndef UNITY_SHELL_APPLICATION_APPLICATIONINFOINTERFACE_H
#define UNITY_SHELL_APPLICATION_APPLICATIONINFOINTERFACE_H

#include <unity/SymbolExport.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QColor>
#include <QSize>

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
    Q_ENUMS(RequestedState)

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
    Q_PROPERTY(Stage stage READ stage WRITE setStage NOTIFY stageChanged)

    /**
     * @brief The application's state.
     *
     * Holds the current application state.
     */
    Q_PROPERTY(State state READ state NOTIFY stateChanged)

    /**
     * @brief The application's requested running state
     */
    Q_PROPERTY(RequestedState requestedState READ requestedState WRITE setRequestedState NOTIFY requestedStateChanged)

    /**
     * @brief The application's focus state.
     *
     * Holds the current application focus state. True if focused, false otherwise.
     */
    Q_PROPERTY(bool focused READ focused NOTIFY focusedChanged)

    /**
     * @brief Splash screen title
     *
     * @see splashShowHeader
     * Title of the splash screen, to be displayed on its header.
     *
     * A splash screen is shown while the application is loading,
     * before it has drawn its first frame.
     */
    Q_PROPERTY(QString splashTitle READ splashTitle CONSTANT)

    /**
     * @brief Splash image
     *
     * Url of the splash image to be shown while the application is loading,
     * before it has drawn its first frame.
     *
     * The splash image is centered on the splash screen and displayed in
     * its actual size (ie, it's not stretched or shrinked and aspect ratio
     * is kept).
     */
    Q_PROPERTY(QUrl splashImage READ splashImage CONSTANT)

    /**
     * @brief Whether an application header should be shown on the splash screen
     *
     * We offer 2 kinds of splash screens for applications:
     * 1. A splash with a gradient background and image
     * 2. A splash faking a MainView with header text set. So it is possible to
     *    arrange things so that once the app starts up, this splash and the app's
     *    first frame are identical.
     *
     * This property is the switch to select between these.
     *
     * The header will display the splashTitle, if defined, or the application
     * name otherwise.
     *
     * @see name, splashTitle
     */
    Q_PROPERTY(bool splashShowHeader READ splashShowHeader CONSTANT)

    /**
     * @brief Background color of the splash screen
     *
     * Any color that is not fully opaque (having an alpha value of less than
     * 1.0) is ignored and the default background color will be used instead.
     *
     * A splash screen is shown while the application is loading,
     * before it has drawn its first frame.
     */
    Q_PROPERTY(QColor splashColor READ splashColor CONSTANT)

    /**
     * @brief Color of the splash screen header
     *
     * Any color that is not fully opaque (having an alpha value of less than
     * 1.0) is ignored and the splashColor will be used instead.
     *
     * A splash screen is shown while the application is loading,
     * before it has drawn its first frame.
     *
     * @see splashColor
     */
    Q_PROPERTY(QColor splashColorHeader READ splashColorHeader CONSTANT)

    /**
     * @brief Color of the splash screen footer
     *
     * Any color that is not fully opaque (having an alpha value of less than
     * 1.0) is ignored and the splashColor will be used instead.
     *
     * A splash screen is shown while the application is loading,
     * before it has drawn its first frame.
     *
     * @see splashColor
     */
    Q_PROPERTY(QColor splashColorFooter READ splashColorFooter CONSTANT)

    /**
     * @brief The orientations supported by the application UI
     * @see rotatesContents
     */
    Q_PROPERTY(Qt::ScreenOrientations supportedOrientations READ supportedOrientations CONSTANT)

    /**
     * @brief Whether the application UI will rotate itself to match the screen orientation
     *
     * Returns true if the application will rotate the UI in its windows to match the screen
     * orientation.
     *
     * If false, it means that the application never rotates its UI, so it will
     * rely on the window manager to appropriately rotate his windows to match the screen
     * orientation instead.
     *
     * @see supportedOrientations
     */
    Q_PROPERTY(bool rotatesWindowContents READ rotatesWindowContents CONSTANT)

    /**
     * @brief Whether the application is an app targeting the Ubuntu Touch platform.
     */
    Q_PROPERTY(bool isTouchApp READ isTouchApp CONSTANT)

    /**
     * @brief Whether this app is exempt from lifecycle management
     *
     * If true, this app will never entirely suspend its process.
     */
    Q_PROPERTY(bool exemptFromLifecycle READ exemptFromLifecycle WRITE setExemptFromLifecycle NOTIFY exemptFromLifecycleChanged)

    /**
     * @brief The size to be given for new surfaces created by this application
     */
    Q_PROPERTY(QSize initialSurfaceSize READ initialSurfaceSize WRITE setInitialSurfaceSize NOTIFY initialSurfaceSizeChanged)

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

    /**
     * @brief The desired state of an application
     *
     * RequestedRunning: If state is Suspended or Stopped, the application will be resumed
     *                   or restarted, respectively.
     * RequestedSuspended: If state is Running, the application will be suspended.
     */
    enum RequestedState {
        RequestedRunning = Running,
        RequestedSuspended = Suspended
    };

    /// @cond
    virtual ~ApplicationInfoInterface() {}

    virtual QString appId() const = 0;
    virtual QString name() const = 0;
    virtual QString comment() const = 0;
    virtual QUrl icon() const = 0;
    virtual Stage stage() const = 0;
    virtual void setStage(Stage) = 0;
    virtual State state() const = 0;
    virtual RequestedState requestedState() const = 0;
    virtual void setRequestedState(RequestedState) = 0;
    virtual bool focused() const = 0;
    virtual QString splashTitle() const = 0;
    virtual QUrl splashImage() const = 0;
    virtual bool splashShowHeader() const = 0;
    virtual QColor splashColor() const = 0;
    virtual QColor splashColorHeader() const = 0;
    virtual QColor splashColorFooter() const = 0;
    virtual Qt::ScreenOrientations supportedOrientations() const = 0;
    virtual bool rotatesWindowContents() const = 0;
    virtual bool isTouchApp() const = 0;
    virtual bool exemptFromLifecycle() const = 0;
    virtual void setExemptFromLifecycle(bool) = 0;
    virtual QSize initialSurfaceSize() const = 0;
    virtual void setInitialSurfaceSize(const QSize &size) = 0;
    /// @endcond

Q_SIGNALS:
    /// @cond
    void nameChanged(const QString &name);
    void commentChanged(const QString &comment);
    void iconChanged(const QUrl &icon);
    void stageChanged(Stage stage);
    void stateChanged(State state);
    void requestedStateChanged(RequestedState value);
    void focusedChanged(bool focused);
    void exemptFromLifecycleChanged(bool exemptFromLifecycle);
    void initialSurfaceSizeChanged(const QSize &size);
    /// @endcond
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATIONMANAGER_APPLICATIONINFOINTERFACE_H
