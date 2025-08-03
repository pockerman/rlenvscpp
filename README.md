[![Build rlenvs](https://github.com/pockerman/rlenvs_from_cpp/actions/workflows/build.yml/badge.svg)](https://github.com/pockerman/rlenvs_from_cpp/actions/workflows/build.yml)
# rlenvscpp

```rlenvscpp``` is an effort to provide implementations and wrappers of environments suitable for training reinforcement learning agents
using  C++. 

In addition, the library provides various utilities such as experiment tracking,
representing trajectories  via waypoints and simple implementation of popular dynamics such as 
quadrotor dynamics.

Furthermore, there is some minimal support for working with Arduino UNO boards over USB or WiFi.
See also <a href="https://rlenvscpp.readthedocs.io/en/latest/working_with_webots.html">Working with Webots</a>
for how to integrate ```rlenvscpp``` with <a href="https://cyberbotics.com/doc/guide/installing-webots">Webots</a>.
Example <a href="https://rlenvscpp.readthedocs.io/en/latest/examples/ray/ray_example_2.html">Using rlenvscpp with Ray</a>
shows how to use <a href="https://www.ray.io/">Ray</a> with the ```rlenvscpp```.

Various RL algorithms using the environments can be found at <a href="https://github.com/pockerman/cuberl/tree/master">cuberl</a>.

The documentation for the library can be found <a href="https://rlenvscpp.readthedocs.io/en/latest/">here</a>.
The following is an example how to use the 
``FrozenLake``   environment from <a href="https://github.com/Farama-Foundation/Gymnasium/tree/main">Gymnasium</a>.

```

#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/gymnasium/toy_text/frozen_lake_env.h"
#include "rlenvs/envs/api_server/apiserver.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <any>

namespace example_1{
    const std::string SERVER_URL = "http://0.0.0.0:8001/api";
	using rlenvscpp::envs::gymnasium::FrozenLake;
	using rlenvscpp::envs::RESTApiServerWrapper;

	void test_frozen_lake(const RESTApiServerWrapper& server){

		FrozenLake<4> env(server);

		std::cout<<"Environame URL: "<<env.get_url()<<std::endl;

		// make the environment
		std::unordered_map<std::string, std::any> options;
		options.insert({"is_slippery", false});
		env.make("v1", options);

		std::cout<<"Is environment created? "<<env.is_created()<<std::endl;
		std::cout<<"Is environment alive? "<<env.is_alive()<<std::endl;
		std::cout<<"Number of valid actions? "<<env.n_actions()<<std::endl;
		std::cout<<"Number of states? "<<env.n_states()<<std::endl;

		// reset the environment
		auto time_step = env.reset(42, std::unordered_map<std::string, std::any>());

		std::cout<<"Reward on reset: "<<time_step.reward()<<std::endl;
		std::cout<<"Observation on reset: "<<time_step.observation()<<std::endl;
		std::cout<<"Is terminal state: "<<time_step.done()<<std::endl;

		//...print the time_step
		std::cout<<time_step<<std::endl;

		// take an action in the environment
		// 2 = RIGHT
		auto new_time_step = env.step(2);

		std::cout<<new_time_step<<std::endl;

		// get the dynamics of the environment for the given state and action
		auto state = 0;
		auto action = 1;
		auto dynamics = env.p(state, action);

		std::cout<<"Dynamics for state="<<state<<" and action="<<action<<std::endl;

		for(auto item:dynamics){

			std::cout<<std::get<0>(item)<<std::endl;
			std::cout<<std::get<1>(item)<<std::endl;
			std::cout<<std::get<2>(item)<<std::endl;
			std::cout<<std::get<3>(item)<<std::endl;
		}
		
		action = env.sample_action();
		new_time_step = env.step(action);

		std::cout<<new_time_step<<std::endl;
		
		// synchronize the environment
		env.sync(std::unordered_map<std::string, std::any>());
		
		auto copy_env = env.make_copy(1);
		copy_env.reset();
		
		std::cout<<"Org env cidx: "<<env.cidx()<<std::endl;
		std::cout<<"Copy env cidx: "<<copy_env.cidx()<<std::endl;
		
		copy_env.close();

		// close the environment
		env.close();
	}
}

int main(){

	using namespace example_1;
		
	RESTApiServerWrapper server(SERVER_URL, true);

	std::cout<<"Testing FrozenLake..."<<std::endl;
	example_1::test_frozen_lake(server);
	std::cout<<"===================="<<std::endl;
	return 0;
}
```
