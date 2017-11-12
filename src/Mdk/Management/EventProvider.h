//
// Title:
//      EventProvider.h
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
//      This file defines the EventProvider class, which provides
//      an implementation for the IEventProvider interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_MANAGEMENT_EVENTPROVIDER_H_
#define MDK_MANAGEMENT_EVENTPROVIDER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/Management/IEventProvider.h"

namespace Smp 
{
    namespace Mdk
    {
        namespace Management
        {
            /// Event Provider.
            /// This is the MDK implementation for the IEventProvider interface.
            class EventProvider : public virtual Smp::Management::IEventProvider
            {
            private:
                /// Collection of event sources.
                Smp::EventSourceCollection m_eventSources;

            public:
                // ------------------------------------------------------------
                // ---------------------------- Constructor -------------------
                // ------------------------------------------------------------

                /// Default Constructor.
                EventProvider();

                /// Virtual destructor.
                /// Delete all event sources.
                /// @remarks This is needed to be able to destroy objects
                ///          using the actual derived object's destructor.
                virtual ~EventProvider();

                // ------------------------------------------------------------
                // ---------------------------- IEventProvider ----------------
                // ------------------------------------------------------------

                /// Get all event sources.
                /// Query for the collection of all event sources of the component.
                /// @return  Collection of event sources.
                /// @remarks The collection may be empty if no event sources exist.
                virtual const Smp::EventSourceCollection* GetEventSources() const;

                /// Get an event source by name.
                /// Query for an event source of this component by its name.
                /// @param   name Event source name.
                /// @return  Event source with the given name, or null if no
                ///          event source with the given name could be found.
                /// @remarks The returned event source may be null if no
                ///          event source with the given name could be found.
                virtual Smp::IEventSource* GetEventSource(Smp::String8 name) const;

            protected:
                // ------------------------------------------------------------
                // ---------------------------- Helper methods ----------------
                // ------------------------------------------------------------

                /// Add an event source 
                /// @param  eventSource Event source to add.
                void AddEventSource(Smp::IEventSource* eventSource);

                /// Delete all event sources
                void Clear();
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_EVENTPROVIDER_H_

/***********
 * History *
 ***********/

//$Log: EventProvider.h,v $
//Revision 1.2  2006/09/27 11:49:56  nin
//SMP2 v1.2
// 

