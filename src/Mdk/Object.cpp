#include "Mdk/Object.h"

using namespace Smp::Mdk;

Object::Object()
{
}

Object::~Object()
{
}

Smp::String8 Object::GetName() const
{
    return NULL;
}

Smp::String8 Object::GetDescription() const
{
    return NULL;
}

static Smp::Bool Object::ValidateName(Smp::String8 name)
{
    return false;
}
