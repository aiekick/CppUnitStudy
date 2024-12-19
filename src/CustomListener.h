#pragma once

#include <cppunit/TestListener.h>
#include <cppunit/TestFailure.h>
#include <iostream>
#include <vector>
#include <string>
#include <cppunit/Exception.h>

class CustomTestListener : public CppUnit::TestListener {
public:
    struct AssertionResult {
        std::string testName;
        std::string message;
        bool success;
    };

    std::vector<AssertionResult> results;

    void startTest(CppUnit::Test *test) override {
        currentTest = test->getName();
    }

    void addFailure(const CppUnit::TestFailure &failure) override {
        results.push_back({currentTest, failure.thrownException()->what(), false});
    }

    void addSuccessfulTest() {
        results.push_back({currentTest, "Assertion passed", true});
    }

    void printReport() const {
        for (const auto &result : results) {
            std::cout << result.testName << " : " 
                      << (result.success ? "SUCCESS" : "FAILURE") 
                      << " - " << result.message << std::endl;
        }
    }

private:
    std::string currentTest;
};
