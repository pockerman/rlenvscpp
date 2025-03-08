#include "rlenvs/rlenvscpp_config.h"

#ifdef RLENVSCPP_WEBOTS

#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/time_step.h"
#include "rlenvs/envs/webots_envs/epuck_simple_grid_world.h"

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <any>
#include <exception>
#include <chrono>
#include <thread>



// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace rlenvscpp;

namespace webots_example_1{
		  
using rlenvscpp::envs::webots_envs::EpuckSimpleGridWorld;
using rlenvscpp::uint_t;

}

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main() {
	
	
   using namespace webots_example_1;
   
   try
   {
		// create the environment
		EpuckSimpleGridWorld env;
	  
		// create the environment...this initializes
		// the robot sensors and motors
		std::unordered_map<std::string, std::any> options;
		options["right_motor_init_velocity"] = 1.25; // 2.0;
		options["left_motor_init_velocity"] = 1.25; // 2.0;
		options["sim_time_step"] = std::any(static_cast<uint_t>(64));
		
		// above this reading we assume there is a wall
		options["max_dist_sensor_reading_goal"] = 120.0;
		
		// we don't want the robot to be far away from the
		// wall either
		options["min_dist_sensor_reading_goal"] = 80.0;
 
		env.make("v0", options); 

		// reset the environment...this will reload the 
		// whole simulation world
		env.reset();
		
		// access the robot
		auto& robot = env.get_robot();
		
		auto time_step = robot.get_basic_time_step();
		std::cout<<"Basic time step used: "<<time_step<<std::endl;
		
		real_t total_reward = 0.0;
		
		// do 500 episodes 270
		for(uint_t e=0; e<272; ++e){
			
			std::cout<<"At step: "<<e<<std::endl;
			std::cout<<"Robot left motor velocity: "<<robot.get_motor_velocity(0)<<std::endl;
			std::cout<<"Robot right motor velocity: "<<robot.get_motor_velocity(1)<<std::endl;
			
			auto r_position = robot.get_position();
		
			std::cout<<"Robot position: "<<r_position<<std::endl;
		
			// what is the max reward
			auto reward = env.compute_reward();
			std::cout<<"Reward predicted: "<<reward<<std::endl;
			
			// move forward unless the
			// reward is the highest
			auto action = 1;
			if(reward == 10.0){
				action = 0;
			}
			
			std::cout<<"Executing action: "<<action<<std::endl;
			
			// step in the environment
			auto time_step = env.step(action);
				
			total_reward += time_step.reward();
			
			std::cout<<"Total reward at episode: "<<e<<" "<<total_reward<<std::endl;
			
			auto distances = robot.read_distance_sensors();
			for(uint_t s=0; s < distances.size(); ++s){
					std::cout<<"Sensor: "<<s<<" distance: " << distances[s]<<std::endl;
			}
			
			if(time_step.done()){
				
				std::cout<<"Reset the environment..."<<std::endl;
				env.reset();
				break;
			}
		}

		std::cout<<"Total reward "<<total_reward<<std::endl;
		
		// this will quit the simulation window
		//env.close();
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
		env.pause_simulation();
   }
   catch(const std::logic_error& e){
	   std::cout<<e.what()<<std::endl;
   }

  return 0;
}
#else
#include <iostream>
int main(){

std::cout<<"This example requires Webots enabled. Rebuild the library with -DENABLE_WEBOTS=ON"<<std::endl;
return 0;
}
#endif