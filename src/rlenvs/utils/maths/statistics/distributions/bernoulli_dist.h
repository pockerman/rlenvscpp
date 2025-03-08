#ifndef BERNOULLI_DIST_H
#define BERNOULLI_DIST_H

#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/rlenvs_consts.h"

#include <vector>
#include <random>

namespace rlenvscpp {
namespace utils{
namespace maths {
namespace stats {
	
class BernoulliDist
{
public:
		
	///	
	/// \breif The return type every time we call pdf, sample
	///
	typedef real_t result_type;  
	
	///
	/// \brief Constructor
	///
	explicit BernoulliDist(result_type p=0.5);
		
	///
	/// \brief Sample from the distribution
	///
	result_type sample() const;
	
	///
	/// \brief Sample from the distribution
	///
	result_type sample(uint_t seed) const;
	
	///
	/// \brief sample from the distribution
	///
	std::vector<result_type> sample_many(uint_t size) const;
	
	///
	/// \brief sample from the distribution
	///
	std::vector<result_type> sample_many(uint_t size, uint_t seed) const;
	
	///
	/// \brief The mean value of the distribution
	///
	result_type mean()const{return p_;}
	
	///
	/// \brief The STD of the distribution
	///
	result_type std()const{return p_*(1.0 - p_);}
	
private:
	
	const real_t p_;
	mutable std::bernoulli_distribution dist_;
	
};
	
}
}
}
}

#endif