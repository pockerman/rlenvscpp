#include "rlenvs/rigid_bodies/webots_robots/epuck_robot.h"

#ifdef RLENVSCPP_WEBOTS

namespace rlenvscpp{
namespace rigid_bodies{
namespace webots_robots{
	
using namespace webots;

const std::string EpuckRobot::name = "epuck";

EpuckRobot::EpuckRobot()
:
robot_(),
left_position_sensor_(nullptr),
right_position_sensor_(nullptr),
motors_(2, nullptr),
proximity_sensors_(EpuckRobot::DISTANCE_SENSORS_NUMBER, nullptr)
{
	
	robot_ = std::make_shared<webots::Robot>();
}


void 
EpuckRobot::activate_motor(uint_t motor_id, real_t init_velocity){
	
	if(motor_id == 0){
		motors_[0] = robot_ -> getMotor("left wheel motor");
		motors_[0] -> setPosition(INFINITY);
		motors_[0] -> setVelocity(init_velocity);
	}
	
	if(motor_id == 1){
		motors_[1] = robot_ -> getMotor("right wheel motor");
		motors_[1] -> setPosition(INFINITY);
		motors_[1] -> setVelocity(init_velocity);
	}
}

void 
EpuckRobot::activate_position_sensor(uint_t sensor_id, uint_t time_step){
	
	if(sensor_id == 0){
		left_position_sensor_ = robot_->getPositionSensor("left wheel sensor");
		left_position_sensor_ -> enable(time_step);
	}
	
	if(sensor_id == 1){
		right_position_sensor_ = robot_->getPositionSensor("right wheel sensor");
		right_position_sensor_ -> enable(time_step);
	}
	
}

void 
EpuckRobot::activate_proximity_sensor(const std::string& name, uint_t time_step){
	
	if(name == "ps0"){
		proximity_sensors_[0] = robot_ -> getDistanceSensor("ps0");
		proximity_sensors_[0] -> enable(time_step);
	}
	
	if(name == "ps1"){
		proximity_sensors_[1] = robot_ -> getDistanceSensor("ps1");
		proximity_sensors_[1] -> enable(time_step);
	}
	
	if(name == "ps2"){
		proximity_sensors_[2] = robot_ -> getDistanceSensor("ps2");
		proximity_sensors_[2] -> enable(time_step);
	}
	
	if(name == "ps3"){
		proximity_sensors_[3] = robot_ -> getDistanceSensor("ps3");
		proximity_sensors_[3] -> enable(time_step);
	}
	
	if(name == "ps4"){
		proximity_sensors_[4] = robot_ -> getDistanceSensor("ps4");
		proximity_sensors_[4] -> enable(time_step);
	}
	
	if(name == "ps5"){
		proximity_sensors_[5] = robot_ -> getDistanceSensor("ps5");
		proximity_sensors_[5] -> enable(time_step);
	}
	
	if(name == "ps6"){
		proximity_sensors_[6] = robot_ -> getDistanceSensor("ps6");
		proximity_sensors_[6] -> enable(time_step);
	}
	
	if(name == "ps7"){
		proximity_sensors_[7] = robot_ -> getDistanceSensor("ps7");
		proximity_sensors_[7] -> enable(time_step);
	}
}


EpuckOdometry 
EpuckRobot::compute_odometry()const{
	
	
  real_t l = left_position_sensor_ -> getValue();
  real_t r = right_position_sensor_ -> getValue(); 
  real_t dl = l * WHEEL_RADIUS;         // distance covered by left wheel in meter
  real_t dr = r * WHEEL_RADIUS;         // distance covered by right wheel in meter
  real_t da = (dr - dl) / AXLE_LENGTH;  // delta orientation
  
  return EpuckOdometry(dl, dr, da);
	
}

int_t 
EpuckRobot::step(uint_t time_step){
	
	return robot_ -> step(time_step);
}


std::ostream& 
EpuckOdometry::print(std::ostream& out)const noexcept{
	
	out<<"dl: "<< dl <<std::endl;
	out<<"dr: "<< dr <<std::endl;
	out<<"da: "<< da <<std::endl;
	return out;
}
	
}
}
}


#endif