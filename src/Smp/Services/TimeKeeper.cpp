#include "TimeKeeper.h"

namespace Smp {
namespace Services {

TimeKeeper::TimeKeeper( ::Smp::String8 name,
                        ::Smp::String8 description,
                        ::Smp::IComposite* parent)
    :
        Service(name,description,parent)
{
    
}

TimeKeeper::~TimeKeeper()
{

}

Duration TimeKeeper::GetSimulationTime()
{
    // FIXME
    return 0;
}

DateTime TimeKeeper::GetEpochTime()
{
    // FIXME
    return 0;
}

Duration TimeKeeper::GetMissionTime()
{
    // FIXME
    return 0;
}

DateTime TimeKeeper::GetZuluTime()
{
    // FIXME
    return 0;
}

void TimeKeeper::SetEpochTime(const DateTime epochTime)
{
    // FIXME
}

void TimeKeeper::SetMissionStart(const DateTime missionStart)
{
    // FIXME
}

void TimeKeeper::SetMissionTime(const Duration missionTime)
{
    // FIXME
}


} // end namespace Services
} // end namespace Smp