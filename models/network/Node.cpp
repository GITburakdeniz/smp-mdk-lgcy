#include "Node.h"

// Initialise private fields
void Node::Init(void)
{
    // Initialise references
    logger = NULL;
    scheduler = NULL;
    //eventManager = NULL;
}

// Publish fields to environment
void Node::Publish(Smp::IPublication *receiver)
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
void Node::Configure(Smp::Services::ILogger*) 
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
void Node::Connect(Smp::ISimulator *simulator)
{
    if (state == Smp::MSK_Configured)
    {
        state = Smp::MSK_Connected;
        logger = simulator->GetLogger();
        scheduler = simulator->GetScheduler();
        //eventManager = simulator->GetEventManager();
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Configured);
    }
}


/* Implementation-specific */

extern "C" Smp::IModel* create_Node(Smp::String8 name, Smp::IComposite *parent)
{    
    return dynamic_cast<Smp::IModel*>(new Node(name,parent));
}

extern "C" void destroy_Node( Smp::IModel* obj )
{
    delete dynamic_cast<Node*>(obj);
}

void Node::ReadInitializationParameters(const YAML::Node& paramsNode)
{    
    //this->frequency =  paramsNode["frequency"].as<double>();
}