#include "Horizon.h"

const int debug = 1;

Point::Point(float _x, float _y):
		x(_x), y(_y) {}

Point::Point(const Point& master):
		x(master.x), y(master.y) {}

void Point::read(FILE *fin) {
	fscanf(fin, "%f%f", &x, &y);
}
void Point::write(FILE *fout) {
	fprintf(fout, "(%.3f , %.3f)", x, y);
}

Segment::Segment(float x1, float y1, float x2, float y2):
		left(x1, y1), right(x2, y2) {}

Segment::Segment(const Point& _left, const Point& _right):
		left(_left), right(_right) {}

void Segment::read(FILE *fin) {
	left.read(fin);
	right.read(fin);
}

void Segment::write(FILE *fout) {
	fprintf(fout, "( ");
	left.write(fout);
	fprintf(fout, " , ");
	right.write(fout);
	fprintf(fout, " )");
}

Point Segment::value(Point pivot) {
	///TODO: safe version
	Point res(
			pivot.x,
			((right.x - pivot.x) * left.y
					+
			(pivot.x - left.x) * right.y)
					/
			(right.x - left.x)
	);
	return res;
}

void Segment::cut_left_off(Point pivot) {
	left = value(pivot);
}

void Segment::cut_right_off(Point pivot) {
	right = value(pivot);
}

Point Segment::intersection(Segment s)
{
	///TODO: Safe intersection
	Point res(0, 0);
	float left_dy = s.left.y - value(s.left).y;
	float right_dy = s.right.y - value(s.right).y;
	res.x = (
			right_dy * s.left.x
					-
			right_dy * s.right.x)
					/
			(right_dy - left_dy);
	res = value(res);
	return res;
}

Horizon::Horizon(Segment _bound):
		bound(_bound), outline()
{
	clear();
}

void Horizon::clear() {
	outline.clear();
	outline.push_back(Segment(bound.left.x, 0, bound.right.x, 0));
}

void Horizon::add(Segment s) {
	list<Segment>::iterator left_bound;
	list<Segment>::iterator right_bound;

	list<Segment>::iterator it = outline.begin();

	if (s.left.x < outline.front().left.x)
	{
		s.cut_left_off(outline.front().left);
		left_bound = outline.begin();
	}
	else if (s.right.x > outline.back().right.x)
	{
		s.cut_right_off(outline.front().left);
		right_bound = outline.end();
		--right_bound;
	}
	else
	{
		it = outline.begin();
		while (it != outline.end()) {
			if (it->right.x > s.left.x) {
				left_bound = it;
				break;
			}
			it++;
		}
		while (it != outline.end()) {
			if (it->right.x > s.right.x) {
				right_bound = it;
				break;
			}
			it++;
		}
	}
	if (debug) {
		printf("Left : ");
		left_bound->write(stdout);
		printf("\n Right : ");
		right_bound->write(stdout);
		printf("\n");
	}
	///TODO: merge and split implement
}

void Horizon::d_erase() {
	outline.clear();
}

void Horizon::d_push(Segment s) {
	outline.push_back(s);
}
