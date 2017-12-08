#include <cppunit/ui/text/TestRunner.h>

#include "ObjectTest.h"
#include "EntryPointTest.h"

int main(int argc, char* argv[])
{
    ::CppUnit::TextUi::TestRunner runner;

    runner.addTest(ObjectTest::suite());
    runner.addTest(EntryPointTest::suite());
    bool testResult = runner.run();

    return testResult ? 0 : 1;
}
