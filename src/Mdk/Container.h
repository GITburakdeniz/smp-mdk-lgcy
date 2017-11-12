//
// Title:
//      Container.h
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
//      This file defines the Container template, which provides
//      an implementation for the IContainer interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//
// Note:
//      As this class is a template class, its implementation is provided
//      in this header file as well, and instantiated on use.

#ifndef MDK_CONTAINER_H_
#define MDK_CONTAINER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Mdk/Component.h"
#include "Smp/IContainer.h"
#include "Smp/Management/IManagedContainer.h"

namespace Smp 
{ 
    namespace Mdk
    {
        /// Template that provides a type-safe container implementing IContainer.
        /// This template class implements the IContainer interface, and provides
        /// Helper methods for the implementation of IManagedContainer.
        template <class ComponentType>
        class Container :
            public Object,
            public virtual Smp::IContainer
        {
            // ----------------------------------------------------------------
            // ---------------------------- Typedefs --------------------------
            // ----------------------------------------------------------------

        public:
            /// This defines a typed collection of child components.
            typedef std::vector<ComponentType*> ChildCollection;

            /// Iterator type to iterate on contained components (types!).
            typedef typename ChildCollection::const_iterator ChildIterator;

            // ----------------------------------------------------------------
            // ---------------------------- Fields ----------------------------
            // ----------------------------------------------------------------

        private:
            Smp::ComponentCollection m_components;  ///< Untyped references.
            ChildCollection          m_children;    ///< Typed references.

        protected:
            // This needs to be protected to give access for ManagedContainer.
            Smp::IComposite*         m_parent;      ///< Parent component.

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Constructor with name, description and parent.
            /// @param name Name of container.
            /// @param description Description of container.
            /// @param parent Parent of container.
            Container(
                Smp::String8 name, 
                Smp::String8 description, 
                Smp::IComposite* parent)
                : Object(name, description), m_parent(parent)
            {
            }

            /// Virtual destructor.
            /// Clears the component collection.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Container()
            {
                Clear();
            }

            // ----------------------------------------------------------------
            // ---------------------------- IContainer ------------------------
            // ----------------------------------------------------------------

            /// Get all contained components.
            /// Query for the collection of all contained components.
            /// @return Collection of contained component.
            /// @remarks The collection may be empty if no components exist.
            virtual const Smp::ComponentCollection* GetComponents() const
            {
                return &m_components;
            }

            /// Get a contained component by name.
            /// Query for a contained component by its name.
            /// @param   name Child name.
            /// @return  Child component, or undefined if no component
            ///             with the given name is contained.
            /// @remarks The returned component may be undefined if no
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

            /// Get the number of contained components.
            /// Query for the number of contained components.
            /// @return Current number of contained components.
            virtual Smp::Int64 Count() const 
            { 
                return (Smp::Int64) m_components.size(); 
            }

            /// Iterator to iterate on contained components (typed!).
            ChildIterator Begin()
            {
                return m_children.begin();
            }

            /// Iterator to iterate on contained components (typed!).
            ChildIterator End()
            {
                return m_children.end();
            }

            /// Get a typed collection of all children.
            /// @return Collection of child components.
            const ChildCollection* GetChildren()
            {
                return &m_children;
            }

            /// Get a typed child by name.
            /// @param name Name of child to get.
            /// @return Child component with given name, or NULL for none.
            virtual ComponentType* GetChild(Smp::String8 name) const
            {
                return dynamic_cast <ComponentType*> (GetComponent(name));
            }

            /// Delete all child components.
            /// @remarks Delete references and components.
            void Clear()
            {
                // Delete components
                for (Smp::ComponentCollection::const_iterator it = m_components.begin();
                    it != m_components.end();
                    ++it)
                {
                    Smp::IComponent* component = *it;
                    delete component;
                }
                
                // Clear collections, thus deleting the references.
                m_children.clear();
                m_components.clear();
            }

        protected:
            /// Add a child component.
            /// @param component Component to add as a child.
            /// @remarks This method is called by derived classes.
            void Add(Smp::IComponent* component) throw (
                Smp::DuplicateName,
                Smp::InvalidObjectType)
            {
                // Need a component here to add.
                assert(component != NULL);

                // Check for duplicate names
                Smp::IComponent* duplicate = GetComponent(component->GetName());
                if (duplicate)
                {
                    throw Smp::DuplicateName(component->GetName());
                }

                // Check type of child component
                ComponentType* child = dynamic_cast<ComponentType*>(component);
                if (!child)
                {
                    throw Smp::InvalidObjectType(component);
                }

                // Save in typed container
                m_children.push_back(child);

                // Save in untyped container
                m_components.push_back(component);
            }
        };
    }
}

#endif  // MDK_CONTAINER_H_

/***********
 * History *
 ***********/

//$Log: Container.h,v $
//Revision 1.3  2008/02/19 18:39:12  nin
//SPR-721: Memory leak analysis of the SMP2 Adapter
//
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

