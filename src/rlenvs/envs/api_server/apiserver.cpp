#include "rlenvs/envs/api_server/apiserver.h"
#include "rlenvs/rlenvs_consts.h"
#include "rlenvs/extern/HTTPRequest.hpp"
#include "rlenvs/extern/nlohmann/json/json.hpp"

#include <string>
#include <stdexcept>

namespace rlenvscpp{
namespace envs{

RESTApiServerWrapper::RESTApiServerWrapper(const std::string& url, const bool initialize)
:
url_(url),
is_init_(false),
envs_()
{
  if(initialize){
	  init_();
  }
}

void 
RESTApiServerWrapper::init_(){
	
	envs_["FrozenLake"] = "/gymnasium/frozen-lake-env";
	envs_["Taxi"] = "/gymnasium/taxi-env";
	envs_["CliffWalking"] = "/gymnasium/cliff-walking-env";
	envs_["BlackJack"] = "/gymnasium/black-jack-env";
	envs_["MountainCar"] = "/gymnasium/mountain-car-env";
	envs_["CartPole"] = "/gymnasium/cart-pole-env";
	envs_["Acrobot"] = "/gymnasium/acrobot-env";
	envs_["Pendulum"] = "/gymnasium/pendulum-env";
	envs_["AcrobotV"] = "/gymnasium/acrobot-env/v";
	envs_["GymWalk"]= "/gdrl/gym-walk-env";
	
}

void 
RESTApiServerWrapper::register_new(const std::string& name, const std::string& uri){
	
	auto env_itr = envs_.find(name);
	
	if(env_itr == envs_.end()){
		envs_[name] = uri;
		return;
	}
	
	throw std::logic_error("Environment: " + name + " already exists");
	
}

void 
RESTApiServerWrapper::register_if_not(const std::string& name, 
									  const std::string& uri){
	
	try{
		register_new(name, uri);
	}
	catch(const std::logic_error& e){
		
	}
	
}

std::string 
RESTApiServerWrapper::get_uri(const std::string& name)const noexcept{
	
	auto env_itr = envs_.find(name);
	
	if(env_itr == envs_.end()){
		return rlenvscpp::consts::INVALID_STR;
	}
	
	return env_itr -> second;
}

std::string 
RESTApiServerWrapper::get_env_url(const std::string& name)const noexcept{
	
	auto uri_ = get_uri(name);
	
	if(uri_ == rlenvscpp::consts::INVALID_STR){
		return rlenvscpp::consts::INVALID_STR;
	}
	
	return get_url() + uri_;
}

nlohmann::json 
RESTApiServerWrapper::is_alive(const std::string& env_name, 
                               const uint_t cidx)const{
	
	// find the source
	auto url_ = get_env_url(env_name);
	
	if(url_ == rlenvscpp::consts::INVALID_STR){
		throw std::logic_error("Environment: " + env_name + " is not registered");
	}
	
	
	auto copy_idx_str = std::to_string(cidx);
	
    http::Request request{url_ + "/is-alive?cidx="+copy_idx_str};
    const auto response = request.send("GET");
    
	auto str_response = std::string(response.body.begin(), response.body.end());
    nlohmann::json j = nlohmann::json::parse(str_response);
	return j;	

}

nlohmann::json 
RESTApiServerWrapper::close(const std::string& env_name, 
                            const uint_t cidx)const{
	
	// find the source
	auto url_ = get_env_url(env_name);
	
	if(url_ == rlenvscpp::consts::INVALID_STR){
		throw std::logic_error("Environment: " + env_name + " is not registered");
	}
	
    http::Request request{url_ + "/close?cidx="+std::to_string(cidx)};
    const auto response = request.send("POST");
    
	
	if(response.status.code != 202){
        throw std::runtime_error("Could not close environment " + env_name);
    }
	
	auto str_response = std::string(response.body.begin(), response.body.end());
    nlohmann::json j = nlohmann::json::parse(str_response);
	return j;	
}

nlohmann::json 
RESTApiServerWrapper::reset(const std::string& env_name, 
                            const uint_t cidx,
                            const uint_t seed,
	                        const nlohmann::json& options)const{
								
	
    // find the source
	auto url_ = get_env_url(env_name);
	
	if(url_ == rlenvscpp::consts::INVALID_STR){
		throw std::logic_error("Environment: " + env_name + " is not registered");
	}

	const auto request_url = url_ + "/reset";
    http::Request request{request_url};

    nlohmann::json request_body;
    request_body["seed"] = seed;
	request_body["cidx"] = cidx;
	request_body["options"] = options;
	
    const auto response = request.send("POST", request_body.dump());

     if(response.status.code != 202){
        throw std::runtime_error("Environment server failed to reset environment");
    }
								
	auto str_response = std::string(response.body.begin(), response.body.end());
    nlohmann::json j = nlohmann::json::parse(str_response);
	return j;							
								
}


nlohmann::json 
RESTApiServerWrapper::make(const std::string& env_name, 
                           const uint_t cidx,
						   const std::string& version,
						   const nlohmann::json& options)const{

	// find the source
	auto url_ = get_env_url(env_name);
	
	if(url_ == rlenvscpp::consts::INVALID_STR){
		throw std::logic_error("Environment: " + env_name + " is not registered");
	}
	
	const auto request_url = url_ + "/make";
    http::Request request{request_url};
	
    nlohmann::json request_body;
    request_body["version"] = version;
	request_body["cidx"] = cidx;
	request_body["options"] = options;
	
    const auto response = request.send("POST", request_body.dump());

    if(response.status.code != 201){
        throw std::runtime_error("Environment server failed to create Environment");
    }
	
	auto str_response = std::string(response.body.begin(), response.body.end());
    nlohmann::json j = nlohmann::json::parse(str_response);
	return j;	
								
}

nlohmann::json 
RESTApiServerWrapper::dynamics(const std::string& env_name, 
							   const uint_t cidx,
	                           const uint_t sidx, 
							   const uint_t aidx)const{
								   
	// find the source
	auto url_ = get_env_url(env_name);
	
	if(url_ == rlenvscpp::consts::INVALID_STR){
		throw std::logic_error("Environment: " + env_name + " is not registered");
	}
	
	const auto request_url = url_ + "/dynamics?cidx="+std::to_string(cidx)
	                                                +"&stateId="+std::to_string(sidx)
													+"&actionId="+std::to_string(aidx);
    http::Request request{request_url};
    const auto response = request.send("GET");
	
	auto str_response = std::string(response.body.begin(), response.body.end());
    nlohmann::json j = nlohmann::json::parse(str_response);
	return j;	
}

bool
RESTApiServerWrapper::has_gymnasium()const{

    const auto request_url = url_ + "/api-info/gymnasium";
    http::Request request{request_url};

    const auto response = request.send("GET");
    return response.status.code == 200;

}

std::vector<std::string>
RESTApiServerWrapper::gymnasium_envs()const{

    const auto request_url = url_ + "/api-info/gymnasium/envs";
    http::Request request{request_url};

    const auto response = request.send("GET");

    if(response.status.code != 200){
        throw std::runtime_error("Environment server responded with error");
    }

    auto str_response = std::string(response.body.begin(), response.body.end());
    using json = nlohmann::json;
    json j = json::parse(str_response);
    return j["envs"];
}

}
}
