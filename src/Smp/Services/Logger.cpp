#include "Logger.h"

#include <iostream>

namespace Smp {
namespace Services {

Logger::Logger( ::Smp::String8 name,
                ::Smp::String8 description,
                ::Smp::IComposite* parent)
    :
        Service(name,description,parent)
{

}

Logger::~Logger()
{

}

Smp::Services::LogMessageKind Logger::GetLogMessageKind(Smp::String8 messageKindName)
{
    return m_logMessageKind;
}

void Logger::Log(const IObject* sender, String8 message, const LogMessageKind kind)
{
    if (sender)
    {
        std::cout << "[" << sender->GetName() << "] " << message << std::endl;
    }
    else
    {
        std::cout << "[General] " << message << std::endl;
    }

    
}

} // end namespace Services
} // end namespace Smp