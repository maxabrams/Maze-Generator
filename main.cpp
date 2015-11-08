//Maxwell Abrams
#include "Maze.h"

using namespace std;

int main()
{
    
    int size;
    
    cout << "Welcome to the maze generator! Please give a maze size:" << endl;
    cin >> size;

    Maze* maze = new Maze(size);
    maze->createMaze();
    cout<<"Maze"<<endl;
    maze->printMaze();
    cout<<"DFS"<<endl;
    maze->DFS();
}
