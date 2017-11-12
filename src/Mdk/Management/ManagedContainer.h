//
// Title:
//      ManagedContainer.h
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
//      This file defines the ManagedContainer template, which provides
//      an implementation for the IManagedContainer interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//
// Note:
//      As this class is a template class, its implementation is provided
//      in this header file as well, and instantiated on use.

#ifndef MDK_MANAGEMENT_MANAGEDCONTAINER_H_
#define MDK_MANAGEMENT_MANAGEDCONTAINER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include <map>
#include <string>

#include "Mdk/Container.h"
#include "Smp/Management/IManagedContainer.h"
#include "Smp/Management/IManagedComponent.h"

namespace Smp 
{ 
    namespace Mdk
    {
        namespace Management
        {
            /// Managed Container..
            /// This is the MDK template for the IManagerContainer interface.
            template <class ReferenceType>
            class ManagedContainer:
                public Container<ReferenceType>,
                public virtual Smp::Management::IManagedContainer
            {
            private:
                Int64 m_lower;  ///< Lower bound for components.
                Int64 m_upper;  ///< Upper bound for components (-1=no bound).

            public:
                // ------------------------------------------------------------
                // ---------------------------- Constructor -------------------
                // ------------------------------------------------------------

                /// Constructor with name, description, parent, and range.
                ManagedContainer(
                    Smp::String8 name, 
                    Smp::String8 description, 
                    Smp::IComposite* parent, 
                    Int64 lower = 0, 
                    Int64 upper = -1)
                    : Container<ReferenceType>(name, description, parent),
                    m_lower(lower),
                    m_upper(upper)
                {
                }

                /// Virtual destructor.
                /// @remarks This is needed to be able to destroy objects
                ///          using the actual derived object's destructor.
                virtual ~ManagedContainer() {}

                // ------------------------------------------------------------
                // ---------------------------- IManagedContainer -------------
                // ------------------------------------------------------------

                /// Add component.
                /// Add a contained component to the container.
                /// @param  component New contained component.
                /// @return Index in container (0-based).
                /// @remarks This method raises a ContainerFull exception if the 
                /// container is full.
                virtual void AddComponent(Smp::IComponent* component) throw (
                    Smp::Management::IManagedContainer::ContainerFull, 
                    Smp::DuplicateName,
                    Smp::InvalidObjectType)
                {
                    // Check multiplicity
                    if ((Upper() >= 0) && 
                        (Count() >= Upper()))
                    {
                        throw ContainerFull(GetName(), Upper());
                    }

                    // Use base implementation to add the component
                    this->Add(component);

                    // Check if component is manageable
                    Smp::Management::IManagedComponent* managedComponent = dynamic_cast<Smp::Management::IManagedComponent*>(component);
                    if (managedComponent != NULL)
                    {
                        // The parent of the component is the parent of the container
                        managedComponent->SetParent(this->m_parent);
                    }
                }

                /// Get the number of contained components.
                /// Query for the number of components in the container.
                /// @return Current number of components.
                virtual Smp::Int64 Count() const 
                { 
                    return Container<ReferenceType>::Count(); 
                }

                /// Get lower bound of multiplicity.
                /// Query the minimum number of components in the container.
                /// @return Minimum number of components.
                virtual Int64 Lower() const
                {
                    return m_lower;
                }

                /// Get upper bound for number of components.
                /// Query the maximum number of components in the container.
                /// @return  Maximum number of contained components (-1 = unlimited).
                /// @remarks A return value of -1 indicates that the container has
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

#endif  // MDK_MANAGEMENT_MANAGEDCONTAINER_H_

/***********
 * History *
 ***********/

//$Log: ManagedContainer.h,v $
//Revision 1.2  2006/09/27 11:49:56  nin
//SMP2 v1.2
// 

