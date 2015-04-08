/*
 * method_test.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Method
#include <boost/test/unit_test.hpp>

#include "method.h"

#define POINT_SIZE 5
#define VECTOR_SIZE 10

BOOST_AUTO_TEST_SUITE( MethodSuite )
BOOST_AUTO_TEST_CASE( createMethod )
{
    Method m;
    std::vector<Point*> initPoints;
    Point* p;
    for (int i=0; i<VECTOR_SIZE; ++i) {
        p = new Point(POINT_SIZE);
        p->generateRandom();
        p->evaluate();
        initPoints.push_back(p);
    }
    
    Point r = new Point(m(initPoints));
    p=&r;
    
	for (int i=0; i<VECTOR_SIZE; ++i)
    	BOOST_CHECK_GE(initPoints[i]->getEval(),p->getEval());

    for (int i=0; i<VECTOR_SIZE; ++i) {
        delete initPoints[i];
    }
}
BOOST_AUTO_TEST_SUITE_END()

