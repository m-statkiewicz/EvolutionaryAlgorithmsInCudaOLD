/*
 * test_point.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Individual
#include <boost/test/unit_test.hpp>

#include "individual.h"

#define POINT_SIZE 5

BOOST_AUTO_TEST_SUITE( IndividualSuite )
BOOST_AUTO_TEST_CASE( PointIssues )
{
    Individual* ind = new Individual(POINT_SIZE);
    BOOST_CHECK_EQUAL( ind->getSize(), POINT_SIZE );	
    for (int i=0; i<POINT_SIZE; ++i)
    	BOOST_CHECK_EQUAL( ind->getCoord(i), 0 );
    delete ind;
}
BOOST_AUTO_TEST_CASE( createIndividual )
{
    Individual* ind = new Individual(POINT_SIZE);
    BOOST_CHECK_EQUAL( ind->getSize(), POINT_SIZE );	
    for (int i=0; i<POINT_SIZE; ++i)
    	BOOST_CHECK_EQUAL( ind->getCoord(i), 0 );
    for (int i=0; i<POINT_SIZE; ++i)
    	BOOST_CHECK_EQUAL( ind->getSigma(i), 0 );
    delete ind;
}
BOOST_AUTO_TEST_CASE( constructIndividual )
{
    Individual* ind = new Individual(POINT_SIZE);
    ind->generateRandom();
    Individual* i1 = new Individual(ind);
    BOOST_CHECK_EQUAL( i1->getSize() , ind->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i) {
    	BOOST_CHECK_EQUAL( i1->getCoord(i) , ind->getCoord(i) );
    	BOOST_CHECK_EQUAL( i1->getSigma(i) , ind->getSigma(i) );
    }
    Individual* i2 = new Individual(*ind);
    BOOST_CHECK_EQUAL( i2->getSize() , ind->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i) {
    	BOOST_CHECK_EQUAL( i2->getCoord(i) , ind->getCoord(i) );
    	BOOST_CHECK_EQUAL( i2->getSigma(i) , ind->getSigma(i) );
    }
    BOOST_CHECK_EQUAL( i1->getSize() , i2->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i) {
    	BOOST_CHECK_EQUAL( i1->getCoord(i) , i2->getCoord(i) );
    	BOOST_CHECK_EQUAL( i1->getSigma(i) , i2->getSigma(i) );
    }
    delete ind;
    delete i1;
    delete i2;
}
BOOST_AUTO_TEST_CASE( constructPoint )
{
    Individual* ind = new Individual(POINT_SIZE);
    ind->generateRandom();
    Point* p1 = new Point(ind);
    BOOST_CHECK_EQUAL( p1->getSize() , ind->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i) {
    	BOOST_CHECK_EQUAL( p1->getCoord(i) , ind->getCoord(i) );
    }
    Point* p2 = new Point(*ind);
    BOOST_CHECK_EQUAL( p2->getSize() , ind->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i) {
    	BOOST_CHECK_EQUAL( p2->getCoord(i) , ind->getCoord(i) );
    }

    BOOST_CHECK_EQUAL( p1->getSize() , p2->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i) {
    	BOOST_CHECK_EQUAL( p1->getCoord(i) , p2->getCoord(i) );
    }

	delete ind;
    delete p1;
    delete p2;
}
BOOST_AUTO_TEST_CASE( constructIndFromPoint )
{
    Point* p = new Point(POINT_SIZE);
    p->generateRandom();
    Individual* ind1 = new Individual(p);
    Individual* ind2 = new Individual(*p);
    BOOST_CHECK_EQUAL( ind1->getSize() , ind2->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i) {
    	BOOST_CHECK_EQUAL( ind1->getCoord(i) , ind2->getCoord(i) );
    }

	delete ind1;
    delete ind2;
    delete p;
}
BOOST_AUTO_TEST_CASE( mutate )
{
    Individual* p = new Individual(POINT_SIZE);
    p->generateRandom();
    Individual* c = new Individual(p);
    c->mutate();
    for (int i=0; i<POINT_SIZE; ++i) {
    	BOOST_CHECK_NE( p->getCoord(i) , c->getCoord(i) );
    }
    delete p;
    delete c;
}
BOOST_AUTO_TEST_CASE( crossover )
{
    Individual* p1 = new Individual(POINT_SIZE);
    Individual* p2 = new Individual(POINT_SIZE);
    p1->generateRandom();
    p2->generateRandom();
    Individual* c1 = new Individual(p1);
    Individual* c2 = new Individual(p2);
    c1->crossover(c2);
    
    int coordMatched=0;
    for (int i=0; i<POINT_SIZE; ++i) {
    	BOOST_CHECK_SMALL( (double)c1->getCoord(i)+c2->getCoord(i) - 
    		p1->getCoord(i)-p2->getCoord(i),0.00001 );
    	BOOST_CHECK_SMALL( (double)c1->getSigma(i)+c2->getSigma(i) - 
    		p1->getSigma(i)-p2->getSigma(i),0.00001 );
    	if(c1->getCoord(i)==c2->getCoord(i) && p1->getCoord(i)!=p2->getCoord(i))
    		coordMatched++;
    }
   	BOOST_WARN_EQUAL( coordMatched , 0 );
    
    delete p1;
    delete p2;
    delete c1;
    delete c2;
}
BOOST_AUTO_TEST_CASE( IndividualExceptions )
{
//    Point* p = new Point(POINT_SIZE);
//	BOOST_CHECK_THROW(p->getCoord(POINT_SIZE+1));
//	BOOST_CHECK_THROW(p->setCoord(POINT_SIZE+1,10));
//    delete p;
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( IndividualRosenbrockSuite )
BOOST_AUTO_TEST_CASE( optimalPoint )
{
    Individual* ind = new Individual(POINT_SIZE);
    for (int i=0; i<POINT_SIZE; ++i)
		ind->setCoord(i,1.0);
	ind->evaluate();
    BOOST_CHECK_EQUAL( ind->getEval() , 0 );
    delete ind;
}
BOOST_AUTO_TEST_CASE( randomIndividual )
{
    Individual* ind = new Individual(POINT_SIZE);
    ind->generateRandom();
    ind->evaluate();
    BOOST_CHECK_GT( ind->getEval() , 0 );
    delete ind;
}

BOOST_AUTO_TEST_CASE( baseIndividual )
{
    Individual* ind = new Individual(POINT_SIZE);
    ind->evaluate();
    BOOST_CHECK_GT( ind->getEval() , 0 ); 
    delete ind;
}
BOOST_AUTO_TEST_SUITE_END()
