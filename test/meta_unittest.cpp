//
// Created by guozhenxiong on 2021-11-05.
//

#include "gtest/gtest.h"

#include "wtf/meta/meta.h"

using namespace sm;

class Base : public meta::Meta {
    DECLARE_META_INFO(Base, meta::Meta);
};

class Sub : public Base {
    DECLARE_META_INFO(Sub, Base);
};

class SubSub : public Sub {
    DECLARE_META_INFO(SubSub, Sub);

};

TEST(TYPE_META, CastFromBaseToBase)
{
    std::unique_ptr<Base> object = std::make_unique<Base>();

    Base* ptr = meta::Traits<Base*>::Cast(object.get());
    EXPECT_EQ(ptr, object.get());
}

TEST(TYPE_META, CastFromBaseToSub)
{
    std::unique_ptr<Base> object = std::make_unique<Sub>();

    Sub* ptr = meta::Traits<Sub*>::Cast(object.get());
    EXPECT_EQ(ptr, object.get());
}

TEST(TYPE_META, CastFromSubToSub)
{
    std::unique_ptr<Sub> object = std::make_unique<Sub>();

    Sub* ptr = meta::Traits<Sub*>::Cast(object.get());
    EXPECT_EQ(ptr, object.get());
}

TEST(TYPE_META, CastFromSubToBase)
{
    std::unique_ptr<Sub> object = std::make_unique<Sub>();

    Base* ptr = meta::Traits<Base*>::Cast(object.get());
    EXPECT_EQ(ptr, object.get());
}

TEST(TYPE_META, CastFromBaseToSubSub)
{
    std::unique_ptr<Base> object = std::make_unique<SubSub>();

    SubSub* ptr = meta::Traits<SubSub*>::Cast(object.get());
    EXPECT_EQ(ptr, object.get());
}

class Other : public meta::Meta {
    DECLARE_META_INFO(Other, meta::Meta);
};

TEST(TYPE_META, CastFromSubToOther)
{
    std::unique_ptr<Base> object = std::make_unique<Sub>();

    Other* ptr = meta::Traits<Other*>::Cast(object.get());
    EXPECT_EQ(ptr, nullptr);
}

TEST(TYPE_META, CastFromOtherToBase)
{
    std::unique_ptr<Other> object = std::make_unique<Other>();

    Base* ptr = meta::Traits<Base*>::Cast(object.get());
    EXPECT_EQ(ptr, nullptr);
}

TEST(TYPE_META, CastFromOtherToSub)
{
    std::unique_ptr<Other> object = std::make_unique<Other>();

    Sub* ptr = meta::Traits<Sub*>::Cast(object.get());
    EXPECT_EQ(ptr, nullptr);
}

class Base1 : virtual public meta::Meta {
    DECLARE_META_INFO(Base1, meta::Meta);
};

class Base2 : virtual public meta::Meta {
    DECLARE_META_INFO(Base2, meta::Meta);
};

class Derived1 : public Base1 {
    DECLARE_META_INFO(Derived1 , Base1);
};

class Derived2 : public Base2 {
    DECLARE_META_INFO(Derived2 , Base2);
};

class Derived12 : public Derived1, public Derived2 {
    DECLARE_META_INFO(Derived12 ,Derived1, Derived2);
};

TEST(TYPE_META, MultiDerived)
{
    Derived12* derived12 = new Derived12();

    Base1* b1 = derived12;
    Base2* b2 = derived12;
    Derived1* d1 = derived12;
    Derived2* d2 = derived12;
    EXPECT_EQ(b1, meta::Traits<Base1*>::Cast(derived12));
    EXPECT_EQ(b2, meta::Traits<Base2*>::Cast(derived12));
    EXPECT_EQ(d1, meta::Traits<Derived1*>::Cast(derived12));
    EXPECT_EQ(d2, meta::Traits<Derived2*>::Cast(derived12));
    delete derived12;

    d1 = new Derived1();
    EXPECT_EQ(nullptr, meta::Traits<Derived12*>::Cast(d1));
    delete d1;

    d2 = new Derived2();
    EXPECT_EQ(nullptr, meta::Traits<Derived12*>::Cast(d2));
    delete d2;

}