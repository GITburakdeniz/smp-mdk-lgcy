//
// Title:
//      Component.h
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
//      This file defines the Component class, which provides
//      an implementation for the IComponent interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_COMPONENT_H_
#define MDK_COMPONENT_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"
#include "Mdk/Object.h"

namespace Smp 
{
    // Forward declaration because of circular references.
    class IComposite;

    namespace Mdk
    {
        /// Component implementing of IComponent interface.
        /// This is the MDK implementation for the IComponent interface.
        /// It is derived from Object.
        class Component:
            public Smp::Mdk::Object,
            public virtual Smp::IComponent
        {
        protected:
            /// Parent of component.
            /// Protected field to store reference to parent component.
            /// @remarks This field needs to be protected to give access to the
            ///          derived class ManagedComponent.
            IComposite* m_parent;

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Default constructor.
            Component();

            /// Constructor with name, description, and parent.
            /// @param name Name of component.
            /// @param description Description of component.
            /// @param parent Parent of component.
            Component(
                Smp::String8 name, 
                Smp::String8 description, 
                IComposite* parent) throw (Smp::InvalidObjectName);

            /// Virtual destructor.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Component();

            // ----------------------------------------------------------------
            // ---------------------------- IComponent ------------------------
            // ----------------------------------------------------------------

            /// Returns the parent component of the component ("property getter").
            /// Components link to their parent to allow traversing the
            /// tree of components upwards to the root component, which is 
            /// typically the simulation environment (ISimulator).
            /// @return  Parent component of component, or null if component
            ///          has no parent.
            /// @remarks Components that are part of a composition
            ///          point to their parent via this property.
            ///          The parent is null for root components.
            ///          Typically, only the simulator itself is a root component,
            ///          so all other components should have a parent component.
            virtual IComposite* GetParent() const;
        };
    }
}

#endif  // MDK_COMPONENT_H_

/***********
 * History *
 ***********/

//$Log: Component.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

