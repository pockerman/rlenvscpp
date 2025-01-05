# ```rlenvscpp``` environment specification

This document discusses the specification of 
the environments exposed by ```rlenvscpp``` v1.6.0.

Overall, the environments  in ```rlenvscpp``` expose a blend of semantics from  
<a href="https://github.com/deepmind/dm_env/blob/master/docs/index.md">Environment API and Semantics</a>
and <a href="https://github.com/Farama-Foundation/Gymnasium/tree/main">Gymnasium</a>.


## The ```EnvBase``` class

The ```EnvBase``` class is a the base class for deriving RL environments.
The interface exposed by the class is shown in the listing below:

```
# Listing 1.0: The EnvBase class API

template<typename TimeStepType, typename SpaceType>
class EnvBase: public SpaceType, public synchronized_env_mixin
{
public:
	
	/// \brief The time step type we return every time a step in the
	/// environment is performed
    typedef TimeStepType time_step_type;
	
	/// \brief The type describing the state space for the environment
	typedef typename SpaceType::state_space state_space_type;
	
	/// \brief The type of the state
	typedef typename SpaceType::state_type state_type;
	
	/// \brief The type of the action space for the environment
	typedef typename SpaceType::action_space action_space_type;

	/// \brief The type of the action to be undertaken in the environment
    typedef typename SpaceType::action_type action_type;

	/// \brief dctor
    virtual ~EnvBase()=default;

	/// \brief make. Builds the environment. 
    virtual void make(const std::string& version,
                      const std::unordered_map<std::string, std::any>& options) = 0;

	/// \brief close the environment
    virtual void close()=0;
	
	/// \brief Reset the environment
    virtual time_step_type reset(uint_t seed,
                                 const std::unordered_map<std::string, std::any>& options)=0;
								 
	
	/// \brief step in the environment by performing the given action
    /// \param action The action to execute in the environment 
	/// \return The time step 
    virtual time_step_type step(const action_type& action)=0;
	
	/// \brief Reset the environment always using the same seed
    time_step_type reset(){
        return reset(DEFAULT_ENV_SEED, std::unordered_map<std::string, std::any>());}

	/// \brief is_created Returns true is make has been called successfully
    bool is_created()const noexcept{return is_created_;}

	/// \brief version
    std::string version()const noexcept{return version_;}

	/// \brief name of the environment
    std::string env_name()const noexcept{return name_;}

	/// \brief The number of agents acting in the environment
    uint_t cidx()const noexcept{return cidx_;}

protected:

	/// \brief Constructor
    explicit EnvBase(const uint_t cidx=0, 
	                 const std::string& name=rlenvscpp::consts::INVALID_STR);
					 
	/// \brief Copy constructor
	EnvBase(const EnvBase&);

	/// \brief Helper function to set the version. To be called only when the make is called
    void set_version_(const std::string& version )noexcept{version_ = version;}

    void invalidate_is_created_flag_()noexcept{is_created_ = false;}

	/// \brief mark the environment as created
    void make_created_()noexcept{is_created_= true;}
	
	time_step_type& get_current_time_step_()noexcept{return current_state_;}
    const time_step_type& get_current_time_step_()const noexcept{return current_state_;}
	
...

};

```


The class requires two template parameters; the ```TimeStepType``` and the ```SpaceType```.
In most cases, the  ```TimeStepType``` will of type ```TimeStep``` or ```VectorTimeStep```. The semantics
of these two classes follow the semantics of the ```TimeStep``` 
in <a href="https://github.com/deepmind/dm_env/blob/master/docs/index.md">Environment API and Semantics</a>.
The ```SpaceType``` encapsulates both the state and action spaces in RL parlance. There are various variants
of these spaces (see section Space types). 

### Core functions

The core functions exposed by the ```EnvBase``` class are:

- ```void make(const std::string&, const std::unordered_map<std::string, std::any>&)```
- ```time_step_type reset(uint_t, const std::unordered_map<std::string, std::any>&)```
- ```time_step_type step(const action_type&)```
- ```void close()```

These are the functions that most likely RL solvers will use.
These function follow to a large extent exposed by the environments in
<a href="https://github.com/Farama-Foundation/Gymnasium/tree/main">Gymnasium</a>.
The implementation of these functions is environment dependent i.e. they are virtual functions
in C++ parlance.

----
**Remark** 

The ```EnvBase``` class does not expose a ```render``` function that allows
visualisation of the agent acting on the environment.

----

## The ```TimeStep``` and ```VectorTimeStep``` classes 

The ```TimeStep``` class wraps the environment response when calling ```reset``` or ```step```.
The class exposes the following API:

```
# Listing 2.0: The TimeStep class API

template<typename StateTp>
class TimeStep
{
public:
    /// \brief state_ Type of the state
    typedef StateTp state_type;

    /// \brief TimeStep
    TimeStep();

    /// \brief TimeStep. Constructor
    TimeStep(TimeStepTp type, real_t reward, const state_type&  obs);

    /// \brief TimeStep. Constructor
    TimeStep(TimeStepTp type, real_t reward, const state_type&  obs, real_t discount_factor);

    /// \brief TimeStep. Constructor
    TimeStep(TimeStepTp type, real_t reward, const state_type& obs,
             real_t discount_factor, std::unordered_map<std::string, std::any>&& extra);

    /// \brief TimeStep
    TimeStep(const TimeStep& other);

	/// \brief Assignment operator
    TimeStep& operator=(const TimeStep& other);

    /// \brief TimeStep
    TimeStep(TimeStep&& other)noexcept;

    /// \brief operator =
    TimeStep& operator=(TimeStep&& other)noexcept;
    
    /// \brief first
    bool first()const noexcept{return type_ == TimeStepTp::FIRST;}

    /// \brief mid
    bool mid()const noexcept{return type_ == TimeStepTp::MID;}

    /// \brief last
    bool last()const noexcept{return type_ == TimeStepTp::LAST;}

    /// \brief type
    TimeStepTp type()const noexcept{return type_;}

    /// \brief observation
    state_type observation()const{return obs_;}

    /// \brief reward
    real_t reward()const noexcept{return reward_;}

    /// \brief discount. Returns the discount factor
    real_t discount()const noexcept{return discount_;}

    /// \brief done
    bool done()const noexcept{return type_ == TimeStepTp::LAST;}

    /// \brief clear
    void clear()noexcept;

    /// \brief get_extra
    template<typename T>
    const T& get_extra(std::string name)const;

    /// \brief info
    const std::unordered_map<std::string, std::any>& info()const noexcept{return extra_;}

    /// \brief info
    std::unordered_map<std::string, std::any>& info()noexcept{return extra_;}

...

};

```

The ```VectorTimeStep``` is the time step instance the is returned by the reset and step
functions of vector environments. The API is shown in the listing below

```
# Listing 3.0: The VectorTimeStep class API

template<typename StateType>
class VectorTimeStep
{

public:
	
    /// \brief state_ Type of the state
    typedef StateType state_type;

	/// \brief Default construcotr
    VectorTimeStep()=default;
	
    /// \brief VectorTimeStep. Constructor
    VectorTimeStep(const std::vector<TimeStepTp>& types, 
	               const std::vector<real_t>& rewards, 
				   const std::vector<state_type>&  obs);

    /// \brief VectorTimeStep. Constructor
    VectorTimeStep(const std::vector<TimeStepTp>& types, 
	               const std::vector<real_t>& rewards, 
				   const std::vector<state_type>&  obs, 
				   const std::vector<real_t>& discount_factors);
				   
	VectorTimeStep(const std::vector<TimeStepTp>& types, 
	               const std::vector<real_t>& rewards, 
				   const std::vector<state_type>&  obs, 
				   const std::vector<real_t>& discount_factors,
				   std::unordered_map<std::string, std::any>&& extra);
				   
    /// \brief TimeStep
    VectorTimeStep(const VectorTimeStep& other);

	/// \brief Assignment operator
    VectorTimeStep& operator=(const VectorTimeStep& other);

    /// \brief TimeStep
    VectorTimeStep(VectorTimeStep&& other)noexcept;

    /// \brief operator =
    VectorTimeStep& operator=(VectorTimeStep&& other)noexcept;

    /// \brief type
    const std::vector<TimeStepTp>& types()const noexcept{return types_;}

    /// \brief observation
    const std::vector<state_type>& observations()const{return obs_;}

    /// \brief reward
    const std::vector<real_t>& rewards()const noexcept{return rewards_;}
	
	/// \brief Returns the sum of the rewards received
	real_t reward()const noexcept;
	
	/// \brief Returns true if any time step is LAST
	bool done()const noexcept; 

    /// \brief discount. Returns the discount factor
    const std::vector<real_t>& discounts()const noexcept{return discounts_;}
	
    /// \brief last
    bool last()const noexcept;

...

};
```

## Space types