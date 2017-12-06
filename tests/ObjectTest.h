#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "Mdk/Object.h"

class ObjectTest :
    public ::CppUnit::TestFixture
{
    public: 
        static ::CppUnit::TestSuite* suite(void);

        void setUp(void);
        void tearDown(void);

        void testInstantiation(void);
        void testInterface(void);
        void testExceptions(void);
};
