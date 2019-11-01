#include "Maze.hpp"
#include "Direction.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include <vector>
#include <random>

#ifndef JSOLVE_HPP
#define JSOLVE_HPP
class Jsolve: public MazeSolver
{
std::vector<std::vector<int>> visited;
public:
Jsolve();
~Jsolve();
void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
void makemove(int x, int y, const Maze& maze, MazeSolution& mazeSolution);
Direction chosenDir(std::vector<Direction> v);
std::vector<Direction> getValidDir(int x, int y, const Maze& maze);
};
#endif
