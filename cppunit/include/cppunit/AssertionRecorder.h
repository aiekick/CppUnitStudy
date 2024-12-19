#pragma once

#include <cppunit/Portability.h>
#include <cppunit/Message.h>
#include <vector>
#include <string>
#include <exception>
#include <iostream>

CPPUNIT_NS_BEGIN

class CPPUNIT_API AssertionRecorderException : public std::exception {
private:
    std::vector<Message> m_messages;

public:
    explicit AssertionRecorderException(const std::vector<Message>& messages);
    const char* what() const noexcept override;
    const std::vector<Message>& messages() const;
};

class CPPUNIT_API AssertionRecorder {
private:
    std::vector<Message> m_messages;

public:
    AssertionRecorder();
    ~AssertionRecorder();

    Message record(Message message);
    AssertionRecorderException createException() const;
};

CPPUNIT_NS_END
