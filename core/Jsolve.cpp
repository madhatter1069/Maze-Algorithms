#include <ics46/factory/DynamicFactory.hpp>
#include "Jsolve.hpp"
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, Jsolve, "Jared Solve (Required)");
Jsolve:: Jsolve(){}
Jsolve:: ~Jsolve(){}
void Jsolve:: solveMaze(const Maze& maze, MazeSolution& mazeSolution){
    mazeSolution.restart();
    visited.resize(maze.getHeight(),std::vector<int>(maze.getWidth(),0));
    int x=mazeSolution.getStartingCell().first;
    int y=mazeSolution.getStartingCell().second;
    while (!mazeSolution.isComplete())
        makemove(x,y,maze,mazeSolution);
}
void Jsolve:: makemove(int x, int y, const Maze& maze, MazeSolution& mazeSolution){
    visited[y][x]=1;
    std::vector<Direction> direction=getValidDir(x,y,maze);
    while(direction.size()>0 && !mazeSolution.isComplete()){
        Direction go=chosenDir(direction);
        direction.clear();
        if(go==Direction::up && y>=1 && visited[y-1][x]==0){
            mazeSolution.extend(go);
            makemove(x,y-1,maze,mazeSolution);}
        else if(go==Direction::down && y<maze.getHeight()-1 && visited[y+1][x]==0){
            mazeSolution.extend(go);
            makemove(x,y+1,maze,mazeSolution);}
        else if(go==Direction::left && x>=1 && visited[y][x-1]==0){
            mazeSolution.extend(go);
            makemove(x-1,y,maze,mazeSolution);}
        else if(go==Direction::right && x<maze.getWidth()-1 && visited[y][x+1]==0){
            mazeSolution.extend(go);
            makemove(x+1,y,maze,mazeSolution);}
        direction=getValidDir(x,y,maze);
        }
        if(direction.size()==0 && !mazeSolution.isComplete())
            mazeSolution.backUp();
}
Direction Jsolve:: chosenDir(std::vector<Direction> v){
    int size=v.size();
    std::random_device dev;
    std::default_random_engine engine{dev()};
    std::uniform_int_distribution<int> dir{0,size-1};
    int path=dir(engine);
    return v[path];
}
std::vector<Direction> Jsolve:: getValidDir(int x, int y, const Maze& maze){
    std::vector<Direction> dir;
    dir.clear();
    if(y>=1 && !maze.wallExists(x,y,Direction::up) && visited[y-1][x]==0)
        dir.push_back(Direction::up);
    if (y<maze.getHeight()-1 && !maze.wallExists(x,y, Direction::down) && visited[y+1][x]==0)
        dir.push_back(Direction::down);
    if (x>=1 && !maze.wallExists(x,y,Direction::left) && visited[y][x-1]==0)
        dir.push_back(Direction::left);
    if (x<maze.getWidth()-1 && !maze.wallExists(x,y,Direction::right) && visited[y][x+1]==0)
        dir.push_back(Direction::right);
    return dir;
}
