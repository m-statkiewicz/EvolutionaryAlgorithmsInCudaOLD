/*
 * strategy.h
 */

#ifndef MIPLUSLAMBDASTRATEGY
#define MIPLUSLAMBDASTRATEGY

#include<cstdlib>
#include<vector>

#include"method.h"

class MiPlusLambdaStrategy : public Method
{
private:
	int mi;
	int lambda;
	int iterations;

public:
	MiPlusLambdaStrategy (int mi, int lambda, int iterations);
	Point operator () (const std::vector<Point*>& initialPoints) const;
};

#endif
