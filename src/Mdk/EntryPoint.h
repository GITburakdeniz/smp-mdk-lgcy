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

#ifndef MDK_ENTRYPOINT_H_
#define MDK_ENTRYPOINT_H_

#include "Mdk/Object.h"
#include "Smp/IEntryPoint.h"

namespace Smp 
{
    namespace Mdk
    {
        template< typename T>
            class EntryPointHelper
            {
                private:
                    typedef void (T::EntryPointType*)(void);

                public:
                    EntryPointHelper(
                            T* owner,
                            EntryPointType entryPoint) :
                        _owner(owner),
                        _entryPoint(entryPoint)
                    {
                    }

                    void Execute(void)
                    {
                        if (this->_owner != NULL) {
                            (this->_owner->*_entryPoint)();
                        }
                    }

                private:
                    T* _owner;
                    EntryPointType _entryPoint;
            };

        class EntryPoint :
            public ::Smp::Mdk::Object,
            public virtual ::Smp::IEntryPoint
        {
            public:
                template< typename T>
                    EntryPoint(
                            ::Smp::String8 name,
                            ::Smp::String8 description,
                            T* owner,
                            void (T::entryPoint*)(void))
                    throw (::Smp::InvalidObjectName) :
                        _helper(new EntryPointHelper(owner, entryPoint)),
                        _owner(owner)
                {
                }

                virtual ~EntryPoint(void)
                {
                    if (this->_helper != NULL) {
                        delete this->_helper;
                        this->_helper = NULL;
                    }
                }

                ::Smp::IComponent* GetOwner(void) const
                {
                    return this->_owner;
                }

                void Execute(void) const
                {
                    if (this->_helper != NULL) {
                        this->_helper->Execute();
                    }
                }

            private:
                ::Smp::IComponent* _owner;
                EntryPointHelper* _helper;
        };
    }
}

#endif  // MDK_ENTRYPOINT_H_
