//
// Title:
//      EventConsumer.h
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
//      This file defines the EventConsumer class, which provides
//      an implementation for the IEventConsumer interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_MANAGEMENT_EVENTCONSUMER_H_
#define MDK_MANAGEMENT_EVENTCONSUMER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/Management/IEventConsumer.h"

namespace Smp 
{
    namespace Mdk
    {
        namespace Management
        {
            /// Event consumer.
            /// This is the MDK implementation for the IEventConsumer interface.
            class EventConsumer : public virtual Smp::Management::IEventConsumer
            {
            private:
                /// Collection of event sinks.
                Smp::EventSinkCollection m_eventSinks;

            public:
                // ------------------------------------------------------------
                // ---------------------------- Constructor -------------------
                // ------------------------------------------------------------

                /// Default Constructor.
                EventConsumer();

                /// Virtual destructor.
                /// Delete all event consumers.
                /// @remarks This is needed to be able to destroy objects
                ///          using the actual derived object's destructor.
                virtual ~EventConsumer();

                // ------------------------------------------------------------
                // ---------------------------- IEventConsumer ----------------
                // ------------------------------------------------------------

                /// Get all event sinks.
                /// Query for the collection of all event sinks of the component.
                /// @return Collection of event sinks.
                /// @remarks The collection may be empty if no event sinks exist.
                virtual const Smp::EventSinkCollection* GetEventSinks() const;

                /// Get an event sink by name.
                /// Query for an event sink of this component by its name.
                /// @param   name Event sink name.
                /// @return  Event sink with the given name, or null if no
                ///          event sink with the given name could be found.
                /// @remarks The returned event sink may be null if no
                ///          event sink with the given name could be found.
                virtual Smp::IEventSink* GetEventSink(Smp::String8 name) const;

            protected:
                // ------------------------------------------------------------
                // ---------------------------- Helper methods ----------------
                // ------------------------------------------------------------

                /// Add an event sink 
                /// @param  eventSink Event sink to add.
                void AddEventSink(Smp::IEventSink* eventSink);

                /// Delete all event Sinks
                void Clear();
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_EVENTCONSUMER_H_

/***********
 * History *
 ***********/

//$Log: EventConsumer.h,v $
//Revision 1.2  2006/09/27 11:49:56  nin
//SMP2 v1.2
// 

