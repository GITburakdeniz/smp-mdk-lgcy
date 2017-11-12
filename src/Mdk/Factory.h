//
// Title:
//      Factory.h
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
//      This file defines the Factory class, which provides
//      an implementation for the IFactory interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_FACTORY_H_
#define MDK_FACTORY_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IFactory.h"
#include "Mdk/Object.h"

// ----------------------------------------------------------------------------
// ---------------------------- Factory ---------------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Mdk
    {
        /// Template that implements the IFactory interface.
        /// This template class provides an implementation of the IFactory
        /// interface. It can be applied to any type that implements the
        /// IComponent interface.
        template <class ComponentType>
        class Factory :
            public Smp::Mdk::Object,
            public virtual Smp::IFactory
        {
        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor with name and description.
            /// @param name Name of component.
            /// @param description Description of component.
            /// @param specification Specification Uuid of component.
            /// @param implementation Implementation Uuid of component.
            /// @remarks The implementation Uuid needs to be unique.
            Factory(
                Smp::String8 name, 
                Smp::String8 description,
                Smp::Uuid specification,
                Smp::Uuid implementation)
                : Smp::Mdk::Object(name, description),
                m_specification(specification),
                m_implementation(implementation)
            {
            }

            /// Virtual destructor.
            /// Releases the name and parameter.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Factory()
            {
            }

            // ----------------------------------------------------------------
            // ---------------------------- IFactory --------------------------
            // ----------------------------------------------------------------

            /// Get specification identifier of factory.
            /// @return  Identifier of component specification.
            Smp::Uuid GetSpecification() const
            {
                return m_specification;
            }

            /// Get implementation identifier of factory.
            /// @return  Identifier of component implementation.
            Smp::Uuid GetImplementation() const
            {
                return m_implementation;
            }

            /// Create a new instance.
            /// This method creates a new component instance.
            Smp::IComponent* CreateInstance()
            {
                return new ComponentType();
            }

            /// Delete an existing instance.
            /// This method deletes an existing component instance that has been 
            /// created using CreateInstance() earlier.
            /// @param instance Instance to delete.
            void DeleteInstance(Smp::IComponent* instance)
            {
                assert(instance);

                if (instance != NULL)
                {
                    delete instance;
                }
            }

        private:
            /// Specification identifier in a Catalogue.
            Smp::Uuid m_specification;
            /// Implementation identifier of the Model.
            Smp::Uuid m_implementation;
        };
    }
}

#endif  // MDK_FACTORY_H_

/***********
 * History *
 ***********/

//$Log: Factory.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

