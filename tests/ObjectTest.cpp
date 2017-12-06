#include "ObjectTest.h"

#include "Mdk/Object.h"

using namespace ::Smp::Mdk;

::CppUnit::TestSuite* ObjectTest::suite(void)
{
    ::CppUnit::TestSuite* suite = new ::CppUnit::TestSuite("EntryPointTests");

    suite->addTest(new ::CppUnit::TestCaller< ObjectTest>( 
                "testInstantiation",
                &ObjectTest::testInstantiation));
    suite->addTest(new ::CppUnit::TestCaller< ObjectTest>(
                "testInterface",
                &ObjectTest::testInterface));
    suite->addTest(new ::CppUnit::TestCaller< ObjectTest>(
                "testExceptions",
                &ObjectTest::testExceptions));

    return suite;
}

void ObjectTest::setUp(void)
{
}

void ObjectTest::tearDown(void)
{
}

void ObjectTest::testInstantiation(void)
{
    Object* obj1 = new Object();

    CPPUNIT_ASSERT(obj1 != NULL);

    delete obj1;

    Object* obj2 = new Object("ObjectName", "Object description");

    CPPUNIT_ASSERT(obj2 != NULL);

    delete obj2;
}

void ObjectTest::testInterface(void)
{
    {
        ::std::string nameGiven("");
        ::std::string descGiven("");

        const Object* obj1 = new Object();

        ::std::string nameGot = obj1->GetName();
        CPPUNIT_ASSERT_EQUAL(nameGiven, nameGot);

        ::std::string descGot = obj1->GetDescription();
        CPPUNIT_ASSERT_EQUAL(descGiven, descGot);

        delete obj1;
    }

    {
        ::std::string nameGiven("ObjectName");
        ::std::string descGiven("Object description");

        const Object* obj2 = new Object(
                nameGiven.c_str(),
                descGiven.c_str());

        ::std::string nameGot = obj2->GetName();
        CPPUNIT_ASSERT_EQUAL(nameGiven, nameGot);

        ::std::string descGot = obj2->GetDescription();
        CPPUNIT_ASSERT_EQUAL(descGiven, descGot);

        delete obj2;
    }
}

void ObjectTest::testExceptions(void)
{
    bool exceptionCatched = false;

    try {
        const Object* obj = new Object("", "");
        delete obj;
    } catch (::Smp::InvalidObjectName& ex) {
        exceptionCatched = true;
    }

    CPPUNIT_ASSERT_EQUAL(true, exceptionCatched);
}
