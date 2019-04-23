/*
 * Copyright (C) 2016 Canonical, Ltd.
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

#ifndef UNITY_SHELL_APPLICATION_SURFACEMANAGERINTERFACE_H
#define UNITY_SHELL_APPLICATION_SURFACEMANAGERINTERFACE_H

#include "Mir.h"

#include <QObject>
#include <QVector>

#include <memory>

namespace miral {
class Window;
class Workspace;
}

namespace unity {
namespace shell {
namespace application {

class MirSurfaceInterface;

class SurfaceManagerInterface : public QObject
{
    Q_OBJECT

public:
    virtual ~SurfaceManagerInterface() {}

    virtual void raise(MirSurfaceInterface *surface) = 0;
    virtual void activate(MirSurfaceInterface *surface) = 0;

    virtual void forEachSurfaceInWorkspace(const std::shared_ptr<miral::Workspace> &workspace,
                                           const std::function<void(unity::shell::application::MirSurfaceInterface*)> &callback) = 0;
    virtual void moveSurfaceToWorkspace(unity::shell::application::MirSurfaceInterface* surface,
                                        const std::shared_ptr<miral::Workspace> &workspace) = 0;
    virtual void moveWorkspaceContentToWorkspace(const std::shared_ptr<miral::Workspace> &to,
                                                 const std::shared_ptr<miral::Workspace> &from) = 0;

Q_SIGNALS:
    void surfaceCreated(unity::shell::application::MirSurfaceInterface *surface);
    void surfaceRemoved(unity::shell::application::MirSurfaceInterface *surface);
    void surfaceReady(unity::shell::application::MirSurfaceInterface *surface);
    void surfaceMoved(unity::shell::application::MirSurfaceInterface *surface, const QPoint &topLeft);
    void surfaceResized(unity::shell::application::MirSurfaceInterface *surface, const QSize &size);
    void surfaceStateChanged(unity::shell::application::MirSurfaceInterface *surface, Mir::State state);
    void surfaceFocusChanged(unity::shell::application::MirSurfaceInterface *surface, bool focused);
    void surfacesRaised(const QVector<unity::shell::application::MirSurfaceInterface*> &surfaces);
    void surfaceRequestedRaise(unity::shell::application::MirSurfaceInterface *surface);
    void surfacesAddedToWorkspace(const std::shared_ptr<miral::Workspace> &workspace,
                                  const QVector<unity::shell::application::MirSurfaceInterface*> &surfaces);
    void surfacesAboutToBeRemovedFromWorkspace(const std::shared_ptr<miral::Workspace> &workspace,
                                               const QVector<unity::shell::application::MirSurfaceInterface*> &surfaces);
    void modificationsStarted();
    void modificationsEnded();
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_SURFACEMANAGERINTERFACE_H
