/** This file is part of smp-mdk
 *
 * Copyright (C) 2018 Juan R. Garcia Blanco
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

#ifndef MDK_CONTAINER_H_
#define MDK_CONTAINER_H_

#include "Smp/IContainer.h"
#include "Mdk/Object.h"

namespace Smp
{
    namespace Mdk
    {
        template < typename T> class Container :
            public ::Smp::Mdk::Object,
            public virtual ::Smp::IContainer
        {
            public:
                Container(void) :
                    Object()
                {
                }

                Container(
                        ::Smp::String8 name,
                        ::Smp::String8 description)
                    throw (::Smp::InvalidObjectName) :
                        Object(name, description)
                {
                }

                virtual ~Container(void)
                {
                    for (TypedContainerCollection::iterator it(this->_components.begin());
                            it != this->_components.end();
                            ++it)
                    {
                        delete *it;
                    }
                }

                const ComponentCollection* GetComponents(void) const
                {
                    return &(this->_components);
                }

                ::Smp::IComponent* GetComponent(
                        ::Smp::String8 name) const
                {
                    TypedContainerCollection::iterator it(this->_components.begin());
                    TypedContainerCollection::iterator endIt(this->_components.end());
                    ::Smp::IComponent* comp = NULL;

                    while ((comp == NULL) && (it != endIt)) {
                        if (::strcmp(name, (*it)->GetName()) == 0) {
                            comp = *it;
                        }

                        ++it;
                    }

                    return comp;
                }

            protected:
                void _AddComponent(const T* component)
                {
                    this->_components.push_back(component);
                }

            private:
                typedef ::std::vector< T*> TypedContainerCollection;

                TypedContainerCollection _components;
        };

//        template< typename T>
//        class Reference :
//            public ::Smp::Mdk::Object,
//            public virtual ::Smp::IReference
//        {
//            public:
//                Reference(void) :
//                    Object()
//                {
//                }
//
//                Reference(
//                        ::Smp::String8 name,
//                        ::Smp::String8 description)
//                    throw (::Smp::InvalidObjectName) :
//                        Object(name, description)
//                {
//                }
//
//                virtual ~Reference(void)
//                {
//                }
//
//                const ::Smp::ComponentCollection* GetComponents(void) const
//                {
//                    return &(this->_components);
//                }
//
//                ::Smp::IComponent* GetComponent(
//                        ::Smp::String8 name) const
//                {
//                    TypedComponentCollection::iterator it(this->_components.begin());
//                    TypedComponentCollection::iterator endIt(this->_components.end());
//                    ::Smp::IComponent* comp = NULL;
//
//                    while ((comp == NULL) && (it != endIt)) {
//                        if (::strcmp(name, (*it)->GetName()) == 0) {
//                            comp = *it;
//                        }
//
//                        ++it;
//                    }
//
//                    return comp;
//                }
//
//            protected:
//                void _AddComponent(const T* component)
//                {
//                    this->_components.push_back(component);
//                }
//
//            private:
//                typedef ::std::vector< T*> TypedComponentCollection;
//
//                TypedComponentCollection _components;
//        };
    }
}

#endif  // MDK_CONTAINER_H_
