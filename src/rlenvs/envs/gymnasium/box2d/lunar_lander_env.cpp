//
// Created by alex on 6/29/25.
//

#include "rlenvs/envs/gymnasium/box2d/lunar_lander_env.h"

namespace rlenvscpp
{
    namespace envs::gymnasium
    {


        const std::string LunarLanderDiscreteEnv::name = "LunarLanderDiscrete";
        const std::string LunarLanderDiscreteEnv::URI = "/gymnasium/lunar-lander-discrete-env";

        LunarLanderDiscreteEnv::LunarLanderDiscreteEnv(const RESTApiServerWrapper& api_server)
        :
        LunarLanderDiscreteEnv::base_type(api_server, 0, LunarLanderDiscreteEnv::name, LunarLanderDiscreteEnv::URI)
        {}

        LunarLanderDiscreteEnv::LunarLanderDiscreteEnv(const RESTApiServerWrapper& api_server, const uint_t cidx)
        :
        LunarLanderDiscreteEnv::base_type(api_server, cidx, LunarLanderDiscreteEnv::name, LunarLanderDiscreteEnv::URI)
        {}

        LunarLanderDiscreteEnv::LunarLanderDiscreteEnv(const LunarLanderDiscreteEnv& other)
            :
        LunarLanderDiscreteEnv::base_type(other)
        {}

        void
        LunarLanderDiscreteEnv::make(const std::string& version,
                             const std::unordered_map<std::string, std::any>& options)
        {

            if(this->is_created()){
                return;
            }


            nlohmann::json ops;

            if (auto gravity_itr = options.find("gravity"); gravity_itr != options.end())
            {
                auto gravity = std::any_cast<real_t>(gravity_itr->second);
                ops["gravity"] = gravity;
            }

            if (auto enable_wind_itr = options.find("enable_wind"); enable_wind_itr != options.end())
            {
                auto wind = std::any_cast<bool>(enable_wind_itr->second);
                ops["enable_wind"] = wind;
            }

            if (auto wind_power_itr = options.find("wind_power"); wind_power_itr != options.end())
            {
                auto wind_power = std::any_cast<real_t>(wind_power_itr->second);
                ops["wind_power"] = wind_power;
            }

            if (auto turbulence_power_itr = options.find("turbulence_power"); turbulence_power_itr != options.end())
            {
                auto turbulence_power = std::any_cast<real_t>(turbulence_power_itr->second);
                ops["turbulence_power"] = turbulence_power;
            }

            auto response  = this -> get_api_server().make(this -> env_name(),
                                                               this -> cidx(),
                                                               version, ops);

            this -> base_type::make(version, options);
        }


        LunarLanderDiscreteEnv::time_step_type
        LunarLanderDiscreteEnv::step(const action_type& action)
        {
            return this -> base_type::step(action);
        }

        LunarLanderDiscreteEnv
        LunarLanderDiscreteEnv::make_copy(uint_t cidx)const
        {

            LunarLanderDiscreteEnv copy(this -> get_api_server(), cidx);
            auto version = this -> version();
            copy.make(version, this -> make_options());
            return copy;

        }

        LunarLanderDiscreteEnv::time_step_type
        LunarLanderDiscreteEnv::create_time_step_from_response_(const nlohmann::json& response)const
        {
                auto step_type = response["time_step"]["step_type"].template get<uint_t>();
                auto reward    = response["time_step"]["reward"];
                auto discount  = response["time_step"]["discount"];
                auto obs       = response["time_step"]["observation"];
                auto info      = response["time_step"]["info"];
                return LunarLanderDiscreteEnv::time_step_type(TimeStepEnumUtils::time_step_type_from_int(step_type),
                                                             reward, obs, discount,
                                                             std::unordered_map<std::string, std::any>());


        }
    }
}
