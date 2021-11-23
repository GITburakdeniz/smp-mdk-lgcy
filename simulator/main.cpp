#include <iostream>
#include <boost/format.hpp>

#include "Smp/Simulator.h"
#include "Smp/Exceptions.h"

// A custom dummy model
#include "Mdk/Model.h"

#include "Smp/IEntryPoint.h"
#include "Smp/Services/IScheduler.h"
#include "Mdk/Object.h"


class SimulatorService
{
public:
	SimulatorService();
	~SimulatorService();

	void run();

private:
	Smp::Simulator m_sim;
};


SimulatorService::SimulatorService()
{
	// TODO
}

SimulatorService::~SimulatorService()
{
	// TODO
}

void SimulatorService::run()
{
	// Access services from simulator	
	this->m_sim.GetLogger()->Log(nullptr,"Simulation service started", Smp::Services::LMK_Information);

	// 1. Create models
	this->m_sim.GetLogger()->Log(nullptr,"Creating models", Smp::Services::LMK_Information);

	// TODO load config and add models

	// Publish variables in the simulation environment
	this->m_sim.GetLogger()->Log(nullptr,"Publishing model variables", Smp::Services::LMK_Information);
	this->m_sim.Publish();

	// Configure
	this->m_sim.GetLogger()->Log(nullptr,"Configuring models", Smp::Services::LMK_Information);
	this->m_sim.Configure();

	// Connect
	this->m_sim.GetLogger()->Log(nullptr,"Connecting models", Smp::Services::LMK_Information);
	this->m_sim.Connect();

	// Initialize
	this->m_sim.GetLogger()->Log(nullptr,"Initializing models", Smp::Services::LMK_Information);
	this->m_sim.Initialise();

	// TODO. start RPC and listen to RPC commands

	// Run simulation
	this->m_sim.GetLogger()->Log(nullptr,"Running simulation", Smp::Services::LMK_Information);
	this->m_sim.Run();

	std::cout << "Press any key to stop" << std::endl;
	std::getchar();
	
	this->m_sim.GetLogger()->Log(nullptr,"Holding simulation", Smp::Services::LMK_Information);
	this->m_sim.Hold();

	// Exit simulation
	this->m_sim.GetLogger()->Log(nullptr,"Leaving simulation", Smp::Services::LMK_Information);
	this->m_sim.Exit();
}

int main(int argc,const char* argv[])
{
	try {
		SimulatorService sim;
		sim.run();
	} 
	catch(const Smp::Exception& ex)
	{		
		std::cerr << "Exception " << ex.GetName() << ". " 
		          << ex.GetDescription() << std::endl
				  << "Cause: " << ex.what() << std::endl;
	}

	return 0;	
}