/*
 * particle.cpp
 */

#include "particle.h"
#include <math.h>
#include <climits>

#define RADIUS 40
#define PRECISION 1000

Particle::Particle(int size) : Point(size){
};

Particle::Particle(const Particle * p) : Point(i){
};

Particle::Particle(const Particle & p) : Point(i){
};

Particle::~Particle(){
}

