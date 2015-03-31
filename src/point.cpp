#include <math.h>
#include <climits>
#include "state.h"

#define RADIUS 40
#define PRECISION 1000

State::State(int size){
	n=size;
	value = new float[n];
	sigma = new float[n];
	for (int i = 0; i<n; ++i)
	{
		value[i]=0;
		sigma[i]=0;
	}
};


State::State(const State * st){
	n=st->n;
	value = new float[n];
	sigma = new float[n];
	for (int i = 0; i<n; ++i)
	{
		value[i]=st->value[i];	
		sigma[i]=st->sigma[i];
	}
};


State::State(const State & st){
	n=st.n;
	value = new float[n];
	sigma = new float[n];
	for (int i = 0; i<n; ++i)
	{
		value[i]=st.value[i];	
		sigma[i]=st.sigma[i];
	}
};

State::~State(){
	delete value;
	delete sigma;
}

int State::getSize(){
	return n;
}

float State::evaluate() const{
	//Griewank function
	float sum=0, prod=1;
	for (int i = 0; i<n; ++i)
	{
		sum+=value[i]*value[i];
		prod*=cos(value[i]/(i+1));
	}
	return sum/40+1-prod;
};

void State::mutate(){
	float xi = (float)rand()/INT_MAX;
	float tau = 1/sqrt(2*n),tau_=1/sqrt(2*sqrt(n));
	for (int i=0; i<n; ++i){
		float xi_sigma=(float)rand()/INT_MAX;	
		sigma[i]=sigma[i]*exp(tau_*xi+tau*xi_sigma);
		float xi_val=(float)rand()/INT_MAX;
		value[i]=value[i]+sigma[i]*xi_val;	
	}
};

void State::crossover(State* st){
	float a = (float)rand()/INT_MAX;
	for (int i=0; i<n; ++i){
		float x1,x2;
		x1=a*value[i]+(1-a)*st->value[i];
		x2=a*st->value[i]+(1-a)*value[i];
		value[i]=x1;
		st->value[i]=x2;
		if ((float)rand()/INT_MAX<=a){
			float tmp_sigma=sigma[i];
			sigma[i]=st->sigma[i];
			st->sigma[i]=tmp_sigma;
		}
	}
}

void State::generateRandomState(){
	for (int i = 0; i<n; ++i)
	{
		value[i]=(float)(rand()%(2*RADIUS*PRECISION))/PRECISION-RADIUS;
		sigma[i]=(float)(rand()%(2*PRECISION))/PRECISION-1;
	};
};

std::ostream& operator<< (std::ostream &os, State & s){
	os<<"size="<<s.n<<"\n";	
	os<<"values=[";
	for (int i=0; i<s.n; ++i)
	{
	os<<s.value[i];
	if (i<s.n-1) 
		os<<",";
	}
	os<<"]\n";
	os<<"sigma=[";
	for (int i=0; i<s.n; ++i)
	{
	os<<s.sigma[i];
	if (i<s.n-1) 
		os<<",";
	}
	os<<"]\n";
	os<<"eval="<<s.evaluate()<<"\n";
	return os;
};


