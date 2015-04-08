/*
 * strategy.h
 */

#ifndef MILAMBDASTRATEGY
#define MILAMBDASTRATEGY

#include<cstdlib>
#include<vector>

#include"method.h"

class MiLambdaStrategy : public Method
{
private:
	int mi;
	int lambda;
	int iterations;

public:
	MiLambdaStrategy (const int mi, const int lambda, const int iterations);
	Point operator () (const std::vector<Point*>& initialPoints) const;
};


#endif
