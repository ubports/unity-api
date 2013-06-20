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

#include<unity/UnityExceptions.h>
#include<unity/util/IniParser.h>
#include<glib.h>

using namespace std;

namespace unity
{

namespace util
{


namespace internal
{

struct IniParserPrivate
{
    GKeyFile *k;
    string filename;
};
}

using internal::IniParserPrivate;

/*
 * This is not a private member function, because it takes
 * a GError and we don't want to leak that.
 */

static void inspect_error(GError* e, const char* prefix, const string& filename, const string& group)
{
    if (e)
    {
        string message(prefix);
        message += " (";
        message += filename;
        message += ", group: ";
        message += group;
        message += "): ";
        message += e->message;
        g_error_free(e);
        throw LogicException(message);
    }
}

IniParser::IniParser(const char* filename)
{
    GKeyFile* kf = g_key_file_new();
    GError* e = nullptr;
    if (!kf)
    {
        throw ResourceException("Could not create keyfile parser.");
    }
    if (!g_key_file_load_from_file(kf, filename, G_KEY_FILE_NONE, &e))
    {
        string message = "Could not load ini file ";
        message += filename;
        message += ": ";
        message += e->message;
        int errnum = e->code;
        g_error_free(e);
        g_key_file_free(kf);
        throw FileException(message, errnum);
    }
    p = new IniParserPrivate();
    p->k = kf;
    p->filename = filename;
}

IniParser::~IniParser() noexcept
{
    g_key_file_free(p->k);
    delete p;
}

bool IniParser::has_group(const std::string& group) const noexcept
{
    gboolean rval;
    rval = g_key_file_has_group(p->k, group.c_str());
    return rval;
}

bool IniParser::has_key(const std::string& group, const std::string& key) const
{
    gboolean rval;
    GError* e = nullptr;
    rval = g_key_file_has_key(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Error checking for key existence", p->filename, group);
    return rval;
}

std::string IniParser::get_string(const std::string& group, const std::string& key) const
{
    gchar* value;
    GError* e = nullptr;
    string result;
    value = g_key_file_get_string(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Could not get string value", p->filename, group);
    result = value;
    g_free(value);
    return result;
}

bool IniParser::get_boolean(const std::string& group, const std::string& key) const
{
    bool rval;
    GError* e = nullptr;
    rval = g_key_file_get_boolean(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Could not get boolean value", p->filename, group);
    return rval;
}

int IniParser::get_int(const std::string& group, const std::string& key) const
{
    int rval;
    GError* e = nullptr;
    rval = g_key_file_get_integer(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Could not get integer value", p->filename, group);
    return rval;
}

std::vector<std::string> IniParser::get_string_array(const std::string& group, const std::string& key) const
{
    vector<string> result;
    GError* e = nullptr;
    gchar** strlist;
    gsize count;
    strlist = g_key_file_get_string_list(p->k, group.c_str(), key.c_str(), &count, &e);
    inspect_error(e, "Could not get string array", p->filename, group);
    for (gsize i = 0; i < count; i++)
    {
        result.push_back(strlist[i]);
    }
    g_strfreev(strlist);
    return result;
}

vector<int> IniParser::get_int_array(const std::string& group, const std::string& key) const
{
    vector<int> result;
    GError* e = nullptr;
    gint* ints;
    gsize count;
    ints = g_key_file_get_integer_list(p->k, group.c_str(), key.c_str(), &count, &e);
    inspect_error(e, "Could not get integer array", p->filename, group);
    for (gsize i = 0; i < count; i++)
    {
        result.push_back(ints[i]);
    }
    g_free(ints);
    return result;
}

vector<bool> IniParser::get_boolean_array(const std::string& group, const std::string& key) const
{
    vector<bool> result;
    GError* e = nullptr;
    gboolean* bools;
    gsize count;
    bools = g_key_file_get_boolean_list(p->k, group.c_str(), key.c_str(), &count, &e);
    inspect_error(e, "Could not get boolean array", p->filename, group);
    for (gsize i = 0; i < count; i++)
    {
        result.push_back(bools[i]);
    }
    g_free(bools);
    return result;
}

string IniParser::get_start_group() const
{
    gchar* sg = g_key_file_get_start_group(p->k);
    string result(sg);
    g_free(sg);
    return result;
}

vector<string> IniParser::get_groups() const
{
    vector<string> result;
    gsize count;
    gchar** groups = g_key_file_get_groups(p->k, &count);
    for (gsize i = 0; i < count; i++)
    {
        result.push_back(groups[i]);
    }
    g_strfreev(groups);
    return result;
}

vector<string> IniParser::get_keys(const std::string& group) const
{
    vector<string> result;
    GError* e = nullptr;
    gchar** strlist;
    gsize count = 0;
    IniParserPrivate f;
    strlist = g_key_file_get_keys(p->k, group.c_str(), &count, &e);
    inspect_error(e, "Could not get list of keys", p->filename, group);
    for (gsize i = 0; i < count; i++)
    {
        result.push_back(strlist[i]);
    }
    g_strfreev(strlist);
    return result;
}


} // namespace util

} // namespace unity
