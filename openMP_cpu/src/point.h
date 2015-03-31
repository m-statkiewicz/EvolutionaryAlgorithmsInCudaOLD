/*
 * point.h
 */

#ifndef POINT
#define POINT

#include<cstdlib>
#include<iostream>

class Point {
protected:
	int size;	
	float* value;
	
public:
	Point();
	Point(int size);
	Point(const Point* p);
	Point(const Point& p);
	~Point();
	
	int getSize() const;
	float getCoord(int i) const;
	void setCoord(int i, float val);
	
	float evaluate() const;
	void generateRandom();

	friend std::ostream& operator<< (std::ostream &os, Point & p);
};


#endif
