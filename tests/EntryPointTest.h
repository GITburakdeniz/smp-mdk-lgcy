#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/Test.h>

class EntryPointTest :
    public ::CppUnit::TestFixture
{
    public: 
        static ::CppUnit::Test* suite(void);

        void setUp(void);
        void tearDown(void);

        void testInstantiation(void);
        void testExecution(void);
};
