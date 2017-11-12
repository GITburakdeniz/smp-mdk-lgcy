//
// Title:
//      ManagedReference.h
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
//      This file defines the ManagedReference template, which provides
//      an implementation for the IManagedReference interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//
// Note:
//      As this class is a template class, its implementation is provided
//      in this header file as well, and instantiated on use.

#ifndef MDK_MANAGEMENT_MANAGEDREFERENCE_H_
#define MDK_MANAGEMENT_MANAGEDREFERENCE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Mdk/Reference.h"
#include "Smp/Management/IManagedReference.h"

// ----------------------------------------------------------------------------
// ---------------------------- ManagedReference ------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{ 
    namespace Mdk
    {
        namespace Management
        {
            /// Managed Reference.
            /// This is the MDK template for the IManagedReference interface.
            template <class Interface>
            class ManagedReference:
                public Reference<Interface>,
                public virtual Smp::Management::IManagedReference
            {
            private:
                Smp::Int64 m_lower;     ///< Lower limit for multiplicity.
                Smp::Int64 m_upper;     ///< Upper limit for multiplicity.

            public:
                // ------------------------------------------------------------
                // ------------------------- Constructor ----------------------
                // ------------------------------------------------------------

                /// Constructor with name, description, parent, and range.
                /// @param name Name of reference.
                /// @param description Description of reference.
                /// @param parent Parent component of reference.
                /// @param lower Lower limit for multiplicity.
                /// @param upper Upper limit for multiplicity (-1=no limit).
                ManagedReference(
                    Smp::String8 name, 
                    Smp::String8 description, 
                    Smp::IComponent* parent, 
                    Smp::Int64 lower = 0, 
                    Smp::Int64 upper = -1)
                    : Reference<Interface>(name, description, parent),
                    m_lower(lower),
                    m_upper(upper)
                {
                }

                /// Virtual destructor.
                /// @remarks This is needed to be able to destroy objects
                ///          using the actual derived object's destructor.
                virtual ~ManagedReference()
                {
                }

                // ------------------------------------------------------------
                // ---------------------------- IManagedReference -------------
                // ------------------------------------------------------------

                /// Add component.
                /// Add a referenced component.
                /// @param   component New referenced component.
                /// @remarks This method raises a ReferenceFull exception if the 
                /// reference is full.
                virtual void AddComponent(Smp::IComponent* component) throw (
                    Smp::Management::IManagedReference::ReferenceFull,
                    Smp::InvalidObjectType)
                {
                    // Check multiplicity
                    if ((Upper() >= 0) && 
                        (Count() >= Upper()))
                    {
                        throw ReferenceFull(GetName(), Upper());
                    }

                    // Use base implementation to add the component
                    this->Add(component);
                }

                /// Remove component.
                /// Remove a referenced component.
                /// @param   component Referenced component to remove.
                /// @remarks This method raises a NotReferenced exception if the 
                ///          given component is not referenced.
                virtual void RemoveComponent(Smp::IComponent* component) throw (
                    Smp::Management::IManagedReference::NotReferenced)
                {
                    if (!this->Remove(component))
                    {
                        throw Smp::Management::IManagedReference::NotReferenced(this->GetName(), component);
                    }
                }

                /// Get the number of referenced components.
                /// Query for the number of referenced components.
                /// @return Current number of referenced components.
                virtual Smp::Int64 Count() const 
                { 
                    return Reference<Interface>::Count(); 
                }

                /// Get lower bound of multiplicity.
                /// Query the minimum number of components in the collection of references.
                /// @return Minimum number of referenced components.
                virtual Int64 Lower() const
                {
                    return m_lower;
                }

                /// Get upper bound for number of components.
                /// Query the maximum number of components in the collection of references.
                /// @return  Maximum number of referenced components (-1 = unlimited).
                /// @remarks A return value of -1 indicates that the reference has
                ///          no upper limit. This is consistent with the use of upper
                ///          bounds in UML, where a value of -1 represents no limit 
                ///          (typically shown as “*”).
                virtual Int64 Upper() const
                {
                    return m_upper;
                }
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_MANAGEDREFERENCE_H_

/***********
 * History *
 ***********/

//$Log: ManagedReference.h,v $
//Revision 1.2  2006/09/27 11:49:56  nin
//SMP2 v1.2
// 

