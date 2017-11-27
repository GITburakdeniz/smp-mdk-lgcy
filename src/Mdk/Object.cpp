/** This file is part of smp-mdk
 *
 * Copyright (C) 2017 Juan R. Garcia Blanco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Mdk/Object.h"

#include <string>
#include <cstring>
#include <cctype>

const size_t NAME_MIN_LEN = 0;
const size_t NAME_MAX_LEN = 32;

namespace Smp
{
    namespace Mdk
    {
        class ObjectImpl
        {
            public:
                ObjectImpl(void);
                ObjectImpl(
                        ::Smp::String8 name, ::Smp::String8 description)
                    throw (::Smp::InvalidObjectName);
                virtual ~ObjectImpl();

                ::Smp::String8 GetName(void) const;
                ::Smp::String8 GetDescription(void) const;

            private:
                ::Smp::Bool IsValidName(
                        ::Smp::String8 name) const;
                inline ::Smp::Bool IsValidNameLength(
                            size_t nameLen) const;
                inline ::Smp::Bool IsValidNameChars(
                        ::Smp::String8 name,
                        size_t nameLen) const;
                ::Smp::Bool IsValidDescription(
                        ::Smp::String8 description) const;

                ::std::string _name;
                ::std::string _description;
        };
    }
}

using namespace Smp::Mdk;

Object::Object()
    : _impl(new ObjectImpl)
{
}

Object::Object(
        ::Smp::String8 name, ::Smp::String8 description)
throw (::Smp::InvalidObjectName)
    : _impl(new ObjectImpl(name, description))
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

ObjectImpl::ObjectImpl(void)
{
}

ObjectImpl::ObjectImpl(
        ::Smp::String8 name, ::Smp::String8 description)
throw (::Smp::InvalidObjectName)
{
    if (IsValidName(name)) {
        this->_name = name;

        if (IsValidDescription(description)) {
            this->_description = description;
        }
    } else {
        throw new ::Smp::InvalidObjectName(name);
    }
}

ObjectImpl::~ObjectImpl(void)
{
}

::Smp::String8 ObjectImpl::GetName(void) const
{
    return static_cast< ::Smp::String8>(this->_name.c_str());
}

::Smp::String8 ObjectImpl::GetDescription(void) const
{
    return static_cast< ::Smp::String8>(this->_description.c_str());
}

::Smp::Bool ObjectImpl::IsValidName(
        ::Smp::String8 name) const
{
    ::Smp::Bool ret = true;

    if (name == NULL) {
        ret = false;
    } else {
        size_t nameLen = ::strlen(name);
        ret = IsValidNameLength(nameLen) && IsValidNameChars(name, nameLen);
    }

    return ret;
}

inline ::Smp::Bool ObjectImpl::IsValidNameLength(
        size_t nameLen) const
{
    return (nameLen > NAME_MIN_LEN) && (nameLen <= NAME_MAX_LEN);
}

inline ::Smp::Bool ObjectImpl::IsValidNameChars(
        ::Smp::String8 name,
        size_t nameLen) const
{
    ::Smp::Bool remainsValid = (::isalpha(name[0]) != 0) ? true : false;
    ::Smp::UInt32 i = 1;

    while (remainsValid && (i < nameLen)) {
        const ::Smp::Bool isLetterOrDigit = (::isalnum(name[i]) != 0) ? true : false;
        const ::Smp::Bool isUnderscore = (name[i] == '_');
        const ::Smp::Bool isBracket = (name[i] == '[') || (name[i] == ']');

        remainsValid = isLetterOrDigit || isUnderscore || isBracket;
        ++i;
    }

    return remainsValid;
}

::Smp::Bool ObjectImpl::IsValidDescription(
        ::Smp::String8 description) const
{
    return description != NULL;
}
