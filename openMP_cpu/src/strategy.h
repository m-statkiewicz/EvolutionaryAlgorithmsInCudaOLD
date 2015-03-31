/*
 * strategy.h
 */

#ifndef STRATEGY
#define STRATEGY

#include<cstdlib>
#include<vector>

#include"state.h"

/*
class OnePlusLambdaStrategy
{
public:
	State operator () (const int lambda, const State & initialState,const int iterations,const float sigma_, const int k) const;
};
*/
class MiPlusLambdaStrategy
{
public:
	State operator () (const int mi, const int lambda, const int iterations, const int p,const int threads, const std::vector<State*>& initialStates) const;
};

#endif
