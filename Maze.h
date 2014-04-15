#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include <fstream>


using namespace std;

class Maze
{
private:
    friend class Tmp;
    bool isGenerated, isLoaded;
    int n, m, startX, startY;
    vector< vector< bool > > used;
    vector< vector< bool > > direction[4];
    vector< vector< bool > > field;
    pair< int, int > delta[4];
    class Tmp
    {
        Maze *maze;
        int i;
        Tmp();
        Tmp(Maze *maze, int i);
        friend class Maze;
    public:
        int operator[](int j);
    };
    void bfs(int x, int y);
    void dfs(int x, int y);
    void makeEdge(int x, int y, int dir);
    void makeField();
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
    Tmp operator[](int i);
};

#endif // MAZE_H
