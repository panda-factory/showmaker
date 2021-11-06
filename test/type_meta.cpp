//
// Created by guozhenxiong on 2021-11-05.
//

#include "gtest/gtest.h"

#include "wtf/meta/type_decriptor.h"

using namespace sm::meta;

TEST(TYPE_META, VOID_TYPE)
{
    std::string descriptor = TypeDescriptor<void>::Descriptor();
    EXPECT_EQ("void", descriptor);
    descriptor = TypeDescriptor<void*>::Descriptor();
    EXPECT_EQ("void*", descriptor);
    descriptor = TypeDescriptor<const void*>::Descriptor();
    EXPECT_EQ("const void*", descriptor);
}

TEST(TYPE_META, INT_TYPE)
{
    std::string descriptor = TypeDescriptor<int>::Descriptor();
    EXPECT_EQ("int", descriptor);
    descriptor = TypeDescriptor<int*>::Descriptor();
    EXPECT_EQ("int*", descriptor);
    descriptor = TypeDescriptor<const int*>::Descriptor();
    EXPECT_EQ("const int*", descriptor);
    descriptor = TypeDescriptor<int&>::Descriptor();
    EXPECT_EQ("int&", descriptor);
    descriptor = TypeDescriptor<const int&>::Descriptor();
    EXPECT_EQ("const int&", descriptor);
}

TEST(TYPE_META, INT64_TYPE)
{
    std::string descriptor = TypeDescriptor<int64_t>::Descriptor();
    EXPECT_EQ("int64_t", descriptor);
    descriptor = TypeDescriptor<int64_t*>::Descriptor();
    EXPECT_EQ("int64_t*", descriptor);
    descriptor = TypeDescriptor<const int64_t*>::Descriptor();
    EXPECT_EQ("const int64_t*", descriptor);
    descriptor = TypeDescriptor<int64_t&>::Descriptor();
    EXPECT_EQ("int64_t&", descriptor);
    descriptor = TypeDescriptor<const int64_t&>::Descriptor();
    EXPECT_EQ("const int64_t&", descriptor);
}

TEST(TYPE_META, CHAR_TYPE)
{
    std::string descriptor = TypeDescriptor<char>::Descriptor();
    EXPECT_EQ("char", descriptor);
    descriptor = TypeDescriptor<char*>::Descriptor();
    EXPECT_EQ("char*", descriptor);
    descriptor = TypeDescriptor<const char*>::Descriptor();
    EXPECT_EQ("const char*", descriptor);
    descriptor = TypeDescriptor<char&>::Descriptor();
    EXPECT_EQ("char&", descriptor);
    descriptor = TypeDescriptor<const char&>::Descriptor();
    EXPECT_EQ("const char&", descriptor);
}

TEST(TYPE_META, INT8_TYPE)
{
    std::string descriptor = TypeDescriptor<int8_t>::Descriptor();
    EXPECT_EQ("int8_t", descriptor);
    descriptor = TypeDescriptor<int8_t*>::Descriptor();
    EXPECT_EQ("int8_t*", descriptor);
    descriptor = TypeDescriptor<const int8_t*>::Descriptor();
    EXPECT_EQ("const int8_t*", descriptor);
    descriptor = TypeDescriptor<int8_t&>::Descriptor();
    EXPECT_EQ("int8_t&", descriptor);
    descriptor = TypeDescriptor<const int8_t&>::Descriptor();
    EXPECT_EQ("const int8_t&", descriptor);
}

TEST(TYPE_META, SHORT_TYPE)
{
    std::string descriptor = TypeDescriptor<short>::Descriptor();
    EXPECT_EQ("short", descriptor);
    descriptor = TypeDescriptor<short*>::Descriptor();
    EXPECT_EQ("short*", descriptor);
    descriptor = TypeDescriptor<const short*>::Descriptor();
    EXPECT_EQ("const short*", descriptor);
    descriptor = TypeDescriptor<short&>::Descriptor();
    EXPECT_EQ("short&", descriptor);
    descriptor = TypeDescriptor<const short&>::Descriptor();
    EXPECT_EQ("const short&", descriptor);
}

TEST(TYPE_META, FLOAT_TYPE)
{
    std::string descriptor = TypeDescriptor<float>::Descriptor();
    EXPECT_EQ("float", descriptor);
    descriptor = TypeDescriptor<float*>::Descriptor();
    EXPECT_EQ("float*", descriptor);
    descriptor = TypeDescriptor<const float*>::Descriptor();
    EXPECT_EQ("const float*", descriptor);
    descriptor = TypeDescriptor<float&>::Descriptor();
    EXPECT_EQ("float&", descriptor);
    descriptor = TypeDescriptor<const float&>::Descriptor();
    EXPECT_EQ("const float&", descriptor);
}

TEST(TYPE_META, DOUBLE_TYPE)
{
    std::string descriptor = TypeDescriptor<double>::Descriptor();
    EXPECT_EQ("double", descriptor);
    descriptor = TypeDescriptor<double*>::Descriptor();
    EXPECT_EQ("double*", descriptor);
    descriptor = TypeDescriptor<const double*>::Descriptor();
    EXPECT_EQ("const double*", descriptor);
    descriptor = TypeDescriptor<double&>::Descriptor();
    EXPECT_EQ("double&", descriptor);
    descriptor = TypeDescriptor<const double&>::Descriptor();
    EXPECT_EQ("const double&", descriptor);
}

TEST(TYPE_META, BOOL_TYPE)
{
    std::string descriptor = TypeDescriptor<bool>::Descriptor();
    EXPECT_EQ("bool", descriptor);
    descriptor = TypeDescriptor<bool*>::Descriptor();
    EXPECT_EQ("bool*", descriptor);
    descriptor = TypeDescriptor<const bool*>::Descriptor();
    EXPECT_EQ("const bool*", descriptor);
    descriptor = TypeDescriptor<bool&>::Descriptor();
    EXPECT_EQ("bool&", descriptor);
    descriptor = TypeDescriptor<const bool&>::Descriptor();
    EXPECT_EQ("const bool&", descriptor);
}