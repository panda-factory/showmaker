//
// Created by guozhenxiong on 2021-11-05.
//

#include "gtest/gtest.h"

#include "wtf/meta/meta.h"

using namespace sm::meta;

class Base : public Meta {
    DECLARE_META_INFO(Base, Meta);
};

class Sub : public Base {
    DECLARE_META_INFO(Sub, Base);
};

TEST(TYPE_META, CastFromBaseToBase)
{
    std::unique_ptr<Base> object = std::make_unique<Base>();

    Base* ptr = Traits<Base*>::Cast(object.get());
    EXPECT_EQ(ptr, object.get());
}

TEST(TYPE_META, CastFromBaseToSub)
{
    std::unique_ptr<Base> object = std::make_unique<Sub>();

    Sub* ptr = Traits<Sub*>::Cast(object.get());
    EXPECT_EQ(ptr, object.get());
}

TEST(TYPE_META, CastFromSubToSub)
{
    std::unique_ptr<Sub> object = std::make_unique<Sub>();

    Sub* ptr = Traits<Sub*>::Cast(object.get());
    EXPECT_EQ(ptr, object.get());
}

TEST(TYPE_META, CastFromSubToBase)
{
    std::unique_ptr<Sub> object = std::make_unique<Sub>();

    Base* ptr = Traits<Base*>::Cast(object.get());
    EXPECT_EQ(ptr, object.get());
}

class Other : public Meta {
    DECLARE_META_INFO(Other, Meta);
};

TEST(TYPE_META, CastFromSubToOther)
{
    std::unique_ptr<Base> object = std::make_unique<Sub>();

    Other* ptr = Traits<Other*>::Cast(object.get());
    EXPECT_EQ(ptr, nullptr);
}

TEST(TYPE_META, CastFromOtherToBase)
{
    std::unique_ptr<Other> object = std::make_unique<Other>();

    Base* ptr = Traits<Base*>::Cast(object.get());
    EXPECT_EQ(ptr, nullptr);
}

TEST(TYPE_META, CastFromOtherToSub)
{
    std::unique_ptr<Other> object = std::make_unique<Other>();

    Sub* ptr = Traits<Sub*>::Cast(object.get());
    EXPECT_EQ(ptr, nullptr);
}