//
// Title:
//      ManagedModel.h
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
//      This file defines the ManagedModel class, which provides
//      an implementation for the IManagedModel interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_MANAGEMENT_MANAGEDMODEL_H_
#define MDK_MANAGEMENT_MANAGEDMODEL_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include <string>

#include "Mdk/Model.h"
#include "Smp/Management/IManagedModel.h"

// ----------------------------------------------------------------------------
// ---------------------------- ManagedModel ----------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{ 
    namespace Mdk
    {
        namespace Management
        {
            /// Managed Model.
            /// This is the MDK implementation for the IManagedModel interface.
            class ManagedModel:
                public Model,
                public virtual Smp::Management::IManagedModel
            {
            public:
                // ------------------------------------------------------------
                // ------------------------- Constructor ----------------------
                // ------------------------------------------------------------

                /// Default constructor.
                ManagedModel();

                /// Constructor with name, description and parent.
                /// @param name Name of model.
                /// @param description Description of model.
                /// @param parent Parent of model.
                ManagedModel(Smp::String8 name, 
                             Smp::String8 description, 
                             Smp::IComposite* parent) throw (Smp::InvalidObjectName);

                /// Virtual destructor.
                /// @remarks This is needed to be able to destroy objects
                ///          using the actual derived object's destructor.
                virtual ~ManagedModel();

                // ------------------------------------------------------------
                // ---------------------------- IManagedModel -----------------
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

                /// Get the value of a field which is typed by a simple type.
                /// @param   fullName Fully qualified field name.
                /// @return  value Field value.
                /// @remarks This method can only be used to get values of simple
                ///          fields. For setting values of structured fields,
                ///          this method may be called multiply, e.g. specifying
                ///          "Position.x" to get the x component of a position.
                ///          For arrays of simple type, use GetArrayValue.
                virtual Smp::AnySimple GetFieldValue(String8 fullName) throw (
                    Smp::Management::IManagedModel::InvalidFieldName);

                /// Set the value of a field which is typed by a simple type.
                /// @param   fullName Fully qualified field name.
                /// @param   value Field value.
                /// @remarks This method can only be used to set values of simple
                ///          fields. For setting values of structured fields,
                ///          this method may be called multiply, e.g. specifying
                ///          "Position.x" to set the x component of a position.
                ///          For arrays of simple type, use SetArrayValue.
                virtual void SetFieldValue(
                    String8 fullName, 
                    const Smp::AnySimple value) throw (
                Smp::Management::IManagedModel::InvalidFieldName, 
                Smp::Management::IManagedModel::InvalidFieldValue);

                /// Get the value of an array field which is typed by a system type.
                /// @param   fullName Fully qualified array field name.
                /// @param   values Array of field values.
                /// @param   length Length of array for safety checks.
                /// @remarks This method can only be used to get values of arrays of
                ///          simple type. These may be nested in a structure or array.
                virtual void GetArrayValue(
                    String8 fullName,
                    const AnySimpleArray values,
                    const Int32 length) throw (
                    Smp::Management::IManagedModel::InvalidFieldName, 
                    Smp::Management::IManagedModel::InvalidArraySize);

                /// Set the value of an array field which is typed by a system type.
                /// @param   fullName Fully qualified array field name.
                /// @param   values Array of field values.
                /// @param   length Length of array for safety checks.
                /// @remarks This method can only be used to set values of arrays of
                ///          system type. For setting values of structured or array
                ///          fields, this method may be called multiply, e.g. by
                ///          specifying a field name "MyField.Position[2]"
                ///          in order to access an array item of a structure.
                virtual void SetArrayValue(
                    String8 fullName, 
                    const AnySimpleArray values, 
                    const Int32 length) throw (
                    Smp::Management::IManagedModel::InvalidFieldName, 
                    Smp::Management::IManagedModel::InvalidArraySize, 
                    Smp::Management::IManagedModel::InvalidArrayValue);
            };
        }
    }
}

#endif  // MDK_MANAGEMENT_MANAGEDMODEL_H_

/***********
 * History *
 ***********/

//$Log: ManagedModel.h,v $
//Revision 1.2  2006/09/27 11:49:56  nin
//SMP2 v1.2
// 

