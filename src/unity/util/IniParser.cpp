/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>
 */

#include <unity/UnityExceptions.h>
#include <unity/util/IniParser.h>

#include <glib.h>

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
    bool dirty = false;
};

static std::mutex parser_mutex;

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
    lock_guard<std::mutex> lock(internal::parser_mutex);

    GKeyFile* kf = g_key_file_new();
    GError* e = nullptr;
    if (!kf)
    {
        throw ResourceException("Could not create keyfile parser."); // LCOV_EXCL_LINE
    }
    if (!g_key_file_load_from_file(kf, filename, G_KEY_FILE_KEEP_TRANSLATIONS, &e))
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
    lock_guard<std::mutex> lock(internal::parser_mutex);

    g_key_file_free(p->k);
    delete p;
}

bool IniParser::has_group(const std::string& group) const noexcept
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    gboolean rval;
    rval = g_key_file_has_group(p->k, group.c_str());
    return rval;
}

bool IniParser::has_key(const std::string& group, const std::string& key) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    gboolean rval;
    GError* e = nullptr;
    rval = g_key_file_has_key(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Error checking for key existence", p->filename, group);
    return rval;
}

std::string IniParser::get_string(const std::string& group, const std::string& key) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    gchar* value;
    GError* e = nullptr;
    string result;
    value = g_key_file_get_string(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Could not get string value", p->filename, group);
    result = value;
    g_free(value);
    return result;
}

std::string IniParser::get_locale_string(const std::string& group, const std::string& key, const std::string& locale) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    gchar* value;
    GError* e = nullptr;
    string result;
    value = g_key_file_get_locale_string(p->k, group.c_str(), key.c_str(), locale.empty() ? nullptr : locale.c_str(), &e);
    inspect_error(e, "Could not get localized string value", p->filename, group);
    result = value;
    g_free(value);
    return result;
}

bool IniParser::get_boolean(const std::string& group, const std::string& key) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    bool rval;
    GError* e = nullptr;
    rval = g_key_file_get_boolean(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Could not get boolean value", p->filename, group);
    return rval;
}

int IniParser::get_int(const std::string& group, const std::string& key) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    int rval;
    GError* e = nullptr;
    rval = g_key_file_get_integer(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Could not get integer value", p->filename, group);
    return rval;
}

double IniParser::get_double(const std::string& group, const std::string& key) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    double rval;
    GError* e = nullptr;
    rval = g_key_file_get_double(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Could not get double value", p->filename, group);
    return rval;
}

std::vector<std::string> IniParser::get_string_array(const std::string& group, const std::string& key) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

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

std::vector<std::string> IniParser::get_locale_string_array(const std::string& group,
                                                            const std::string& key,
                                                            const std::string& locale) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    vector<string> result;
    GError* e = nullptr;
    gchar** strlist;
    gsize count;
    strlist = g_key_file_get_locale_string_list(p->k, group.c_str(), key.c_str(),
                                                locale.empty() ? nullptr : locale.c_str(), &count, &e);
    inspect_error(e, "Could not get localized string array", p->filename, group);
    for (gsize i = 0; i < count; i++)
    {
        result.push_back(strlist[i]);
    }
    g_strfreev(strlist);
    return result;
}

vector<bool> IniParser::get_boolean_array(const std::string& group, const std::string& key) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

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

vector<int> IniParser::get_int_array(const std::string& group, const std::string& key) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

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

vector<double> IniParser::get_double_array(const std::string& group, const std::string& key) const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    vector<double> result;
    GError* e = nullptr;
    gdouble* doubles;
    gsize count;
    doubles = g_key_file_get_double_list(p->k, group.c_str(), key.c_str(), &count, &e);
    inspect_error(e, "Could not get double array", p->filename, group);
    for (gsize i = 0; i < count; i++)
    {
        result.push_back(doubles[i]);
    }
    g_free(doubles);
    return result;
}

string IniParser::get_start_group() const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    gchar* sg = g_key_file_get_start_group(p->k);
    string result(sg);
    g_free(sg);
    return result;
}

vector<string> IniParser::get_groups() const
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

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
    lock_guard<std::mutex> lock(internal::parser_mutex);

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

bool IniParser::remove_group(const std::string& group)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    gboolean rval;
    GError* e = nullptr;
    rval = g_key_file_remove_group(p->k, group.c_str(), &e);
    inspect_error(e, "Error removing group", p->filename, group);
    return rval;
}

bool IniParser::remove_key(const std::string& group, const std::string& key)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    gboolean rval;
    GError* e = nullptr;
    rval = g_key_file_remove_key(p->k, group.c_str(), key.c_str(), &e);
    inspect_error(e, "Error removing key", p->filename, group);
    return rval;
}

void IniParser::set_string(const std::string& group, const std::string& key, const std::string& value)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    g_key_file_set_string(p->k, group.c_str(), key.c_str(), value.c_str());
    p->dirty = true;
}

void IniParser::set_locale_string(const std::string& group, const std::string& key,
                                  const std::string& value, const std::string& locale)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    g_key_file_set_locale_string(p->k, group.c_str(), key.c_str(), locale.c_str(), value.c_str());
    p->dirty = true;
}

void IniParser::set_boolean(const std::string& group, const std::string& key, bool value)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    g_key_file_set_boolean(p->k, group.c_str(), key.c_str(), value);
    p->dirty = true;
}

void IniParser::set_int(const std::string& group, const std::string& key, int value)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    g_key_file_set_integer(p->k, group.c_str(), key.c_str(), value);
    p->dirty = true;
}

void IniParser::set_double(const std::string& group, const std::string& key, double value)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    g_key_file_set_double(p->k, group.c_str(), key.c_str(), value);
    p->dirty = true;
}

void IniParser::set_string_array(const std::string& group, const std::string& key,
                                 const std::vector<std::string>& value)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    int count = value.size();
    gchar** strlist = g_new(gchar*, count+1);

    for (int i = 0; i < count; ++i)
    {
        strlist[i] = g_strdup(value[i].c_str());
    }
    strlist[count] = nullptr;

    g_key_file_set_string_list(p->k, group.c_str(), key.c_str(), strlist, count);
    p->dirty = true;

    g_strfreev(strlist);
}

void IniParser::set_locale_string_array(const std::string& group, const std::string& key,
                                        const std::vector<std::string>& value, const std::string& locale)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    int count = value.size();
    gchar** strlist = g_new(gchar*, count+1);

    for (int i = 0; i < count; ++i)
    {
        strlist[i] = g_strdup(value[i].c_str());
    }
    strlist[count] = nullptr;

    g_key_file_set_locale_string_list(p->k, group.c_str(), key.c_str(), locale.c_str(), strlist, count);
    p->dirty = true;

    g_strfreev(strlist);
}

void IniParser::set_boolean_array(const std::string& group, const std::string& key, const std::vector<bool>& value)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    int count = value.size();
    gboolean* boollist = g_new(gboolean, count);

    for (int i = 0; i < count; ++i)
    {
        boollist[i] = value[i];
    }

    g_key_file_set_boolean_list(p->k, group.c_str(), key.c_str(), boollist, count);
    p->dirty = true;

    g_free(boollist);
}

void IniParser::set_int_array(const std::string& group, const std::string& key, const std::vector<int>& value)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    int count = value.size();
    gint* intlist = g_new(gint, count);

    for (int i = 0; i < count; ++i)
    {
        intlist[i] = value[i];
    }

    g_key_file_set_integer_list(p->k, group.c_str(), key.c_str(), intlist, count);
    p->dirty = true;

    g_free(intlist);
}

void IniParser::set_double_array(const std::string& group, const std::string& key, const std::vector<double>& value)
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    int count = value.size();
    gdouble* doublelist = g_new(gdouble, count);

    for (int i = 0; i < count; ++i)
    {
        doublelist[i] = value[i];
    }

    g_key_file_set_double_list(p->k, group.c_str(), key.c_str(), doublelist, count);
    p->dirty = true;

    g_free(doublelist);
}

void IniParser::sync()
{
    lock_guard<std::mutex> lock(internal::parser_mutex);

    if (p->dirty)
    {
        GError* e = nullptr;
        if (!g_key_file_save_to_file(p->k, p->filename.c_str(), &e))
        {
            string message = "Could not write ini file ";
            message += p->filename;
            message += ": ";
            message += e->message;
            int errnum = e->code;
            g_error_free(e);
            throw FileException(message, errnum);
        }

        p->dirty = false;
    }
}

} // namespace util

} // namespace unity
