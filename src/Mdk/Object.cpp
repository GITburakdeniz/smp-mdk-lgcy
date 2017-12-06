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

using namespace Smp::Mdk;

Object::Object(void)
{
}

Object::Object(
        ::Smp::String8 name, ::Smp::String8 description)
throw (::Smp::InvalidObjectName)
{
    if (!_SetName(name)) {
        throw ::Smp::InvalidObjectName(name);
    }

    _SetDescription(description);
}

Object::~Object()
{
}

Smp::String8 Object::GetName(void) const
{
    return static_cast< ::Smp::String8>(this->_name.c_str());
}

Smp::String8 Object::GetDescription(void) const
{
    return static_cast< ::Smp::String8>(this->_description.c_str());
}

::Smp::Bool Object::_SetName(
        const ::Smp::String8 name)
{
    ::Smp::Bool ret = false;

    if (IsValidName(name)) {
        this->_name = name;
        ret = true;
    }

    return ret;
}

::Smp::Bool Object::_SetDescription(
        const ::Smp::String8 description)
{
    ::Smp::Bool ret = false;

    if (IsValidDescription(description)) {
        this->_description = description;
        ret = true;
    }

    return ret;
}

::Smp::Bool Object::IsValidName(
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

inline ::Smp::Bool Object::IsValidNameLength(
        size_t nameLen) const
{
    return (nameLen > NAME_MIN_LEN) && (nameLen <= NAME_MAX_LEN);
}

inline ::Smp::Bool Object::IsValidNameChars(
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

::Smp::Bool Object::IsValidDescription(
        ::Smp::String8 description) const
{
    return description != NULL;
}
