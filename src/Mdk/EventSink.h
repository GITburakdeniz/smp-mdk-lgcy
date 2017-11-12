//
// Title:
//      EventSink.h
//
// Project:
//      Simulation Model Portability (SMP) Standard 2.0
//      C++ Model Development Kit (MDK)
//      Version 1.2 from October 28th, 2005
//
// Origin:
//      Simulation Model Portability (SMP) Configuration Control Board (CCB)
//
// Purpose:
//      This file defines the EventSink template, which provides
//      an implementation for the IEventSink interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//
// Note:
//      As this class is a template class, its implementation is provided
//      in this header file as well, and instantiated on use.

#ifndef MDK_EVENTSINK_H_
#define MDK_EVENTSINK_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IEventSink.h"
#include "Mdk/Component.h"
#include "Mdk/SimpleTypes.h"

namespace Smp 
{ 
    namespace Mdk
    {
        /// Empty interface to identify MDK Event Sinks
        class MdkEventSink : public virtual Smp::IEventSink
        {
        };

        /// EventSink class implementing IEventSink for void events.
        /// This is the MDK implementation for the IEventSink interface.
        /// It is derived from Object.
        /// @remarks The event argument is type-checked during
        ///          subscription to an associated event source.
        class VoidEventSink :
            public Smp::Mdk::Object,
            public virtual Smp::Mdk::MdkEventSink
        {
        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor with name, description, consumer and event handler.
            /// @param name Name of event sink.
            /// @param description Description of event sink.
            /// @param consumer Event consumer (parent of event sink).
            /// @param handler Event handler (method of event consumer).
            template <class EventConsumerType>
                VoidEventSink(
                Smp::String8 name, 
                Smp::String8 description,
                EventConsumerType* consumer, 
                void (EventConsumerType::*handler)(Smp::IObject* sender))
                : Object(name, description)
            {
                m_eventSinkHelper = new EventSinkHelper<EventConsumerType>(consumer, handler);
            }

            /// Virtual Destructor.
            /// Releases the event sink helper.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~VoidEventSink()
            {
                if (m_eventSinkHelper)
                {
                    delete m_eventSinkHelper;
                }
            }

            // ----------------------------------------------------------------
            // ---------------------------- IEventSink ------------------------
            // ----------------------------------------------------------------

            /// Event notification.
            /// This event handler method is called when an event is emitted.
            /// @param sender Object sending the event.
            /// @param arg Event argument (not used and so not defined to avoid warning).
            void Notify(Smp::IObject* sender, Smp::AnySimple)
            {
                m_eventSinkHelper->Notify(sender);
            }

        private:
            // ----------------------------------------------------------------
            // ---------------------------- Helper classes --------------------
            // ----------------------------------------------------------------

            /// Private helper interface.
            /// Interface that allows to call EventSinkHelper from EventSink
            /// and is independent of template parameters.
            class IEventSinkHelper
            {
            public:
                // Virtual destructor.
                virtual ~IEventSinkHelper() { }
                /// Emit the event.
                virtual void Notify(Smp::IObject* sender) = 0;
            };

            /// Private helper class.
            /// This template class encapsulates the calling mechanism to the
            /// event handler, which is a method of the event consumer.
            /// @remarks By introducing this helper class, the EventSink class
            ///          does not need a global EventConsumerType template
            ///          parameter. This is required to allow type checking in
            ///          in the Subscribe() method of EventSource.
            template<class EventConsumerType>
            class EventSinkHelper : public IEventSinkHelper
            {
            private:
                /// Event consumer, i.e. component to call.
                EventConsumerType* consumer;

                /// Event handler of the consumer, i.e. method to call.
                void (EventConsumerType::*handler)(Smp::IObject* sender);

            public:
                /// Constructor.
                EventSinkHelper(EventConsumerType* consumer, 
                          void (EventConsumerType::*handler)(Smp::IObject* sender))
                {
                    this->consumer = consumer;
                    this->handler  = handler;
                }

                /// Virtual destructor.
                virtual ~EventSinkHelper()
                {
                }

                /// Emit the event.
                virtual void Notify(Smp::IObject* sender)
                {
                    (consumer->*handler)(sender);
                }
            };

        private:
            /// Event sink helper.
            /// Helper class to facilitate the actual method call
            /// into the event consumer.
            IEventSinkHelper* m_eventSinkHelper;
        };

        /// EventSink template implementing IEventSink.
        /// This is the MDK implementation for the IEventSink interface.
        /// It is derived from Object.
        /// @remarks The event argument is type-checked during
        ///          subscription to an associated event source.
        template<class EventArgType>
        class EventSink :
            public Smp::Mdk::Object,
            public virtual Smp::Mdk::MdkEventSink
        {
        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor with name, description, consumer and event handler.
            /// @param name Name of event sink.
            /// @param description Description of event sink.
            /// @param consumer Event consumer (parent of event sink).
            /// @param handler Event handler (method of event consumer).
            template <class EventConsumerType>
                EventSink(
                Smp::String8 name, 
                Smp::String8 description,
                EventConsumerType* consumer, 
                void (EventConsumerType::*handler)(Smp::IObject* sender, EventArgType arg))
                : Object(name, description)
            {
                m_eventSinkHelper = new EventSinkHelper<EventConsumerType>(consumer, handler);
            }

            /// Virtual Destructor.
            /// Releases the event sink helper.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~EventSink()
            {
                if (m_eventSinkHelper)
                {
                    delete m_eventSinkHelper;
                }
            }

            // ----------------------------------------------------------------
            // ---------------------------- IEventSink ------------------------
            // ----------------------------------------------------------------

            /// Event notification.
            /// This event handler method is called when an event is emitted.
            /// @param sender Object sending the event.
            /// @param arg Event argument.
            void Notify(Smp::IObject* sender, Smp::AnySimple arg)
            {
                Smp::Mdk::AnySimple any;
                any = arg;
                m_eventSinkHelper->Notify(sender, any);
            }

        private:
            // ----------------------------------------------------------------
            // ---------------------------- Helper classes --------------------
            // ----------------------------------------------------------------

            /// Private helper interface.
            /// Interface that allows to call EventSinkHelper from EventSink
            /// and is independent of template parameters.
            class IEventSinkHelper
            {
            public:
                // Virtual destructor.
                virtual ~IEventSinkHelper() { }
                /// Emit the event.
                virtual void Notify(Smp::IObject* sender, Smp::Mdk::AnySimple arg) = 0;
            };

            /// Private helper class.
            /// This template class encapsulates the calling mechanism to the
            /// event handler, which is a method of the event consumer.
            /// @remarks By introducing this helper class, the EventSink class
            ///          does not need a global EventConsumerType template
            ///          parameter. This is required to allow type checking in
            ///          in the Subscribe() method of EventSource.
            template<class EventConsumerType>
            class EventSinkHelper : public IEventSinkHelper
            {
            private:
                /// Event consumer, i.e. component to call.
                EventConsumerType* consumer;

                /// Event handler of the consumer, i.e. method to call.
                void (EventConsumerType::*handler)(Smp::IObject* sender, EventArgType arg);

            public:
                /// Constructor.
                EventSinkHelper(EventConsumerType* consumer, 
                          void (EventConsumerType::*handler)(Smp::IObject* sender, EventArgType arg))
                {
                    this->consumer = consumer;
                    this->handler  = handler;
                }

                /// Virtual destructor.
                virtual ~EventSinkHelper()
                {
                }

                /// Emit the event.
                virtual void Notify(Smp::IObject* sender, Smp::Mdk::AnySimple any)
                {
                    EventArgType arg;
                    any.Get(arg);
                    (consumer->*handler)(sender, arg);
                }
            };

        private:
            /// Event sink helper.
            /// Helper class to facilitate the actual method call
            /// into the event consumer.
            IEventSinkHelper* m_eventSinkHelper;
        };
    }
}

#endif  // MDK_EVENTSINK_H_

/***********
 * History *
 ***********/

//$Log: EventSink.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

