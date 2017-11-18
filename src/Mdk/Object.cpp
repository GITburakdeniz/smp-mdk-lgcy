#include "Mdk/Object.h"

using namespace Smp::Mdk;

Object::Object()
    : _impl(new ObjectImpl)
{
}

Object::Object(
        ::Smp::String8 name, ::Smp::String8 description)
throw (::Smp::InvalidObjectName)
    : _impl(new ObjectIimpl(name, description))
{
}

Object::~Object()
{
    if (this->_impl) {
        delete this->_impl;
    }
}

Smp::String8 Object::GetName() const
{
    return this->_impl->GetName();
}

Smp::String8 Object::GetDescription() const
{
    return this->_impl->GetDescription();
}
