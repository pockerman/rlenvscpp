#include "rlenvs/rigid_bodies/body_rotation.h"

namespace rlenvscpp{
namespace rigid_bodies{
	

	std::ostream& 
	RBRotation::print(std::ostream& out)const noexcept{
		out<<x<<", "<<y<<", "<<z<<std::endl;
		return out;
	}
	
	
}
}