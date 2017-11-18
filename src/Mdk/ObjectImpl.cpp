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

#include "Mdk/ObjectImpl.h"

using namespace Smp::Mdk;

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
    return true;
}

::Smp::Bool ObjectImpl::IsValidDescription(
        ::Smp::String8 description) const
{
    return true;
}
