#ifndef EPUCK_ROBOT_H
#define EPUCK_ROBOT_H

///
/// \file webots_robots/epuck_robot.h
///


#include "rlenvs/rlenvscpp_config.h"

#ifdef RLENVSCPP_WEBOTS
                 
#include "rlenvs/rlenvs_types_v2.h"
				
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>

#include <ostream>
#include <memory>

namespace rlenvscpp{
namespace rigid_bodies{
namespace webots_robots{
	
	

struct EpuckRobotProperties{
	
	///
	/// \brief Number of distance or proximity sensors available
	///
	static constexpr  uint_t DISTANCE_SENSORS_NUMBER = 8;
	
	///
	/// \brief The id for the left position sensor
	///
	static constexpr uint_t LEFT_POSITION_SENSOR_ID = 0;
	
	///
	/// \brief The id for the left position sensor
	///
	static constexpr uint_t RIGHT_POSITION_SENSOR_ID = 1;
	
	///
	/// \brief The id of the left motor
	///
	static constexpr uint_t LEFT_MOTOR_ID = 0;
	
	///
	/// \brief The id of the right motor
	///
	static constexpr uint_t RIGHT_MOTOR_ID = 0;
	
	///
	/// \brief The wheel radius in m
	///
	static constexpr real_t WHEEL_RADIUS = 0.025;
	
	///
	/// \brief The axle length in m
	///
	static constexpr real_t AXLE_LENGTH = 0.052;
	
	///
	/// \brief max fwd speed
	///
	static constexpr real_t MAX_FWD_SPEED = 0.25;
	
	///
	/// \brief max backward speed
	///
	static constexpr real_t MAX_BWD_SPEED = 0.25;
	
	///
	/// \brief Rotation maximum speed rad/s
	///
	static constexpr real_t MAX_ROTATION_SPEED = 6.28;
};

struct EpuckOdometry{
	
	///
	/// \brief Distance covered by left wheel in m
	///
	real_t dl;
	
	///
	/// \brief Distance covered by right wheel in m
	///
	real_t dr;
	
	///
	/// \brief Orientation of the robot
	///
	real_t da;
	
	///
	/// \brief Constructor
	///
	EpuckOdometry(real_t dl_, real_t dr_, real_t da_);
	
	
	///
    /// \brief print
    /// \param out
    /// \return
    ///
    std::ostream& print(std::ostream& out)const noexcept;
	
};


inline
EpuckOdometry::EpuckOdometry(real_t dl_, real_t dr_, real_t da_)
:
dl(dl_),
dr(dr_),
da(da_)
{}


inline
std::ostream& operator<<(std::ostream& out, const EpuckOdometry& info){
    return info.print(out);
}

///
/// \brief class Epuck. Wrapper around webots::Robot class that specifically models
/// an Epuck robot. The robot specification can be found at
/// https://www.cyberbotics.com/doc/guide/epuck?version=cyberbotics:R2019a-rev1
///
class EpuckRobot final: protected EpuckRobotProperties 
{
public:
	
	///
    /// \brief name
    ///
    static const std::string name;
	
	///
	/// \brief the default time step for simulating the world
	///
	static constexpr uint_t DEFAULT_SIM_TIME_STEP  = 32;
	
	
	
	using EpuckRobotProperties::LEFT_POSITION_SENSOR_ID;
	using EpuckRobotProperties::RIGHT_POSITION_SENSOR_ID;
	using EpuckRobotProperties::WHEEL_RADIUS;
	using EpuckRobotProperties::AXLE_LENGTH;
	using EpuckRobotProperties::MAX_FWD_SPEED;
	using EpuckRobotProperties::MAX_BWD_SPEED;
	using EpuckRobotProperties::MAX_ROTATION_SPEED;
		
	///
	/// \brief Create an e-puck robot
	///
	EpuckRobot();
	
	///
	/// \brief Returns the actual webots::Robot pointer
	///
	std::shared_ptr<webots::Robot> get_webots_robot_prt(){return robot_;}
	
	///
	/// \brief Activate the motor with the given motor_id
	///
	void activate_motor(uint_t motor_id, real_t init_velocity);
	
	///
	/// \brief Activate the position sensor with the given name
	///
	void activate_position_sensor(uint_t sensor_id, uint_t time_step);
	
	///
	/// \brief Activate the proximity sensor with the given name
	///
	void activate_proximity_sensor(const std::string& name, uint_t time_step);
	
	///
	/// \brief Step in the simulation environment
	///
	int_t step(uint_t time_step);
	
	///
	/// \brief Compute the odometry value
	///
	EpuckOdometry compute_odometry()const;
	
	///
	/// \brief Get the basic time step used by the robot
	///
	uint_t get_basic_time_step()const{return robot_ -> getBasicTimeStep();}
	
	

		
private:
		
	/// pointer to the robot to manipulate
	/// see https://cyberbotics.com/doc/reference/robot
	///
	std::shared_ptr<webots::Robot> robot_;
	
	webots::PositionSensor* left_position_sensor_;
	webots::PositionSensor* right_position_sensor_;
	
	
	///
	/// \brief The two motors of the robot
	///
	std::vector<webots::Motor*> motors_;
	
	///
	/// \brief Array of the proximity sensors
	///
	std::vector<webots::DistanceSensor*> proximity_sensors_;
	
	
	
};
	
	}
}
}


#endif
#endif