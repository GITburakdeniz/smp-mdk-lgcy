#include "Logger.h"

#include <iostream>

namespace Smp {
namespace Services {

Logger::Logger()
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