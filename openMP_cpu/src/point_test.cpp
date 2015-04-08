/*
 * point_test.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Point
#include <boost/test/unit_test.hpp>

#include "point.h"

#define POINT_SIZE 5

BOOST_AUTO_TEST_SUITE( PointSuite )
BOOST_AUTO_TEST_CASE( createPoint )
{
    Point* p = new Point(POINT_SIZE);
    BOOST_CHECK_EQUAL( p->getSize(), POINT_SIZE );	
    for (int i=0; i<POINT_SIZE; ++i)
    	BOOST_CHECK_EQUAL( p->getCoord(i), 0 );
    delete p;
}
BOOST_AUTO_TEST_CASE( constructPoint )
{
    Point* p = new Point(POINT_SIZE);
    p->generateRandom();
    Point* q = new Point(p);
    BOOST_CHECK_EQUAL( q->getSize() , p->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i)
    	BOOST_CHECK_EQUAL( p->getCoord(i) , q->getCoord(i) );
    Point* r = new Point(*p);
    BOOST_CHECK_EQUAL( r->getSize() , p->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i)
    	BOOST_CHECK_EQUAL( p->getCoord(i) , r->getCoord(i) );

    BOOST_CHECK_EQUAL( r->getSize() , q->getSize() );	
    for (int i=0; i<POINT_SIZE; ++i)
    	BOOST_CHECK_EQUAL( q->getCoord(i) , r->getCoord(i) );

    delete p;
    delete q;
    delete r;
}
BOOST_AUTO_TEST_CASE( PointExceptions )
{
//    Point* p = new Point(POINT_SIZE);
//	BOOST_CHECK_THROW(p->getCoord(POINT_SIZE+1));
//	BOOST_CHECK_THROW(p->setCoord(POINT_SIZE+1,10));
//	BOOST_CHECK_THROW(p->getEval());
//    delete p;
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( RosenbrockSuite )
BOOST_AUTO_TEST_CASE( optimalPoint )
{
    Point* p = new Point(POINT_SIZE);
    for (int i=0; i<POINT_SIZE; ++i)
		p->setCoord(i,1.0);
	p->evaluate();
   	BOOST_CHECK_SMALL( (double)p->getEval(), 0.000001 );
    delete p;
}
BOOST_AUTO_TEST_CASE( randomPoint )
{
    Point* p = new Point(POINT_SIZE);
    p->generateRandom();
    p->evaluate();
    BOOST_CHECK_GT( p->getEval() , 0 );
    delete p;
}

BOOST_AUTO_TEST_CASE( basePoint )
{
    Point* p = new Point(POINT_SIZE);
    p->evaluate();
    BOOST_CHECK_GT( p->getEval() , 0 ); 
    delete p;
}
BOOST_AUTO_TEST_SUITE_END()
