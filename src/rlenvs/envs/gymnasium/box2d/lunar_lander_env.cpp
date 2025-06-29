//
// Created by alex on 6/29/25.
//

#include "rlenvs/envs/gymnasium/box2d/lunar_lander_env.h"

namespace rlenvscpp
{
    namespace envs::gymnasium
    {

        LunarLanderEnv::LunarLanderEnv(const RESTApiServerWrapper& api_server);

        ///
        /// \brief Constructor
        ///
        LunarLanderEnv(const RESTApiServerWrapper& api_server,
                       const uint_t cidx);

        ///
        /// \brief ~Pendulum. Destructor
        ///
        ~LunarLanderEnv()=default;

        ///
        /// \brief make. Build the environment
        ///
        virtual void make(const std::string& version,
                          const std::unordered_map<std::string, std::any>& /*options*/) override;

        ///
        /// \brief step. Step in the environment following the given action
        ///
        virtual time_step_type step(const action_type& action)override;

        ///
        /// \brief Create a new copy of the environment with the given
        /// copy index
        ///
        LunarLanderEnv make_copy(uint_t cidx)const;
    }
}
