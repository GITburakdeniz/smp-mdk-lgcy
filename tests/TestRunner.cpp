#include <cppunit/ui/text/TestRunner.h>

#include "ObjectTest.h"
#include "EntryPointTest.h"
#include "EventsTest.h"
#include "UuidTest.h"
#include "ArrayTest.h"
#include "StringTest.h"

int main(int argc, char* argv[])
{
    ::CppUnit::TextUi::TestRunner runner;

    runner.addTest(ObjectTest::suite());
    runner.addTest(EntryPointTest::suite());
    runner.addTest(EventsTest::suite());
    runner.addTest(UuidTest::suite());
    runner.addTest(ArrayTest::suite());
    runner.addTest(StringTest::suite());
    bool testResult = runner.run();

    return testResult ? 0 : 1;
}
