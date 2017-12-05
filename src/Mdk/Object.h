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

#ifndef MDK_OBJECT_H_
#define MDK_OBJECT_H_

#include "Smp/IObject.h"
#include "Smp/Exceptions.h"

#include <string>

namespace Smp 
{ 
    namespace Mdk
    {
        class Object :
            public virtual Smp::IObject
        {
            public:
                Object(void);
                Object(
                        ::Smp::String8 name,
                        ::Smp::String8 description)
                    throw (::Smp::InvalidObjectName);
                virtual ~Object(void);

                virtual ::Smp::String8 GetName(void) const;
                virtual ::Smp::String8 GetDescription(void) const;

            protected:
                ::Smp::Bool _SetName(
                        const ::Smp::String8 name);
                ::Smp::Bool _SetDescription(
                        const ::Smp::String8 description);

                ::std::string _name;
                ::std::string _description;

            private:
                ::Smp::Bool IsValidName(
                        ::Smp::String8 name) const;
                ::Smp::Bool IsValidDescription(
                        ::Smp::String8 description) const;
                ::Smp::Bool IsValidNameLength(
                            size_t nameLen) const;
                ::Smp::Bool IsValidNameChars(
                        ::Smp::String8 name,
                        size_t nameLen) const;
        };
    }
}

#endif  // MDK_OBJECT_H_
