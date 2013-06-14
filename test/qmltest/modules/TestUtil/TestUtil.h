/*
 * Copyright (C) 2012, 2013 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef TESTUTIL_H
#define TESTUTIL_H

#include <QtQuick/QQuickItem>

class TestUtil : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TestUtil)

public:
    TestUtil(QObject *parent = 0);
    ~TestUtil();

    Q_INVOKABLE bool isInstanceOf(QObject*, QString);
};

QML_DECLARE_TYPE(TestUtil)

#endif // TESTUTIL_H
