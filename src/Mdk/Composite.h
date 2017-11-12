//
// Title:
//      Composite.h
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
//      This file defines the Composite class, which provides
//      an implementation for the IComposite interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_COMPOSITE_H_
#define MDK_COMPOSITE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComposite.h"
#include "Mdk/Component.h"

namespace Smp
{
    namespace Mdk
    {
        /// Composite component implementing of IComposite interface.
        /// This is the MDK implementation for the IComposite interface.
        class Composite : public virtual Smp::IComposite
        {
        private:
            /// Collection of containers
            Smp::ContainerCollection m_containers;

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Default Constructor.
            Composite();

            /// Virtual destructor.
            /// Clears the container collection.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Composite();

            // ----------------------------------------------------------------
            // ---------------------------- IComposite ------------------------
            // ----------------------------------------------------------------

            /// Get all containers.
            /// Query for the collection of all containers of the component.
            /// @return Collection of containers.
            /// @remarks The collection may be empty if no containers exist.
            virtual const Smp::ContainerCollection* GetContainers() const;

            /// Get a container by name.
            /// Query for a container of this component by its name.
            /// @param   name Container name.
            /// @return  Container queried for by name, or undefined if
            ///             no container with this name exists.
            /// @remarks The returned container may be undefined if no
            ///          container with the given name could be found.
            virtual Smp::IContainer* GetContainer(Smp::String8 name) const;

        protected:
            // ----------------------------------------------------------------
            // ---------------------------- Helper methods --------------------
            // ----------------------------------------------------------------

            /// Add a container 
            /// @param  container Container to add.
            void AddContainer(Smp::IContainer* container);

            /// Delete all containers
            void Clear();
        };
    }
}

#endif  // MDK_COMPOSITE_H_

/***********
 * History *
 ***********/

//$Log: Composite.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

