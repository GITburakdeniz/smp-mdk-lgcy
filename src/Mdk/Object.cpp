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
#include "Mdk/ObjectImpl.h"

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
