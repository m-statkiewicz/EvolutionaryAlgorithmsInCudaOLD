/*
 * state.h
 */

#ifndef STATE
#define STATE

#include<cstdlib>
#include<iostream>

class State {
private:
	int n;	
	float* value;
	float* sigma;
public:
	State(int size);
	State(const State* st);
	State(const State& st);
	~State();
	int getSize();
	float evaluate() const;
	void mutate();
	void crossover(State* st);
	void generateRandomState();

	friend std::ostream& operator<< (std::ostream &os, State & s);
};


#endif
