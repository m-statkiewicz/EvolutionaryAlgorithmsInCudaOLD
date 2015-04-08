#include<iostream>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include"point.h"
#include"method.h"
#include"timer.h"
#include "mipluslambdastrategy.h"
#include "milambdastrategy.h"


#define VERSION 0.1
#define VECTOR_SIZE 10
#define POINT_SIZE 2


int main (int argc, char **argv){

    srand(time(NULL));
    MiPlusLambdaStrategy m (5, 10, 100);
//    MiLambdaStrategy m (100, 400, 5000);
    std::vector<Point*> initPoints;
    Point* p;
    for (int i=0; i<VECTOR_SIZE; ++i) {
        p = new Point(POINT_SIZE);
        p->generateRandom();
        p->evaluate();
        std::cout<<"p:"<<*p;
        initPoints.push_back(p);
    }
    std::cout<<"\n\n";
	for (int i=0; i<VECTOR_SIZE; ++i)
        std::cout<<"initPoint["<<i<<"]:"<<*initPoints[i];
	
	Point* r = new Point(m(initPoints));
    std::cout<<"r:"<<*r<<'\n';

  //    for (int i=0; i<VECTOR_SIZE; ++i)    
  //    BOOST_CHECK_GT(r->getEval() ,initPoints[i]->getEval());

  //  for (int i=0; i<VECTOR_SIZE; ++i) {
  //      delete initPoints[i];
   // }
  //  delete r;


return 0;
}
	
