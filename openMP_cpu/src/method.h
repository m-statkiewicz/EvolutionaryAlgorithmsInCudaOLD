/*
 * method.h
 */

#ifndef METHOD		
#define METHOD

#include<vector>

#include"point.h"

class Method
{
//protected:
//bool compare(const Point& a,const Point& b) const;
public:
	Point operator () (const std::vector<Point*>& initialPoints) const;
};

#endif
