#include "webots/Robot.hpp"


int main(int argc, char **argv) {

		using namespace webots;
		Robot* robot  = new Robot();
		
		// get the time step of the current world.
		int timeStep = (int)robot->getBasicTimeStep();
		
		delete robot;
		return 0;
	
}


