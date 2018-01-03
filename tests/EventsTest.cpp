#include "EventsTest.h"

#include "Mdk/EventSource.h"
#include "Mdk/EventSink.h"

#include "Smp/IObject.h"

using namespace ::Smp::Mdk;

class Target
{
    public:
        Target(void);
        virtual ~Target(void);

        void EventCallback(
                ::Smp::IObject* sender,
                ::Smp::AnySimple arg);

        const ::Smp::IObject* get_LastSender(void) const;
        const ::Smp::AnySimple& get_LastArg(void) const;

    private:
        ::Smp::IObject* lastSender;
        ::Smp::AnySimple lastArg;
};

Target::Target(void)
{
}

Target::~Target(void)
{
}

void Target::EventCallback(
        ::Smp::IObject* sender,
        ::Smp::AnySimple arg)
{
    this->lastSender = sender;
    this->lastArg = arg;
}

const ::Smp::IObject* Target::get_LastSender(void) const
{
    return this->lastSender;
}

const ::Smp::AnySimple& Target::get_LastArg(void) const
{
    return this->lastArg;
}

class EventProducer :
    public virtual ::Smp::IObject
{
    public:
        EventProducer(void) {}
        virtual ~EventProducer(void) {}

        ::Smp::String8 GetName(void) const { return NULL; }
        ::Smp::String8 GetDescription(void) const { return NULL; }
};

void EventsTest::setUp(void)
{
}

void EventsTest::tearDown(void)
{
}

void EventsTest::testInstantiation(void)
{
    {
        Target* consumer = new Target();
        EventSink* eventSink = new EventSink(
                "Name", "Description", consumer,
                &Target::EventCallback);

        CPPUNIT_ASSERT(eventSink != NULL);

        delete eventSink;
        delete consumer;
    }
}
