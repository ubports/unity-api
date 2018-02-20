/*
 * Copyright 2013-2106 Canonical Ltd.
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

#ifndef UNITY_SHELL_LAUNCHER_LAUNCHERITEM_H
#define UNITY_SHELL_LAUNCHER_LAUNCHERITEM_H

#include <unity/SymbolExport.h>

#include <QtCore/QObject>

namespace unity
{
namespace shell
{
namespace launcher
{

class QuickListModelInterface;

/**
 * @brief An item presented in the launcher
 *
 * The items hold all the information required for the visual representation
 * in the launcher.
 */

class UNITY_API LauncherItemInterface: public QObject
{
    Q_OBJECT

    /**
     * @brief The appId of the application associated with the item.
     */
    Q_PROPERTY(QString appId READ appId CONSTANT)

    /**
     * @brief The user visible name of the item.
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

    /**
     * @brief The full path to the icon to be shown for the item.
     */
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)

    /**
     * @brief The keywords for this item.
     */
    Q_PROPERTY(QStringList keywords READ keywords NOTIFY keywordsChanged)

    /**
     * @brief The popularity of this application, e.g. usage count given by Zeitgeist
     */
    Q_PROPERTY(uint popularity READ popularity NOTIFY popularityChanged)

    /**
     * @brief A flag whether the item is pinned or not
     */
    Q_PROPERTY(bool pinned READ pinned NOTIFY pinnedChanged)

    /**
     * @brief A flag whether the application belonging to the icon is currently running or not
     */
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

    /**
     * @brief A flag wheter the application is in the recently used applications list
     */
    Q_PROPERTY(bool recent READ recent NOTIFY recentChanged)

    /**
     * @brief The percentage of the progress bar shown on the item.
     *
     * For values from 0 and 100 this will present a progress bar on the item.
     * For values outside this range, no progress bar will be drawn.
     */
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)

    /**
     * @brief The number for the count emblem on the item
     *
     * For values >0 this will paint an emblem containing the number.
     * For 0 and negative values, no count emblem will be drawn.
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    /**
     * @brief The visibility of the count emblem.
     *
     * True if the count emblem should be visible, false otherwise.
     */
    Q_PROPERTY(bool countVisible READ countVisible NOTIFY countVisibleChanged)

    /**
     * @brief The focused state of the item
     *
     * True if focused, false if not focused
     */
    Q_PROPERTY(bool focused READ focused NOTIFY focusedChanged)

    /**
     * @brief The alerting state of the item
     *
     * True if alerting/wobbling, false if not alerting/wobbling
     */
    Q_PROPERTY(bool alerting READ alerting NOTIFY alertingChanged)

    /**
     * @brief The number of surfaces that this application entry has opened
     *
     * The Launcher will display up to 3 pips, one for each surface
     */
    Q_PROPERTY(int surfaceCount READ surfaceCount NOTIFY surfaceCountChanged)

    /**
     * @brief The quick list menu contents for the item
     *
     * Items can have a quick list menu. This property holds a model for
     * the contents of that menu. The pointer to the model will be
     * constant, but of course the contents of the model can change.
     */
    Q_PROPERTY(unity::shell::launcher::QuickListModelInterface* quickList READ quickList CONSTANT)

protected:
    /// @cond
    LauncherItemInterface(QObject *parent = 0): QObject(parent) {}

public:
    virtual ~LauncherItemInterface() {}

    virtual QString appId() const = 0;
    virtual QString name() const = 0;
    virtual QString icon() const = 0;
    virtual QStringList keywords() const = 0;
    virtual uint popularity() const = 0;
    virtual bool pinned() const = 0;
    virtual bool running() const = 0;
    virtual bool recent() const = 0;
    virtual int progress() const = 0;
    virtual int count() const = 0;
    virtual bool countVisible() const = 0;
    virtual bool focused() const = 0;
    virtual bool alerting() const = 0;
    virtual int surfaceCount() const = 0;
    virtual unity::shell::launcher::QuickListModelInterface *quickList() const = 0;

Q_SIGNALS:
    void nameChanged(const QString &name);
    void iconChanged(const QString &icon);
    void keywordsChanged(const QStringList &keywords);
    void popularityChanged(uint popularity);
    void pinnedChanged(bool pinned);
    void runningChanged(bool running);
    void recentChanged(bool running);
    void progressChanged(int progress);
    void countChanged(int count);
    void countVisibleChanged(bool countVisible);
    void focusedChanged(bool focused);
    void alertingChanged(bool alerting);
    void surfaceCountChanged(int surfaceCount);
    /// @endcond
};

} // namespace launcher
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_LAUNCHER_LAUNCHERITEMINTERFACE_H
