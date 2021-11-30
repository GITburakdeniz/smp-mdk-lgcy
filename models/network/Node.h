#ifndef NODE_H
#define NODE_H

#include <iostream>

#include "Smp/IModel.h"
#include "Smp/IEntryPoint.h"
#include "Smp/ISimulator.h"
#include "Smp/IPublication.h"
#include "Smp/Services/ILogger.h"
#include "Smp/Services/IScheduler.h"
#include "Smp/Services/IEventManager.h"

#include "IYAMLConfigurable.h"

/// Node model.
class Node : 
    public virtual Smp::IModel,
    public IYAMLConfigurable
{
private:
    char* name;                                 ///< Name of model.
    Smp::ModelStateKind state;                  ///< Model state.
    Smp::IComposite *parent;                    ///< Parent component.
    Smp::Services::ILogger *logger;             ///< Logger service.
    Smp::Services::IScheduler *scheduler;       ///< Scheduler service.    
    void Init();                                ///< Init private fields.    
public:
    Node(Smp::String8 name, Smp::IComposite *parent)
    {
        Init();
        this->name = strdup(name);
        this->state = Smp::MSK_Created;
        this->parent = parent;
    }
    
    virtual ~Node()
    {
        if (name) free(name);
    }
    
    // IModel methods
    virtual Smp::String8 GetName() const { return name; }
    virtual Smp::String8 GetDescription() const { return "Node Model"; }
    virtual Smp::IComposite* GetParent() const { return parent; }
    virtual Smp::ModelStateKind GetState() const { return state; }
    virtual void Publish(Smp::IPublication* receiver);
    virtual void Configure(Smp::Services::ILogger* logger);
    virtual void Connect(Smp::ISimulator* simulator);

    // Implementation-specific
    void ReadInitializationParameters(const YAML::Node& paramsNode);
};

#endif // NODE_H