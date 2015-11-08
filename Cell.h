//Maxwell Abrams

#include <iostream>

using namespace std;

class Cell
{
    
public:
    //Constructor
    Cell();
    //Destructor
    ~Cell();
    
    //Mutator
    void setLeft(Cell*);
    void setRight(Cell*);
    void setUp(Cell*);
    void setDown(Cell*);
    void setParent(Cell*);
    void setColor(int);
    void setNum(int);
    void setSym(char);
    void setDownSym(char);
    void setLeftSym(char);
    
    //Accessor
    Cell* getLeft();
    Cell* getRight();
    Cell* getUp();
    Cell* getDown();
    Cell* getParent();
    int getColor();
    int getNum();
    char getSym();
    char getDownSym();
    char getLeftSym();
    
protected:
    //Member items
    Cell *up;
    Cell *down;
    Cell *left;
    Cell *right;
    int color;
    Cell *parent;
    int num;
    char sym;
    char downSym;
    char leftSym;
    
};

//Constructor
Cell::Cell(){
    up=NULL;
    down=NULL;
    left=NULL;
    right=NULL;
    color = 0;
    parent=NULL;
    num = -1;
    sym = ' ';
    downSym = '-';
    leftSym = '|';
}

//Destructor
Cell::~Cell(){
    
}

//Mutators
void Cell::setLeft(Cell* newCell){
    left = newCell;
}

void Cell::setRight(Cell* newCell){
    right = newCell;
}

void Cell::setUp(Cell* newCell){
    up = newCell;
}

void Cell::setDown(Cell* newCell){
    down = newCell;
}

void Cell::setParent(Cell* newCell){
    parent = newCell;
}

void Cell::setColor(int col){
    color = col;
}

void Cell::setNum(int n){
    num = n;
}

void Cell::setDownSym(char s){
    downSym = s;
}

void Cell::setLeftSym(char s){
    leftSym = s;
}


//Accessors
Cell* Cell::getUp(){
    return up;
}

Cell* Cell::getDown(){
    return down;
}

Cell* Cell::getLeft(){
    return left;
}

Cell* Cell::getRight(){
    return right;
}

Cell* Cell::getParent(){
    return parent;
}

int Cell::getColor(){
    return color;
}

int Cell::getNum(){
    return num;
}

char Cell::getSym(){
    return sym;
}

void Cell::setSym(char s){
    sym = s;
}

char Cell::getDownSym(){
    return downSym;
}

char Cell::getLeftSym(){
    return leftSym;
}
