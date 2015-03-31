#include "strategy.h"
#include <algorithm>
#include <vector>
#include "timer.h"

bool compare(const State& a, const State& b) 
{return a.evaluate()<b.evaluate();};

State MiPlusLambdaStrategy::operator () (const int mi, const int lambda, const int iterations, const int p,const int threads, const std::vector<State*>& initialStates) const{
	std::vector<State*> results;	
	#pragma omp parallel for shared(results) num_threads(threads)
	for (int pi =0; pi <p; ++pi)
	{
		int iter=0;
		//Inicjacja
		std::vector<State*> population (initialStates);
		while (iter<iterations) {
			//Reprodukcja
			for (int i =0; i <lambda; ++i){
				population.push_back(new State(population[rand()%mi]));
			}
			//Krzyżowanie
			for (int i =0; i <lambda/2; ++i){
				population[mi+2*i]->crossover(population[mi+2*i+1]);
			}
			//Mutacja
			for (int i =0; i <lambda; ++i){
				population[mi+i]->mutate();
			}
			//Ocena i wybor kolejnej populacji
			sort(population.begin(),population.end(),compare);
			population.resize(mi);
			++iter;
		}
		results.push_back(new State(population[0]));
	}
	sort(results.begin(),results.end(),compare);
	return results[0];
//	return initialStates[0];
}

