/*
 * particle.h
 */

#ifndef PARTICLE
#define PARTICLE

#include"point.h"

#include<cstdlib>
#include<iostream>

class Particle : public Point {
private:

public:
	Particle(int size);
	Particle(const Particle* i);
	Particle(const Particle& i);
	~Particle();
	
};


#endif
