#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class EntryPointTest :
    public ::CppUnit::TestFixture
{
    public: 
        static ::CppUnit::Test* suite(void)
        {
            ::CppUnit::TestSuite* suite = new ::CppUnit::TestSuite("EntryPointTests");

            suite->addTest(new ::CppUnit::TestCaller< EntryPointTest>( 
                        "testInstantiation",
                        &EntryPointTest::testInstantiation ) );

            return suite;
        }

        void setUp(void)
        {
        }

        void tearDown(void)
        {
        }

        void testInstantiation(void)
        {
            CPPUNIT_ASSERT(false);
        }
};
