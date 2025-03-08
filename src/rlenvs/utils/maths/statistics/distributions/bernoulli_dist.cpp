#include "rlenvs/utils/maths/statistics/distributions/bernoulli_dist.h"


namespace rlenvscpp {
namespace utils{
namespace maths {
namespace stats {


BernoulliDist::BernoulliDist(result_type p)
:
p_(p),
dist_(p)
{}

BernoulliDist::result_type 
BernoulliDist::sample() const{
	
	std::random_device rd{};
    std::mt19937 gen{rd()};
	return dist_(gen);
}


BernoulliDist::result_type 
BernoulliDist::sample(uint_t seed) const{
	
	std::mt19937 gen{seed};
	return dist_(gen);
}


std::vector<BernoulliDist::result_type> 
BernoulliDist::sample_many(uint_t size) const{
	
	std::vector<BernoulliDist::result_type> samples(size);
	std::random_device rd{};
    std::mt19937 gen{rd()};
	
	for(uint_t i=0; i<size; ++i){
		samples[i] = dist_(gen);
	}
	
	return samples;
	
}


std::vector<BernoulliDist::result_type> 
BernoulliDist::sample_many(uint_t size, uint_t seed) const{
	
	std::vector<BernoulliDist::result_type> samples(size);
    std::mt19937 gen(seed);
	
	for(uint_t i=0; i<size; ++i){
		samples[i] = dist_(gen);
	}
	
	return samples;
}
	
}
}
}
}