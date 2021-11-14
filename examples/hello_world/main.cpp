#include <iostream>

#include "Smp/Simulator.h"
#include "Smp/Exceptions.h"

// A custom dummy model
//#include "Mdk/Model.h"


int main(int argc,const char* argv[])
{
	std::cout << "Hello world of SMP2" << std::endl;

	try {
		// Instance a simulator
		Smp::Simulator sim;
	
		// Access services from simulator	
		sim.GetLogger()->Log(nullptr,"Using logger from simulator");

		// 1. Create models

		// Publish variables in the simulation environment
		sim.Publish();

		// Configure
		sim.Configure();

		// Connect
    	sim.Connect();

		// Initialize
		sim.Initialise();

		// Run simulation
    	sim.Run();


		std::cout << "Press any key to stop" << std::endl;
		std::getchar();
		
		sim.Hold();

		// Exit simulation
		sim.Exit();
	} 
	catch(const Smp::Exception& ex)
	{
		std::cerr << "Exception " << ex.GetName() << ". " 
		          << ex.GetDescription() << std::endl
				  << "Cause: " << ex.what() << std::endl;
	}
	
	std::cout << "Bye bye, world of SMP2" << std::endl;
	return 0;

	

	
}