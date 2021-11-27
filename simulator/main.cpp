#include <iostream>
#include <boost/format.hpp>

#include "Smp/Simulator.h"
#include "Smp/Exceptions.h"

// A custom dummy model
#include "Mdk/Model.h"

#include "Smp/IEntryPoint.h"
#include "Smp/Services/IScheduler.h"
#include "Mdk/Object.h"

#include <string>
#include <boost/format.hpp>

#include "rpc/jsonrpc_server.hpp"
#include "rpc/transport/implementation/zmq_reqrep_transport.hpp"


class SimulatorService
{
public:
	SimulatorService(int rpc_port = 5000, int rpc_timeout_ms = 500);
	~SimulatorService();
	void registerRPCMethods();
	void setupAndStart();
	void cleanupAndShutdown();
private:
	std::shared_ptr<rpc_transport_base> rpc_transport;
	jsonrpc_server server;
	Smp::Simulator m_sim;

	/* RPC Methods */
	jsonrpcpp::Response rpc_hello(jsonrpcpp::request_ptr request)
	{
		return jsonrpcpp::Response (
			*request, 
			(boost::format("Hello, %s.") %  request->params().get<std::string>("name")).str()
		);			
	}
};


SimulatorService::SimulatorService(int rpc_port, int rpc_timeout_ms)
	:
			rpc_transport(
				dynamic_cast<rpc_transport_base*>( 
					new zmq_reqrep_transport(rpc_port, rpc_timeout_ms) 
				)
			)
		, 	server(rpc_transport)
{
	this->registerRPCMethods();
	server.start();		
}

SimulatorService::~SimulatorService()
{
	this->server.stop();
}

void SimulatorService::registerRPCMethods() 
{
	this->server.register_handler(
		"hello", 
		std::bind( &SimulatorService::rpc_hello,  this, std::placeholders::_1) 
	);
}

void SimulatorService::setupAndStart()
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

	// Run simulation
	this->m_sim.GetLogger()->Log(nullptr,"Running simulation", Smp::Services::LMK_Information);
	this->m_sim.Run();
}

void SimulatorService::cleanupAndShutdown()
{		
	this->m_sim.GetLogger()->Log(nullptr,"Holding simulation", Smp::Services::LMK_Information);
	this->m_sim.Hold();

	// Exit simulation
	this->m_sim.GetLogger()->Log(nullptr,"Leaving simulation", Smp::Services::LMK_Information);
	this->m_sim.Exit();
}

		


int main(int argc,const char* argv[])
{
	try 
	{
		int rpc_port = 5000;
		int rpc_timeout = 500; // milliseconds
		
		SimulatorService sim(rpc_port,rpc_timeout);
		
		sim.setupAndStart();

		std::cout << "Receiving commands at port " << rpc_port << ". Press any key to stop service.";
		std::getchar();

		sim.cleanupAndShutdown();
	} 
	catch(const Smp::Exception& ex)
	{		
		std::cerr << "Exception " << ex.GetName() << ". " 
		          << ex.GetDescription() << std::endl
				  << "Cause: " << ex.what() << std::endl;
	} 
	catch ( const rpc_transport_base::exception& tex )
	{
		std::cerr << "Server communication exception: " << tex.what() << std::endl;
	}
	catch ( ... )
	{
		std::cerr << "Unhandled exception" << std::endl;
	}

	std::cout << "Application finished gracefully." << std::endl;

	return 0;	
}