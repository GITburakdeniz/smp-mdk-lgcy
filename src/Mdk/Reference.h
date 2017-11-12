//
// Title:
//      Reference.h
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
//      This file defines the Reference template, which provides
//      an implementation for the IReference interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//
// Note:
//      As this class is a template class, its implementation is provided
//      in this header file as well, and instantiated on use.

#ifndef MDK_REFERENCE_H_
#define MDK_REFERENCE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Mdk/Object.h"
#include "Smp/IReference.h"

// ----------------------------------------------------------------------------
// ---------------------------- Reference -------------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{ 
    namespace Mdk
    {
        /// Template that provides a type-safe reference implementing IReference.
        /// This template class implements the IReference interface, and provides
        /// Helper methods for the implementation of IManagedReference.
        template <class ComponentType>
        class Reference :
            public Object,
            public virtual Smp::IReference
        {
            // ----------------------------------------------------------------
            // ---------------------------- Typedefs --------------------------
            // ----------------------------------------------------------------

        public:
            /// This defines a typed collection of provider components.
            typedef typename std::vector<ComponentType*> ProviderCollection;

            /// Iterator type to iterate on referenced components (typed!).
            typedef typename ProviderCollection::const_iterator ProviderIterator;

            // ----------------------------------------------------------------
            // ---------------------------- Fields ----------------------------
            // ----------------------------------------------------------------

        private:
            Smp::IComponent*         m_parent;      ///< Parent component.
            Smp::ComponentCollection m_components;  ///< Untyped references.
            ProviderCollection       m_providers;   ///< Typed references.

            /// Iterator type to iterate on referenced components (typed!).
            typedef typename ProviderCollection::iterator _ProviderIterator;

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor for name, description, parent.
            /// @param name Name of reference.
            /// @param description Description of reference.
            /// @param parent Parent component of reference.
            Reference(
                Smp::String8 name, 
                Smp::String8 description, 
                Smp::IComponent* parent)
                : Object(name, description), m_parent(parent)
            {
            }

            /// Virtual destructor.
            /// Clears the component collection.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Reference()
            {
                Clear();
            }

            // ----------------------------------------------------------------
            // ---------------------------- IReference ------------------------
            // ----------------------------------------------------------------

            /// Get all referenced components.
            /// Query for the collection of all referenced components.
            /// @return Collection of referenced components.
            /// @remarks The collection may be empty if no components exist.
            virtual const Smp::ComponentCollection* GetComponents() const
            {
                return &m_components;
            }

            /// Get a referenced component by name.
            /// Query for a referenced component by its name.
            /// @param   name Component name.
            /// @return  Referenced component with the given name, or null if no 
            ///          referenced component with the given name could be found.
            /// @remarks The returned component may be null if no
            ///          component with the given name could be found.
            virtual Smp::IComponent* GetComponent(Smp::String8 name) const
            {
                for (Smp::ComponentCollection::const_iterator it = m_components.begin();
                    it != m_components.end();
                    it++)
                {
                    Smp::IComponent* component = *it;
                    if (component && strcmp(component->GetName(), name) == 0)
                    {
                        return component;
                    }
                }

                return NULL;
            }

            // ----------------------------------------------------------------
            // ---------------------------- Helper methods --------------------
            // ----------------------------------------------------------------

            /// Get the number of referenced components.
            /// Query for the number of referenced components.
            /// @return Current number of referenced components.
            virtual Smp::Int64 Count() const 
            { 
                return (Smp::Int64) m_components.size(); 
            }

            /// Iterator to iterate on linked interfaces (typed!).
            ProviderIterator Begin()
            {
                return m_providers.begin();
            }

            /// Iterator to iterate on linked interfaces (typed!).
            ProviderIterator End()
            {
                return m_providers.end();
            }

            /// Delete all provider components.
            /// @remarks Only the references are deleted!
            void Clear()
            {
                m_providers.clear();
                m_components.clear();
            }

        protected:
            /// Add a provider component (called by derived classes).
            /// @param component Component to add to reference.
            void Add(Smp::IComponent* component) throw (
                Smp::InvalidObjectType)
            {
                // Need a component here to add.
                assert(component != NULL);

                // Check type of provider component
                ComponentType* provider = dynamic_cast<ComponentType*>(component);
                if (!provider)
                {
                    throw Smp::InvalidObjectType(component);
                }

                // Save in typed container
                m_providers.push_back(provider);

                // Save in untyped container
                m_components.push_back(component);
            }

            /// Remove a provider component (called by derived classes).
            /// @param component Component to remove from reference.
            Smp::Bool Remove(Smp::IComponent* component)
            {
                // Need a component here to add.
                assert(component != NULL);

                // Check type of provider component
                ComponentType* provider = dynamic_cast<ComponentType*>(component);
                if (!provider)
                {
                    return false;
                }

                // Search in untyped container
                Smp::ComponentCollection::iterator component_it;
                for (Smp::ComponentCollection::iterator it = m_components.begin();
                    it != m_components.end();
                    it++)
                {
                    if (*it == component)
                    {
                        component_it = it;
                        break;
                    }
                }

                // Search in typed container
                _ProviderIterator provider_it;
                for (_ProviderIterator it = m_providers.begin();
                    it != m_providers.end();
                    it++)
                {
                    if (*it == provider)
                    {
                        provider_it = it;
                        break;
                    }
                }

                if ((component_it != m_components.end()) && 
                    (provider_it != m_providers.end()))
                {
                    m_components.erase(component_it);
                    m_providers.erase(provider_it);

                    // Return success
                    return true;
                }

                return false;
            }
        };
    }
}

#endif  // MDK_REFERENCE_H_

/***********
 * History *
 ***********/

//$Log: Reference.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

