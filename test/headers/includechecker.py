#!/usr/bin/python3 -tt

# Copyright (C) 2013 Canonical Ltd
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>

"""A script that traverses all header files in a given
directory and scans them for forbidden includes."""

import os, sys, stat

forbidden = {'boost',
             'gobject',
             'gtk',
             'Qt',
             'dbus.h',
             }

#
# List of exceptions. For each of the directory prefixes in the list, allow the #include directive to start
# with one of the specified prefixes.
#
allowed = {
    'unity/shell': { 'Qt' } # Anything under unity/shell can include anything starting with Qt
}

def check_file(filename, permitted_includes):
    errors_found = False
    linenum = 0
    for line in open(filename, encoding='utf-8'):
        line = line.strip()
        if line.startswith('#include'):
            for f in (forbidden - permitted_includes):
                if f in line:
                    msg = 'Forbidden include: %s:%d - %s'\
                        % (filename, linenum, line)
                    print(msg)
                    errors_found = True;
        linenum += 1
    return errors_found

def check_headers(incdir):
    errors_found = False
    suffixes = ('h',
                'hpp',
                'hh',
                'hxx',
                'H',
                'h.in',
                )
    for root, dirs, files in os.walk(incdir):
        if 'internal' in dirs:
            dirs.remove('internal')
        for filename in files:
            if filename.endswith(suffixes):
                fullname = os.path.join(root, filename)
                permitted_includes = set()
                for path, names in allowed.items():
                    if fullname.startswith(os.path.join(incdir, path)):
                        permitted_includes = names
                        break
                if check_file(fullname, permitted_includes):
                    errors_found = True
    return errors_found

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(sys.argv[0], '<include directory>')
        sys.exit(1)
    incdir = sys.argv[1]
    if not stat.S_ISDIR(os.stat(incdir).st_mode):
        print("Argument", incdir, "is not a directory.")
        sys.exit(1)
    if check_headers(incdir):
        sys.exit(1)
