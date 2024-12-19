#pragma once

#include <cppunit/XmlOutputterHook.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <cppunit/tools/XmlDocument.h>
#include <cppunit/tools/XmlElement.h>
#include <cppunit/Message.h>
#include <memory>
#include <vector>
#include <string>
#include <map>

class CustomHook : public CppUnit::XmlOutputterHook {
private:
    std::string m_testCase;
    std::map<std::string, std::vector<CPPUNIT_NS::Message>> m_messages;

public:
    ~CustomHook() override = default;
    void beginDocument(CppUnit::XmlDocument *document) override;
    void endDocument(CppUnit::XmlDocument *document) override;
    void failTestAdded(CppUnit::XmlDocument *document, CppUnit::XmlElement *testElement, CppUnit::Test *test, CppUnit::TestFailure *failure) override;
    void successfulTestAdded(CppUnit::XmlDocument *document, CppUnit::XmlElement *testElement, CppUnit::Test *test) override;
    void statisticsAdded(CppUnit::XmlDocument *document, CppUnit::XmlElement *statisticsElement) override;

    void setTestCase(const std::string &vTestCase);
    CPPUNIT_NS::Message &capture(CPPUNIT_NS::Message &message);
    const std::string &capture(const std::string & message);

public:
    static CustomHook* instance() {
        static auto _instance = std::unique_ptr<CustomHook>(new CustomHook());
        return _instance.get();
    }
};

#include <cppunit/TestAssert.h>

#ifdef CPPUNIT_ASSERT_MESSAGE
#undef CPPUNIT_ASSERT_MESSAGE
#define CPPUNIT_ASSERT_MESSAGE(message, condition)                                                                                                   \
    (CPPUNIT_NS::Asserter::failIf(                                                                                                                   \
        !(condition),                                                                                                                                \
        CustomHook::instance()->capture(CPPUNIT_NS::Message("assertion failed", "Expression: " #condition, CPPUNIT_NS::message_to_string(message))), \
        CPPUNIT_SOURCELINE()))
#endif  // CPPUNIT_ASSERT_MESSAGE

#ifdef CPPUNIT_ASSERT_EQUAL_MESSAGE
#undef CPPUNIT_ASSERT_EQUAL_MESSAGE
#define CPPUNIT_ASSERT_EQUAL_MESSAGE(message, expected, actual) \
    (CPPUNIT_NS::assertEquals((expected), (actual), CPPUNIT_SOURCELINE(), \
     CustomHook::instance()->capture(CPPUNIT_NS::message_to_string(message))))
#endif  // CPPUNIT_ASSERT_EQUAL_MESSAGE
