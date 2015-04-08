#include "mipluslambdastrategy.h"
#include "timer.h"
#include "individual.h"
#include <climits>

MiPlusLambdaStrategy::MiPlusLambdaStrategy(int mi, int lambda, int iterations) : Method()
{
	this->mi=mi;
	this->lambda=lambda;
	this->iterations=iterations;
};

Point MiPlusLambdaStrategy::operator () (const std::vector<Point*>& initialPoints) const{
    std::cout<<"MiPlusLambdaStrategy operator().\n";
	#pragma omp parallel for shared(results) num_threads(threads)
    Point bestPoint=*initialPoints[0];
    std::cout<<"bestPoint:\n\t"<<bestPoint;;		
	int iter=0;
	//Inicjacja
	std::vector<Individual*> basePopulation;
	for (int i =0; i <initialPoints.size(); ++i)
		basePopulation.push_back(new Individual(initialPoints[i]));
	while (iter<iterations) {
		std::cout<<"i:"<<iter<<"\n";
//        std::cout<<"basePopulation:\n";
//        for (int i =0; i <basePopulation.size(); ++i)
//        	std::cout<<"\t"<<*basePopulation[i];
	    std::vector<Individual*> tmpPopulation;
        for (int i =0; i <basePopulation.size(); ++i)
        	tmpPopulation.push_back(basePopulation[i]);
		//Reprodukcja
		for (int i =0; i <lambda; ++i){
			tmpPopulation.push_back(new Individual(basePopulation[rand()%basePopulation.size()]));
		}
		//Krzyżowanie
		for (int i =0; i <lambda/2; ++i){
			tmpPopulation[basePopulation.size()+2*i]->crossover(tmpPopulation[basePopulation.size()+2*i+1]);
		}
		//Mutacja
		for (int i =0; i <lambda; ++i){
			tmpPopulation[basePopulation.size()+i]->mutate();
		}
		//Ocena
		for (int i =0; i <lambda; ++i){
			tmpPopulation[basePopulation.size()+i]->evaluate();
		}
//		std::cout<<"tmpPopulation:\n";
//        for (int i =0; i <tmpPopulation.size(); ++i)
//        	std::cout<<"\t"<<*tmpPopulation[i];

		//Wybor kolejnej populacji
		/* //turniej
		basePopulation.clear();
		for (int i =0; i <mi; ++i){
		    int ind1 = rand()%(mi+lambda); 
		    int ind2 = rand()%(mi+lambda);
            if (tmpPopulation[ind1]<tmpPopulation[ind2])
                basePopulation.push_back(tmpPopulation[ind1]);
            else
                basePopulation.push_back(tmpPopulation[ind2]);
		}*/
		/* //turniej zmodyfikowany
		for (int i =0; i <mi; ++i){
		    int ind1 = rand()%(mi+lambda); 
		    int ind2 = rand()%(mi+lambda);
            if (tmpPopulation[ind1]<tmpPopulation[ind2])
                basePopulation.push_back(tmpPopulation[ind1]);
            else
                basePopulation.push_back(tmpPopulation[ind2]);
		}*/
        /* //ruletka
		    float sum=0;
		   	for (int i =0; i <tmpPopulation.size(); ++i)
		   	    if (tmpPopulation[i]->getEval()<10000)
                    sum+=1-tmpPopulation[i]->getEval()/10000;
    		std::cout<<"roulete sum:"<<sum<<":\n";

    		for (int i =0; i <mi; ++i){
		        float r = rand()%INT_MAX * sum;
        		std::cout<<"roulete r:"<<sum<<":\n";
		        float prob=0; 
    		   	for (int i =0; i <tmpPopulation.size(); ++i){
                    if (tmpPopulation[i]->getEval()<10000)
                        prob+=1-tmpPopulation[i]->getEval()/10000;
            		std::cout<<"roulete prob:"<<sum<<":\n";
                    if (prob>r) {
                        basePopulation.push_back(tmpPopulation[i]);
                        break;
                    } 
                }
            } */
		//najlepsze
        basePopulation.clear();
        for (int it = 0; it<tmpPopulation.size(); ++it){
//		        	std::cout<<"\t\t"<<*tmpPopulation[it];
    		int ib;
    		for (ib = 0; ib<basePopulation.size(); ++ib){
//		        	std::cout<<"\t\t\t"<<tmpPopulation[it]->getEval()<<"\t<\t"<<basePopulation[ib]->getEval()<<"\t"<<ib<<">"<<mi<<"\n";
		        if (*tmpPopulation[it]<*basePopulation[ib] || ib>mi){
                    basePopulation.insert(basePopulation.begin()+ib,new Individual(*tmpPopulation[it]));
//                    std::cout<<"in\n";
                    break;
                }
		    }
		        if (basePopulation.size()<=mi && ib==basePopulation.size()){
                    basePopulation.push_back(new Individual(*tmpPopulation[it]));
//                    std::cout<<"pb\n";
                    }
//                std::cout<<"\t\t\tnewPopulation:\n";
//                for (int i =0; i <basePopulation.size(); ++i){
//               	if (i==mi) std::cout<<"\t\t\t\t--------------------------------------------\n";
//               	std::cout<<"\t\t\t\t"<<*basePopulation[i];
//               	}
		}
//        basePopulation.insert(basePopulation.end()-1,tmpPopulation.begin(),tmpPopulation.end());
              
//        basePopulation.erase(basePopulation.begin());
        basePopulation.resize(mi);
        std::cout<<"worstPoint:\n\t"<<*basePopulation[mi-1];;		
	
//        std::cout<<"newPopulation:\n";
//       for (int i =0; i <basePopulation.size(); ++i)
//        	std::cout<<"\t"<<*basePopulation[i];
	      
        //Wybranie najlepszego dotąd rozwiązania
        for (int i=0; i<basePopulation.size(); ++i)
            if (*basePopulation[i]<bestPoint)
                bestPoint=*basePopulation[i];
        std::cout<<"bestPoint:\n\t"<<bestPoint;;		
		++iter;
	}
    return bestPoint;
};
