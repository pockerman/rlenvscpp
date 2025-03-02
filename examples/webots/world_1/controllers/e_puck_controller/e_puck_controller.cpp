#include "rlenvs/rlenvscpp_config.h"

#ifdef RLENVSCPP_WEBOTS

#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/time_step.h"
#include "rlenvs/envs/webots_envs/epuck_simple_grid_world.h"

#include <webots/Robot.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <any>


#include <iostream>

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
   
   
	// create the Robot instance.
	//std::shared_ptr<Robot> robot = std::make_shared<Robot>();// Robot();
  
	// create the environment
	EpuckSimpleGridWorld env;
  
	// create the environment...this initializes
	// the robot sensors and motors
	std::unordered_map<std::string, std::any> options;
	options["right_motor_init_velocity"] = 1.25; // 2.0;
	options["left_motor_init_velocity"] = 1.25; // 2.0;
	env.make("v0", options); 
	
	
	auto right_pos_sensor_time_step = env.template read_option<uint_t>("right_pos_sensor_time_step");
	std::cout<<"right_pos_sensor_time_step: "<<right_pos_sensor_time_step<<std::endl;
	
	// reset the environment...this will reload the 
	// whole simulation world
	env.reset(42, std::unordered_map<std::string, std::any>());
	
	uint_t counter = 0;
	while(counter < 5000000000){
		counter++;
	}
	
	// access the robot
	auto& robot = env.get_robot();
           
	auto time_step = robot.get_basic_time_step();
	std::cout<<"Basic time step used: "<<time_step<<std::endl;
	
	auto init_odometry = robot.compute_odometry();
	
	std::cout<<"Init odometry: \n"<<init_odometry<<std::endl;
  
	for(uint_t s=0; s<500; ++s){
		
		std::cout<<"At step: "<<s<<std::endl;
		std::cout<<"Robot left motor velocity: "<<robot.get_motor_velocity(0)<<std::endl;
		std::cout<<"Robot right motor velocity: "<<robot.get_motor_velocity(1)<<std::endl;
		
		auto exit_event = robot.step(time_step);
		
		std::cout<<"Exit event flag is: "<<exit_event<<std::endl;
			
		auto distances = robot.read_distance_sensors();
		
		for(uint_t s=0; s < distances.size(); ++s){
				std::cout<<"Sensor: "<<s<<" distance: " << distances[s]<<std::endl;
		}
		
		if( s % 20 == 0){
			std::cout<<"Resetting the environment..."<<std::endl;
			env.reset(42, std::unordered_map<std::string, std::any>());
				
			auto odometry = robot.compute_odometry();
			std::cout<<"With reset odometry: \n"<<odometry<<std::endl;
		}
		else{
			auto odometry = robot.compute_odometry();
			std::cout<<"odometry: \n"<<odometry<<std::endl;
		}
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