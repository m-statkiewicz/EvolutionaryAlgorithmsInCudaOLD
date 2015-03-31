#include <math.h>
#include <climits>
#include "point.h"

#define RADIUS 40
#define PRECISION 1000

Point::Point(){
	size=0;
	value = NULL;
};

Point::Point(int size){
	this->size=size;
	value = new float[size];
	for (int i = 0; i<size; ++i)
		value[i]=0;
};


Point::Point(const Point * p){
	size=p->getSize();
	value = new float[size];
	for (int i = 0; i<size; ++i)
		value[i]=p->value[i];	
};

Point::Point(const Point & p){
	size=p.getSize();
	value = new float[size];
	for (int i = 0; i<size; ++i)
		value[i]=p.value[i];	
};

Point::~Point(){
	delete value;
}

int Point::getSize() const{
	return size;
}

float Point::getCoord(int i) const{
    return value[i];
}
	
void Point::setCoord(int i, float val){
    this->value[i]=val;
}
	
float Point::evaluate() const{
	//Rosenbrock function
	float sum=0, prod=1;
	for (int i = 0; i<size-1; ++i)
	{
		sum+=(1-value[i])*(1-value[i])
		    +100*(value[i+1]-value[i]*value[i])*(value[i+1]-value[i]*value[i]);
	}
	return sum;
};

void Point::generateRandom(){
	for (int i = 0; i<size; ++i)
		value[i]=(float)(rand()%(2*RADIUS*PRECISION))/PRECISION-RADIUS;
};

std::ostream& operator<< (std::ostream &os, Point & p){
	os<<"size="<<p.size<<"\n";	
	os<<"values=[";
	for (int i=0; i<p.getSize(); ++i)
	{
	os<<p.getCoord(i);
	if (i<p.getSize()-1) 
		os<<",";
	}
	os<<"]\n";
	os<<"eval="<<p.evaluate()<<"\n";
	return os;
};


