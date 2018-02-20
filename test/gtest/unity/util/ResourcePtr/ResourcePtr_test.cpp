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
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

#include <gtest/gtest.h>
#include <unity/UnityExceptions.h>
#include <unity/util/ResourcePtr.h>

#include <set>
#include <functional>

using namespace std;
using namespace unity;
using namespace unity::util;

namespace
{

std::set<int*> allocated; // Tracks allocated resources

}

//
// Fake allocation and deallocation functions.
//

int* alloc_int(int p)
{
    int* pointer = reinterpret_cast<int*>(p);
    allocated.insert(pointer);
    return pointer;
}

int dealloc_int(int* i)
{
    auto it = allocated.find(i);
    EXPECT_NE(it, allocated.end());
    allocated.erase(it);
    return 0;
}

//
// Check that allocator and deallocator are called with the correct argument
// and that get() returns the correct value.
//

TEST(ResourcePtr, basic)
{
    {
        ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);
        EXPECT_FALSE(rp.has_resource());
    }

    {
        ResourcePtr<int*, decltype(&dealloc_int)> rp(alloc_int(99), dealloc_int);
        EXPECT_EQ(allocated.size(), 1);
        EXPECT_NE(allocated.find(rp.get()), allocated.end());
        EXPECT_TRUE(rp.has_resource());
    }
    EXPECT_TRUE(allocated.empty());
}

//
// A deallocator that expects two arguments. We use std::bind to call it as if it expected only one.
//

int dealloc_string_int(string const& s, int* i)
{
    EXPECT_EQ(s, "Hello");
    dealloc_int(i);
    return 0;
}

//
// Check that calling with bind works as expected.
//

TEST(ResourcePtr, bind)
{
    {
        auto call_dealloc = std::bind(&dealloc_string_int, "Hello", std::placeholders::_1);
        ResourcePtr<int*, decltype(call_dealloc)> rp(alloc_int(42), call_dealloc);
        EXPECT_EQ(allocated.size(), 1);
        EXPECT_NE(allocated.find(rp.get()), allocated.end());
    }
    EXPECT_TRUE(allocated.empty());
}

//
// Check that reset assigns the new pointer value.
//

TEST(ResourcePtr, reset)
{
    ResourcePtr<int*, decltype(&dealloc_int)> rp(alloc_int(77), dealloc_int);
    EXPECT_EQ(allocated.size(), 1);
    EXPECT_NE(allocated.find(rp.get()), allocated.end());

    rp.reset(alloc_int(33));
    EXPECT_EQ(allocated.size(), 1);
    EXPECT_EQ(allocated.find((int*)77), allocated.end());
    EXPECT_NE(allocated.find((int*)33), allocated.end());

    rp.reset(alloc_int(10));
    rp.reset(alloc_int(20));    // Will deallocate the previous resource, so this will not cause a leak.
}

//
// Check that dealloc deallocates and can be called multiple times without ill effects.
//

TEST(ResourcePtr, dealloc)
{
    ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);

    rp.reset(alloc_int(77));
    EXPECT_EQ(allocated.size(), 1);
    EXPECT_NE(allocated.find(rp.get()), allocated.end());

    rp.dealloc();
    EXPECT_EQ(allocated.size(), 0);
    EXPECT_FALSE(rp.has_resource());

    rp.dealloc();
    EXPECT_EQ(allocated.size(), 0);
    EXPECT_FALSE(rp.has_resource());

    rp.reset(alloc_int(33));
    EXPECT_EQ(allocated.size(), 1);
    EXPECT_NE(allocated.find((int*)33), allocated.end());
    EXPECT_TRUE(rp.has_resource());

    rp.dealloc();
    EXPECT_EQ(allocated.size(), 0);
    EXPECT_FALSE(rp.has_resource());

    rp.dealloc();
    EXPECT_EQ(allocated.size(), 0);
    EXPECT_FALSE(rp.has_resource());
}

int dealloc_throw(int* i)
{
    auto it = allocated.find(i);
    EXPECT_NE(it, allocated.end());
    allocated.erase(it);
    throw 99;
}

//
// Test that things work correctly if the deleter throws.
//

TEST(ResourcePtr, dealloc_throw)
{
    {
        ResourcePtr<int*, decltype(&dealloc_throw)> rp(dealloc_throw);
        rp.reset(alloc_int(77));

        try
        {
            rp.dealloc();
        }
        catch (int i)
        {
            EXPECT_EQ(99, i);
            EXPECT_FALSE(rp.has_resource());
        }
    }

    {
        // Same test again, but this time by causing the deallocation via reset().
        ResourcePtr<int*, decltype(&dealloc_throw)> rp(dealloc_throw);
        rp.reset(alloc_int(77));

        try
        {
            rp.reset(alloc_int(66));
        }
        catch (int i)
        {
            EXPECT_EQ(99, i);
            EXPECT_TRUE(rp.has_resource()); // True because rp now owns the new resource
        }
    }

    {
        // Same test again, but this time by letting the destructor do
        // the deallocation.
        try
        {
            ResourcePtr<int*, decltype(&dealloc_throw)> rp(dealloc_throw);
            rp.reset(alloc_int(77));
        }
        catch (...)
        {
            FAIL();
        }
    }
}

//
// get() without a resource throws.
//

TEST(ResourcePtr, get_throw)
{
    ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);

    try
    {
        rp.get();
        FAIL();
    }
    catch (std::logic_error const& e)
    {
        EXPECT_STREQ("get() called on ResourcePtr without resource", e.what());
    }

    rp.reset(alloc_int(99));
    rp.dealloc();

    try
    {
        rp.get();
        FAIL();
    }
    catch (std::logic_error const& e)
    {
        EXPECT_STREQ("get() called on ResourcePtr without resource", e.what());
    }
}

//
// Check that release() releases the resource and throws if there is no resource to release.
//

TEST(ResourcePtr, release)
{
    ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);

    rp.reset(alloc_int(99));
    EXPECT_TRUE(rp.has_resource());
    rp.release();
    EXPECT_FALSE(rp.has_resource());

    try
    {
        rp.release();
        FAIL();
    }
    catch (std::logic_error const& e)
    {
        EXPECT_STREQ("release() called on ResourcePtr without resource", e.what());
    }
}

//
// operator bool()
//

TEST(ResourcePtr, operator_bool)
{
    {
        ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);
        if (rp)
        {
            FAIL();
        }
    }

    {
        ResourcePtr<int*, decltype(&dealloc_int)> rp(alloc_int(99), dealloc_int);
        if (!rp)
        {
            FAIL();
        }
    }
}

//
// get_deleter() (two versions)
//

TEST(ResourcePtr, get_deleter)
{
    ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);
    EXPECT_EQ(rp.get_deleter(), &dealloc_int);

    const ResourcePtr<int*, decltype(&dealloc_int)> rp_const(dealloc_int);
    EXPECT_EQ(rp_const.get_deleter(), &dealloc_int);
}

class Comparable
{
public:
    Comparable()
        : i_(0)
    {
    }

    Comparable(int i)
        : i_(i)
    {
    }

    bool operator<(Comparable const& rhs) const
    {
        return i_ < rhs.i_;
    }

    bool operator==(Comparable const& rhs) const
    {
        return i_ == rhs.i_;
    }

    int get() const
    {
        return i_;
    }

private:
    int i_;
};

void no_op(Comparable) {}   // Dummy deallocation function

ResourcePtr<Comparable, decltype(&no_op)>
make_comparable(int i)
{
    return ResourcePtr<Comparable, decltype(&no_op)>(Comparable(i), no_op);
}

//
// Check move constructor and move assignment operator
//

TEST(ResourcePtr, move)
{
    {
        ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);
        ResourcePtr<int*, decltype(&dealloc_int)> rp2(std::move(rp));

        EXPECT_FALSE(rp.has_resource());
        EXPECT_FALSE(rp2.has_resource());
    }

    {
        ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);
        rp.reset(alloc_int(99));
        ResourcePtr<int*, decltype(&dealloc_int)> rp2(std::move(rp));

        EXPECT_FALSE(rp.has_resource());
        EXPECT_TRUE(rp2.has_resource());
        EXPECT_EQ(allocated.size(), 1);
        EXPECT_NE(allocated.find((int*)99), allocated.end());
    }

    {
        ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);

        rp = std::move(ResourcePtr<int*, decltype(&dealloc_int)>(dealloc_int));

        EXPECT_FALSE(rp.has_resource());
    }

    {
        ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);
        rp.reset(alloc_int(99));
        EXPECT_TRUE(rp.has_resource());

        rp = std::move(ResourcePtr<int*, decltype(&dealloc_int)>(dealloc_int));

        EXPECT_FALSE(rp.has_resource());
        EXPECT_TRUE(allocated.empty());
    }

    {
        ResourcePtr<int*, decltype(&dealloc_int)> rp(dealloc_int);
        rp.reset(alloc_int(99));

        rp = std::move(ResourcePtr<int*, decltype(&dealloc_int)>(alloc_int(42), dealloc_int));

        EXPECT_TRUE(rp.has_resource());
        EXPECT_EQ(allocated.size(), 1);
        EXPECT_NE(allocated.find((int*)42), allocated.end());
    }

    {
        ResourcePtr<Comparable, decltype(&no_op)> r(make_comparable(53));
        EXPECT_EQ(53, r.get().get());
    }

    {
        ResourcePtr<Comparable, decltype(&no_op)> r(no_op);
        r = make_comparable(44);

        EXPECT_EQ(44, r.get().get());
    }
}

TEST(ResourcePtr, comparisons)
{
    {
        ResourcePtr<Comparable, decltype(&no_op)> zero(Comparable(0), no_op);
        ResourcePtr<Comparable, decltype(&no_op)> one(Comparable(1), no_op);
        ResourcePtr<Comparable, decltype(&no_op)> no_init(no_op);

        EXPECT_TRUE(no_init == no_init);
        EXPECT_FALSE(zero == no_init);
        EXPECT_FALSE(no_init == zero);

        EXPECT_FALSE(zero == one);
        EXPECT_TRUE(zero == zero);

        EXPECT_TRUE(zero != one);

        EXPECT_TRUE(no_init < zero);
        EXPECT_FALSE(no_init < no_init);
        EXPECT_FALSE(zero < no_init);

        EXPECT_TRUE(zero < one);
        EXPECT_FALSE(one < zero);
        EXPECT_FALSE(zero < zero);

        EXPECT_TRUE(zero <= one);
        EXPECT_TRUE(one <= one);
        EXPECT_FALSE(one <= zero);

        EXPECT_TRUE(one > zero);
        EXPECT_FALSE(zero > one);
        EXPECT_FALSE(one > one);

        EXPECT_TRUE(one >= zero);
        EXPECT_TRUE(one >= one);
        EXPECT_FALSE(zero >= one);
    }
}

TEST(ResourcePtr, swap)
{
    {
        ResourcePtr<Comparable, decltype(&no_op)> zero(Comparable(0), no_op);
        ResourcePtr<Comparable, decltype(&no_op)> one(Comparable(1), no_op);
        ResourcePtr<Comparable, decltype(&no_op)> no_init(no_op);

        // Member swap
        zero.swap(one);
        EXPECT_EQ(zero.get(), 1);
        EXPECT_EQ(one.get(), 0);

        // Non-member swap
        unity::util::swap(one, no_init);
        EXPECT_TRUE(no_init.has_resource());
        EXPECT_FALSE(one.has_resource());

        // Self-swap
        zero.swap(zero);
        EXPECT_EQ(zero.get(), 1);
    }
}

TEST(ResourcePtr, std_specializations)
{
    ResourcePtr<Comparable, decltype(&no_op)> nr1(no_op);
    ResourcePtr<Comparable, decltype(&no_op)> nr2(no_op);
    ResourcePtr<Comparable, decltype(&no_op)> zero(Comparable(0), no_op);
    ResourcePtr<Comparable, decltype(&no_op)> one(Comparable(1), no_op);

    std::equal_to<ResourcePtr<Comparable, decltype(&no_op)>> equal;
    std::not_equal_to<ResourcePtr<Comparable, decltype(&no_op)>> not_equal;
    std::less<ResourcePtr<Comparable, decltype(&no_op)>> less;
    std::less_equal<ResourcePtr<Comparable, decltype(&no_op)>> less_equal;
    std::greater<ResourcePtr<Comparable, decltype(&no_op)>> greater;
    std::greater_equal<ResourcePtr<Comparable, decltype(&no_op)>> greater_equal;

    EXPECT_TRUE(equal.operator()(nr1, nr2));
    EXPECT_FALSE(equal.operator()(nr1, one));
    EXPECT_FALSE(equal.operator()(one, nr1));
    EXPECT_TRUE(equal.operator()(one, one));
    EXPECT_FALSE(equal.operator()(zero, one));

    EXPECT_FALSE(not_equal.operator()(nr1, nr2));
    EXPECT_TRUE(not_equal.operator()(nr1, one));
    EXPECT_TRUE(not_equal.operator()(one, nr1));
    EXPECT_FALSE(not_equal.operator()(one, one));
    EXPECT_TRUE(not_equal.operator()(zero, one));

    EXPECT_FALSE(less.operator()(nr1, nr2));
    EXPECT_TRUE(less.operator()(nr1, one));
    EXPECT_FALSE(less.operator()(one, nr1));
    EXPECT_FALSE(less.operator()(one, one));
    EXPECT_TRUE(less.operator()(zero, one));
    EXPECT_FALSE(less.operator()(one, zero));

    EXPECT_TRUE(less_equal.operator()(nr1, nr2));
    EXPECT_TRUE(less_equal.operator()(nr1, one));
    EXPECT_FALSE(less_equal.operator()(one, nr1));
    EXPECT_TRUE(less_equal.operator()(one, one));
    EXPECT_TRUE(less_equal.operator()(zero, one));
    EXPECT_FALSE(less_equal.operator()(one, zero));

    EXPECT_FALSE(greater.operator()(nr1, nr2));
    EXPECT_FALSE(greater.operator()(nr1, one));
    EXPECT_TRUE(greater.operator()(one, nr1));
    EXPECT_FALSE(greater.operator()(one, one));
    EXPECT_FALSE(greater.operator()(zero, one));
    EXPECT_TRUE(greater.operator()(one, zero));

    EXPECT_TRUE(greater_equal.operator()(nr1, nr2));
    EXPECT_FALSE(greater_equal.operator()(nr1, one));
    EXPECT_TRUE(greater_equal.operator()(one, nr1));
    EXPECT_TRUE(greater_equal.operator()(one, one));
    EXPECT_FALSE(greater_equal.operator()(zero, one));
    EXPECT_TRUE(greater_equal.operator()(one, zero));
}
