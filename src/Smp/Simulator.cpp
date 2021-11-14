#include "Simulator.h"

// To be implemented:
// ModelCollection
// ServiceCollection

namespace Smp
{    

Simulator::Simulator():
    Component( "root", "Simulator", nullptr)
    , sliceInterval(1000)
    , timer(this->ioService, this->sliceInterval)
    , simulationTime(0)
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
}

Simulator::~Simulator()
{
    this->m_logger->Log(this,"Shutting down simulator");

    if (SimulatorStateKind::SSK_Executing == this->m_state)
    {
        this->Hold();
    }

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
    this->m_logger->Log(this,"Simulation at Standby state.");
    // FIXME
    this->m_state = SimulatorStateKind::SSK_Standby;

    this->stop();
}

void Simulator::Run()
{    
    if (this->m_state != SimulatorStateKind::SSK_Standby)
    {
        // throw invalid state
        return;
    }
    this->m_logger->Log(this,"Simulation is being resumed.");
    this->m_state = SimulatorStateKind::SSK_Executing;

    this->start();
}

void Simulator::Store(String8 filename)
{
    if (this->m_state != SimulatorStateKind::SSK_Standby)
    {
        // throw invalid state
        return;
    }

    this->m_logger->Log(this,"Store stage.");
    this->m_state = SimulatorStateKind::SSK_Storing;
    
    // FIXME: throw not implemented

    this->m_state = SimulatorStateKind::SSK_Standby;
}

void Simulator::Restore(String8 filename)
{
    if (this->m_state != SimulatorStateKind::SSK_Standby)
    {
        // throw invalid state
        return;
    }

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

void Simulator::start()
{
    // Start 
    this->timer.async_wait( std::bind(&Simulator::tick, this, std::placeholders::_1));    
    this->simulationThread = std::thread([this] { this->ioService.run(); });
}

void Simulator::stop()
{
    this->timer.cancel();
    this->simulationThread.join();
}

void Simulator::executeEvent(const boost::system::error_code& ec, uint32_t param)
{
    if(!ec)
    {
        if ( SimulatorStateKind::SSK_Executing == this->m_state )
        {
            std::cout << "[" << this->simulationTime << "] Scheduled event " << param << std::endl;
        }
    }  
}

void Simulator::tick(const boost::system::error_code& ec)
{
    if(!ec)
    {
        // Reschedule the timer for 1 second in the future:
        this->timer.expires_at(this->timer.expires_at() + this->sliceInterval);
        
        // Posts the timer event
        this->timer.async_wait( std::bind(&Simulator::tick, this, std::placeholders::_1));

        if ( SimulatorStateKind::SSK_Executing == this->m_state )
        {
            // Run scheduler for dt
            //dynamic_cast<Scheduler*>(this->m_scheduler)->
            std::cout << "[" << this->simulationTime << "] Tick" << std::endl;
            this->simulationTime+=1000; // FIXME
        }
    }
}

} // end namespace Smp