//
// Created by alex on 7/5/25.
//

#include "rlenvs/envs/gymnasium/box2d/lunar_lander_env.h"
#include "rlenvs/envs/api_server/apiserver.h"

#include <unordered_map>
#include <iostream>

namespace box2d_example
{
    const std::string SERVER_URL = "http://0.0.0.0:8001/api";
    using rlenvscpp::envs::RESTApiServerWrapper;
    using rlenvscpp::envs::gymnasium::LunarLanderDiscreteEnv;
}

int main()
{
    using namespace box2d_example;

    RESTApiServerWrapper server(SERVER_URL, true);

    LunarLanderDiscreteEnv env(server);

    std::unordered_map<std::string, std::any> options;
    options["wind_power"] = std::any(static_cast<rlenvscpp::real_t>(10.0));
    options["enable_wind"] = std::any(static_cast<bool>(true));
    options["gravity"] = std::any(static_cast<rlenvscpp::real_t>(-9.86));
    options["turbulence_power"] = std::any(static_cast<rlenvscpp::real_t>(1.5));
    env.make("v3", options);

    std::cout<<"Is environment created? "<<env.is_created()<<std::endl;
    std::cout<<"Is environment alive? "<<env.is_alive()<<std::endl;
    std::cout<<"Number of valid actions? "<<env.n_actions()<<std::endl;

    auto time_step = env.reset();
    std::cout<<"Time step: "<<time_step<<std::endl;

    time_step = env.step(1);
    std::cout<<"Time step: "<<time_step<<std::endl;

    auto copy = env.make_copy(1);
    time_step = copy.reset();
    std::cout<<"Time step: "<<time_step<<std::endl;

    env.close();
    copy.close();

}
