#include <iostream>
#include <boost/format.hpp>

#include "Smp/Simulator.h"
#include "Smp/Exceptions.h"

// A custom dummy model
//#include "Mdk/Model.h"

#include "Smp/IEntryPoint.h"
#include "Smp/Services/IScheduler.h"
#include "Mdk/Object.h"


#include "Counter.h"

/* --- Only the entrypoint ----------------------------------------------------------------------------- */

class MyEntryPoint : 
	public Smp::IEntryPoint, 
	public Smp::Mdk::Object 
{
public:
	MyEntryPoint(Smp::ISimulator* sim)
		:
		  Object("MyEntrypoint","Test entrypoint")
		, m_counter(0)
		, m_sim(sim)
		, m_logger(sim->GetLogger())
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
		m_logger->Log(this, (boost::format("Counter is %d at %d ms.") % 
			m_counter %
			static_cast<uint32_t>(m_sim->GetTimeKeeper()->GetSimulationTime()/1000000)).str().c_str(), 
			Smp::Services::LMK_Information
		);		

		//m_counter++;
	}
private:
	uint32_t m_counter;
	Smp::Services::ILogger* m_logger;
	Smp::ISimulator* m_sim;
};


        

int main(int argc,const char* argv[])
{
	try {
		// Instance a simulator
		Smp::Simulator sim;
	
		// Access services from simulator	
		sim.GetLogger()->Log(nullptr,"Simulation started", Smp::Services::LMK_Information);

		// 1. Create models
		sim.GetLogger()->Log(nullptr,"Creating models", Smp::Services::LMK_Information);

		Counter counter("counter", &sim);
		sim.AddModel(&counter);


		// Publish variables in the simulation environment
		sim.GetLogger()->Log(nullptr,"Publishing model variables", Smp::Services::LMK_Information);
		sim.Publish();

		// Configure
		sim.GetLogger()->Log(nullptr,"Configuring models", Smp::Services::LMK_Information);
		sim.Configure();

		// Connect
		sim.GetLogger()->Log(nullptr,"Connecting models", Smp::Services::LMK_Information);
    	sim.Connect();

		// Initialize
		sim.GetLogger()->Log(nullptr,"Initializing models", Smp::Services::LMK_Information);
		sim.Initialise();

		// Run simulation
		sim.GetLogger()->Log(nullptr,"Running simulation", Smp::Services::LMK_Information);
    	sim.Run();

		std::cout << "Press any key to stop" << std::endl;
		std::getchar();
		
		sim.GetLogger()->Log(nullptr,"Holding simulation", Smp::Services::LMK_Information);
		sim.Hold();

		// Exit simulation
		sim.GetLogger()->Log(nullptr,"Leaving simulation", Smp::Services::LMK_Information);
		sim.Exit();
	} 
	catch(const Smp::Exception& ex)
	{		
		std::cerr << "Exception " << ex.GetName() << ". " 
		          << ex.GetDescription() << std::endl
				  << "Cause: " << ex.what() << std::endl;
	}

	return 0;

	

	
}