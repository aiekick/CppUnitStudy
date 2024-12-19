#include <cppunit/AssertionRecorder.h>
#include <vector>
#include <string>
#include <exception>
#include <iostream>

#include <cppunit/TestFixture.h>

CPPUNIT_NS_BEGIN

thread_local AssertionRecorder* TestFixture::mp_assertionRecorder = nullptr;

AssertionRecorderException::AssertionRecorderException(const std::vector<Message>& messages) : m_messages(messages) {
}

const char* AssertionRecorderException::what() const noexcept {
    return "AssertionRecorderException: Assertion results are available in messages.";
}

const std::vector<Message>& AssertionRecorderException::messages() const {
    return m_messages;
}

AssertionRecorder::AssertionRecorder() = default;

AssertionRecorder ::~AssertionRecorder() {
}

Message AssertionRecorder::record(Message message) {
    m_messages.push_back(message);
    return message;
}

AssertionRecorderException AssertionRecorder::createException() const {
    return AssertionRecorderException(m_messages);
}

CPPUNIT_NS_END
