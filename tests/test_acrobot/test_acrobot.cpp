#include "rlenvs/envs/gymnasium/classic_control/acrobot_env.h"
#include "rlenvs/rlenvs_types_v2.h"

#include <gtest/gtest.h>
#include <unordered_map>
#include <string>
#include <any>

namespace{

using rlenvs_cpp::uint_t;
using rlenvs_cpp::real_t;

const std::string SERVER_URL = "http://0.0.0.0:8001/api";

}

TEST(TestAcrobot, TestConstructor) {

    rlenvs_cpp::envs::gymnasium::Acrobot env(SERVER_URL);
    ASSERT_EQ(env.n_actions(), static_cast<uint_t>(3));
}



TEST(TestAcrobot, Test_Make){
    rlenvs_cpp::envs::gymnasium::Acrobot env(SERVER_URL);

    std::unordered_map<std::string, std::any> options;
    env.make("v1", options);
}


TEST(TestAcrobot, Test_Reset){

    rlenvs_cpp::envs::gymnasium::Acrobot env(SERVER_URL);

    std::unordered_map<std::string, std::any> options;
    env.make("v1", options);

    auto state = env.reset();
    ASSERT_TRUE(state.first());

}

TEST(TestAcrobot, Test_Step)
{

    rlenvs_cpp::envs::gymnasium::Acrobot env(SERVER_URL);

    std::unordered_map<std::string, std::any> options;
    env.make("v1", options);
    env.reset();

    auto step_result = env.step(0);
    ASSERT_TRUE(step_result.mid());

}