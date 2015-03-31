#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include"state.h"
#include"strategy.h"
#include"timer.h"

#define VERSION 0.1

int main (int argc, char **argv){

int n = 2;
int mi = 2;
int lambda = 3;
int iterations = 5;
int populations = 5;
int threads = 5;

MiPlusLambdaStrategy strategy;
Timer t;

for (int i=1; i<argc; ++i){
//	std::cout<<argv[i]<<' '<<argv[i+1]<<' ';
	if (std::string(argv[i])=="-n"){
		std::stringstream str(argv[++i]);
		str>>n;
	}
	if (std::string(argv[i])=="-m"){
		std::stringstream str(argv[++i]);
		str>>mi;
	}
	if (std::string(argv[i])=="-l"){
		std::stringstream str(argv[++i]);
		str>>lambda;
	}
	if (std::string(argv[i])=="-i"){
		std::stringstream str(argv[++i]);
		str>>iterations;
	}
	if (std::string(argv[i])=="-p"){
		std::stringstream str(argv[++i]);
		str>>populations;
	}
	if (std::string(argv[i])=="-t"){
		std::stringstream str(argv[++i]);
		str>>threads;
	}
}
std::vector<State*> initialStates;
srand(time(NULL));
State* optstate = NULL;
State* tmp;

for (int i=0;i<mi;++i)
{
	tmp = new State(n);
	tmp->generateRandomState();
	initialStates.push_back(tmp);
}
t.start();
optstate = new State(strategy(mi,lambda,iterations,populations,threads,initialStates));
t.stop();
//std::cout<<*optstate<<std::endl;
//std::cout<<std::endl<<"optimum eval. = "<<optstate->evaluate()<<std::endl;
//std::cout<<"delta time = "<<t.deltaToString()<<std::endl<<std::endl;
std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
std::cout<<optstate->evaluate()<<';'<<t.deltaToString()<<std::endl;
delete optstate;
return 0;
}

