//
// Title:
//      Invocator.h
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
//      This file defines the Invocator class.
//
// Author:
//      Peter Fritzen
//

#ifndef MDK_INVOCATOR_H_
#define MDK_INVOCATOR_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IModel.h"
#include "Smp/IEntryPoint.h"
#include "Smp/IDynamicInvocation.h"

#include "Mdk/Object.h"

// ----------------------------------------------------------------------------
// ---------------------------- Invocator -------------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{
    namespace Mdk
    {
        /// Invocator class.
        /// This class implements the IEntryPoint interface, but internally
        /// calls an operation with parameters via dynamic invocation.
        /// It is derived from Object.
        class Invocator :
            public Smp::Mdk::Object,
            public virtual Smp::IEntryPoint
        {
        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor with name, description, owner and request object.
            /// @param name Name of instance.
            /// @param description Description of instance.
            /// @param owner Owner that holds operation to call.
            /// @param request Request object to pass to model on Execute().
            Invocator(
                Smp::String8 name, 
                Smp::String8 description,
                Smp::IDynamicInvocation* owner,
                Smp::IRequest* request);

            /// Virtual Destructor.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Invocator();

            // ----------------------------------------------------------------
            // ---------------------------- IEntryPoint -----------------------
            // ----------------------------------------------------------------

            /// Entry point owner.
            /// This method returns the Component that owns the entry point.
            /// @return  Owner of entry point.
            /// @remarks This is required to be able to store and later restore
            ///          entry points.
            Smp::IComponent* GetOwner(void) const;

            /// Entry point execution.
            /// Method that is called when an associated event is emitted.
            /// @remarks Models providing entry points must ensure that these 
            ///          entry points do not throw exceptions.
            void Execute() const;

            // ----------------------------------------------------------------
            // ---------------------------- Operators -------------------------
            // ----------------------------------------------------------------

            /// Executes the entry point.
            void operator()() const;

        private:
            /// Owner of operation.
            /// Component that holds the operation to call via dynamic invocation.
            IDynamicInvocation* m_owner;

            /// Request to execute.
            /// This request is invoked during Execute(), so that indirectly an
            /// operation with parameters can be called like an entry points.
            IRequest* m_request;
        };
    }
}

#endif  // MDK_INVOCATOR_H_

/***********
 * History *
 ***********/

//$Log: Invocator.h,v $
//Revision 1.1  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

