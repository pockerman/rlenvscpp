#include "rlenvs/envs/gymnasium/toy_text/cliff_world_env.h"
#include "rlenvs/envs/api_server/apiserver.h"
#include "rlenvs/rlenvs_types_v2.h"

#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <any>


namespace{

const std::string SERVER_URL = "http://0.0.0.0:8001/api";
using rlenvscpp::uint_t;
using rlenvscpp::real_t;
using rlenvscpp::envs::gymnasium::CliffWorld;
using rlenvscpp::envs::RESTApiServerWrapper;
RESTApiServerWrapper server(SERVER_URL);

}

TEST(TestCliffWorld, TestConstructor) {

    CliffWorld env(server);
    ASSERT_EQ(env.n_actions(), static_cast<uint_t>(4));
    ASSERT_EQ(env.name, "CliffWalking");

}

TEST(TestCliffWorld, Test_Make)
{

    CliffWorld env(server);

    std::unordered_map<std::string, std::any> options;
    env.make("v0", options);
    ASSERT_EQ(env.n_actions(), static_cast<uint_t>(4));
    ASSERT_EQ(env.n_states(), static_cast<uint_t>(37));
}


TEST(TestCliffWorld, Test_Reset)
{
    CliffWorld env(server);

    std::unordered_map<std::string, std::any> options;
    env.make("v0", options);

    auto state = env.reset();
    ASSERT_TRUE(state.first());
}

TEST(TestCliffWorld, Test_Step)
{
    CliffWorld env(server);

    std::unordered_map<std::string, std::any> options;
    env.make("v0", options);
    env.reset();

    auto step_result = env.step(0);
    ASSERT_TRUE(step_result.mid());

}

TEST(TestCliffWorld, Test_Step_With_Query)
{
    CliffWorld env(server);

    std::unordered_map<std::string, std::any> options;
    env.make("v0", options);
    env.reset();
    auto step_result = env.step(0);

    ASSERT_TRUE(step_result.mid());
    ASSERT_DOUBLE_EQ(step_result.get_extra<real_t>("prob"), 1.0);

}


TEST(TestCliffWorld, Test_Get_Dynamics)
{

    CliffWorld env(server);

    std::unordered_map<std::string, std::any> options;
    env.make("v0", options);
    env.reset();

    auto step_result = env.step(0);

    ASSERT_TRUE(step_result.mid());
    ASSERT_DOUBLE_EQ(step_result.get_extra<real_t>("prob"), 1.0);

    auto dynamics = env.p(1, 3);
    ASSERT_EQ(dynamics.size(), static_cast<uint_t>(1));

}
