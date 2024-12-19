#include "test1.h"
#include <cppunit/TestAssert.h>
#include <CustomHook.h>

CPPUNIT_TEST_SUITE_REGISTRATION(Test1);


void Test1::setUp() {
    TestFixture::setUp();
}

void Test1::tearDown() {
    TestFixture::tearDown();
}

/*
AAAAAAAAAAAAAAAAAAAAAAA
BBBBBBBBBBBBBBBBBBBBBBB
CCCCCCCCCCCCCCCCCCCCCCC
*/
void Test1::test1Case1() {
    CustomHook::instance()->setTestCase(__FUNCTION__);
    int a = 1;
    ++a;
    CPPUNIT_ASSERT_MESSAGE("A==2", a == 2);
    --a;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("A==1", a, 1);
}


// AAAAAAAAAAAAAAAAAAAAAAA
// BBBBBBBBBBBBBBBBBBBBBBB
// CCCCCCCCCCCCCCCCCCCCCCC

void Test1::test1Case2() {
    CustomHook::instance()->setTestCase(__FUNCTION__);
    int a = 1;
    ++a;
    CPPUNIT_ASSERT_MESSAGE("A==2", a == 2);
    --a;
    CPPUNIT_ASSERT_MESSAGE("A==1", a == 1);
}

// AAAAAAAAAAAAAAAAAAAAAAA
void Test1::test1Case3() {
    CustomHook::instance()->setTestCase(__FUNCTION__);
    int a = 1;
    ++a;
    CPPUNIT_ASSERT_MESSAGE("A==2", a == 2);
    --a;
    CPPUNIT_NS::Asserter::failIf(  //
        !(a == 0),
        CPPUNIT_NS::Message(  //
            "assertion failed",
            "Expression: "
            "a == 0",
            CPPUNIT_NS::message_to_string("A==1")),
        CPPUNIT_SOURCELINE());
}
