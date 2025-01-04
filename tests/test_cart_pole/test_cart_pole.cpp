#include "rlenvs/envs/gymnasium/classic_control/cart_pole_env.h"
#include "rlenvs/envs/api_server/apiserver.h"
#include "rlenvs/rlenvs_types_v2.h"

#include <gtest/gtest.h>

#include <unordered_map>

namespace{

const std::string SERVER_URL = "http://0.0.0.0:8001/api";
using rlenvscpp::uint_t;
using rlenvscpp::real_t;
using rlenvscpp::envs::gymnasium::CartPole;
using rlenvscpp::envs::RESTApiServerWrapper;
RESTApiServerWrapper server(SERVER_URL);
}


TEST(TestCartPole, TestConstructor) {

    CartPole env(server);
	auto url = env.get_url();
	ASSERT_TRUE(url == "http://0.0.0.0:8001/api/gymnasium/cart-pole-env");

}


TEST(TestCartPole, Test_Make)
{
    CartPole env(server);
    auto copy_env = env.make_copy(static_cast<uint_t>(1));
    ASSERT_TRUE(copy_env.is_created());
}







