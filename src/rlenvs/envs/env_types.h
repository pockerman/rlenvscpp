#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/space_type.h"

namespace rlenvscpp{
namespace envs{
	

template<uint_t state_end,  uint_t action_end, uint_t state_start=0, uint_t action_start=0> 
struct ScalarDiscreteEnv{
	
	///
    /// \brief item_t
    ///
    typedef ScalarDiscreteSpace<state_start, state_end> state_space;
	
	///
	/// \brief the State type
	///
	typedef typename state_space::space_item_type state_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t STATE_SPACE_SIZE = state_space::size;


    ///
    /// \brief the action space type
    ///
    typedef ScalarDiscreteSpace<action_start, action_end> action_space;
	
	///
	/// \brief the Action type
	///
	typedef typename action_space::space_item_type action_type;
	
	
	///
    /// \brief action space size
    ///
    static constexpr uint_t ACTION_SPACE_SIZE = action_space::size;
	
	
	///
    /// \brief sample
    /// \return
    ///
    static action_type sample_action(){return action_space::sample(true);}

    ///
    /// \brief sample
    /// \param seed
    /// \return
    ///
    static action_type sample_action(uint_t seed){return action_space::sample(seed, true);}
	
	
	static std::vector<action_type> sample_action(uint_t seed, uint_t size){return action_space::sample(seed, size, true);}
};

template<uint_t StateSpaceSize, 
		 uint_t action_end, 
		 uint_t action_start=0,
		 typename StateSpaceItemType = real_t>
struct ContinuousVectorStateDiscreteActionEnv
{
	
	typedef ContinuousVectorSpace<StateSpaceSize, StateSpaceItemType> state_space;
	
	///
	/// \brief the State type
	///
	typedef typename state_space::space_item_type state_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t STATE_SPACE_SIZE = state_space::size;
	
	///
    /// \brief item_t
    ///
    typedef ScalarDiscreteSpace<action_start, action_end> action_space;
	
	///
	/// \brief the Action type
	///
	typedef typename action_space::space_item_type action_type;
	
	
	///
    /// \brief action space size
    ///
    static constexpr uint_t ACTION_SPACE_SIZE = action_space::size;
	
	
	///
    /// \brief sample
    /// \return
    ///
    static action_type sample_action(){return action_space::sample();}
};


template<uint_t StateSpaceSize,
		 uint_t action_end, 
		 typename real_range,
		 uint_t action_start = 0,
		 typename StateSpaceItemType = real_t>
struct ContinuousVectorStateContinuousScalarBoundedActionEnv
{
	///
	/// \brief The type of the state space
	///
	typedef ContinuousVectorSpace<StateSpaceSize, StateSpaceItemType> state_space;
	
	///
	/// \brief the State type
	///
	typedef typename state_space::space_item_type state_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t STATE_SPACE_SIZE = state_space::size;
	
	///
	/// \brief the action limits
	///
	static constexpr real_range action_limits = real_range();
																												
	///
    /// \brief item_t
    ///
    typedef ScalarDiscreteSpace<action_start, action_end> action_space;
	
	///
	/// \brief the Action type is real valued
	///
	typedef typename real_range::value_type action_type;

	///
    /// \brief action space size
    ///
    static constexpr uint_t ACTION_SPACE_SIZE = action_space::size;
	
};

/*
template<uint_t StateSpaceSize, 
		 uint_t ActionSpaceSize,
		 typename StateSpaceItemType=std::vector<real_t>>
struct ContinousStateDiscreteActionEnv{
	
	///
    /// \brief the state space type
    ///
    typedef ContinuousSpace<StateSpaceSize, StateSpaceItemType> state_space;
	
	///
	/// \brief the State type
	///
	typedef typename state_space::space_item_type state_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t STATE_SPACE_SIZE = StateSpaceSize;
	
	///
    /// \brief the action space type
    ///
    typedef DiscreteSpace<ActionSpaceSize> action_space;
	
	///
	/// \brief the Action type
	///
	typedef typename action_space::space_item_type action_type;
	
	
	///
    /// \brief action space size
    ///
    static constexpr uint_t ACTION_SPACE_SIZE = ActionSpaceSize;
	
	
	///
    /// \brief sample
    /// \return
    ///
    static action_type sample_action(){return action_space::sample();}

    ///
    /// \brief sample
    /// \param seed
    /// \return
    ///
    static action_type sample_action(uint_t seed){return action_space::sample();}
	
};

template<uint_t StateSpaceSize, 
		 uint_t ActionSpaceSize,
		 typename ActionSpaceItemType=std::vector<real_t>>
struct DisceteStateContinuousActionEnv{
	
	///
    /// \brief the action space type
    ///
    typedef DiscreteSpace<StateSpaceSize> state_space;
	
	///
	/// \brief the Action type
	///
	typedef typename state_space::space_item_type state_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t STATE_SPACE_SIZE = StateSpaceSize;
	
	///
    /// \brief the state space type
    ///
    typedef ContinuousSpace<ActionSpaceSize, ActionSpaceItemType> action_space;
	
	///
	/// \brief the State type
	///
	typedef typename action_space::space_item_type action_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t ACTION_SPACE_SIZE = ActionSpaceSize;
	
};


template<uint_t StateSpaceSize, 
		 uint_t ActionSpaceSize,
		 typename StateSpaceItemType = std::vector<real_t>,
		 typename ActionSpaceItemType = std::vector<real_t> >
struct ContinousEnv{
	
	
	///
    /// \brief the state space type
    ///
    typedef ContinuousSpace<StateSpaceSize, StateSpaceItemType> state_space;
	
	///
	/// \brief the State type
	///
	typedef typename state_space::space_item_type state_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t STATE_SPACE_SIZE = StateSpaceSize;
	
	///
    /// \brief the state space type
    ///
    typedef ContinuousSpace<ActionSpaceSize, ActionSpaceItemType> action_space;
	
	///
	/// \brief the State type
	///
	typedef typename action_space::space_item_type action_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t ACTION_SPACE_SIZE = ActionSpaceSize;
	
};
*/
template<uint_t StateSpaceSize, 
		 uint_t AS,
		 uint_t AE,
		 typename StateSpaceItemType = uint_t>
struct DiscreteVectorStateDiscreteActionEnv
{
	///
    /// \brief the state space type
    ///
    typedef DiscreteVectorSpace<StateSpaceSize, StateSpaceItemType> state_space;
	
	///
	/// \brief the State type
	///
	typedef typename state_space::space_item_type state_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t STATE_SPACE_SIZE = StateSpaceSize;
	
	///
    /// \brief the action space type
    ///
    typedef ScalarDiscreteSpace<AS, AE> action_space;
	
	///
	/// \brief the Action type
	///
	typedef typename action_space::space_item_type action_type;
	
	///
    /// \brief state space size
    ///
    static constexpr uint_t ACTION_SPACE_SIZE = action_space::size;
};

}
}