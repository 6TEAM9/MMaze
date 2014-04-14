<<<<<<< HEAD
#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include <fstream>


using namespace std;

class Maze
{
private:
    bool isGenerated, isLoaded;
    int n, m, startX, startY;
    vector< vector< bool > > used;
    vector< vector< bool > > direction[4];
    vector< vector< bool > > field;
    pair< int, int > delta[4];
    void bfs(int x, int y);
    void dfs(int x, int y);
    void makeEdge(int x, int y, int dir);
    void makeField();
=======
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
>>>>>>> 86227d30e8bb0e68725e616289d1215142807113
public:
    Maze();
    Maze(int n, int m);
    Maze(char *filename);
    virtual ~Maze();
    void generate(int way);
    void setStartPos(int inx, int iny);
    void print(char emptycell, char wall);
    void saveToFile(char *filename, char emptycell, char wall);
    bool isFilled(int inx, int iny);
};

#endif // MAZE_H
