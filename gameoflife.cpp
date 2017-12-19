#include "gameoflife.h"

GameOfLife::GameOfLife(const int dim,const int sleepTime, const bool doEvolution){
    /*
     * A C++ implementation of the game
     * Convey's Game of Life
     */
    this->dim = dim;
    this->doEvolution = doEvolution;    //used to keep thread running
    this->sleepTime = sleepTime; //wait time in ms
    setSize(dim);
    createGlider();
}

void GameOfLife::createGlider(){
    /*
     * creates the glider formation
     */
    setCellState(0,0,1);
    setCellState(2,0,1);
    setCellState(1,1,1);
    setCellState(2,1,1);
    setCellState(1,2,1);
}

GameOfLife::~GameOfLife(){
    delete[] currentState;
    delete[] newState;
}

void GameOfLife::run(){
    /*
     * is called when Thread is started, kinda the new timer
     */
    while(this->doEvolution){
        emit evolve();
        msleep(sleepTime);  //wait the set interval before evolving again
    }
}

void GameOfLife::evolve() {
    /*
     * Applies the rules of the game to every instance of the field
     */

    vector<vector<int>> changed;    // vector for changed cells
    for (int y = 0; y < getDim(); y++) { // evaluate which cell should change its state
        for (int x = 0; x < getDim(); x++) {
            bool rule_applied = apply_rules(x, y); // should cell change state
            bool cellState = getCellState(x,y); // current cell state
            if((rule_applied && !cellState) || (!rule_applied && cellState)){ // if cell should change state
                vector<int> newState = {x,y,rule_applied};  // mark x y with new state
                changed.push_back(newState);    // add newState to vectore changed
            }
        }
    }

    for(vector<int> changedCell : changed){ // change every changed cell on the board to its new state
        setCellState(changedCell.at(0),changedCell.at(1),changedCell.at(2)); //.at(x) <- get from index x
    }
}


void GameOfLife::setDoEvolution(bool doEvolution){
    this->doEvolution = doEvolution;
}

void GameOfLife::setSleepTime(int sleepTime){
    this->sleepTime = sleepTime;
}

void GameOfLife::setDim(const int dim) {
    this->dim = dim;
}

void GameOfLife::wipe() {
    /*
     * Resets the dyn arrays, every entry set to False
     */
    for (int y = 0; y < getDim(); y++) {
        for (int x = 0; x < getDim(); x++) {
            setCellState(x, y, false);
            setNewCellState(x, y, false);
        }
    }
}

void GameOfLife::setSize(const int dim) {
    /*
     * resizes the dynamic arrays
     */
    setDim(dim);
    delete[] currentState;
    delete[] newState;
    currentState = new bool[dim * dim];
    newState = new bool[dim * dim];
    wipe();
}

void GameOfLife::setNewCellState(const int x, const int y, const bool state) {
    /*
     * Changes one instance of the newCellState Array
     */
    int address = convertToOneDimension(x, y);
    newState[address] = state;
}

void GameOfLife::setCellState(const int x, const int y, const bool state) {
    /*
     * Changes one instance of the currentCellState Array
     */
    int address = convertToOneDimension(x, y);
    currentState[address] = state;
}

int GameOfLife::convertToOneDimension(const int x, const int y) {
    /*
     * Converts 2D iteration to 1D iteration
     */
    return ((y * getDim()) + x);
}

int GameOfLife::getDim() {
    return dim;
}

bool GameOfLife::field_exists(const int x, const int y) {
    /*
     * Returns true if x and y is in the grids boundaries
     */
    return (x < getDim() && x >= 0) && (y >= 0 && y < getDim());
}

bool GameOfLife::apply_rules(const int x, const int y) {
    /*
     * Checks for a given instance, if any rule has to be applied
     */
    int up = (y - 1);
    int down = (y + 1);
    int left = (x - 1);
    int right = (x + 1);

    int amountOfNeighbours = 0;

    //checks if surrounding cell exist and is alive
    if (field_exists(left, up) && getCellState(left, up)) { amountOfNeighbours++; }     // dia left up
    if (field_exists(left, down) && getCellState(left, down)) { amountOfNeighbours++; }  // dia left down
    if (field_exists(right, down) && getCellState(right, down)) { amountOfNeighbours++; } // dia right down
    if (field_exists(right, up) && getCellState(right, up)) { amountOfNeighbours++; }    // dia right up
    if (field_exists(left, y) && getCellState(left, y)) { amountOfNeighbours++; }        // left
    if (field_exists(right, y) && getCellState(right, y)) { amountOfNeighbours++; }       // right
    if (field_exists(x, up) && getCellState(x, up)) { amountOfNeighbours++; }          // up
    if (field_exists(x, down) && getCellState(x, down)) { amountOfNeighbours++; }       // down

    if (amountOfNeighbours > 3 || amountOfNeighbours < 2) { // not enough or too many neighbors
        return false;
    } else if (getCellState(x, y) && (amountOfNeighbours == 2 || amountOfNeighbours == 3)) { // 2 or 3 neighbors to stay alive
        return true;
    } else if (!getCellState(x, y) && amountOfNeighbours == 3) { // 3 neighbors reproduced
        return true;
    }
    return false;
}

bool GameOfLife::getCellState(const int x, const int y) {
    int address = convertToOneDimension(x, y);
    return currentState[address];
}

bool GameOfLife::getnewCellState(const int x, const int y) {
    int address = convertToOneDimension(x, y);
    return newState[address];
}
