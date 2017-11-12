//
// Title:
//      EventSource.h
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
//      This file defines the EventSource template, which provides
//      an implementation for the IEventSource interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//
// Note:
//      As this class is a template class, its implementation is provided
//      in this header file as well, and instantiated on use.

#ifndef MDK_EVENTSOURCE_H_
#define MDK_EVENTSOURCE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IEventSource.h"
#include "Mdk/Component.h"
#include "Mdk/EventSink.h"

namespace Smp 
{ 
    namespace Mdk
    {
        /// EventSource class implementing IEventSource for void events.
        /// This is the MDK implementation for the IEventSource interface.
        /// It is derived from Object.
        class VoidEventSource :
            public Smp::Mdk::Object,
            public virtual Smp::IEventSource
        {
        private:
            /// Collection of event sinks subscribed to this event source.
            Smp::EventSinkCollection m_eventSinks;

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor.
            /// @param name Name of event source.
            /// @param description Description of event source.
            /// @param publisher Event publisher (parent of event source).
            VoidEventSource(
                Smp::String8 name, 
                Smp::String8 description,
                Smp::IComponent* publisher)
                : Object(name, description)
            {
                (void) publisher;       // Avoid compiler warning
            }

            /// Virtual Destructor.
            /// Clears the event sink collection.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~VoidEventSource()
            {
                m_eventSinks.clear();
            }

            // ----------------------------------------------------------------
            // ---------------------------- IEventSource ----------------------
            // ----------------------------------------------------------------

            /// Event subscription.
            /// Subscribe to the event source, i.e. request notifications.
            /// @param eventSink Event sink to subscribe to event source.
            /// @remarks An event sink can only be subscribed once to each
            ///          event source.
            virtual void Subscribe(Smp::IEventSink* eventSink) throw (
                Smp::IEventSource::AlreadySubscribed,
                Smp::IEventSource::InvalidEventSink)
            {
                // Check if the MDK implementation is used
                if (dynamic_cast< Smp::Mdk::MdkEventSink*>(eventSink) != NULL)
                {
                    // Check argument type
                    if (dynamic_cast< VoidEventSink*>(eventSink) == NULL)
                    {
                        throw Smp::IEventSource::InvalidEventSink(this, eventSink);
                    }
                }

                // Check if event sink is already subscribed
                for (Smp::EventSinkCollection::iterator it = m_eventSinks.begin();
                    it != m_eventSinks.end();
                    it++)
                {
                    if (*it == eventSink)
                    {
                        throw Smp::IEventSource::AlreadySubscribed(this, eventSink);
                    }
                }

                // Store reference to event sink
                m_eventSinks.push_back(eventSink);
            }

            /// Event unsubscription.
            /// Unsubscribe from the event source, i.e. cancel notifications.
            /// @param eventSink Event sink to unsubscribe from event source.
            /// @remarks An event sink can only be unsubscribed if it has been
            ///          subscribed before.
            virtual void Unsubscribe(Smp::IEventSink* eventSink) throw (
                Smp::IEventSource::NotSubscribed)
            {
                for (Smp::EventSinkCollection::iterator it = m_eventSinks.begin();
                    it != m_eventSinks.end();
                    it++)
                {
                    if (*it == eventSink)
                    {
                        // Remove reference to event sink
                        m_eventSinks.erase(it);
                        return;
                    }
                }

                throw Smp::IEventSource::NotSubscribed(this, eventSink);
            }

            // ----------------------------------------------------------------
            // ---------------------------- Helper methods --------------------
            // ----------------------------------------------------------------

            /// Emit event.
            /// All subscribed event sinks are notified.
            void Emit(Smp::IComponent* sender)
            {
                Smp::AnySimple any;
                any.type = Smp::ST_None;

                for (Smp::EventSinkCollection::iterator it = m_eventSinks.begin();
                    it != m_eventSinks.end();
                    it++)
                {
                    (*it)->Notify(sender, any);
                }
            }

            // ----------------------------------------------------------------
            // ---------------------------- Operators -------------------------
            // ----------------------------------------------------------------

            /// Emit event.
            /// All subscribed event sinks are notified.
            void operator()(Smp::IComponent* sender)
            {
                Emit(sender);
            }
        };

        /// EventSource template implementing IEventSource.
        /// This is the MDK implementation for the IEventSource interface.
        /// It is derived from Object.
        template<class EventArgType>
        class EventSource :
            public Smp::Mdk::Object,
            public virtual Smp::IEventSource
        {
        private:
            /// Collection of event sinks subscribed to this event source.
            Smp::EventSinkCollection m_eventSinks;

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor.
            /// @param name Name of event source.
            /// @param description Description of event source.
            /// @param publisher Event publisher (parent of event source).
            EventSource(
                Smp::String8 name, 
                Smp::String8 description,
                Smp::IComponent* publisher)
                : Object(name, description)
            {
                (void) publisher;       // Avoid compiler warning
            }

            /// Virtual Destructor.
            /// Clears the event sink collection.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~EventSource()
            {
                m_eventSinks.clear();
            }

            // ----------------------------------------------------------------
            // ---------------------------- IEventSource ----------------------
            // ----------------------------------------------------------------

            /// Event subscription.
            /// Subscribe to the event source, i.e. request notifications.
            /// @param eventSink Event sink to subscribe to event source.
            /// @remarks An event sink can only be subscribed once to each
            ///          event source.
            virtual void Subscribe(Smp::IEventSink* eventSink) throw (
                Smp::IEventSource::AlreadySubscribed,
                Smp::IEventSource::InvalidEventSink)
            {
                // Check if the MDK implementation is used
                if (dynamic_cast< Smp::Mdk::MdkEventSink*>(eventSink) != NULL)
                {
                    // Check argument type
                    if (dynamic_cast< EventSink<EventArgType> *>(eventSink) == NULL)
                    {
                        throw Smp::IEventSource::InvalidEventSink(this, eventSink);
                    }
                }

                // Check if event sink is already subscribed
                for (Smp::EventSinkCollection::iterator it = m_eventSinks.begin();
                    it != m_eventSinks.end();
                    it++)
                {
                    if (*it == eventSink)
                    {
                        throw Smp::IEventSource::AlreadySubscribed(this, eventSink);
                    }
                }

                // Store reference to event sink
                m_eventSinks.push_back(eventSink);
            }

            /// Event unsubscription.
            /// Unsubscribe from the event source, i.e. cancel notifications.
            /// @param eventSink Event sink to unsubscribe from event source.
            /// @remarks An event sink can only be unsubscribed if it has been
            ///          subscribed before.
            virtual void Unsubscribe(Smp::IEventSink* eventSink) throw (
                Smp::IEventSource::NotSubscribed)
            {
                for (Smp::EventSinkCollection::iterator it = m_eventSinks.begin();
                    it != m_eventSinks.end();
                    it++)
                {
                    if (*it == eventSink)
                    {
                        // Remove reference to event sink
                        m_eventSinks.erase(it);
                        return;
                    }
                }

                throw Smp::IEventSource::NotSubscribed(this, eventSink);
            }

            // ----------------------------------------------------------------
            // ---------------------------- Helper methods --------------------
            // ----------------------------------------------------------------

            /// Emit event.
            /// All subscribed event sinks are notified.
            void Emit(Smp::IComponent* sender, EventArgType arg)
            {
                Smp::Mdk::AnySimple any;
                any.Set(arg);

                for (Smp::EventSinkCollection::iterator it = m_eventSinks.begin();
                    it != m_eventSinks.end();
                    it++)
                {
                    (*it)->Notify(sender, any);
                }
            }

            // ----------------------------------------------------------------
            // ---------------------------- Operators -------------------------
            // ----------------------------------------------------------------

            /// Emit event.
            /// All subscribed event sinks are notified.
            void operator()(Smp::IComponent* sender, EventArgType arg)
            {
                Emit(sender, arg);
            }
        };
    }    
}

#endif  // MDK_EVENTSOURCE_H_

/***********
 * History *
 ***********/

//$Log: EventSource.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

