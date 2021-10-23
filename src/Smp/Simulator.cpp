#include "Simulator.h"

// To be implemented:
// ModelCollection
// ServiceCollection

namespace Smp
{    

Simulator::Simulator():
    Component( "root", "Simulator", nullptr)
    , interval(1)
    , timer(this->ioService, this->interval)
    , simulationThread(  [this] { this->ioService.run(); })
{
    // FIXME: ver estado inicial.
    m_state = SimulatorStateKind::SSK_Building;
    //FIXME    

    // Create mandatory services

    // Create logger
    this->m_logger = new Smp::Services::Logger();
    this->m_logger->Log(this,"Simulator instanced");

    // Create scheduler
    this->m_scheduler = new Smp::Services::Scheduler();
    this->m_logger->Log(this,"Scheduler instanced");

    // Create timekeeper
    this->m_timeKeeper = new Smp::Services::TimeKeeper;
    this->m_logger->Log(this,"Timekeeper instanced");

    // Create timekeeper
    this->m_eventManager = new Smp::Services::EventManager;
    this->m_logger->Log(this,"EventManager instanced");

    // Start 
    this->timer.async_wait( std::bind(&Simulator::tick, this, std::placeholders::_1));
}

Simulator::~Simulator()
{
    this->m_logger->Log(this,"Shutting down simulator");

    this->timer.cancel();
    this->simulationThread.join();

    delete this->m_logger;
    delete this->m_scheduler;
    delete this->m_timeKeeper;
    delete this->m_eventManager;
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
    this->m_logger->Log(this,"Publication stage.");
    for(auto model: this->m_models)
    {
        // FIXME: implement Receiver
        //model->Publish()
    }    

    // FIXME: unsupported
}

void Simulator::Configure()
{
    this->m_logger->Log(this,"Configuration stage.");
    for(auto model: this->m_models)
    {
        model->Configure(m_logger);
    }    
}

void Simulator::Connect()
{    
    this->m_logger->Log(this,"Connection stage.");
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
    this->m_logger->Log(this,"Initialization stage.");
    if (this->m_state != SimulatorStateKind::SSK_Initialising)
    {
        // throw invalid state
    }

    this->m_state = SimulatorStateKind::SSK_Standby;    
}

void Simulator::Hold()
{
    this->m_logger->Log(this,"Simulation at hold state.");
    // FIXME
    this->m_state = SimulatorStateKind::SSK_Standby;
}

void Simulator::Run()
{    
    if (this->m_state != SimulatorStateKind::SSK_Standby)
    {
        // throw invalid state
    }
    this->m_logger->Log(this,"Simulation is being resumed.");
    this->m_state = SimulatorStateKind::SSK_Executing;

    
}

void Simulator::Store(String8 filename)
{
    this->m_logger->Log(this,"Store stage.");
    this->m_state = SimulatorStateKind::SSK_Storing;
    
    // FIXME: throw not implemented

    this->m_state = SimulatorStateKind::SSK_Standby;
}

void Simulator::Restore(String8 filename)
{
    this->m_logger->Log(this,"Restore stage.");
    this->m_state = SimulatorStateKind::SSK_Restoring;

    // FIXME: throw not implemented
        
    this->m_state = SimulatorStateKind::SSK_Standby;
}

void Simulator::Exit()
{
    this->m_logger->Log(this,"Exiting.");
    this->m_state = SimulatorStateKind::SSK_Exiting;
}

void Simulator::Abort()
{
    this->m_logger->Log(this,"Aborting.");
    this->m_state = SimulatorStateKind::SSK_Aborting;
}

void Simulator::AddInitEntryPoint(IEntryPoint* entryPoint)
{
    // FIXME: not implemented
}

void Simulator::tick(const boost::system::error_code& ec)
{
    if(!ec)
    {
        // Reschedule the timer for 1 second in the future:
        this->timer.expires_at(timer.expires_at() + this->interval);
        // Posts the timer event
        this->timer.async_wait( std::bind(&Simulator::tick, this, std::placeholders::_1));

        if ( SimulatorStateKind::SSK_Executing == this->m_state )
        {
            
            std::cout << "Tick" << std::endl ;
        }
    }
}

void Simulator::tick(const boost::system::error_code& ec)
{

}