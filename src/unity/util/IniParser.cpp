/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>
 */

#include<stdexcept>
#include<glib.h>
#include<unity/util/IniParser.h>

using namespace std;


namespace unity
{

namespace util
{

struct IniParserPrivate {
    GKeyFile *k;
};

/*
 * This is not a private member function, because it takes
 * a GError and we don't want to leak that.
 */

static void inspectError(GError *e, const char *prefix) {
    if(e) {
        string message(prefix);
        message += e->message;
        g_error_free(e);
        throw runtime_error(message);
    }
}

IniParser::IniParser(const char *filename) {
    GKeyFile *kf = g_key_file_new();
    GError *e = nullptr;
    if(!kf) {
        throw runtime_error("Could not create keyfile parser.");
    }
    if(!g_key_file_load_from_file(kf, filename, G_KEY_FILE_NONE, &e)) {
        string message = "Could not load ini file: ";
        message += e->message;
        g_error_free(e);
        g_key_file_free(kf);
        throw runtime_error(message);
    }
    p = new IniParserPrivate();
    p->k = kf;
}

IniParser::~IniParser() {
    g_key_file_free(p->k);
    delete p;
}

bool IniParser::hasGroup(const std::string &group) const {
    gboolean rval;
    rval = g_key_file_has_group(p->k, group.c_str());
    return rval;
}

bool IniParser::hasKey(const std::string &group, const std::string &key) const {
    gboolean rval;
    GError *e = nullptr;
    rval = g_key_file_has_key(p->k, group.c_str(), key.c_str(), &e);
    inspectError(e, "Error checking for key existence: ");
    return rval;
}

std::string IniParser::getString(const std::string &group, const std::string &key) const {
    gchar *value;
    GError *e = nullptr;
    string result;
    value = g_key_file_get_string(p->k, group.c_str(), key.c_str(), &e);
    inspectError(e, "Could not get string value: ");
    result = value;
    g_free(value);
    return result;
}

bool IniParser::getBoolean(const std::string &group, const std::string &key) const {
    bool rval;
    GError *e = nullptr;
    rval = g_key_file_get_boolean(p->k, group.c_str(), key.c_str(), &e);
    inspectError(e, "Could not get boolean value: ");
    return rval;
}

int IniParser::getInt(const std::string &group, const std::string &key) const {
    int rval;
    GError *e = nullptr;
    rval = g_key_file_get_integer(p->k, group.c_str(), key.c_str(), &e);
    inspectError(e, "Could not get integer value: ");
    return rval;
}

std::vector<std::string> IniParser::getStringArray(const std::string &group, const std::string &key) const {
    vector<string> result;
    GError *e = nullptr;
    gchar **strlist;
    gsize count;
    strlist = g_key_file_get_string_list(p->k, group.c_str(), key.c_str(), &count, &e);
    inspectError(e, "Could not get string array: ");
    for(gsize i= 0; i < count; i++) {
        result.push_back(strlist[i]);
    }
    g_strfreev(strlist);
    return result;
}

vector<int> IniParser::getIntArray(const std::string &group, const std::string &key) const {
    vector<int> result;
    GError *e = nullptr;
    gint *ints;
    gsize count;
    ints = g_key_file_get_integer_list(p->k, group.c_str(), key.c_str(), &count, &e);
    inspectError(e, "Could not get integer array; ");
    for(gsize i=0; i<count; i++) {
        result.push_back(ints[i]);
    }
    g_free(ints);
    return result;
}

vector<bool> IniParser::getBooleanArray(const std::string &group, const std::string &key) const {
    vector<bool> result;
    GError *e = nullptr;
    gboolean *bools;
    gsize count;
    bools = g_key_file_get_boolean_list(p->k, group.c_str(), key.c_str(), &count, &e);
    inspectError(e, "Could not get boolean array; ");
    for(gsize i=0; i<count; i++) {
        result.push_back(bools[i]);
    }
    g_free(bools);
    return result;
}

string IniParser::getStartGroup() const {
    return g_key_file_get_start_group(p->k);
}

vector<string> IniParser::getGroups() const {
    vector<string> result;
    gsize count;
    gchar **groups = g_key_file_get_groups(p->k, &count);
    for(gsize i=0; i<count; i++) {
        result.push_back(groups[i]);
    }
    g_strfreev(groups);
    return result;
}

vector<string> IniParser::getKeys(const std::string &group) const {
    vector<string> result;
    GError *e = nullptr;
    gchar **strlist;
    gsize count;
    strlist = g_key_file_get_keys(p->k, group.c_str(), &count, &e);
    inspectError(e, "Could not get list of keys: ");
    for(gsize i= 0; i < count; i++) {
        result.push_back(strlist[i]);
    }
    g_strfreev(strlist);
    return result;
}


} // namespace util

} // namespace unity
