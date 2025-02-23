#include "rlenvs/envs/webots_envs/epuck_simple_grid_world.h"

#ifdef RLENVSCPP_WEBOTS

#include "rlenvs/envs/time_step.h"

#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/Motor.hpp>

namespace rlenvscpp{
namespace envs{
namespace webots_envs{
	
	
const std::string EpuckSimpleGridWorld::name = "EpuckSimpleGridWorld";
	
EpuckSimpleGridWorld::EpuckSimpleGridWorld()
:
WebotsEnvBase<TimeStep<state_type>,
			  ContinuousVectorStateDiscreteActionEnv<
										 2, // the state space has size 2 
										 1, // the action space ends at 1
										 0, // the action space starts at 0
										 real_t
										>
			>(static_cast<uint_t>(0), "EpuckSimpleGridWorld"),
			robot_()
{}



void 
EpuckSimpleGridWorld::make(const std::string& version,
                           const std::unordered_map<std::string, std::any>& options){
							   
	if(this -> is_created()){
        return;
    }
	
	
	build_make_options_(options);
	
	robot_.activate_position_sensor(0, std::any_cast<uint_t>(options_["left_pos_sensor_time_step"]));
	robot_.activate_position_sensor(1, std::any_cast<uint_t>(options_["right_pos_sensor_time_step"]));
	
	robot_.activate_motor(0, std::any_cast<real_t>(options_["left_motor_init_velocity"]));
	robot_.activate_motor(1, std::any_cast<real_t>(options_["right_motor_init_velocity"]));
	
	// set the version and set the board
    // to created
	this->set_version_(version);
    this->make_created_();
							   

}


void 
EpuckSimpleGridWorld::build_make_options_(const std::unordered_map<std::string, std::any>& options){
	
	auto sim_time_step_itr = options.find("sim_time_step");
	
	if(sim_time_step_itr != options.end()){
		options_["sim_time_step"] = sim_time_step_itr->second;
	}
	else{
		
		options_["sim_time_step"] = this -> DEFAULT_SIM_TIME_STEP;
	}
	
	auto left_pos_sensor_time_step_itr = options.find("left_pos_sensor_time_step");
	if(left_pos_sensor_time_step_itr != options.end()){
		options_["left_pos_sensor_time_step"] = sim_time_step_itr->second;
	}
	else{
		options_["left_pos_sensor_time_step"] = this -> DEFAULT_SIM_TIME_STEP;
	}
	
	auto right_pos_sensor_time_step_itr = options.find("right_pos_sensor_time_step");
	if(right_pos_sensor_time_step_itr != options.end()){
		options_["right_pos_sensor_time_step"] = sim_time_step_itr->second;
	}
	else{
		options_["right_pos_sensor_time_step"] = this -> DEFAULT_SIM_TIME_STEP;
	}
	
	auto left_motor_init_velocity_itr = options.find("left_motor_init_velocity");
	if(left_motor_init_velocity_itr != options.end()){
		options_["left_motor_init_velocity"] = left_motor_init_velocity_itr->second;
	}
	else{
		options_["left_motor_init_velocity"] = std::any(static_cast<real_t>(0.0));
	}
	
	auto right_motor_init_velocity_itr = options.find("right_motor_init_velocity");
	if(right_motor_init_velocity_itr != options.end()){
		options_["right_motor_init_velocity"] = right_motor_init_velocity_itr->second;
	}
	else{
		options_["right_motor_init_velocity"] = std::any(static_cast<real_t>(0.0));
	}
	
}


void 
EpuckSimpleGridWorld::close(){}
			


EpuckSimpleGridWorld::time_step_type 
EpuckSimpleGridWorld::step(const action_type& action){
	
	
	auto distance_from_wall = distance_from_wall_();
	
	// if the distance from wall is 
	// less than distance_from_goal_
	// and the action == 0 then this is a win
	if(distance_from_wall < distance_from_goal_){
		
		if(action == 0){
			auto reward = 5.0;
			
			// tell the robot that this was
			// the last step
		}
		else{
			
			//this is a crash 
			auto reward = -5.0;
			
			// this is the last step
		}
	}
	
	if(distance_from_wall > 2.0 * distance_from_goal_){
		
		if(action == 0){
			
			// we punish the agent
			auto reward = -5.0;
			
			// this is middle step
		}
		else{
			
			// we didn't crash we need to
			// keep moving
			auto reward = 0.0;
			
			// this is middle step
		}
		
	}
}


real_t 
EpuckSimpleGridWorld::distance_from_wall_()const{
	
}

}
}
}

#endif 

