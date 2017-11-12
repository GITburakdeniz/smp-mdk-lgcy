//
// Title:
//      Object.h
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
//      This file defines the Object class, which provides
//      an implementation for the IObject interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_OBJECT_H_
#define MDK_OBJECT_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IObject.h"
#include "Smp/Exceptions.h"

// ----------------------------------------------------------------------------
// ---------------------------- Object ----------------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{ 
    namespace Mdk
    {
        /// Object implementing the IObject interface.
        /// This is the MDK implementation for the IObject interface.
        class Object : public virtual Smp::IObject
        {
        protected:
            // These fields need to be protected for ManagedObject.
            char* m_name;           ///< Name of object.
            char* m_description;    ///< Description of object.

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Default constructor.
            Object();

            /// Constructor with name and description.
            /// @param name Name of object.
            /// @param description Description of object.
            Object(Smp::String8 name, Smp::String8 description) throw (
                Smp::InvalidObjectName);
 
            /// Virtual destructor.
            /// Release name and description.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Object();

            // ----------------------------------------------------------------
            // ---------------------------- IObject ---------------------------
            // ----------------------------------------------------------------

            /// Returns the name of the object ("property getter").
            /// Applications may display the name as user readable object
            /// identification.
            /// @return  Name of object.
            /// @remarks Names 
            ///          - must be unique within their context,
            ///          - must not be empty, 
            ///          - must not exceed 32 characters in size,
            ///          - must start with a letter, and
            ///          - must only contain letters, digits, the underscore ("_")
            ///            and brackets ("[" and "]").
            virtual Smp::String8 GetName() const;

            /// Returns the description of the object ("property getter").
            /// Applications may display the description as additional
            /// information on the object.
            /// @return  Description of object.
            /// @remarks Descriptions are optional and may be empty.
            virtual Smp::String8 GetDescription() const;

            // ----------------------------------------------------------------
            // ---------------------------- Helper methods --------------------
            // ----------------------------------------------------------------

            /// Validate the name for rules mentioned at SetName().
            /// @param name Name to validate.
            /// @returns True if name is valid, false otherwise.
            static Smp::Bool ValidateName(Smp::String8 name);
        };
    }
}

#endif  // MDK_OBJECT_H_

/***********
 * History *
 ***********/

//$Log: Object.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

