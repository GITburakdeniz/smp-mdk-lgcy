//
// Title:
//      EntryPoint.h
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
//      This file defines the EntryPoint template, which provides
//      an implementation for the IEntryPoint interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//
// Note:
//      As this class is a template class, its implementation is provided
//      in this header file as well, and instantiated on use.

#ifndef MDK_ENTRYPOINT_H_
#define MDK_ENTRYPOINT_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Mdk/Object.h"
#include "Smp/IEntryPoint.h"

namespace Smp 
{
    namespace Mdk
    {
        /// EntryPoint template.
        /// This is the MDK implementation for the IEntryPoint interface.
        /// It is derived from Object.
        class EntryPoint :
            public Smp::Mdk::Object,
            public virtual Smp::IEntryPoint
        {
        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor with name, description, publisher and entry point.
            /// @param name Name of event sink.
            /// @param description Description of event sink.
            /// @param publisher Entry point publisher (parent of entry point).
            /// @param entryPoint Entry point (method of publisher).
            template<class EntryPointPublisherType>
            EntryPoint(
                Smp::String8 name, 
                Smp::String8 description,
                EntryPointPublisherType* publisher, 
                void (EntryPointPublisherType::*entryPoint)(void))
                : Object(name, description),
                m_owner(publisher)
            {
                m_entryPointHelper = new EntryPointHelper<EntryPointPublisherType>(publisher, entryPoint);
            }

            /// Virtual Destructor
            /// Releases the entry point helper.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~EntryPoint()
            {
                if (m_entryPointHelper)
                {
                    delete m_entryPointHelper;
                }
            }

            // ----------------------------------------------------------------
            // ---------------------------- IEntryPoint -----------------------
            // ----------------------------------------------------------------

            /// Entry point owner.
            /// This method returns the Component that owns the entry point.
            /// @return  Owner of entry point.
            /// @remarks This is required to be able to store and later restore
            ///          entry points.
            IComponent* GetOwner(void) const
            {
                return m_owner;
            }

            /// Entry point execution.
            /// Method that is called when an associated event is emitted.
            /// @remarks Models providing entry points must ensure that these 
            ///          entry points do not throw exceptions.
            void Execute() const
            {
                m_entryPointHelper->Execute();
            }

            // ----------------------------------------------------------------
            // ---------------------------- Operators -------------------------
            // ----------------------------------------------------------------

            /// Executes the entry point.
            void operator()() const
            {
                Execute();
            }

        private:
            // ----------------------------------------------------------------
            // ---------------------------- Helper class ----------------------
            // ----------------------------------------------------------------

            /// Private helper interface.
            /// Interface that allows to call EntryPointHelper from EntryPoint
            /// and is independent of template parameters.
            class IEntryPointHelper
            {
            public:
                // Virtual destructor.
                virtual ~IEntryPointHelper() { }
                /// Execute entry point.
                virtual void Execute() = 0;
            };

            /// Private helper class.
            /// This template class encapsulates the calling mechanism to the
            /// actual entry point, which is a method of the entry point publisher.
            /// @remarks By introducing this helper class, the EntryPoint class
            ///          does not need a global EntryPointPublisherType template
            ///          parameter.
            template<class EntryPointPublisherType>
            class EntryPointHelper : public IEntryPointHelper
            {
            private:
                /// Entry point publisher.
                EntryPointPublisherType* publisher;

                /// Entry point to execute.
                void (EntryPointPublisherType::*entryPoint)(void);

            public:
                /// Constructor.
                EntryPointHelper(EntryPointPublisherType* publisher, 
                           void (EntryPointPublisherType::*entryPoint)(void))
                {
                    this->publisher  = publisher;
                    this->entryPoint = entryPoint;
                }

                /// Virtual destructor.
                virtual ~EntryPointHelper()
                {
                }

                /// Execute the entry point.
                void Execute()
                {
                    (publisher->*entryPoint)();
                }
            };

        private:
            /// Entry point owner.
            /// Component that owns the entry point.
            IComponent* m_owner;

            /// Entry point helper.
            /// Helper class to facilitate the actual method call
            /// into the entry point publisher.
            IEntryPointHelper* m_entryPointHelper;
        };
    }
}

#endif  // MDK_ENTRYPOINT_H_

/***********
 * History *
 ***********/

//$Log: EntryPoint.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

