#include "cabase.h"

CAbase::CAbase(const int dim,const int sleepTime, const bool doEvolution){
    this->dim = dim;
    this->doEvolution = doEvolution;    //used to keep thread running
    this->sleepTime = sleepTime; //in ms
    setSize(dim);

    //glider
    setCellState(0,0,1);
    setCellState(2,0,1);
    setCellState(1,1,1);
    setCellState(2,1,1);
    setCellState(1,2,1);
}

CAbase::~CAbase(){
    delete[] currentState;
    delete[] newState;
}

void CAbase::run(){
    /*
     * is called when Thread is started, kinda the new timer
     */
    while(this->doEvolution){
        emit evolve();
        msleep(sleepTime);  //wait the set interval before evolving again
    }
}

void CAbase::evolve() {
    /*
     * Applies the rules of the game to every instance of the field
     */

    vector<vector<int>> changed;
    for (int y = 0; y < getDim(); y++) {
        for (int x = 0; x < getDim(); x++) {
            bool rule_applied = apply_rules(x, y);
            bool cellState = getCellState(x,y);
            if((rule_applied && !cellState) || (!rule_applied && cellState)){
                vector<int> newState = {x,y,rule_applied};
                changed.push_back(newState);
            }
        }
    }

    for(vector<int> changedCell : changed){
        setCellState(changedCell.at(0),changedCell.at(1),changedCell.at(2));
    }
}


void CAbase::setDoEvolution(bool doEvolution){
    this->doEvolution = doEvolution;
}

void CAbase::setSleepTime(int sleepTime){
    this->sleepTime = sleepTime;
}

void CAbase::setDim(const int dim) {
    this->dim = dim;
}

void CAbase::wipe() {
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

void CAbase::setSize(const int dim) {
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

void CAbase::setNewCellState(const int x, const int y, const bool state) {
    /*
     * Changes one instance of the newCellState Array
     */
    int address = convertToOneDimension(x, y);
    newState[address] = state;
}

void CAbase::setCellState(const int x, const int y, const bool state) {
    /*
     * Changes one instance of the currentCellState Array
     */
    int address = convertToOneDimension(x, y);
    currentState[address] = state;
}

int CAbase::convertToOneDimension(const int x, const int y) {
    /*
     * Converts 2D iteration to 1D iteration
     */
    return ((y * getDim()) + x);
}

int CAbase::getDim() {
    return dim;
}

bool CAbase::field_exists(const int x, const int y) {
    /*
     * Returns true if x and y is in the grids boundaries
     */
    return (x < getDim() && x >= 0) && (y >= 0 && y < getDim());
}

bool CAbase::apply_rules(const int x, const int y) {
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
}

bool CAbase::getCellState(const int x, const int y) {
    int address = convertToOneDimension(x, y);
    return currentState[address];
}

bool CAbase::getnewCellState(const int x, const int y) {
    int address = convertToOneDimension(x, y);
    return newState[address];
}
