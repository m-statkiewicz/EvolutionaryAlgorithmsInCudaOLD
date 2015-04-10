/*
 * pso.h
 */

#ifndef PSO
#define PSO

#include<cstdlib>
#include<vector>

#include"method.h"

class Pso : public Method
{
private:
	int size;
	float cs;			//wspolczynik socjalny
	float ck;			//wspolczynik kognitywny
	int iterations;

public:
	Pso (float social, float cognitive, int max_iterations);
	Point operator () (const std::vector<Point*>& initialPoints) const;
};

#endif
