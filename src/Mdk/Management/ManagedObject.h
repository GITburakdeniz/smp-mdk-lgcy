//
// Title:
//      ManagedObject.h
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
//      This file defines the ManagedObject class, which provides
//      an implementation for the IManagedObject interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_MANAGEMENT_MANAGEDOBJECT_H_
#define MDK_MANAGEMENT_MANAGEDOBJECT_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Mdk/Object.h"
#include "Smp/Management/IManagedObject.h"

namespace Smp 
{ 
    namespace Mdk
    {
        namespace Management 
        {
            /// Managed Object.
            /// This is the MDK implementation for the IManagedObject interface.
            class ManagedObject :
                public Object,
                public virtual Smp::Management::IManagedObject
            {
            public:
                // ------------------------------------------------------------
                // ---------------------------- Constructor -------------------
                // ------------------------------------------------------------

                /// Default Constructor.
                ManagedObject();

                /// Constructor with name and description.
                /// @param name Name of object.
                /// @param description Description of object.
                ManagedObject(Smp::String8 name, Smp::String8 description);

                /// Virtual destructor.
                /// @remarks This is needed to be able to destroy objects
                ///          using the actual derived object's destructor.
                virtual ~ManagedObject();

                // ------------------------------------------------------------
                // ---------------------------- IManagedObject ----------------
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
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_MANAGEDOBJECT_H_

/***********
 * History *
 ***********/

//$Log: ManagedObject.h,v $
//Revision 1.2  2006/09/27 11:49:56  nin
//SMP2 v1.2
// 

