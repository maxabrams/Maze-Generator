//Maxwell Abrams

#include <iostream>
#include "Cell.h"
#include <stack>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Maze
{
    
public:
    //Constructor
    Maze(int);
    //Deconstructor
    ~Maze();
    //Function to print a maze
    void printMaze();
    //Function to create a maze
    void createMaze();
    //Function to use DFS and print the shortest path
    void DFS();
protected:
    //Member items
    int size;
    Cell* blocks;
};

//Create a maze of given size (sizeXsize)
Maze::Maze(int mazeSize){
    size = mazeSize;
    blocks = new Cell[size*size];
}

//Destructor for the maze
Maze::~Maze(){
    delete []blocks;
}

//Print the maze once constructed
void Maze::printMaze(){
    //print the top border
    cout << "+ ";
    for (int r = 1; r < size; r++){
        cout <<"+-";
    }
    cout <<"+"<<endl;
    
    int index = 0;
    while(index<size){
        //print the edges and spaces
        for(int r = 0; r < size; r++){
            if(blocks[(size*index)+r].getLeft() == NULL || r == 0)
                cout<<"| ";
            else
                cout<<"  ";
        }
        cout<<"|"<<endl;
        
        //print the bottom border of a row
        if(index == size-1){
            for(int r = 0; r < size; r++){
                if(r == size - 1)
                    cout<<"+ ";
                else
                    cout<<"+-";
            }
            cout<<"+"<<endl;
        }
        else //last row
        {
            for(int r = 0; r < size; r++){
                if(blocks[(size*index)+r].getDown()!=NULL){
                    cout<<"+ ";
                }
                else
                    cout<<"+-";
            }
        cout <<"+"<<endl;
        }
        index++;
    }
    cout <<endl;
}

//Create the maze
void Maze::createMaze(){
    stack <int> CellStack;
    int TotalCells = size * size;
    
    int i;
    int CurrentCell = 0;
    int VisitedCells = 1;
    srand(time(NULL));
    
    while(VisitedCells < TotalCells){
        int nb[4] = {0, 0, 0, 0}; //make an array to store which neighbors a cell has
        int num = 0;
        
        //check if cell has neighbors
        if (CurrentCell-size >= 0 && blocks[CurrentCell-size].getColor() == 0){
            nb[num] = 1;
            num++;
        }
        if ((CurrentCell % size < size -1) && blocks[CurrentCell+1].getColor() == 0){
            nb[num] = 2;
            num++;
        }
        if (CurrentCell < TotalCells - size && blocks[CurrentCell+size].getColor() == 0){
            nb[num] = 3;
            num++;
        }
        if (CurrentCell % size != 0 && blocks[CurrentCell-1].getColor() == 0){
            nb[num] = 4;
            num++;
        }
        
        //if cell has neighbors, pick one and "knock down the wall between them"
        if(num > 0){
            int choice = nb[rand()%(num)];
            switch(choice){
                case 1:
                    i = CurrentCell-size;
                    blocks[CurrentCell].setUp(&blocks[i]);
                    blocks[i].setDown(&blocks[CurrentCell]);
                    blocks[CurrentCell].setColor(1);
                    blocks[i].setColor(1);
                    CellStack.push(CurrentCell);
                    CurrentCell = i;
                    VisitedCells++;
                    break;
                case 2:
                    i = CurrentCell + 1;
                    blocks[CurrentCell].setRight(&blocks[i]);
                    blocks[i].setLeft(&blocks[CurrentCell]);
                    blocks[CurrentCell].setColor(1);
                    blocks[i].setColor(1);
                    CellStack.push(CurrentCell);
                    CurrentCell =i;
                    VisitedCells++;
                    break;
                case 3:
                    i = CurrentCell + size;
                    blocks[CurrentCell].setDown(&blocks[i]);
                    blocks[i].setUp(&blocks[CurrentCell]);
                    blocks[CurrentCell].setColor(1);
                    blocks[i].setColor(1);
                    CellStack.push(CurrentCell);
                    CurrentCell =i;
                    VisitedCells++;
                    break;
                case 4:
                    i = CurrentCell - 1;
                    blocks[CurrentCell].setLeft(&blocks[i]);
                    blocks[i].setRight(&blocks[CurrentCell]);
                    blocks[CurrentCell].setColor(1);
                    blocks[i].setColor(1);
                    CellStack.push(CurrentCell);
                    CurrentCell =i;
                    VisitedCells++;
                    break;
                default:
                    break;
                    
            }
        }
        else //cell has no neighbors, pop off the stack
        {
            blocks[CurrentCell].setColor(2);
            CurrentCell = CellStack.top();
            CellStack.pop();
        }
    }
    //reset all marks to 0
    for (int i = 0; i < TotalCells; i++)
        blocks[i].setColor(0);
 }

//DFS function to traverse the maze and find the shortest path
void Maze::DFS(){
    stack<int> s;
    int i = 0;
    int j;
    s.push(i);
    int num = 0;
    int reset = 0;
    
    while(s.empty()==false){
        i = s.top();
        s.pop();
        if(num == 0 && reset == 0)
            blocks[i].setParent(NULL);
        
        blocks[i].setNum(num);
        
        //if the current cell is the exit cell, break out of the loop
        if(blocks[i].getColor() == 0){
            if(i == (size*size)-1){
                break;
            }
        }
        
        //do DFS and set parent
        if(blocks[i].getRight() != NULL && blocks[i].getRight()->getColor()==0){
            s.push(i+1);
            blocks[i+1].setParent(&blocks[i]);
        }
        if(blocks[i].getDown() != NULL && blocks[i].getDown()->getColor()==0){
            s.push(i+size);
            blocks[i+size].setParent(&blocks[i]);
        }
        if(blocks[i].getLeft() != NULL && blocks[i].getLeft()->getColor()==0){
            s.push(i-1);
            blocks[i-1].setParent(&blocks[i]);
        }
        if(blocks[i].getUp() != NULL && blocks[i].getUp()->getColor()==0){
            s.push(i-size);
            blocks[i-size].setParent(&blocks[i]);
        }
        blocks[i].setColor(1);
        num++;
        if(num ==10){
            num = 0;
            reset++;
        }
    }
    
    //print out maze with DFS order of cells visited
    cout << "+ ";
    for (int r = 1; r < size; r++){
        cout <<"+-";
    }
    cout <<"+"<<endl;
    
    int index = 0;
    while(index<size){
        for(int r = 0; r < size; r++){
            if(blocks[(size*index)+r].getLeft() == NULL || r == 0){
                if(blocks[(size*index)+r].getNum() >= 0)
                    cout<<"|"<<blocks[(size*index)+r].getNum();
                else
                    cout<<"| ";
            }
            else{
                if(blocks[(size*index)+r].getNum() >= 0)
                    cout<<" "<<blocks[(size*index)+r].getNum();
                else
                    cout<<"  ";
            }
        }
        cout<<"|"<<endl;
        
        if(index == size-1){
            for(int r = 0; r < size; r++){
                if(r == size - 1)
                    cout<<"+ ";
                else
                    cout<<"+-";
            }
            cout<<"+"<<endl;
        }
        else{
            for(int r = 0; r < size; r++){
                if(blocks[(size*index)+r].getDown()!=NULL){
                    cout<<"+ ";
                }
                else
                    cout<<"+-";
            }
            cout <<"+"<<endl;
        }
        index++;
    }
    
    cout <<endl;
    
    //traverse starting from the end cell to find the shortest path
    cout <<"Shortest Path"<<endl;
    int last = (size*size)-1;
    while(last != 0){
        blocks[last].setSym('#');
        if(&blocks[last-size] == blocks[last].getParent()){
            blocks[last-size].setDownSym('#');
            last = last-size;
        }
        else if(&blocks[last+1] == blocks[last].getParent()){
            blocks[last+1].setLeftSym('#');
            last = last+1;
        }
        else if(&blocks[last+size] == blocks[last].getParent()){
            blocks[last].setDownSym('#');
            last = last+size;
        }
        else{
            blocks[last].setLeftSym('#');
            last = last-1;
        }
    }
    blocks[0].setSym('#');
    
    
    //print maze with shortest path
    cout << "+ ";
    for (int r = 1; r < size; r++){
        cout <<"+-";
    }
    cout <<"+"<<endl;
    
    index = 0;
    while(index<size){
        for(int r = 0; r < size; r++){
            if(blocks[(size*index)+r].getLeft() == NULL || r == 0)
                cout<<"|"<<blocks[(size*index)+r].getSym();
            else{
                if(blocks[(size*index)+r].getLeft() != NULL && blocks[(size*index)+r].getLeftSym() == '|')
                    cout<<" "<<blocks[(size*index)+r].getSym();
                else
                    cout<<blocks[(size*index)+r].getLeftSym()<<blocks[(size*index)+r].getSym();
            }
        }
        cout<<"|"<<endl;
        
        if(index == size-1){
            for(int r = 0; r < size; r++){
                if(r == size - 1)
                    cout<<"+ ";
                else
                    cout<<"+-";
            }
            cout<<"+"<<endl;
        }
        else{
            for(int r = 0; r < size; r++){
                if(blocks[(size*index)+r].getDown() == NULL)
                    cout<<"+-";
                else{
                    if(blocks[(size*index)+r].getDown() != NULL && blocks[(size*index)+r].getDownSym() == '-')
                        cout<<"+ ";
                    else
                        cout<<"+"<<blocks[(size*index)+r].getDownSym();
                }
            }
            cout <<"+"<<endl;
        }
        index++;
    }
    cout <<endl;
}
