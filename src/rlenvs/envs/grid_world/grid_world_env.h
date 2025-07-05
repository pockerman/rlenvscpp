#ifndef GRID_WORLD_ENV_H
#define GRID_WORLD_ENV_H

/**
  * Implements the Gridworld environment from the
  * book Deep Reinforcement Learning in Action by Manning publications.
  * You can find the original environment here:
  * https://github.com/DeepReinforcementLearning/DeepReinforcementLearningInAction
  * */

#include "rlenvs/rlenvscpp_config.h"
#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/rlenvs_consts.h"
#include "rlenvs/envs/time_step.h"
#include "rlenvs/envs/env_base.h"
#include "rlenvs/envs/space_type.h"

#ifdef RLENVSCPP_DEBUG
#include <cassert>
#endif

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <any>
#include <memory>

namespace rlenvscpp{
namespace envs::grid_world
{

	enum class GridWorldInitType: int {STATIC=0, RANDOM=1, PLAYER=2, INVALID_TYPE};
	enum class GridWorldActionType: uint_t {UP=0, DOWN=1, LEFT=2, RIGHT=3, INVALID_TYPE};

	namespace detail{

		///
		/// \brief Models a position on the board
		typedef std::pair<int,  int> board_position;

		///
		/// \brief Array specifying the state of the board
		///
		typedef std::vector<std::vector<std::vector<real_t>>> board_state_type;

		///
		/// \brief The BoardComponentType enum
		///
		enum board_component_type{PLAYER=0, GOAL=1, PIT=2, WALL=3};

		///
		/// \brief The MoveType enum
		///
		enum board_move_type{VALID=0, INVALID=1, LOST_GAME=2};

		///
		/// \brief Test if two positions are equal
		///
		bool operator==(const board_position& p1, const board_position& p2);

		///
		/// \brief Test if two positions are equal
		///
		bool operator!=(const board_position& p1, const board_position& p2);

		///
		/// \brief Add two positions and return their result
		///
		board_position operator+(const board_position& p1, const board_position& p2);

		///
		/// \brief Returns the max component of a position
		///
		int_t max(const board_position& p);

		///
		/// \brief Returns the min component of a position
		///
		int_t min(const board_position& p);

		///
		/// \brief The BoardPiece struct
		///
		struct board_piece
		{
			///
			/// \brief Name of the piece
			///
			std::string name;

			///
			/// \brief pos 2-tuple e.g. (1,4)
			///
			board_position pos;

			///
			/// \brief BoardPiece
			/// \param name_
			/// \param pos_
			///
			board_piece(std::string name_,  board_position pos_)
				:
				name(std::move(name_)),
				pos(std::move(pos_))
			{}

			///
			/// \brief Default constructor
			///
			board_piece()=default;
		};

		using board_mask = board_piece;

		///
		/// Represents the board
		///
		struct board
		{
			uint_t board_size;
			uint_t seed = 42;
			std::map<board_component_type, board_piece> components;
			std::map<std::string, board_mask> masks;
			bool is_board_init = {false};

			///
			/// \brief initialize the board
			///
			board_state_type init_board(uint_t board_s,
			                            GridWorldInitType init_type);

			///
			/// \brief Execute the action on the board
			///
			board_state_type step(GridWorldActionType action);

			///
			/// \brief move_piece Move the pice to the given position
			/// \param piece
			/// \param pos
			///
			void move_piece(board_component_type piece, board_position pos);

			///
			/// \brief get_state. Returns the state of the board
			/// \return
			///
			board_state_type get_state()const;

			///
			/// \brief Get the reward the board currently returns depending
			/// on the position of the player
			///
			real_t get_reward()const;

			///
			/// \brief close
			///
			void close();

			///
        /// \brief build_static_mode
        ///
			void build_static_mode();

			///
        /// \brief build_random_mode
        ///
			void build_random_mode();

			///
        /// \brief build_player_mode
        ///
			void build_player_mode(uint_t seed);

			///
        /// \brief check if the given move is valid and
        /// change the position of the player if the move
        /// either causes the game to be lost (PIT) or is a valid
        /// move i.e. not stepping into the WALL or out of the board
        ///
			void check_and_move(int_t row, int_t col);

			///
        /// \brief validate_move_
        /// \param piece
        /// \param pos
        ///
			[[nodiscard]] board_move_type validate_move(board_component_type piece, board_position pos)const;
		};

		template<uint_t size_size>
		struct GridWorldEnv
		{

			typedef detail::board state_space;

			typedef detail::board_state_type state_type;

			///
		/// \brief state space size
		///
			static constexpr uint_t STATE_SPACE_SIZE = size_size * size_size;

			///
        /// \brief the action space type
        ///
			typedef ScalarDiscreteSpace<0, 4> action_space;

			///
		/// \brief the Action type
		///
			typedef action_space::space_item_type action_type;


			///
		/// \brief action space size
		///
			static constexpr uint_t ACTION_SPACE_SIZE = action_space::size;
		};
	}


	///
	/// The Gridworld class models a square board. There are three ways to initialize the board.
	/// - static
	/// - random
	/// - player
	/// See the GridworldInitType enumeration.
	/// Static initialization means that the objects on the board are initialized at the same predetermined locations.
	/// Player initialization means that the player is initialized at a random position on the board.
	/// Random initialization means that all the objects are placed randomly
	///
	template<uint_t side_size_>
	class Gridworld final: public EnvBase<TimeStep<detail::board_state_type>,
	                                      detail::GridWorldEnv<side_size_>>
	{
	public:

		static_assert (side_size_ >= 4,
		               "The side size should be greater than or equal to 4");

		///
    /// \brief name
    ///
		static  const std::string name;

		///
    /// \brief n_components
    ///
		static const uint_t n_components;

		///
    /// \brief side_size
    ///
		static const uint_t side_size;

		///
	/// \brief The base_type
	///
		typedef EnvBase<TimeStep<detail::board_state_type>,
		                detail::GridWorldEnv<side_size_>> base_type;

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
	/// \brief The type of the action to be undertaken in the environment
	///
		typedef typename base_type::state_type state_type;

		///
	/// \brief Expose the various reset methods we use from base class
	///
		using base_type::reset;

		///
    /// \brief Constructor
    ///
		Gridworld();

		///
    /// \brief Gridworld. Constructor
    ///
		explicit Gridworld(const uint_t cidx);

		///
    /// \brief Gridworld. Constructor
    ///
		Gridworld(const Gridworld& other);

		///
    /// \brief make. Builds the environment. Optionally we can choose if the
    /// environment will be slippery
    ///
		void make(const std::string& version,
		          const std::unordered_map<std::string, std::any>& options) override final;

		///
	/// \brief Reset the environment
	///
		time_step_type reset(uint_t /*seed*/,
		                     const std::unordered_map<std::string, std::any>& /*options*/) override final;

		///
	/// \brief Create a new copy of the environment with the given
	/// copy index
	///
		Gridworld make_copy(uint_t cidx)const;

		///
    /// \brief step
    /// \param action
    /// \return
    ///
		time_step_type step(const action_type& action) override final;

		///
    /// \brief close
    ///
		void close()override final;

		///
    /// \brief has_random_state
    /// \return
    ///
		[[nodiscard]] bool has_random_state()const noexcept{return randomize_state_;}

		///
    /// \brief n_states. Returns the number of states
    ///
		[[nodiscard]] uint_t n_states()const noexcept{ return side_size_ * side_size_; }

		///
    /// \brief n_actions. Returns the number of actions
    ///
		[[nodiscard]] uint_t n_actions()const noexcept{return action_space_type::size;}

		///
    /// \brief seed
    /// \return
    ///
		[[nodiscard]] uint_t seed()const noexcept{return seed_;}

		///
    /// \brief noise_factor
    /// \return
    ///
		[[nodiscard]] real_t noise_factor()const noexcept{return noise_factor_;}

		///
	/// \brief Returns true if the PLAYER position is the same
	///as the PIT position
	///
		[[nodiscard]] bool is_game_lost()const;

		///
    /// \brief init_type
    /// \return
    ///
		[[nodiscard]] GridWorldInitType init_type()const noexcept{return init_mode_;}

	private:

		///
    /// \brief init_mode_
    ///
		GridWorldInitType init_mode_;

		///
    /// \brief randomize_state_
    ///
		bool randomize_state_;

		///
    /// \brief seed_
    ///
		uint_t seed_;

		///
    /// \brief noise_factor_
    ///
		real_t noise_factor_;

		///
    /// \brief board_
    ///
		detail::board board_;
	};

	template<uint_t side_size>
	const std::string Gridworld<side_size>::name = "Gridworld";

	template<uint_t side_size_>
	const uint_t Gridworld<side_size_>::side_size = side_size_;

	template<uint_t side_size_>
	const uint_t Gridworld<side_size_>:: n_components = 4;

	template<uint_t side_size_>
	Gridworld<side_size_>::Gridworld()
		:
		EnvBase<TimeStep<detail::board_state_type>,
		        detail::GridWorldEnv<side_size_>>(0, "Gridworld"),
		init_mode_(GridWorldInitType::INVALID_TYPE),
		randomize_state_(false),
		seed_(0),
		noise_factor_(0.0),
		board_()
	{
	}

	template<uint_t side_size_>
	Gridworld<side_size_>::Gridworld(uint_t cidx)
		:
		EnvBase<TimeStep<detail::board_state_type>,
		        detail::GridWorldEnv<side_size_>>(cidx, "Gridworld"),
		init_mode_(GridWorldInitType::INVALID_TYPE),
		randomize_state_(false),
		seed_(0),
		noise_factor_(0.0),
		board_()
	{
	}


	template<uint_t side_size_>
	Gridworld<side_size_>::Gridworld(const Gridworld<side_size_>& other)
		:
		EnvBase<TimeStep<detail::board_state_type>,
		        detail::GridWorldEnv<side_size_>>(other),
		init_mode_(other.init_mode_),
		randomize_state_(other.randomize_state_),
		seed_(other.seed_),
		noise_factor_(other.noise_factor_),
		board_(other.board_)
	{}


	template<uint_t side_size_>
	void
	Gridworld<side_size_>::make(const std::string& version,
	                            const std::unordered_map<std::string, std::any>& options){

		if(this -> is_created()){
			return;
		}

		if(const auto mode = options.find("mode"); mode != options.end()){
			init_mode_ = std::any_cast<GridWorldInitType>(mode->second);
		}
		else{
			init_mode_ = GridWorldInitType::STATIC;
		}

		if(const auto seed = options.find("seed"); seed != options.end()){
			seed_ = std::any_cast<uint_t>(seed->second);
		}

		if(const auto noise_factor = options.find("noise_factor"); noise_factor != options.end()){
			noise_factor_ = std::any_cast<real_t>(noise_factor->second);
		}

		if(const auto randomize_state = options.find("randomize_state"); randomize_state != options.end()){
			randomize_state_ = std::any_cast<bool>(randomize_state->second);
		}

		// initialize the board
		board_.init_board(side_size_, init_mode_);

		// set the version and set the board
		// to created
		this->set_version_(version);
		this->make_created_();
	}

	template<uint_t side_size_>
	Gridworld<side_size_>
	Gridworld<side_size_>::make_copy(uint_t cidx)const{

		Gridworld<side_size_> copy(cidx);
		std::unordered_map<std::string, std::any> ops;
		ops["randomize_state"] = this -> has_random_state();
		ops["noise_factor"] = this -> noise_factor_;
		ops["seed"] = std::any(static_cast<uint_t>(this -> seed_));
		auto version = this -> version();
		copy.make(version, ops);
		return copy;
	}

	template<uint_t side_size_>
	typename Gridworld<side_size_>::time_step_type
	Gridworld<side_size_>::step(const action_type& action){

		auto obs = board_.step(static_cast<GridWorldActionType>(action));
		auto reward = board_.get_reward();

		// if the reward is not -1.0 then either
		// we reached the goal or we hit the PIT
		// in any case the game is over
		auto step_type = reward != -1.0 ? TimeStepTp::LAST : TimeStepTp::MID;

		this->get_current_time_step_() = time_step_type(step_type, reward, obs);
		return this->get_current_time_step_();
	}


	template<uint_t side_size_>
	typename Gridworld<side_size_>::time_step_type
	Gridworld<side_size_>::reset(uint_t /*seed*/,
	                             const std::unordered_map<std::string, std::any>& /*options*/){

		// reinitialize the board
		auto obs = board_.init_board(side_size_, init_mode_);
		auto reward = board_.get_reward();
		this->get_current_time_step_() = time_step_type(TimeStepTp::FIRST, reward, obs);
		return this->get_current_time_step_();
	}

	template<uint_t side_size_>
	bool
	Gridworld<side_size_>::is_game_lost()const{

		auto player = board_.components.find(detail::board_component_type::PLAYER)->second.pos;
		auto pit_pos = board_.components.find(detail::board_component_type::PIT)->second.pos;

		if (player == pit_pos){
			return true;
		}

		return false;
	}

	template<uint_t side_size_>
	void
	Gridworld<side_size_>::close(){
		board_.close();
	}

}
}// rlenvs_cpp

#endif // GRID_WORLD_ENV_H
