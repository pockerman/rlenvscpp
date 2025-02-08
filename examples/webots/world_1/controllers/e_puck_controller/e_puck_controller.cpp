// File:          e_puck_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>


#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/env_types.h"
#include "rlenvs/envs/time_step.h"
#include "rlenvs/envs/env_base.h"

// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace rlenvscpp;

namespace epuck_ctrl{
	

	
typedef std::vector<real_t> state_type;

class EpuckCtrlWorld: public envs::EnvBase<TimeStep<state_type>,
                                     envs::ContinuousVectorStateDiscreteActionEnv<
										 2, // the state space has size 2 
										 1, // the action space ends at 1
										 0, // the action space starts at 0
										 real_t
										>
									 >{

public:
	
	///
    /// \brief name
    ///
    static const std::string name;
	
	
	///
	/// \brief Base class type
	///
	typedef EnvBase<TimeStep<std::vector<real_t>>,
                                     ContinuousVectorStateDiscreteActionEnv<
									 2, // the state space has size 2 
									 1, // the action space ends at 1
									 0, // the action space starts at 0
									 real_t
									 >> base_type;
									 
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
	EpuckCtrlWorld(std::shared_ptr<Robot> robot);
	
	
	///
	/// \brief make. Builds the environment. 
	/// In the context of Webots means getting the basic timestep
	/// the starting position of the robot e.t.c. Anything, we need 
	/// to know to reset the environment back to each original form
	///
    virtual void make(const std::string& version,
                      const std::unordered_map<std::string, std::any>& options)final{}
					  
	///
	/// \brief close the environment
	///
    virtual void close()final{};
	
	
	/// 
	/// \brief Reset the environment
	///
    virtual time_step_type reset(uint_t seed,
                                 const std::unordered_map<std::string, std::any>& options)final {};
					  
					  
	///
    /// \brief step. Step in the environment following the given action
    ///
    virtual time_step_type step(const action_type& action)override final{};


	///
	/// \brief Create a new copy of the environment with the given
	/// copy index
	///
	EpuckCtrlWorld make_copy(uint_t cidx)const{}
	
	///
    /// \brief n_actions. Returns the number of actions
    ///
    uint_t n_actions()const noexcept{return action_space_type::size;}
	
	
private:
	
	
	std::shared_ptr<Robot> robot_;
	
};
	
const std::string EpuckCtrlWorld::name = "EpuckCtrlWorld";
	
EpuckCtrlWorld::EpuckCtrlWorld(std::shared_ptr<Robot> robot)
:
EnvBase<TimeStep<std::vector<real_t>>,
                                     ContinuousVectorStateDiscreteActionEnv<
									 2, // the state space has size 2 
									 1, // the action space ends at 1
									 0, // the action space starts at 0
									 real_t
									 >>(0, "EpuckCtrlWorld"),
robot_(robot)
{}
	
	
}

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
	
	
   using namespace epuck_ctrl;
   
   
  // create the Robot instance.
  std::shared_ptr<Robot> robot = std::make_shared<Robot>();// Robot();
  
  EpuckCtrlWorld env(robot);
  
  std::unordered_map<std::string, std::any> options;
  env.make("v0", options); 
  
  

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();
  
  //std::cout<<"Time step size: "<<timeStep<<std::endl;

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
//  while (robot->step(timeStep) != -1) {
//    // Read the sensors:
//    // Enter here functions to read sensor data, like:
//    //  double val = ds->getValue();
//
//    // Process sensor data here.
//
//    // Enter here functions to send actuator commands, like:
//    //  motor->setPosition(10.0);
//  };
//
//  // Enter here exit cleanup code.
//
//  delete robot;
  return 0;
}
