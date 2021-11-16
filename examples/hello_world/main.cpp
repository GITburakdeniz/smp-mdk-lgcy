#include <iostream>

#include "Smp/Simulator.h"
#include "Smp/Exceptions.h"

// A custom dummy model
//#include "Mdk/Model.h"
#include "Smp/IEntryPoint.h"
#include "Mdk/Object.h"


class MyEntryPoint : public Smp::IEntryPoint, Smp::Mdk::Object 
{
public:
	MyEntryPoint()
		:
			counter(0)
		{}
	~MyEntryPoint() {}
	/// Entry point owner.
	/// This method returns the Component that owns the entry point.
	/// @return  Owner of entry point.
	/// @remarks This is required to be able to store and later restore
	///          entry points.
	Smp::IComponent* GetOwner() const
	{
		return nullptr;
	}

	/// Entry point execution.
	/// Method that is called when an associated event is emitted.
	/// @remarks Models providing entry points must ensure that these 
	///          entry points do not throw exceptions.
	void Execute() const
	{
		std::cout << "Executing event" << std::endl;
	}
private:
	uint32_t counter;
};


        

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