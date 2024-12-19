#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

class Test1 : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(Test1);
    CPPUNIT_TEST(test1Case1);
    CPPUNIT_TEST(test1Case2);
    CPPUNIT_TEST(test1Case3);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;
    void tearDown() override;
        
private:
    void test1Case1();
    void test1Case2();
    void test1Case3();
};
