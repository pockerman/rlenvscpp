#include "rlenvs/envs/webots/epuck_simple_grid_world.h"

#ifndef RLENVSCPP_WEBOTS



#include <webots/PositionSensor.hpp>
#include <webots/Motor.hpp>

namespace rlenvscpp{
namespace envs{
namespace webots_envs{
	
	
const std::string EpuckSimpleGridWorld::name = "EpuckSimpleGridWorld";
	
EpuckSimpleGridWorld::EpuckSimpleGridWorld(std::shared_ptr<Robot> robot)
:
WebotsEnvBase<TimeStep<state_type>,
			  ContinuousVectorStateDiscreteActionEnv<
										 2, // the state space has size 2 
										 1, // the action space ends at 1
										 0, // the action space starts at 0
										 real_t
										>
			>(robot, static_cast<uint_t>(0), "EpuckSimpleGridWorld")
{}



void 
EpuckSimpleGridWorld::make(const std::string& version,
                           const std::unordered_map<std::string, std::any>& options){
							   
	if(this -> is_created()){
        return;
    }
	
	
	auto sim_time_step_itr = options.find("sim_time_step");
	
	if(sim_time_step_itr != options.end()){
		options_["sim_time_step"] = sim_time_step_itr->second;
	}
	else{
		
		options_["sim_time_step"] = this- > DEFAULT_SIM_TIME_STEP;
	}
	
	auto left_pos_sensor_time_step_itr = options.find("left_pos_sensor_time_step");
	if(left_pos_sensor_time_step_itr != options.end()){
		options_["left_pos_sensor_time_step"] = sim_time_step_itr->second;
	}
	else{
		options_["left_pos_sensor_time_step"] = this- > DEFAULT_SIM_TIME_STEP;
	}
	
	auto right_pos_sensor_time_step_itr = options.find("right_pos_sensor_time_step");
	if(right_pos_sensor_time_step_itr != options.end()){
		options_["right_pos_sensor_time_step"] = sim_time_step_itr->second;
	}
	else{
		options_["right_pos_sensor_time_step"] = this- > DEFAULT_SIM_TIME_STEP;
	}
	
	
	left_pos_sensor_time_step_itr = options_.find("left_pos_sensor_time_step");
	
	left_position_sensor_ = this -> robot_ -> getDivice("left wheel sensor");
	
	// enable the sensors
	left_position_sensor_
	
	right_position_sensor_ = this -> robot_ -> getDistanceSensor("right wheel sensor");
	
	
	// set the version and set the board
    // to created
	this->set_version_(version);
    this->make_created_();
							   

}


void 
EpuckSimpleGridWorld::close()final{}
			
	
}
}
}

#endif 

