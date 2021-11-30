#include "Bus.h"

// Initialise private fields
void Bus::Init(void)
{
    // Initialise references
    logger = NULL;
    scheduler = NULL;
    //eventManager = NULL;
}

// Publish fields to environment
void Bus::Publish(Smp::IPublication *receiver)
{
    if (state == Smp::MSK_Created)
    {
        state = Smp::MSK_Publishing;
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Created);
    }
}
// Perform custom configuration.
void Bus::Configure(Smp::Services::ILogger*) 
{
    if (state == Smp::MSK_Publishing)
    {
        state = Smp::MSK_Configured;
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Publishing);
    }
}

// Get access to services, and register entry points.
void Bus::Connect(Smp::ISimulator *simulator)
{
    if (state == Smp::MSK_Configured)
    {
        state = Smp::MSK_Connected;
        logger = simulator->GetLogger();
        scheduler = simulator->GetScheduler();
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Configured);
    }
}


/* Implementation-specific */

extern "C" Smp::IModel* create_Bus(Smp::String8 name, Smp::IComposite *parent)
{    
    return dynamic_cast<Smp::IModel*>(new Bus(name,parent));
}

extern "C" void destroy_Bus( Smp::IModel* obj )
{
    delete dynamic_cast<Bus*>(obj);
}

void Bus::ReadInitializationParameters(const YAML::Node& paramsNode)
{   
    std::cout << "Initializing bus. Nodes: " << paramsNode["nodes"].size() << std::endl;    
    for (YAML::const_iterator it  = paramsNode["nodes"].begin(); 
                              it != paramsNode["nodes"].end(); ++it) 
    {    
        std::cout << "Adding node: " << it->as<std::string>() << "\n";
    }
    //this->frequency =  paramsNode["frequency"].as<double>();
}

