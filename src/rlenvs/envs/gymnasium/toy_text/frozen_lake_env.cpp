#include "rlenvs/envs/gymnasium/toy_text/frozen_lake_env.h"
#include "rlenvs/rlenvscpp_config.h"
#include "rlenvs/envs/time_step_type.h"
#include "rlenvs/extern/nlohmann/json/json.hpp"


#ifdef RLENVSCPP_DEBUG
#include <cassert>
#endif

#include <iostream>
#include <memory>

namespace rlenvscpp{
namespace envs{
namespace gymnasium{

template<uint_t side_size>
const std::string FrozenLake<side_size>::name = "FrozenLake";

template<uint_t side_size>
const std::string FrozenLake<side_size>::URI = "/gymnasium/frozen-lake-env";

template<uint_t side_size>
FrozenLake<side_size>::FrozenLake(const RESTApiServerWrapper& api_server)
:
ToyTextEnvBase<TimeStep<uint_t>,
			   frozenlake_state_size<side_size>::size, 
			   3>(api_server, 0, FrozenLake<side_size>::name),
is_slippery_(true)
{
		this -> get_api_server().register_if_not(FrozenLake<side_size>::name,FrozenLake<side_size>::URI);
}
 
template<uint_t side_size>
FrozenLake<side_size>::FrozenLake(const RESTApiServerWrapper& api_server, 
		                          const uint_t cidx, bool slippery)
		   :
ToyTextEnvBase<TimeStep<uint_t>,
			   frozenlake_state_size<side_size>::size, 
			   3>(api_server, cidx, FrozenLake<side_size>::name),
is_slippery_(slippery)
{
	this -> get_api_server().register_if_not(FrozenLake<side_size>::name,FrozenLake<side_size>::URI);
}

template<uint_t side_size>
FrozenLake<side_size>::FrozenLake(const FrozenLake<side_size>& other)
:
ToyTextEnvBase<TimeStep<uint_t>,
			   frozenlake_state_size<side_size>::size, 
			   3>(other),
is_slippery_(other.is_slippery_)
{}		
			   
template<uint_t side_size>
typename FrozenLake<side_size>::time_step_type
FrozenLake<side_size>::create_time_step_from_response_(const nlohmann::json& response)const{

    auto step_type = response["time_step"]["step_type"].template get<uint_t>();
	auto step_type_val = TimeStepEnumUtils::time_step_type_from_int(step_type);
    auto reward = response["time_step"]["reward"];
    auto discount = response["time_step"]["discount"];
    auto observation = response["time_step"]["observation"];
    auto info = response["time_step"]["info"];
	
	auto time_step = FrozenLake<side_size>::time_step_type(step_type_val,
                                                 reward, observation, discount,
                                                 std::unordered_map<std::string, std::any>());
												 
    return time_step;
}

template<uint_t side_size>
void
FrozenLake<side_size>::make(const std::string& version,
                            const std::unordered_map<std::string, std::any>& options){

    if(this->is_created()){
        return;
    }

    is_slippery_ = true;

    auto slip_itr = options.find("is_slippery");
    if( slip_itr != options.end()){
        is_slippery_ = std::any_cast<bool>(slip_itr->second);
    }
	
	nlohmann::json ops;
	ops["map_name"] = map_type();
	ops["is_slippery"] = is_slippery_;
    auto response = this -> get_api_server().make(this -> env_name(),
												  this -> cidx(),
												  version, ops);
												  
    this->set_version_(version);
    this->make_created_();
}

template<uint_t side_size>
typename FrozenLake<side_size>::time_step_type
FrozenLake<side_size>::step(const action_type& action){

#ifdef RLENVSCPP_DEBUG
     assert(this->is_created() && "Environment has not been created");
#endif

     if(this->get_current_time_step_().last()){
         return this->reset(42, std::unordered_map<std::string, std::any>());
     }
	 
	 auto response = this -> get_api_server().step(this -> env_name(),
												  this -> cidx(),
												  action);

    this->get_current_time_step_() = this->create_time_step_from_response_(response);
    return this->get_current_time_step_();

}

template<uint_t side_size>
FrozenLake<side_size> 
FrozenLake<side_size>::make_copy(uint_t cidx)const{
	
	auto slippery = this -> is_slippery();
	FrozenLake<side_size> copy(this -> get_api_server(),
							   cidx, slippery);
	
	std::unordered_map<std::string, std::any> ops;
	ops["is_slippery"] = this -> is_slippery();
	auto version = this -> version();
	copy.make(version, ops);
	return copy;
												
}

template class FrozenLake<4>;
template class FrozenLake<8>;

}
}
}
