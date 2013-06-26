/*
 * Copyright (C) 2013 Canonical Ltd
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
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

#ifndef SYMBOL_EXPORT_H
#define SYMBOL_EXPORT_H

#define UNITY_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))

#ifdef UNITY_DLL_EXPORTS                          // Defined if we are building the Unity API library
#    define UNITY_API UNITY_HELPER_DLL_EXPORT
#else
#    define UNITY_API /**/
#endif

#endif
