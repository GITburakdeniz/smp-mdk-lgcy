//
// Title:
//      Model.h
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
//      This file defines the Model class, which provides
//      an implementation for the IModel interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_MODEL_H_
#define MDK_MODEL_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/IModel.h"
#include "Smp/IService.h"
#include "Mdk/Component.h"
#include "Smp/ISimulator.h"
#include "Smp/IPublication.h"

// ----------------------------------------------------------------------------
// ---------------------------- Model -----------------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{ 
    namespace Mdk
    {
        /// Model implementing the IModel interface.
        /// This class provides an implementation of the IModel interface.
        /// It can be used as base class for unmanaged models.
        class Model:
            public Component,
            public virtual Smp::IModel
        {
        protected:
            Smp::ModelStateKind m_state;        ///< Model state kind.
            Smp::ISimulator*    m_simulator;    ///< Simulator interface.
            Smp::IPublication*  m_publication;  ///< Publication receiver.

        public:
            // ----------------------------------------------------------------
            // ---------------------------- Constructor -----------------------
            // ----------------------------------------------------------------

            /// Default constructor.
            Model();

            /// Constructor with name, description and parent.
            /// @param name Name of model.
            /// @param description Description of model.
            /// @param parent Parent of model.
            Model(Smp::String8 name, 
                  Smp::String8 description, 
                  Smp::IComposite* parent) throw (Smp::InvalidObjectName);

            /// Virtual destructor.
            /// @remarks This is needed to be able to destroy objects
            ///          using the actual derived object's destructor.
            virtual ~Model();

            // ----------------------------------------------------------------
            // ---------------------------- IModel ----------------------------
            // ----------------------------------------------------------------

            /// Return model state.
            /// Return the state the model is currently in.
            /// @return  Current model state.
            /// @remarks The model state can be changed using the Publish(), 
            ///          Configure() and Connect() state transition methods.
            ModelStateKind GetState() const;

            /// Request for publication.
            /// Request the model to publish its fields and operations
            /// against the provided IPublication interface.
            /// @par
            /// This method can only be called once for each model, and only
            /// when the model is in the <em>Created</em> state.
            /// When this operation is called, the model immediately enters
            /// the <em>Publishing</em> state, before it publishes any of its
            /// features.
            /// @param   receiver Publication receiver.
            /// @remarks The simulation environment typically calls this
            ///          method in the <em>Building</em> state.
            void Publish(IPublication* receiver) throw (
                Smp::IModel::InvalidModelState);

            /// Request for configuration.
            /// Request the model to perform any custom configuration.
            /// The model can create and configure other models using
            /// the field values of its published fields.
            /// @par
            /// This method can only be called once for each model, and only
            /// when the model is in <em>Publishing</em> state. The model can still
            /// publish further features in this call, and can even create other
            /// models, but at the end of this call, it needs to enter the
            /// <em>Configured</em> state.
            /// @param   logger Logger.
            /// @remarks The simulation environment typically calls this
            ///          method in the <em>Building</em> state.
            void Configure(Smp::Services::ILogger* logger) throw (
                Smp::IModel::InvalidModelState);

            /// Connect model to simulator.
            /// Allow the model to connect to the simulator (ISimulator).
            /// @par
            /// This method can only be called once for each model, and only
            /// when the model is in the <em>Configured</em> state.
            /// When this operation is called, the model immediately enters
            /// the <em>Connected</em> state, before it uses any of the simulator
            /// methods and services.
            /// @par
            /// In this method, the model may query for and use any of the 
            /// available simulation services, as they are all guaranteed to be 
            /// fully functional at that time. It may as well
            /// connect to other models' functionality (e.g. to event sources),
            /// as it is guaranteed that all models have been created and
            /// configured before the Connect() method of any model is called.
            /// @param   simulator Simulation Environment that hosts the model.
            /// @remarks The simulation environment typically calls this
            ///          method in the <em>Connecting</em> state.
            void Connect(ISimulator* simulator) throw (
                Smp::IModel::InvalidModelState);

        protected:
            // ----------------------------------------------------------------
            // ---------------------------- Helper methods --------------------
            // ----------------------------------------------------------------

            /// Get a service by name.
            /// Convenience method that delegates the service query to the
            /// service provider, which is the simulator passed to Connect().
            /// @param   serviceName Service name.
            /// @return  Service component.
            /// @remarks The returned component may be NULL if no
            ///          service with the given name could be found.
            Smp::IService* GetService(const Smp::String8 serviceName) const;
        };
    }
}

#endif  // MDK_MODEL_H_

/***********
 * History *
 ***********/

//$Log: Model.h,v $
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

