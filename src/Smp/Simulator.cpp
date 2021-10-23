#include "Simulator.h"

// To be implemented:
// ModelCollection
// ServiceCollection

namespace Smp
{    

Simulator::Simulator()
{
    // FIXME: ver estado inicial.
    this->m_state = SimulatorStateKind::SSK_Building;
    //FIXME
}

Simulator::~Simulator()
{
    //FIXME
}   
        
    
const ModelCollection* Simulator::GetModels()
{
    return &this->m_models;
}

IModel* Simulator::GetModel(String8 name)
{
    // FIXME: unsupported
    return nullptr;
}

void Simulator::AddModel(IModel* model)
{
    this->m_models.push_back(model);
}

const ServiceCollection* Simulator::GetServices()
{
    // FIXME: unsupported
    return nullptr;
}

IService* Simulator::GetService(String8 name)
{
    // FIXME: unsupported
    return nullptr;
}

void Simulator::AddService(IService* service)
{
    //FIXME: Unsupported
}

Services::ILogger* Simulator::GetLogger() const
{
    return this->m_logger;
}

Services::IScheduler* Simulator::GetScheduler() const
{
    return this->m_scheduler;
}

Services::ITimeKeeper* Simulator::GetTimeKeeper() const
{
    return this->m_timeKeeper;
}

Services::IEventManager* Simulator::GetEventManager() const
{
    return this->m_eventManager;
}

SimulatorStateKind Simulator::GetState() const
{
    return this->m_state;
}

void Simulator::Publish()
{
    for(auto model: this->m_models)
    {
        // FIXME: implement Receiver
        //model->Publish()
    }    

    // FIXME: unsupported
}

void Simulator::Configure()
{
    for(auto model: this->m_models)
    {
        model->Configure(this->m_logger);
    }    
}

void Simulator::Connect()
{    
    this->m_state = SimulatorStateKind::SSK_Connecting;

    // Call Connect for each model.
    
    for(auto model: this->m_models)
    {
        model->Connect(this);
    }

    // If everything's ok, set to initializing ok
    this->m_state = SimulatorStateKind::SSK_Initialising;
}

void Simulator::Initialise()
{
    if (this->m_state != SimulatorStateKind::SSK_Initialising)
    {
        // throw invalid state
    }
    
}

void Simulator::Hold()
{
    // FIXME
    this->m_state = SimulatorStateKind::SSK_Standby;
}

void Simulator::Run()
{
    if (this->m_state != SimulatorStateKind::SSK_Standby)
    {
        // throw invalid state
    }

    this->m_state = SimulatorStateKind::SSK_Executing;
}

void Simulator::Store(String8 filename)
{
    this->m_state = SimulatorStateKind::SSK_Storing;
    
    // FIXME: throw not implemented
}

void Simulator::Restore(String8 filename)
{
    this->m_state = SimulatorStateKind::SSK_Restoring;

    // FIXME: throw not implemented
}

void Simulator::Exit()
{
    this->m_state = SimulatorStateKind::SSK_Exiting;
}

void Simulator::Abort()
{
    this->m_state = SimulatorStateKind::SSK_Aborting;
}

void Simulator::AddInitEntryPoint(IEntryPoint* entryPoint)
{
    // FIXME: not implemented
}

}