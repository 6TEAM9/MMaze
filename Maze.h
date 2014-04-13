#ifndef MAZE_H_INCLUDED

#include <stdio.h>

using namespace std;

const int debug = 1;

const char EMPTY = 0;
const char FILLED = 1;

struct Cell{
	int row;
	int col;
	Cell(int _row, int _col) {
		row = _row;
		col = _col;
	}
};

const Cell DIRS[4] = {
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1}
};

template <class T> class Queue {
	T *a;
	int head;
	int tail;
	///TODO: implement or remove
};

class Maze {
	Cell m_size;
	char **m_f;
public:
	Maze(int rows = 0, int cols = 0);
	const Cell& getSize();
	void print();
	void generate();
};

#endif // MAZE_H_INCLUDED
