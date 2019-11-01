#include "Jmaze.hpp"
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, Jmaze, "Jared's Algorithm (Required)");
Jmaze:: Jmaze(){}
Jmaze:: ~Jmaze(){}
std::vector<Direction> Jmaze:: getValidDir(int x, int y){
    std::vector<Direction> dir;
    dir.clear();
    if(y>=1 && visited[y-1][x]==0){
        dir.push_back(Direction::up);
    }
    if(y<mh-1 && visited[y+1][x]==0){
        dir.push_back(Direction::down);
    }
    if(x>=1 && visited[y][x-1]==0){
        dir.push_back(Direction::left);
    }
    if (x<mw-1 && visited[y][x+1]==0){
        dir.push_back(Direction::right);
    }
    return dir;
}
Direction Jmaze:: chosenDir(std::vector<Direction> v){
    int size=v.size();
    std::random_device dev;
    std::default_random_engine engine{dev()};
    std::uniform_int_distribution<int> dir{0,size-1};
    int path=dir(engine);
    return v[path];
}

void Jmaze:: generateMaze(Maze& maze){
    maze.addAllWalls();
    mh=maze.getHeight();
    mw=maze.getWidth();
    int total_cells=mw*mh;
    num_visited=0;
    visited.resize(maze.getHeight(),std::vector<int>(maze.getWidth(),0));
    while(num_visited<total_cells-1){
       makemove(0,0,maze);
    }
}
void Jmaze:: makemove(int x, int y, Maze& maze){
    visited[y][x]=1;
    ++num_visited;
    std::vector<Direction> direction=getValidDir(x,y);
    while (direction.size()>0){
        Direction go=chosenDir(direction);
        direction.clear();
        maze.removeWall(x,y,go);
        if(go==Direction::up && y>=1 && visited[y-1][x]==0)
            makemove(x,y-1,maze);
        else if(go==Direction::down && y<mh-1 && visited[y+1][x]==0)
            makemove(x,y+1,maze);
        else if(go==Direction::left && x>0 && visited[y][x-1]==0)
            makemove(x-1,y,maze);
        else if(go==Direction::right && x<mw-1 && visited[y][x+1]==0)
            makemove(x+1,y,maze);
        direction=getValidDir(x,y);
    }
}
