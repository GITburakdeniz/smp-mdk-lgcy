//
// Title:
//      Request.h
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
//      This file defines the Request class, which provides
//      an implementation for the IRequest interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_REQUEST_H_
#define MDK_REQUEST_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IRequest.h"
#include "Mdk/SimpleTypes.h"

// ----------------------------------------------------------------------------
// ---------------------------- Parameter -------------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Mdk
    {
        /// Helper class for a parameter.
        /// This class is used by the Request class to store the parameters.
        class Parameter
        {
        private:
            char* m_name;                   ///< Name  of parameter.
            Smp::Mdk::AnySimple m_value;    ///< Value of parameter.

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor with name and type.
            /// @param name Name of parameter.
            /// @param type Type of parameter.
            Parameter(Smp::String8 name, Smp::SimpleTypeKind type);

            /// Virtual destructor.
            /// Releases the name.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Parameter();

            // ----------------------------------------------------------------
            // ---------------------------- Getter methods --------------------
            // ----------------------------------------------------------------

            /// Returns the name of the parameter.
            /// @return  Name of parameter.
            Smp::String8 GetName() const;

            /// Returns the type of the parameter.
            /// @return  Type of parameter.
            Smp::SimpleTypeKind GetType() const;

            /// Returns the value of the parameter.
            /// @return  Value of parameter.
            Smp::AnySimple GetValue() const;

            // ----------------------------------------------------------------
            // ---------------------------- Setter methods --------------------
            // ----------------------------------------------------------------

            /// Set the value of the parameter.
            /// @param value Value of parameter.
            void SetValue(const Smp::AnySimple value) throw
                (Smp::InvalidAnyType);
        };

        /// Collection of parameters.
        typedef std::vector<Parameter*> ParameterCollection;
    }
}

// ----------------------------------------------------------------------------
// ---------------------------- Request ---------------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Mdk
    {
        /// Request object implementing IRequest.
        /// This is the MDK implementation for the IRequest interface.
        class Request : public virtual Smp::IRequest
        {
        private:
            char*                m_name;        ///< Name of operation
            ParameterCollection* m_parameters;  ///< Parameters of operation.
            Smp::Mdk::AnySimple  m_returnValue; ///< Return value of operation.

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor with name and return type.
            /// @param name Name of operation.
            /// @param type Return type of operation.
            /// @remarks Use ST_None for void operations.
            Request(Smp::String8 name, Smp::SimpleTypeKind type = Smp::ST_None);

            /// Virtual destructor.
            /// Releases the name and parameters.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Request();

            // ----------------------------------------------------------------
            // ---------------------------- IRequest --------------------------
            // ----------------------------------------------------------------

            /// Get operation name.
            /// Returns the name of the operation that this request is for.
            /// @remarks A request is typically created using the CreateRequest() 
            ///          method to dynamically call a specific method of a component
            ///          implementing the IDynamicInvocation interface.
            ///          This method returns the name passed to it, to allow finding
            ///          out which method is actually called on Invoke().
            Smp::String8 GetOperationName() const;

            /// Get parameter count.
            /// Returns the number of parameters stored in the request.
            /// @remarks Parameters are typically accessed by their 0-based index.
            ///          This index 
            ///          - must not be negative, 
            ///          - must be smaller than the parameter count.
            ///
            ///          Use the GetParameterIndex() method to access parameters by
            ///          name.
            Smp::Int32 GetParameterCount() const;

            /// Get index of a parameter.
            /// Query for a parameter index by parameter name.
            /// @param   parameterName Name of parameter.
            /// @return  Index of parameter with the given name (0-based), or 
            ///          -1 if no parameter with the given name could be found.
            /// @remarks An index of -1 indicates that no parameter with the
            ///          given name exists.
            Smp::Int32 GetParameterIndex(String8 parameterName) const;

            /// Set a parameter value.
            /// Assign a value to a parameter at a given position.
            /// @param   index Index of parameter (0-based).
            /// @param   value Value of parameter.
            void SetParameterValue(
                const Smp::Int32 index, 
                const Smp::AnySimple value) throw (
                Smp::InvalidAnyType,
                Smp::IRequest::InvalidParameterIndex, 
                Smp::IRequest::InvalidParameterValue);

            /// Get a parameter value.
            /// Query a value of a parameter at a given position.
            /// @param   index Index of parameter (0-based).
            /// @return  Value of parameter with given index.
            Smp::AnySimple GetParameterValue(const Smp::Int32 index) const throw (
                Smp::IRequest::InvalidParameterIndex);

            /// Set the return value.
            /// Assign the return value of the operation.
            /// @param   value Return value.
            void SetReturnValue(const Smp::AnySimple value) throw (
                Smp::IRequest::InvalidReturnValue, 
                Smp::IRequest::VoidOperation,
                Smp::InvalidAnyType);

            /// Get the return value.
            /// Query the return value of the operation.
            /// @return  Return value of the operation.
            Smp::AnySimple GetReturnValue() const throw (
                Smp::IRequest::VoidOperation);

            // ----------------------------------------------------------------
            // ---------------------------- Helper methods --------------------
            // ----------------------------------------------------------------

            /// Add a parameter. 
            /// @param name Name of parameter.
            /// @param type Type of parameter.
            /// @remarks Only parameters of simple types are allowed.
            virtual void AddParameter(const Smp::String8 name, 
                                      const Smp::SimpleTypeKind type);
        };
    }
}

#endif  // MDK_REQUEST_H_

/***********
 * History *
 ***********/

//$Log: Request.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

