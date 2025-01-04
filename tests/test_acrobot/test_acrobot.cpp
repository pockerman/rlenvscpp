#include "rlenvs/envs/gymnasium/classic_control/acrobot_env.h"
#include "rlenvs/envs/api_server/apiserver.h"
#include "rlenvs/rlenvs_types_v2.h"

#include <gtest/gtest.h>
#include <unordered_map>
#include <string>
#include <any>

namespace{

using namespace rlenvscpp;
using rlenvscpp::envs::gymnasium::Acrobot;
const std::string SERVER_URL = "http://0.0.0.0:8001/api";
using rlenvscpp::envs::RESTApiServerWrapper;
RESTApiServerWrapper server(SERVER_URL);

}

TEST(TestAcrobot, TestConstructor) {

    Acrobot env(server);
    ASSERT_EQ(env.n_actions(), static_cast<uint_t>(3));
}



TEST(TestAcrobot, Test_Make){
    Acrobot env(server);

    std::unordered_map<std::string, std::any> options;
    env.make("v1", options);
}


TEST(TestAcrobot, Test_Reset){

    Acrobot env(server);

    std::unordered_map<std::string, std::any> options;
    env.make("v1", options);

    auto state = env.reset();
    ASSERT_TRUE(state.first());

}

TEST(TestAcrobot, Test_Step)
{

    Acrobot env(server);

    std::unordered_map<std::string, std::any> options;
    env.make("v1", options);
    env.reset();

    auto step_result = env.step(0);
    ASSERT_TRUE(step_result.mid());

}
