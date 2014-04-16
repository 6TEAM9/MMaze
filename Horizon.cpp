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
	///TODO: find bug
	Point res(0, 0);
	float left_dy = s.left.y - value(s.left).y;
	float right_dy = s.right.y - value(s.right).y;
	float k1 = right_dy * s.left.x;
	float k2 = left_dy * s.right.x;// I will never copypaste code any more!
	float norm = (right_dy - left_dy);
	res.x = (k1 - k2) / norm;
	res = value(res);
	return res;
}

float Segment::rise(Point pivot) {
	return pivot.y - value(pivot).y;
}

Horizon::Horizon(Segment _bound):
		bound(_bound), outline()
{
	clear();
}

void Horizon::clear() {
	outline.clear();
	///TODO: remove after debug
	outline.push_back(Segment(bound.left.x, 0, bound.right.x, 0.5));
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

	///TODO: add epsilon
	if (left_bound == right_bound) {
		float rise_left = it->rise(s.left);
		float rise_right = it->rise(s.right);
		Point fracture_left(0, 0);
		Point fracture_right(0, 0);
		if (rise_left > 0) {
			fracture_left = s.left;
			if (rise_right > 0) {
				fracture_right = s.right;
			} else {
	 			fracture_right = it->intersection(s);
			}
		} else {
			if (rise_right > 0) {
				fracture_left = it->intersection(s);
				fracture_right = s.right;
			} else {
				fracture_left = it->value(s.left);
				fracture_right = it->value(s.right);
			}
		}

		// fracture!
		{
			Segment cliff_left(*it);
			Segment cliff_right(*it);
			Segment cliff_center(fracture_left, fracture_right);

			cliff_left.cut_right_off(fracture_left);
			cliff_right.cut_left_off(fracture_right);

			*it = cliff_right;
			outline.insert(it, cliff_left);
			outline.insert(it, cliff_center);
			return;
		}
	}

	printf("Not done yet!\n");

	it = left_bound;
	// left bound fracture
	{

	}
}

void Horizon::print() {
	///WTF: cannot put this inside the loop
	list<Segment>::iterator it = outline.begin();
	for (; it != outline.end(); it++) {
		it->write(stdout);
		printf("\n");
	}
}

void Horizon::d_erase() {
	outline.clear();
}

void Horizon::d_push(Segment s) {
	outline.push_back(s);
}
