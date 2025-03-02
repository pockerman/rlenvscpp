#ifndef EPUCK_SIMPLE_GRID_WORLD_H
#define EPUCK_SIMPLE_GRID_WORLD_H

#include "rlenvs/rlenvscpp_config.h"

#ifdef RLENVSCPP_WEBOTS

#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/time_step.h"
#include "rlenvs/envs/env_types.h"
#include "rlenvs/rigid_bodies/webots_robots/epuck_robot.h"
#include "rlenvs/envs/webots_envs/webots_base_env.h"

#include <webots/PositionSensor.hpp>
#include <webots/Robot.hpp>

#include <vector>
#include <any>
#include <exception>

namespace rlenvscpp{
namespace envs{
namespace webots_envs{

using namespace rlenvscpp::rigid_bodies::webots_robots;	
	
///
/// \brief class EpuckSimpleGridWorld. Simple grid world that
/// only assumes the presence of a differential drive robot.
/// Specifically the e-puck robot. Checkout the robot specification
/// at: https://www.cyberbotics.com/doc/guide/epuck?version=cyberbotics:R2019a-rev1
/// You can find the location of the PROTO files at: 
/// "WEBOTS_HOME/projects/robots/gctronic/e-puck/protos/E-puck.proto"
///
class EpuckSimpleGridWorld final: public WebotsEnvBase<TimeStep<std::vector<real_t>>, 
                                                       ContinuousVectorStateDiscreteActionEnv<2, // the state space has size 2 
											  1, // the action space ends at 1
											  0, // the action space starts at 0
											  real_t
											  >>
{

public:
	
	///
    /// \brief name
    ///
    static const std::string name;
	
	///
	/// \brief Base class type
	///
	typedef WebotsEnvBase<TimeStep<state_type>,
						  envs::ContinuousVectorStateDiscreteActionEnv<
										 2, // the state space has size 2 
										 1, // the action space ends at 1
										 0, // the action space starts at 0
										 real_t
										>
						> base_type; 
									
	///
	/// \brief The time step type we return every time a step in the
	/// environment is performed
	///
    typedef typename base_type::time_step_type time_step_type;
	
	///
	/// \brief The type describing the state space for the environment
	///
	typedef typename base_type::state_space_type state_space_type;
	
	///
	/// \brief The type of the action space for the environment
	///
	typedef typename base_type::action_space_type action_space_type;

    ///
	/// \brief The type of the action to be undertaken in the environment
	///
    typedef typename base_type::action_type action_type;
	
	///
	/// \brief The type of the state
	///
	typedef typename base_type::state_type state_type;

	///
	/// \brief Constructor
    /// 
	EpuckSimpleGridWorld();
	
	
	///
	/// \brief make. Builds the environment. 
	/// In the context of Webots means getting the basic timestep
	/// the starting position of the robot e.t.c. Anything, we need 
	/// to know to reset the environment back to each original form.
	/// Available options include
	/// sim_time_step: int If not set base_type::DEFAULT_SIM_TIME_STEP is used
	/// left_pos_sensor_time_step: int If not set base_type::DEFAULT_SIM_TIME_STEP is used
	/// rigth_pos_sensor_time_step: int If not set base_type::DEFAULT_SIM_TIME_STEP is used
	/// 
    virtual void make(const std::string& version,
                      const std::unordered_map<std::string, std::any>& options)final;
					  
	///
	/// \brief close the environment
	///
    virtual void close()final;
	
	
	/// 
	/// \brief Reset the environment. When calling reset
	/// the whole simulation environment is reinitialized
	///
    virtual time_step_type reset(uint_t /*seed*/,
                                 const std::unordered_map<std::string, std::any>& /*options*/)final;
					  
					  
	///
    /// \brief step. Step in the environment following the given action.
	/// action = 1 means move whilst action = 0 means stop
    ///
    virtual time_step_type step(const action_type& action)override final;

	///
	/// \brief Create a new copy of the environment with the given
	/// copy index
	///
	EpuckSimpleGridWorld make_copy(uint_t cidx)const{}
	
	///
    /// \brief n_actions. Returns the number of actions
    ///
    uint_t n_actions()const noexcept{return action_space_type::size;}
	
	///
	/// \brief Read the option with the given name
	///
	template<typename T>
	T read_option(const std::string& op_name)const;
	
	
	EpuckRobot& get_robot()noexcept{return robot_;}
	const EpuckRobot& get_robot()const noexcept{return robot_;}
	
private:
	
	///
	/// \brief The robot in the world
	///
	EpuckRobot robot_;
	
	///
	/// \brief The options we use to initialize the world.
	/// These options are used as well as when reset is called
	///
	std::unordered_map<std::string, std::any> options_;
	
	///
	/// \brief Builds the given options so that these can be used
	/// when reseting the environment
	///
	void build_make_options_(const std::unordered_map<std::string, std::any>& options);
	
	///
	/// \brief Set up the robot sensors
	///
	void activate_robot_();
	
	///
	/// \brief Handles the stop command
	///
	time_step_type on_stop_();
	
	///
	/// \brief Handles the move command
	///
	time_step_type on_move_();
	
	///
	/// \brief Compute the reward to be returned
	///
	real_t compute_reward_()const;
	
};


template<typename T>
T 
EpuckSimpleGridWorld::read_option(const std::string& op_name)const{
	
	auto op_itr = options_.find(op_name);
	
	if(op_itr != options_.end()){
		return std::any_cast<T>(op_itr -> second);
	}
	
	throw std::logic_error("Option: " + op_name + " not found");
}
	

}
}
}


#endif 
#endif