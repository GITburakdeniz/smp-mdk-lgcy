#include "CompositeTest.h"

#include "Mdk/Composite.h"

using namespace ::Smp::Mdk;

void CompositeTest::setUp(void)
{
}

void CompositeTest::tearDown(void)
{
}

void CompositeTest::testInstantiation(void)
{
    Composite* comp = new Composite();

    CPPUNIT_ASSERT(comp != NULL);

    delete comp;
}

void CompositeTest::testInterface(void)
{
    Composite* comp = new Composite();

    ::Smp::IContainer* containter1 = comp->GetContainer("");
    CPPUNIT_ASSERT_EQUAL(NULL, container1);

    ::Smp::IContainer* containter2 = comp->GetContainer(NULL);
    CPPUNIT_ASSERT_EQUAL(NULL, container2);

    ::Smp::ContainerCollection* containerCollection =
        comp->GetContainers();
    CPPUNIT_ASSERT_EQUAL(NULL, containerCollection);

    delete comp;
}
