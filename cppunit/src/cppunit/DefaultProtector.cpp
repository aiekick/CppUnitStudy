#include <cppunit/Exception.h>
#include <cppunit/extensions/TypeInfoHelper.h>
#include "DefaultProtector.h"
#include <cppunit/AssertionRecorder.h>

CPPUNIT_NS_BEGIN

bool DefaultProtector::protect(const Functor &functor, const ProtectorContext &context) {
    try {
        return functor();
    } catch (const CPPUNIT_NS::AssertionRecorderException &ex) {
        for (const auto &msg : ex.messages()) {
            std::cout << msg.details() << std::endl;
        }
    } catch (Exception &failure) {
        reportFailure(context, failure);
    } catch (std::exception &e) {
        std::string shortDescription("uncaught exception of type ");
#if defined(CPPUNIT_USE_TYPEINFO_NAME)
        shortDescription += TypeInfoHelper::getClassName(typeid(e));
#else
        shortDescription += "std::exception (or derived).";
#endif
        Message message(shortDescription, e.what());
        reportError(context, message);
    } catch (...) {
        reportError(context, Message("uncaught exception of unknown type"));
    }

    return false;
}

CPPUNIT_NS_END
