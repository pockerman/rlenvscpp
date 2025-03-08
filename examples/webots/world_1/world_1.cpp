//#include "rlenvs/envs/webots_envs/epuck_simple_grid_world.h"
#include "rlenvs/rlenvscpp_config.h"
#include "rlenvs/envs/webots_envs/webots_base_env.h"
#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/time_step.h"
#include "rlenvs/envs/env_types.h"

using namespace rlenvscpp;
using namespace rlenvscpp::envs;
using namespace rlenvscpp::envs::webots_envs;

typedef std::vector<real_t> state_type;
typedef TimeStep<uint_t> time_step_type;
typedef ScalarDiscreteEnv<1, 1> state_action_space_type;
class MyClass: public WebotsEnvBase<time_step_type, state_action_space_type>
{};

int main() {
	
	//using rlenvscpp::envs::webots_envs::EpuckSimpleGridWorld;
	//EpuckSimpleGridWorld env;

	return 0;
	
}


