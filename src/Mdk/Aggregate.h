//
// Title:
//      Aggregate.h
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
//      This file defines the Aggregate class, which provides
//      an implementation for the IAggregate interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_AGGREGATE_H_
#define MDK_AGGREGATE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IAggregate.h"

namespace Smp 
{ 
    namespace Mdk
    {
        /// Aggregate component implementing the IAggregate interface.
        /// This is the MDK implementation for the IAggregate interface.
        class Aggregate : public virtual Smp::IAggregate
        {
        private:
            /// Collection of references.
            Smp::ReferenceCollection m_references;

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Default Constructor.
            Aggregate();

            /// Virtual destructor.
            /// Clears the reference collection.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Aggregate();

            // ----------------------------------------------------------------
            // ---------------------------- IAggregate ------------------------
            // ----------------------------------------------------------------

            /// Get all references.
            /// Query for the collection of all references of the component.
            /// @return  Collection of references.
            /// @remarks The collection may be empty if no references exist.
            virtual const Smp::ReferenceCollection* GetReferences() const;

            /// Get a reference by name.
            /// Query for a reference of this component by its name.
            /// @param   name Reference name.
            /// @return  Reference with the given name, or null if no
            ///          reference with the given name could be found.
            /// @remarks The returned reference may be null if no
            ///          reference with the given name could be found.
            virtual Smp::IReference* GetReference(Smp::String8 name) const;

        protected:
            // ----------------------------------------------------------------
            // ---------------------------- Helper methods --------------------
            // ----------------------------------------------------------------

            /// Add a reference 
            /// @param  reference Reference to add.
            void AddReference(Smp::IReference* reference);

            /// Delete all references
            void Clear();
        };
    }
}

#endif  // MDK_AGGREGATE_H_

/***********
 * History *
 ***********/

//$Log: Aggregate.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

