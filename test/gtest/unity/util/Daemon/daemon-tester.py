#! /usr/bin/env python3

#
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
# Authored by: Michi Henning <michi.henning@canonical.com>
#

#
# Little test driver program to execute the Daemon_test binary, wait a little, and check
# whether the test reported any errors. If the file /tmp/Daemon_test.out has non-zero size,
# the test run produced errors.
#

import argparse
import os
import sys
import subprocess
import time

def run_daemon(path):
    status = subprocess.call(path)
    if status != 0:
        exit("cannot run " + path)
    time.sleep(1)                   # Give process time to complete

def run():
    parser = argparse.ArgumentParser(description = 'Test driver for Daemon_test')
    parser.add_argument('Daemon_test', nargs = 1, help = 'Full path to Daemon_test executable')

    args = parser.parse_args()

    daemon = args.Daemon_test[0]
    run_daemon(daemon)

    size = os.stat("Daemon_test.out").st_size
    if size == 0:
        exit(0)

    with open("Daemon_test.out", 'r') as file:
        sys.stderr.write(file.read())
        exit(1)

if __name__ == '__main__':
   run()
