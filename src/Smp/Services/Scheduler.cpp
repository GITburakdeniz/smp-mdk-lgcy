#include "Scheduler.h"

namespace Smp {
namespace Services {

HWTimedEvent::HWTimedEvent(  boost::asio::io_service& ioservice,
                             int offsetInterval, 
                             int count,
                             int interval,
                             const IEntryPoint* entryPoint,
                             EventId eventId,
                             std::map<EventId,std::shared_ptr<HWTimedEvent>>& events)
    :           
      m_timer(ioservice)
    , m_entryPoint(entryPoint)
    , m_offsetInterval(offsetInterval)
    , m_count(count)
    , m_interval(interval)
    , m_eventId(eventId)
    , m_events(events)
{
    // Schedule start to be ran by the io_service
    ioservice.post(boost::bind(&HWTimedEvent::start, this));    
}

HWTimedEvent::~HWTimedEvent() 
{
    std::cout << "Event destroyed" << std::endl;
}


void HWTimedEvent::execute(boost::system::error_code const& ec)
{
    if (!ec)
    {
        if (m_count)
        {
            m_timer.expires_at( m_timer.expires_at() + boost::posix_time::milliseconds(m_interval) );
            this->startWait();

            // -1 is infinite
            if( m_count != -1 )
            {
                m_count--;
            }
        }
        else
        {
            m_events.erase(m_eventId);
        }
        m_entryPoint->Execute();
    }
    else
    {
        if ( boost::asio::error::operation_aborted == ec) 
        {
            // FIXME
            std::cerr << "Operation aborted" << std::endl;            
        }
        else 
        {
            // FIXME
            std::cerr << "Other error" << std::endl;
            
        }

        m_events.erase(m_eventId);
    }
}

void HWTimedEvent::start()
{
    m_timer.expires_from_now(boost::posix_time::milliseconds(m_offsetInterval));
    this->startWait();
}

void HWTimedEvent::cancel()
{
    m_timer.cancel();
}


void HWTimedEvent::startWait()
{
    m_timer.async_wait(boost::bind(&HWTimedEvent::execute
        , this
        , boost::asio::placeholders::error));
}

Scheduler::Scheduler(::Smp::String8 name,
                     ::Smp::String8 description,
                     ::Smp::IComposite* parent)
    :
          Service(name,description,parent)
        , m_isRunning(false)
        , eventIdCounter(0)
{

}

Scheduler::~Scheduler()
{
    this->stop();   
}

void Scheduler::AddImmediateEvent(const IEntryPoint* entryPoint)
{
    if(m_isRunning)
    {
        // aquire mutex
        EventId eventId = ++eventIdCounter;
        m_events[eventId] = std::make_shared<HWTimedEvent>( *m_ioservice, 
                                                            0, 
                                                            1,
                                                            0, 
                                                            this,
                                                            eventId, m_events );
    }
    else
    {
        std::cerr << "Inmediate events are only supported when running" << std::endl;
    }
}

EventId Scheduler::AddSimulationTimeEvent(
    const IEntryPoint* entryPoint,
    const Duration simulationTime,
    const Duration cycleTime,
    const Int64 count)
{
    if(m_isRunning)
    {
        // TODO: aquire lock
        // TODO: convert simulationTime
        // TODO: convert cycleTime
        EventId eventId = ++eventIdCounter;
        m_events[eventId] = std::make_shared<HWTimedEvent>( *m_ioservice, 
                                                            0,              // converted simulationTime
                                                            count,
                                                            1000,              // convert cycleTime
                                                            this,
                                                            eventId, m_events );
    }   
    else
    {
        // TODO
    }
    
    return 0; 
}

EventId Scheduler::AddMissionTimeEvent(
    const IEntryPoint* entryPoint,
    const Duration missionTime,
    const Duration cycleTime,
    const Int64 count)
{
    // Unsupported
    return 0; 
}

EventId Scheduler::AddEpochTimeEvent(
    const IEntryPoint* entryPoint,
    const DateTime epochTime,
    const Duration cycleTime,
    const Int64 count)
{
    // Unsupported
    return 0; 
}

EventId Scheduler::AddZuluTimeEvent(
    const IEntryPoint* entryPoint,
    const DateTime zuluTime,
    const Duration cycleTime,
    const Int64 count)
{
    // Unsupported
    return 0; 
}

void Scheduler::SetEventSimulationTime(
    const EventId event, 
    const Duration simulationTime)
{
    // This is not so straightforward in HIL.
    // Unsupported
}    

void Scheduler::SetEventMissionTime(
    const EventId event, 
    const Duration missionTime)
{
    // This is not so straightforward in HIL.
    // Unsupported
}

void Scheduler::SetEventEpochTime(
    const EventId event, 
    const DateTime epochTime)
{
    // This is not so straightforward in HIL.
    // Unsupported
}

void Scheduler::SetEventZuluTime(
    const EventId event, 
    const DateTime zuluTime)
{
    // This is not so straightforward in HIL.
    // Unsupported
}

void Scheduler::SetEventCycleTime( const EventId event, const Duration cycleTime)
{
    // This is not so useful in HIL.
    // Unsupported
}

void Scheduler::SetEventCount(const EventId event, const Int64 count)
{
    // This is not so useful in HIL.
    // Unsupported
}

void Scheduler::RemoveEvent(const EventId event)
{
    // FIXME: lock!
    m_events[event]->cancel();
}


void Scheduler::start()
{
    if(m_isRunning)
    {
        return;
    }

    m_ioservice = std::make_unique<boost::asio::io_service>();
    m_work = std::make_unique<boost::asio::io_service::work>(*m_ioservice);
    m_isRunning = true;

    // All events registered by the scheduler should be actually scheduled in the HW clock.
    EventId eventId = eventIdCounter;
    m_events[eventId] = std::make_shared<HWTimedEvent>( *m_ioservice, 
                                                        0,          // offsetInterval
                                                        -1,         // count (-1=infinite)
                                                        1000,       // cycleTime (ms)
                                                        this,       // EntryPoint
                                                        eventId, m_events ); 
    eventIdCounter++;
    m_workingThread = std::make_unique<std::thread>([this]() { m_ioservice->run(); } );    
}

void Scheduler::stop()
{
    if(!m_isRunning)
    {
        return;
    }

    // WARNING All scheduled events will be lost!
    if (m_events.size() > 0 )
    {
        
    }

    m_ioservice->stop();
    m_workingThread->join();
    m_isRunning = false;
}


// FIXME: Scheduler owns an entrypoint to use as synchonizer, etc.
// Requires Execute() and GetOwner()
void Scheduler::Execute() const
{
    std::cout << "Synch event" << std::endl;
}

Smp::IComponent* Scheduler::GetOwner() const
{
    return nullptr;
}

} // end namespace Services
} // end namespace Smp