/*
 * strategy_test.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Strategy
#include <boost/test/unit_test.hpp>

#include "mipluslambdastrategy.h"
#include "milambdastrategy.h"

#define POINT_SIZE 5
#define VECTOR_SIZE 10

#define MI 5
#define LAMBDA 10
#define ITERATIONS 10

BOOST_AUTO_TEST_SUITE( StrategySuite )
BOOST_AUTO_TEST_CASE( MiPlusLambdaStrategy )
{
    MiPlusLambdaStrategy m (1, 2, 3);
    std::vector<Point*> initPoints;
    Point* p;
    for (int i=0; i<VECTOR_SIZE; ++i) {
        p = new Point(POINT_SIZE);
        p->generateRandom();
        initPoints.push_back(p);
    }
    
    Point r = m(initPoints);
    p=&r;
    
	for (int i=0; i<VECTOR_SIZE; ++i)
    	BOOST_CHECK_GE(initPoints[i]->getEval(),p->getEval());

    for (int i=0; i<VECTOR_SIZE; ++i) {
        delete initPoints[i];
    }
}

BOOST_AUTO_TEST_CASE( MiLambdaStrategy )
{
/*    MiLambdaStrategy m (MI,LAMBDA,ITERATIONS);
    std::vector<Point*> initPoints;
    Point* p;
    for (int i=0; i<VECTOR_SIZE; ++i) {
        p = new Point(POINT_SIZE);
        p->generateRandom();
        initPoints.push_back(p);
    }
    
    Point r = new Point(m(initPoints));
    p=&r;
    
	for (int i=0; i<VECTOR_SIZE; ++i)
    	BOOST_CHECK_GE(initPoints[i]->getEval(),p->getEval());

    for (int i=0; i<VECTOR_SIZE; ++i) {
        delete initPoints[i];
    }
*/
}
BOOST_AUTO_TEST_SUITE_END()

