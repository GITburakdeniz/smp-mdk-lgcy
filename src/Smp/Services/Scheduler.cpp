#include "Scheduler.h"

namespace Smp {
namespace Services {

Scheduler::Scheduler()
{

}

Scheduler::~Scheduler()
{
    
}

void Scheduler::AddImmediateEvent(const IEntryPoint* entryPoint)
{

}

EventId Scheduler::AddSimulationTimeEvent(
    const IEntryPoint* entryPoint,
    const Duration simulationTime,
    const Duration cycleTime,
    const Int64 count)
{
    // FIXME
    return 0; 
}

EventId Scheduler::AddMissionTimeEvent(
    const IEntryPoint* entryPoint,
    const Duration missionTime,
    const Duration cycleTime,
    const Int64 count)
{
    // FIXME
    return 0; 
}

EventId Scheduler::AddEpochTimeEvent(
    const IEntryPoint* entryPoint,
    const DateTime epochTime,
    const Duration cycleTime,
    const Int64 count)
{
    // FIXME
    return 0; 
}

EventId Scheduler::AddZuluTimeEvent(
    const IEntryPoint* entryPoint,
    const DateTime zuluTime,
    const Duration cycleTime,
    const Int64 count)
{
    // FIXME
    return 0; 
}

void Scheduler::SetEventSimulationTime(
    const EventId event, 
    const Duration simulationTime)
{

}    

void Scheduler::SetEventMissionTime(
    const EventId event, 
    const Duration missionTime)
{

}

void Scheduler::SetEventEpochTime(
    const EventId event, 
    const DateTime epochTime)
{

}

void Scheduler::SetEventZuluTime(
    const EventId event, 
    const DateTime zuluTime)
{

}

void Scheduler::SetEventCycleTime( const EventId event, const Duration cycleTime)
{

}

void Scheduler::SetEventCount(const EventId event, const Int64 count)
{

}

void Scheduler::RemoveEvent(const EventId event)
{

}

} // end namespace Services
} // end namespace Smp