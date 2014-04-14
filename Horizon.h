#ifndef HORIZON_H_INCLUDED
#define HORIZON_H_INCLUDED

#include <list>
#include <stdio.h>

using namespace std;

struct Point {
	float x;
	float y;
	Point(float _x, float _y);
	Point(const Point& master);
	void read(FILE *fin);
	void write(FILE *fout);
};

struct Segment {
	Point left;
	Point right;
	Segment(float x1, float y1, float x2, float y2);
	Segment(const Point& _left, const Point& _right);
	void read(FILE *fin);
	void write(FILE *fout);
	Point value(Point pivot);
	void cut_left_off(Point pivot);
	void cut_right_off(Point pivot);
};

class Horizon{
	Segment bound;
	list<Segment> outline;
public:
	Horizon(Segment _bound);
	void clear();
	void add(Segment s);
	void d_erase();
	void d_push(Segment s);
};

#endif // HORIZON_H_INCLUDED
