#include "pso.h"
#include "timer.h"
#include "particle.h"
#include <climits>

Pso::Pso (float social, float cognitive, int max_iterations) : Method()
{
	cs=social;			//wspolczynik socjalny
	ck=cognitive;			//wspolczynik kognitywny
	iterations=max_iterations;
};

Point Pso::operator () (const std::vector<Point*>& initialPoints) const{
    std::cout<<"PSO operator().\n";
	int size=initialPoints.size();

	#pragma omp parallel for shared(results) num_threads(threads)
    Point bestPoint=*initialPoints[0];
	int iter=0;
	//Inicjacja
	std::vector<Particle*> swarm;
	for (int i =0; i <initialPoints.size(); ++i){
		swarm.push_back(new Particle(initialPoints[i]));
	    if (*swarm[i]<bestPoint)
            bestPoint=*swarm[i];
	}
    std::cout<<"bestPoint:\n\t"<<bestPoint;

	while (iter<iterations) {
		std::cout<<"i:"<<iter<<"\n";
		for (int i =0; i <swarm.size(); ++i){
		    std::cout<<"\t swarm["<<i<<"]:"<<*swarm[i];
			double rs,rk;
			rs = rand() / (double) RAND_MAX;
			rs = rand() / (double) RAND_MAX;
			Point p(bestPoint.getSize());
			for (int crd =0; crd<p.getSize(); crd++){
 				double tmp=0;
			//    std::cout<<"\t 0: "<<tmp;
 					//składowa socjalna
				tmp+=(bestPoint.getCoord(crd)-swarm[i]->getCoord(crd))*rs*cs;
			//    std::cout<<"\t s:"<<tmp;
					//skladowa kognitywna
				tmp+=(swarm[i]->getBest().getCoord(crd)-swarm[i]->getCoord(crd))*rk*ck;
			//    std::cout<<"\t sk:"<<tmp;
					//składowa inercji
				tmp+=(swarm[i]->getCoord(crd)-swarm[i]->getLast().getCoord(crd));
			//    std::cout<<"\t ski:"<<tmp;
				p.setCoord(crd,tmp);
			//    std::cout<<"\t vector:"<<p;
			}
			swarm[i]->add(p);
			swarm[i]->evaluate();
			swarm[i]->chooseBest();
			if (*swarm[i]<bestPoint)
				bestPoint=*swarm[i];
		}
		iter++;	
	}			
  	return bestPoint;
}

