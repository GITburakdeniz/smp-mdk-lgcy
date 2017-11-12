//
// Title:
//      EntryPointPublisher.h
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
//      This file defines the EntryPointPublisher class, which provides
//      an implementation for the IEntryPointPublisher interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_MANAGEMENT_ENTRYPOINTPUBLISHER_H_
#define MDK_MANAGEMENT_ENTRYPOINTPUBLISHER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/Management/IEntryPointPublisher.h"

namespace Smp 
{ 
    namespace Mdk
    {
        namespace Management
        {
            /// EntryPoint Publisher.
            /// This is the MDK implementation for the IEntryPointPublisher interface.
            class EntryPointPublisher : public virtual Smp::Management::IEntryPointPublisher
            {
            private:
                /// Collection of event sources.
                Smp::EntryPointCollection m_entryPoints;

            public:
                // ------------------------------------------------------------
                // ---------------------------- Constructor -------------------
                // ------------------------------------------------------------

                /// Default Constructor.
                EntryPointPublisher();

                /// Virtual destructor.
                /// Delete all entry points.
                /// @remarks This is needed to be able to destroy objects
                ///          using the actual derived object's destructor.
                virtual ~EntryPointPublisher();

                // ------------------------------------------------------------
                // ---------------------------- IEntryPointPublisher ----------
                // ------------------------------------------------------------

                /// Get all entry points.
                /// Query for the collection of all entry points of the model.
                /// @return Collection of entry points.
                /// @remarks The collection may be empty if no entry points exist.
                virtual const Smp::EntryPointCollection* GetEntryPoints() const;

                /// Get an entry point by name.
                /// Query for an entry point of this model by its name.
                /// @param  name Entry point name.
                /// @return  Entry point with given name, or null if no
                ///          entry point with given name could be found.
                /// @remarks The returned entry point may be null if no
                ///          entry point with the given name could be found.
                virtual const Smp::IEntryPoint* GetEntryPoint(Smp::String8 name) const;

            protected:
                // ------------------------------------------------------------
                // ---------------------------- Helper methods ----------------
                // ------------------------------------------------------------

                /// Add an entry point 
                /// @param  entryPoint EntryPoint to add.
                void AddEntryPoint(Smp::IEntryPoint* entryPoint);

                /// Delete all entryPoints
                void Clear();
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_ENTRYPOINTPUBLISHER_H_

/***********
 * History *
 ***********/

//$Log: EntryPointPublisher.h,v $
//Revision 1.2  2006/09/27 11:49:56  nin
//SMP2 v1.2
// 

