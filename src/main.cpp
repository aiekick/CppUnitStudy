#include <iostream>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TestResultCollector.h>
#include "CustomHook.h"
#include "CustomListener.h"
#include <cppunit/TestResult.h>

int main(int vArgc, char** vArgv) {
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    CppUnit::TextUi::TestRunner runner;

    CustomTestListener listener;
    runner.eventManager().addListener(&listener);

    runner.addTest(registry.makeTest());
    runner.run("", false);
    std::ofstream xmlFile("cppunit_report.xml");
    CppUnit::XmlOutputter xmlOut(&runner.result(), xmlFile);
    xmlOut.addHook(CustomHook::instance());
    xmlOut.write();
    xmlFile.close();
    listener.printReport();
    return runner.result().wasSuccessful() ? 0 : 1;
}
