//
// Created by alex on 6/29/25.
//

#ifndef LUNAR_LANDER_ENV_H
#define LUNAR_LANDER_ENV_H

#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/time_step.h"
#include "rlenvs/envs/gymnasium/gymnasium_env_base.h"
#include "rlenvs/envs/api_server/apiserver.h"
#include "rlenvs/envs/env_types.h"
#include "rlenvs/extern/nlohmann/json/json.hpp"

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
                /// @param name
                /// @param uri
                ///
                _LunarLanderEnv(const RESTApiServerWrapper& api_server, uint_t cidx,
                                const std::string& name, const std::string& uri);

                ///
                /// @param other
                ///
                _LunarLanderEnv(const _LunarLanderEnv& other);

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


            };

            template<typename TimeStepType, typename SpaceType>
            _LunarLanderEnv<TimeStepType, SpaceType>::_LunarLanderEnv(const RESTApiServerWrapper& api_server, uint_t cidx,
                const std::string& name, const std::string& uri)
                :
            GymnasiumEnvBase<TimeStepType, SpaceType >(api_server, cidx, name)
            {
                this -> get_api_server().register_if_not(name, uri);
            }

            template<typename TimeStepType, typename SpaceType>
            _LunarLanderEnv<TimeStepType, SpaceType>::_LunarLanderEnv(const _LunarLanderEnv<TimeStepType, SpaceType>& other)
                :
            GymnasiumEnvBase<TimeStepType, SpaceType >(other)
            {}

            template<typename TimeStepType, typename SpaceType>
            void
            _LunarLanderEnv<TimeStepType, SpaceType>::make(const std::string& version,
                                                           const std::unordered_map<std::string, std::any>& options)
            {
                this -> set_version_(version);
                this -> set_make_options_(options);
                this -> make_created_();
            }

            template<typename TimeStepType, typename SpaceType>
            typename _LunarLanderEnv<TimeStepType, SpaceType>::time_step_type
            _LunarLanderEnv<TimeStepType, SpaceType>::step(const action_type& action)
            {

#ifdef RLENVSCPP_DEBUG
                assert(this->is_created() && "Environment has not been created");
#endif

                if(this->get_current_time_step_().last()){
                    return this->reset(42, std::unordered_map<std::string, std::any>());
                }

                const auto response  = this -> get_api_server().step(this -> env_name(),
                                                                         this -> cidx(),
                                                                         action);

                this->get_current_time_step_() = this->create_time_step_from_response_(response);
                return this->get_current_time_step_();
            }

        }


        ///
        /// \brief LunarLanderDiscreteEnv environment with discrete action space
        ///
        class LunarLanderDiscreteEnv final : public lunar_lander_detail::_LunarLanderEnv<TimeStep<std::vector<real_t>>,
                ContinuousVectorStateDiscreteActionEnv<8, 4, 0, real_t>>
        {
        public:
            ///
            /// \brief name
            ///
            static const std::string name;

            ///
            /// \brief The URI for accessing the environment
            ///
            static const std::string URI;

            ///
            /// \brief Base class type
            ///
            typedef lunar_lander_detail::_LunarLanderEnv<TimeStep<std::vector<real_t>>,
                                                         ContinuousVectorStateDiscreteActionEnv<8, 4, 0, real_t> > base_type;

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
                LunarLanderDiscreteEnv(const RESTApiServerWrapper& api_server);

                ///
                /// \brief Constructor
                ///
                LunarLanderDiscreteEnv(const RESTApiServerWrapper& api_server, const uint_t cidx);

                ///
                /// @param other
                ///
                LunarLanderDiscreteEnv(const LunarLanderDiscreteEnv& other);

                ///
                /// \brief ~Pendulum. Destructor
                ///
                ~LunarLanderDiscreteEnv() override =default;

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
                LunarLanderDiscreteEnv make_copy(uint_t cidx)const;

                ///
                /// \brief n_actions. Returns the number of actions
                ///
                uint_t n_actions()const noexcept{return action_space_type::size;}


        protected:

                ///
                /// \brief build the time step from the server response
                ///
                virtual time_step_type create_time_step_from_response_(const nlohmann::json& response)const override;

        };




    }
}

#endif //LUNAR_LANDER_ENV_H
