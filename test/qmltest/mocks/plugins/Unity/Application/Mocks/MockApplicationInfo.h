/*
 * Copyright 2013,2015 Canonical Ltd.
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

#ifndef MOCKAPPLICATIONINFO_H
#define MOCKAPPLICATIONINFO_H

#include <ApplicationInfoInterface.h>

#include <QUrl>

using namespace unity::shell::application;

class UNITY_API MockApplicationInfo: public ApplicationInfoInterface
{
    Q_OBJECT
public:
    MockApplicationInfo(const QString &appId, const QString& name, const QString& comment, const QUrl& icon, QObject* parent = 0);

    QString appId() const;
    QString name() const;
    QString comment() const;
    QUrl icon() const;

    ApplicationInfoInterface::Stage stage() const;
    void setStage(ApplicationInfoInterface::Stage stage);

    ApplicationInfoInterface::State state() const;
    void setState(ApplicationInfoInterface::State state);

    bool focused() const;
    void setFocused(bool focused);

    QString splashTitle() const override;
    QUrl splashImage() const override;
    bool splashShowHeader() const override;
    QColor splashColor() const override;
    QColor splashColorHeader() const override;
    QColor splashColorFooter() const override;
    RequestedState requestedState() const override;
    void setRequestedState(RequestedState) override;

    Qt::ScreenOrientations supportedOrientations() const override;
    bool rotatesWindowContents() const override;

    bool isTouchApp() const override;
    bool canSuspend() const override;
    void setCanSuspend(bool canSuspend) override;

private:
    QString m_appId;
    QString m_name;
    QString m_comment;
    QUrl m_icon;
    ApplicationInfoInterface::Stage m_stage;
    ApplicationInfoInterface::State m_state;
    bool m_focused;
    bool m_canSuspend;
};

#endif // MOCKAPPLICATIONINFO_H
