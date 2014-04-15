#include "Maze.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define up 0
#define down 1
#define left 2
#define right 3
#define X first
#define Y second

Maze::Tmp::Tmp(Maze *maze, int i): maze(maze), i(i)
{

}

int Maze::Tmp::operator[](int j)
{
    return maze->field[i][j];
}

Maze::Maze()
{
    Maze(1, 1);
}

Maze::Maze(int n, int m): n(n), m(m)
{
    isGenerated = isLoaded = false;
    startX = startY = 0;
    delta[up] = make_pair(-1, 0);
    delta[down] = make_pair(1, 0);
    delta[left] = make_pair(0, -1);
    delta[right] = make_pair(0, 1);
    used.resize(n);
    field.resize(2 * n + 1);
    for (int i  = 0; i < 2 * n + 1; ++i)
        field[i].resize(2 * m + 1);

    for (int i = 0; i < n; ++i)
    {
        used.resize(m);
        for (int j = 0; j < m; ++j)
            used[i][j] = false;
    }
    for (int k = 0; k < 4; ++k)
    {
        direction[k].resize(n);
        for (int i = 0; i < n; ++i)
        {
            direction[k][i].resize(m);
            for (int j = 0; j < m; ++j)
                direction[k][i][j] = false;
        }
    }
}

Maze::Maze(char *filename)
{
    /// no spaces in input!!!
    char fld;
    char tmp[10000];
    FILE *pFile;
    pFile = fopen(filename, "r");
    fscanf(pFile, "%d%d", &n, &m);
    field.resize(2 * n + 1);
    for (int i  = 0; i < 2 * n + 1; ++i)
        field[i].resize(2 * m + 1);
    for (int i = 0; i < 2 * n + 1; ++i)
    {
        fscanf(pFile, "%s", tmp);
        fld = tmp[0];
        for (int j = 0; j < 2 * m + 1; ++j)
            field[i][j] = (tmp[j] == fld);
    }
    fclose(pFile);
    isLoaded = true;
    isGenerated = true;
}

Maze::~Maze()
{
    //dtor
}

void Maze::setStartPos(int inx, int iny)
{
    startX = inx, startY = iny;
}

void Maze::dfs(int x, int y)
{
    used[x][y] = true;
    vector< int > possibleDirections;
    for (int i = 0; i < 4; ++i)
        if (x + delta[i].X >= 0 &&
            x + delta[i].X < n &&
            y + delta[i].Y >= 0 &&
            y + delta[i].Y < m)
        {
            possibleDirections.push_back(i);
        }
    while (!possibleDirections.empty())
    {
        int idx = rand() % possibleDirections.size();
        int curDirection = possibleDirections[idx];
        possibleDirections.erase(possibleDirections.begin() + idx);
        if (!used[x + delta[curDirection].X][y + delta[curDirection].Y])
        {
            makeEdge(x, y, curDirection);
            dfs(x + delta[curDirection].X, y +delta[curDirection].Y);
        }
    }
}

void Maze::generate(int way)
{
    if (isGenerated || isLoaded) return;
    switch(way)
    {
        case 1:
            dfs(startX, startY);
        break;
        //case 2:
        //    bfs(startX, startY);
        //break;
    }
    makeField();
    isGenerated = true;
}

void Maze::makeEdge(int x, int y, int dir)
{
    direction[dir][x][y] = true;
    direction[dir^1][x + delta[dir].X][y + delta[dir].Y] = true;
}

void Maze::makeField()
{
    for (int i = 0; i < 2 * n + 1; i += 2)
        for (int j = 0; j < 2 * m + 1; j += 2)
            field[i][j] = true;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < 4; ++k)
                if (!direction[k][i][j])
                    field[2 * i + 1 + delta[k].X][2 * j + 1 + delta[k].Y] = true;
}

void Maze::print(char emptycell, char wall)
{
    for (int i = 0; i < 2 * n + 1; ++i)
    {
        for (int j = 0; j < 2 * m + 1; ++j)
            if (field[i][j]) cout << wall;
            else cout << emptycell;
        cout << "\n";
    }
}

void Maze::saveToFile(char *filename, char emptycell, char wall)
{
    FILE *pFile;
    pFile = fopen(filename, "w");
    for (int i = 0; i < 2 * n + 1; ++i)
    {
        for (int j = 0; j < 2 * m + 1; ++j)
            if (field[i][j]) fprintf(pFile, "%c", wall);
            else fprintf(pFile, "%c", emptycell);
        fprintf(pFile, "\n");
    }
    fclose(pFile);
}

bool Maze::isFilled(int inx, int iny)
{
    return field[inx][iny];
}

Maze::Tmp Maze::operator[](int i)
{
    return Maze::Tmp(&(*this), i);
}
