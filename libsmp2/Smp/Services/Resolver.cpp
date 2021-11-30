#include "Resolver.h"

namespace Smp {
namespace Services {

Resolver::Resolver()
{

}

Resolver::~Resolver()
{

}

IComponent* Resolver::ResolveAbsolute(String8 absolutePath)
{
    std::vector<std::string> result;
    boost::split(result, absolutePath, boost::is_any_of("."));
    return nullptr;
}

IComponent* Resolver::ResolveRelative(String8 relativePath, IComponent* sender)
{
    // FIXME: Not implemented
    return nullptr;
}

} // end namespace Services
} // end namespace Smp