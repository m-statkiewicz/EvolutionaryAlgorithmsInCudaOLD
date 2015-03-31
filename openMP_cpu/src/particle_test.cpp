/*
 * particle_test.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Individual
#include <boost/test/unit_test.hpp>

#include "particle.h"

#define POINT_SIZE 5

BOOST_AUTO_TEST_SUITE( ParticleSuite )
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

BOOST_AUTO_TEST_CASE( ParticleExceptions )
{
//    Point* p = new Point(POINT_SIZE);
//	BOOST_CHECK_THROW(p->getCoord(POINT_SIZE+1));
//	BOOST_CHECK_THROW(p->setCoord(POINT_SIZE+1,10));
//    delete p;
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( ParticleRosenbrockSuite )
BOOST_AUTO_TEST_CASE( optimalPoint )
{
    Particle* p = new Particle(POINT_SIZE);
    for (int i=0; i<POINT_SIZE; ++i)
		p->setCoord(i,1.0);
    BOOST_CHECK_EQUAL( p->evaluate(), 0 );
    delete p;
}
BOOST_AUTO_TEST_CASE( randomIndividual )
{
    Particle* p = new Particle(POINT_SIZE);
    ind->generateRandom();
    BOOST_CHECK_GT( p->evaluate() , 0 );
    delete p;
}

BOOST_AUTO_TEST_CASE( baseIndividual )
{
    Particle* p = new Particle(POINT_SIZE);
    BOOST_CHECK_GT( p->evaluate() , 0 ); 
    delete p;
}
BOOST_AUTO_TEST_SUITE_END()
