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

#ifndef MDK_EVENTSINK_H_
#define MDK_EVENTSINK_H_

#include "Mdk/Object.h"
#include "Smp/IComponent.h"
#include "Smp/IEventSink.h"

namespace Smp 
{
    namespace Mdk
    {
        class MdkEventSink :
            public virtual ::Smp::IEventSink
        {
        };

        class VoidEventSink :
            public ::Smp::Mdk::Object,
            public virtual MdkEventSink
        {
            public:
                template< typename T> VoidEventSink(
                        ::Smp::String8 name,
                        ::Smp::String8 description,
                        T* consumer,
                        void (T::*callback)(::Smp::IObject* sender)) throw (::Smp::InvalidObjectName)
                    : Object(name, description),
                    _helper(new VoidEventSinkHelper< T>(consumer, callback))
                {
                }

                virtual ~VoidEventSink(void)
                {
                    if (this->_helper != NULL) {
                        delete this->_helper;
                        this->_helper = NULL;
                    }
                }

                void Notify(
                        ::Smp::IObject* sender,
                        ::Smp::AnySimple arg)
                {
                    if (this->_helper != NULL) {
                        this->_helper->Notify(sender);
                    }
                }

            private:
                class IVoidEventSinkHelper
                {
                    public:
                        virtual ~IVoidEventSinkHelper(void)
                        {
                        }

                        virtual void Notify(
                                ::Smp::IObject* sender) = 0;
                };

                template< typename T> class VoidEventSinkHelper :
                    public virtual IVoidEventSinkHelper
            {
                private:
                    typedef void (T::*CallbackType)(::Smp::IObject* sender);

                public:
                    VoidEventSinkHelper(
                            T* consumer,
                            CallbackType callback)
                        : _consumer(consumer),
                        _callback(callback)
                    {
                    }

                    virtual ~VoidEventSinkHelper(void)
                    {
                    }

                    void Notify(
                            ::Smp::IObject* sender)
                    {
                        if (this->_consumer != NULL) {
                            (this->_consumer->*_callback)(sender);
                        }
                    }

                private:
                    T* _consumer;
                    CallbackType _callback;
            };

                IVoidEventSinkHelper* _helper;
        };

        class EventSink :
            public ::Smp::Mdk::Object,
            public virtual ::Smp::IEventSink
        {
            public:
                template< typename T> EventSink(
                            ::Smp::String8 name,
                            ::Smp::String8 description,
                            T* consumer,
                            void (T::*callback)(::Smp::IObject* sender, ::Smp::AnySimple arg))
                    throw (::Smp::InvalidObjectName)
                        : Object(name, description),
                        _helper(new EventSinkHelper< T>(consumer, callback))
                {
                }

                virtual ~EventSink(void)
                {
                    if (this->_helper != NULL) {
                        delete this->_helper;
                        this->_helper = NULL;
                    }
                }

                void Notify(::Smp::IObject* sender, ::Smp::AnySimple arg)
                {
                    if (this->_helper != NULL) {
                        this->_helper->Notify(sender, arg);
                    }
                }

            private:
                class IEventSinkHelper
                {
                    public:
                        virtual ~IEventSinkHelper(void)
                        {
                        }

                        virtual void Notify(
                                ::Smp::IObject* sender,
                                const ::Smp::AnySimple& arg) = 0;
                };

                template< typename T> class EventSinkHelper :
                        public virtual IEventSinkHelper
                {
                    private:
                        typedef void (T::*CallbackType)(
                                ::Smp::IObject* sender,
                                ::Smp::AnySimple arg);

                    public:
                        EventSinkHelper(
                                T* consumer,
                                CallbackType callback) :
                            _consumer(consumer),
                            _callback(callback)
                        {
                        }

                        virtual ~EventSinkHelper(void)
                        {
                        }

                        void Notify(
                                ::Smp::IObject* sender,
                                const ::Smp::AnySimple& arg)
                        {
                            if (this->_consumer != NULL) {
                                (this->_consumer->*_callback)(sender, arg);
                            }
                        }

                    private:
                        T* _consumer;
                        CallbackType _callback;
                };

            private:
                IEventSinkHelper* _helper;
        };
    }
}

#endif  // MDK_EVENTSINK_H_
