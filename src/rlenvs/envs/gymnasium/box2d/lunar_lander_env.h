//
// Created by alex on 6/29/25.
//

#ifndef LUNAR_LANDER_ENV_H
#define LUNAR_LANDER_ENV_H

#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/time_step.h"
#include "rlenvs/envs/gymnasium/gymnasium_env_base.h"
#include "rlenvs/envs/api_server/apiserver.h"

namespace rlenvscpp
{
    namespace envs::gymnasium
    {

        namespace lunar_lander_detail
        {
            template<typename TimeStepType, typename SpaceType>
            class _LunarLanderEnv: public GymnasiumEnvBase<TimeStepType, SpaceType >
            {
                public:

                ///
                /// \brief name
                ///
                static  const std::string name;

                ///
                /// \brief The URI for accessing the environment
                ///
                static const std::string URI;

                ///
                /// \brief Base class type
                ///
                typedef GymnasiumEnvBase<TimeStepType, SpaceType >::base_type base_type;

                ///
                /// \brief The time step type we return every time a step in the
                /// environment is performed
                ///
                typedef typename base_type::time_step_type time_step_type;

                ///
                /// \brief The type describing the state space for the environment
                ///
                typedef typename base_type::state_space_type state_space_type;

                ///
                /// \brief The type of the action space for the environment
                ///
                typedef typename base_type::action_space_type action_space_type;

                ///
                /// \brief The type of the action to be undertaken in the environment
                ///
                typedef typename base_type::action_type action_type;

                ///
                /// \brief The type of the state
                ///
                typedef typename base_type::state_type state_type;

                /// Constructor
                /// @param api_server
                ///
                _LunarLanderEnv(const RESTApiServerWrapper& api_server);

                ///
                /// \brief Constructor
                ///
                _LunarLanderEnv(const RESTApiServerWrapper& api_server,
                               const uint_t cidx);

                ///
                /// \brief ~Pendulum. Destructor
                ///
                ~_LunarLanderEnv()=default;

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
                LunarLanderEnv make_copy(uint_t cidx) const;


                ///
                /// \brief n_actions. Returns the number of actions
                ///
                uint_t n_actions()const noexcept{return action_space_type::size;}

            };

        }


        class LunarLanderEnv final: public lunar_lander_detail::_LunarLanderEnv<TimeStep<std::vector<real_t>>,
                                                                                ContinuousVectorStateDiscreteActionEnv<8, 4, 0, real_t> >
        {
        public:

                ///
                /// \brief Base class type
                ///
                typedef lunar_lander_detail::_LunarLanderEnv<TimeStep<std::vector<real_t>>,
                                                          ContinuousVectorStateDiscreteActionEnv<8, 4, 0, real_t> >::base_type base_type;

                ///
                /// \brief The time step type we return every time a step in the
                /// environment is performed
                ///
                typedef typename base_type::time_step_type time_step_type;

                ///
                /// \brief The type describing the state space for the environment
                ///
                typedef typename base_type::state_space_type state_space_type;

                ///
                /// \brief The type of the action space for the environment
                ///
                typedef typename base_type::action_space_type action_space_type;

                ///
                /// \brief The type of the action to be undertaken in the environment
                ///
                typedef typename base_type::action_type action_type;

                ///
                /// \brief The type of the state
                ///
                typedef typename base_type::state_type state_type;

                /// Constructor
                /// @param api_server
                ///
                LunarLanderEnv(const RESTApiServerWrapper& api_server);

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

                ///
                /// \brief n_actions. Returns the number of actions
                ///
                uint_t n_actions()const noexcept{return action_space_type::size;}

            };


    }
}

#endif //LUNAR_LANDER_ENV_H
