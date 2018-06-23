#include "ManagedContainerTest.h"

#include "Mdk/Management/ManagedContainer.h"

using namespace ::Smp::Mdk::Management;

class ComponentStub :
    public ::Smp::IComponent
{
    public:
        ComponentStub(
                ::Smp::String8 name,
                ::Smp::String8 desc,
                ::Smp::IComposite* parent) :
            _name(name),
            _desc(desc)
        {
        }

        virtual ~ComponentStub(void)
        {
        }

        virtual ::Smp::String8 GetName(void) const
        {
            return this->_name.c_str();
        }

        virtual ::Smp::String8 GetDescription(void) const
        {
            return this->_desc.c_str();
        }

        virtual ::Smp::IComposite* GetParent(void) const
        {
            return NULL;
        }

    private:
        ::std::string _name;
        ::std::string _desc;
};

class OtherComponentStub :
    public ::Smp::IComponent
{
    public:
        OtherComponentStub(
                ::Smp::String8 name,
                ::Smp::String8 desc,
                ::Smp::IComposite* parent) :
            _name(name),
            _desc(desc)
        {
        }

        virtual ~OtherComponentStub(void)
        {
        }

        virtual ::Smp::String8 GetName(void) const
        {
            return this->_name.c_str();
        }

        virtual ::Smp::String8 GetDescription(void) const
        {
            return this->_desc.c_str();
        }

        virtual ::Smp::IComposite* GetParent(void) const
        {
            return NULL;
        }

    private:
        ::std::string _name;
        ::std::string _desc;
};

void ManagedContainerTest::setUp(void)
{
}

void ManagedContainerTest::tearDown(void)
{
}

void ManagedContainerTest::testInstantiation(void)
{
    ManagedContainer< ComponentStub>* cont1 =
        new ManagedContainer< ComponentStub>("Cont1", "ManagedContainer 1", NULL);

    CPPUNIT_ASSERT(cont1 != NULL);

    delete cont1;
}

void ManagedContainerTest::testPublicInterface(void)
{
    ManagedContainer< ComponentStub>* cont1 =
        new ManagedContainer< ComponentStub>("cont1", "ManagedContainer 1", NULL);
    CPPUNIT_ASSERT(cont1 != NULL);

    /*
    CPPUNIT_ASSERT_EQUAL(::Smp::Int64(0), cont1->Count());
    CPPUNIT_ASSERT(cont1->Begin() == cont1->End());

    ComponentStub* comp1 = new ComponentStub("Comp1", "Comp 1", NULL);
    cont1->AddPublic(comp1);
    CPPUNIT_ASSERT_EQUAL(::Smp::Int64(1), cont1->Count());
    CPPUNIT_ASSERT(cont1->Begin() != cont1->End());

    ComponentStub* comp2 = new ComponentStub("Comp2", "Comp 2", NULL);
    cont1->AddPublic(comp2);
    CPPUNIT_ASSERT_EQUAL(::Smp::Int64(2), cont1->Count());
    CPPUNIT_ASSERT(cont1->Begin() != cont1->End());

    {
        ::Smp::IComponent* comp = cont1->GetComponent("Comp1");
        CPPUNIT_ASSERT_EQUAL(dynamic_cast< ::Smp::IComponent*>(comp1), comp);

        ComponentStub* child = cont1->GetChild("Comp1");
        CPPUNIT_ASSERT_EQUAL(comp1, child);
    }

    {
        ::Smp::IComponent* comp = cont1->GetComponent("Comp2");
        CPPUNIT_ASSERT_EQUAL(dynamic_cast< ::Smp::IComponent*>(comp2), comp);

        ComponentStub* child = cont1->GetChild("Comp2");
        CPPUNIT_ASSERT_EQUAL(comp2, child);
    }

    {
        ::Smp::IComponent* comp = cont1->GetComponent("Comp3");
        CPPUNIT_ASSERT(comp == NULL);

        ComponentStub* child = cont1->GetChild("Comp3");
        CPPUNIT_ASSERT(child == NULL);
    }

    cont1->Clear();
    CPPUNIT_ASSERT_EQUAL(::Smp::Int64(0), cont1->Count());
    */

    delete cont1;
}
