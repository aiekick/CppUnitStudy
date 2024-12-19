#include "CustomHook.h"
 #include <cppunit/tools/StringTools.h>

using namespace CppUnit;

void CustomHook::beginDocument(XmlDocument *document) {
    if (document == nullptr) {
        return;
    }

    std::string szDate = CppUnit::StringTools::toString((int)time(0));
    CppUnit::XmlElement *metaEl = new CppUnit::XmlElement("SuiteInfo", "");

    metaEl->addElement(new CppUnit::XmlElement("Author", AUTHOR));
    metaEl->addElement(new CppUnit::XmlElement("Project", PROJECT));
    metaEl->addElement(new CppUnit::XmlElement("Date", szDate));

    document->rootElement().addElement(metaEl);
}

void CustomHook::endDocument(XmlDocument *document) {
}

void CustomHook::failTestAdded(XmlDocument *document, XmlElement *testElement, Test *test, TestFailure *failure) {
    CppUnit::XmlElement *metaEl = new CppUnit::XmlElement("TestFailure", "");
    metaEl->addElement(new CppUnit::XmlElement("Name", failure->failedTestName()));
    document->rootElement().addElement(metaEl);
}

void CustomHook::successfulTestAdded(XmlDocument *document, XmlElement *testElement, Test *test) {
    auto msgIT = m_messages.find(test->getName());
    if (msgIT != m_messages.end()) {
        for (const auto &it : msgIT->second) {
            testElement->addElement(new CppUnit::XmlElement("MESSAGE", it.details()));
        }
    }
}

void CustomHook::statisticsAdded(XmlDocument *document, XmlElement *statisticsElement) {
}

void CustomHook::setTestCase(const std::string &vTestCase) {
    m_testCase = vTestCase;
}

CPPUNIT_NS::Message &CustomHook::capture(CPPUNIT_NS::Message &message) {
    m_messages[m_testCase].push_back(message);
    return message;
}

const std::string &CustomHook::capture(const std::string &message) {
    m_messages[m_testCase].push_back(CPPUNIT_NS::Message(message));
    return message;
}
