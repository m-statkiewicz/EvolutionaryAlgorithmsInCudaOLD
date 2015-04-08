/*
 * strategy.h
 */

#ifndef STRATEGY
#define STRATEGY

#include<cstdlib>
#include<vector>

#include"method.h"

class Strategy : public Method
{
private:
	int mi;
	int lambda;
	int iterations;

public:
	Strategy (int mi, int lambda, int iterations);
	Point operator () (const std::vector<Point*>& initialPoints) const;
};

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
