//
// Title:
//      ManagedComponent.h
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
//      This file defines the ManagedComponent class, which provides
//      an implementation for the IManagedComponent interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_MANAGEMENT_MANAGEDCOMPONENT_H_
#define MDK_MANAGEMENT_MANAGEDCOMPONENT_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Mdk/Component.h"
#include "Smp/Management/IManagedComponent.h"

namespace Smp 
{ 
    namespace Mdk
    {
        namespace Management
        {
            /// Managed Component.
            /// This is the MDK implementation for the IManagedComponent interface.
            class ManagedComponent:
                public Component,
                public virtual Smp::Management::IManagedComponent
            {
            public:
                // ------------------------------------------------------------
                // ---------------------------- Constructor -------------------
                // ------------------------------------------------------------

                /// Default Constructor.
                ManagedComponent();

                /// Constructor with name, description, and parent.
                /// @param name Name of component.
                /// @param description Description of component.
                /// @param parent Parent of component.
                ManagedComponent(
                    Smp::String8 name, 
                    Smp::String8 description, 
                    IComposite* parent);

                /// Virtual destructor.
                /// @remarks This is needed to be able to destroy objects
                ///          using the actual derived object's destructor.
                virtual ~ManagedComponent();

                // ------------------------------------------------------------
                // ---------------------------- IManagedComponent -------------
                // ------------------------------------------------------------

                /// Defines the name of the managed object ("property setter").
                /// Management components may use this to assign names to objects.
                /// @param   name Name of object.
                /// @remarks Names 
                ///          - must be unique within their context,
                ///          - must not be empty, 
                ///          - must not exceed 32 characters in size,
                ///          - must start with a letter, and
                ///          - must only contain letters, digits, the underscore ("_")
                ///            and brackets ("[" and "]").
                virtual void SetName(String8 name) throw (
                    Smp::InvalidObjectName);

                /// Defines the description of the managed object ("property setter").
                /// Management components may use this to set object descriptions.
                /// @param   description Description of object.
                virtual void SetDescription(String8 description);

                /// Defines the parent component ("property setter").
                /// Components link to their parent to allow traversing the
                /// tree of components in any direction.
                /// @param   parent Parent of component.
                /// @remarks Components that are part of a composition 
                ///          point to their parent via this property.
                ///          The parent is null for root components.
                virtual void SetParent(IComposite* parent);
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_MANAGEDCOMPONENT_H_

/***********
 * History *
 ***********/

//$Log: ManagedComponent.h,v $
//Revision 1.2  2006/09/27 11:49:56  nin
//SMP2 v1.2
// 

