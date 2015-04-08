#include "strategy.h"
#include "timer.h"
#include "individual.h"
#include <iostream>

MiPlusLambdaStrategy::MiPlusLambdaStrategy(int mi, int lambda, int iterations)
{
	this->mi=mi;
	this->lambda=lambda;
	this->iterations=iterations;
};

Point MiPlusLambdaStrategy::operator () (const std::vector<Point*>& initialPoints) const{
	Point bestPoint=*initialPoints[0];
    #pragma omp parallel for shared(results) num_threads(threads)
	int iter=0;
	//Inicjacja
	std::vector<Individual*> basePopulation;
	std::cout<<"i:"<<iter<<"\n";
	for (int i =0; i <initialPoints.size(); ++i)
		basePopulation.push_back(new Individual(initialPoints[i]));
	while (iter<iterations) {
        std::cout<<"basePopulation:\n";
        for (int i =0; i <basePopulation.size(); ++i)
        	std::cout<<"\t"<<*basePopulation[i]<<"\n";
	    std::vector<Individual*> tmpPopulation (basePopulation);
		//Reprodukcja
		for (int i =0; i <lambda; ++i){
			tmpPopulation.push_back(new Individual(basePopulation[rand()%basePopulation.size()]));
		}
		//Krzyżowanie
		for (int i =0; i <lambda/2; ++i){
			tmpPopulation[mi+2*i]->crossover(tmpPopulation[mi+2*i+1]);
		}
		//Mutacja
		for (int i =0; i <lambda; ++i){
			tmpPopulation[mi+i]->mutate();
		}
		//Ocena
		for (int i =0; i <lambda; ++i){
			tmpPopulation[mi+i]->evaluate();
		}
        std::cout<<"tmpPopulation:\n";		
        for (int i =0; i <tmpPopulation.size(); ++i)
        	std::cout<<"\t"<<*tmpPopulation[i]<<"\n";
		//Wybor kolejnej populacji
		basePopulation.clear();
		for (int i =0; i <mi; ++i){
		    int ind1 = rand()%(mi+lambda); 
		    int ind2 = rand()%(mi+lambda);
            if (tmpPopulation[ind1]<tmpPopulation[ind2])
                basePopulation.push_back(tmpPopulation[ind1]);
            else
                basePopulation.push_back(tmpPopulation[ind2]);
		}
		++iter;
        //Wybranie najlepszego dotąd rozwiązania
        for (int i=0; i<basePopulation.size(); ++i)
            if (*basePopulation[i]<bestPoint)
                bestPoint=basePopulation[i];
        std::cout<<"bestPoint:\n\t"<<bestPoint;;		
         
	}
    return bestPoint;
};

MiLambdaStrategy::MiLambdaStrategy(const int mi, const int lambda, const int iterations) {
	this->mi=mi;
	this->lambda=lambda;
	this->iterations=iterations;
};

Point MiLambdaStrategy::operator () (const std::vector<Point*>& initialPoints) const{
/*	#pragma omp parallel for shared(results) num_threads(threads)
	int iter=0;
	//Inicjacja
	std::vector<Indvidual*> basePopulation();
	for (int i =0; i <initialPoints.size(); ++i){
		basePopulation.push_back(new Individual(initialPoints[i]));
	}
	while (iter<iterations) {
	    std::vector<Indvidual*> tmpPopulation();
		//Reprodukcja
		for (int i =0; i <lambda; ++i){
			tmpPopulation.push_back(new Individual(basePopulation[rand()%basePopulation.size()]));
		}
		//Krzyżowanie
		for (int i =0; i <lambda/2; ++i){
			tmpPopulation[2*i]->crossover(tmpPopulation[2*i+1]);
		}
		//Mutacja
		for (int i =0; i <lambda; ++i){
			tmpPopulation[i]->mutate();
		}
		//Ocena
		for (int i =0; i <lambda; ++i){
			tmpPopulation[i]->evaluate();
		}
		//Wybor kolejnej populacji
		basePopulation.clear();
		for (int i =0; i <mi; ++i){
		    int ind1 = rand()%(lambda); 
		    int ind2 = rand()%(lambda);
            if (population[ind1]<population[ind2])
                basePopulation.push_back(population[ind1]);
            else
                basePopulation.push_back(population[ind2]);
		}
		++iter;
	}
    
    Point bestPoint=*basePopulation[0];
    for (int i=1; i<basePopulation.size(); ++i)
        if (*basePopulation[i]<v)
            v=basePopulation[i];
    return bestPoint;*/
    return new Point(0);
}

Strategy::Strategy(int mi, int lambda, int iterations)
{
	this->mi=mi;
	this->lambda=lambda;
	this->iterations=iterations;
};

Point Strategy::operator () (const std::vector<Point*>& initialPoints) const{
	#pragma omp parallel for shared(results) num_threads(threads)
	int iter=0;
	//Inicjacja
	std::vector<Individual*> basePopulation;
	for (int i =0; i <initialPoints.size(); ++i)
		basePopulation.push_back(new Individual(initialPoints[i]));
	while (iter<iterations) {
	    std::vector<Individual*> tmpPopulation (basePopulation);
		//Reprodukcja
		for (int i =0; i <lambda; ++i){
			tmpPopulation.push_back(new Individual(basePopulation[rand()%mi]));
		}
		//Krzyżowanie
		for (int i =0; i <lambda/2; ++i){
			tmpPopulation[mi+2*i]->crossover(tmpPopulation[mi+2*i+1]);
		}
		//Mutacja
		for (int i =0; i <lambda; ++i){
			tmpPopulation[mi+i]->mutate();
		}
		//Ocena
		for (int i =0; i <lambda; ++i){
			tmpPopulation[mi+i]->evaluate();
		}
		//Wybor kolejnej populacji
		basePopulation.clear();
		for (int i =0; i <mi; ++i){
		    int ind1 = rand()%(mi+lambda); 
		    int ind2 = rand()%(mi+lambda);
            if (tmpPopulation[ind1]<tmpPopulation[ind2])
                basePopulation.push_back(tmpPopulation[ind1]);
            else
                basePopulation.push_back(tmpPopulation[ind2]);
		}
		++iter;
	}
    Point bestPoint=*basePopulation[0];
    for (int i=1; i<basePopulation.size(); ++i)
        if (*basePopulation[i]<bestPoint)
            bestPoint=basePopulation[i];
    return bestPoint;
};

