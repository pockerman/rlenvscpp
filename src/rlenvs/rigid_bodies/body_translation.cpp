#include "rlenvs/rigid_bodies/body_translation.h"

namespace rlenvscpp{
namespace rigid_bodies{
	

	std::ostream& 
	RBTranslation::print(std::ostream& out)const noexcept{
		out<<x<<", "<<y<<", "<<z<<std::endl;
		return out;
	}
	
	
}
}