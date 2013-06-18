/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>
 */


/*
 * List of (system) headers to precompile.
 * This is not a fire-and-forget file, the list
 * of headers must be updated as includes change.
 *
 * Grepping for includes in include and src
 * will give a pretty good idea what to include.
 */

#include<memory>
#include<vector>
#include<map>
#include<string>
#include<mutex>
#include<exception>
#include<sstream>
