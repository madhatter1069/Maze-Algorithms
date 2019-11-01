#include "MazeGenerator.hpp"
#include <vector>
#include "Direction.hpp"
#include "Maze.hpp"
#include <random>

#ifndef JMAZE_HPP
#define JMAZE_HPP

class Jmaze: public MazeGenerator
{
std::vector<std::vector<int> > visited;
int num_visited;
int mw;
int mh;

public:
Jmaze();
~Jmaze();
std::vector<Direction> getValidDir(int x, int y);
Direction chosenDir(std::vector<Direction> v);
void generateMaze(Maze& maze);
void makemove(int x, int y, Maze& maze);
};
#endif

