#include "predatorprey.h"

PredatorPrey::PredatorPrey(const int gameSize, const int lifetime){
    /*
     * A C++ implementation of the Game Predator-Victim|Predetator-Prey
     */
    field.reserve(gameSize*gameSize); // allocate memory to fit the field size
    this->gameSize = gameSize;
    this->maxLifetime = lifetime;
    this->preySpawnRate = 0.05;
    this->predatorSpawnRate = 0.01;
    this->foodSpawnRate = 0.1;
    clear();
}

void PredatorPrey::moveCells(){
    /*
     * updates every Cell in the game field
     * to its new position
     */
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            Cell currentCell = getCell(x,y);
            // If cell has not been moved and cell can move
            if(!currentCell.isChecked() && (currentCell.isPredator() || currentCell.isPrey())){
                srand((int) time(0) + rand());
                vector<vector<vector<int>>> possibleMoves = possibleCellMoves(currentCell);
                if(!possibleMoves.empty()) // If cell can move
                    repositionCell(currentCell,possibleMoves[0],possibleMoves[1]);
            }
        }
    }
}

vector<vector<vector<int>>> PredatorPrey::possibleCellMoves(Cell cell){
    /*
     * returns all possible moves
     * seperated in fist nourishmentCells
     * and second freeCells
     * otherwise returns an empty vector
     */
    const int x = cell.getX();
    const int y = cell.getY();
    vector<vector<int>> nourishment;
    vector<vector<int>> freeNeighbours;

    for(int j = -1; j < 2;j++){ // look at adjacent cells
        if(y + j < 0 || j + y >= gameSize) continue; // y boundaries
        for(int i = -1; i < 2;i++){
            if(i + x < 0 || i + x >= gameSize) continue; // x boundaries
            if(j == 0 && i == 0) continue; // skip own cell
            Cell neighbour = this->getCell(x+i, y+j);
            bool predCanEat = cell.isPredator() && neighbour.isPrey();
            bool preyCanEat = cell.isPrey() && neighbour.isFood();
            if(predCanEat || preyCanEat){ // If Predator can eat Prey OR Prey can eat Food
                vector<int> relNeighbour = {i,j};
                nourishment.push_back(relNeighbour);
            }else if(cell.isPrey() && neighbour.isPredator()){ // Prey can't move
                cell.decreaseLifetime();
                return {};
            }else if(neighbour.isDead()){
                vector<int> relFreeSpace = {i,j};
                freeNeighbours.push_back(relFreeSpace);
            }
        }
    }
    return {nourishment,freeNeighbours};
}

void PredatorPrey::repositionCell(Cell cell, vector<vector<int>> nourishment, vector<vector<int>> freeNeighbour){
    /*
     * moves given cell to its possible
     * new position, favouring the cells with
     * nourishment first.
     * If given cell dies, it is removed from the game
     */
    const int x = cell.getX();
    const int y = cell.getY();
    int newX = 0;
    int newY = 0;

    cell.decreaseLifetime();
    if(!nourishment.empty()){                   // If cell can eat a neighbour
        if(cell.isPredator()) amountOfPrey--;   // If Predator eats a Prey, reduce the PreyCounter
        int foodIdx = rand() % nourishment.size();
        newX = x + nourishment[foodIdx][0];
        newY = y + nourishment[foodIdx][1];
        cell.setLifetime(this->maxLifetime);
    }else if(!freeNeighbour.empty()){           // If cell has a free neighbour to move to
        int freeNeighbourIdx = rand() % freeNeighbour.size();
        newX = x + freeNeighbour[freeNeighbourIdx][0];
        newY = y + freeNeighbour[freeNeighbourIdx][1];
    }else{
        return;
    }

    // If the cell lifetime reached zero.
    if(cell.lostItsLife()){
        if(field[y * gameSize + x].isPredator())
            amountOfPredators--;
        else if(field[y * gameSize + x].isPrey())
            amountOfPrey--;
        killCell(x,y);
        return;
    }

    //move cell to newX,newY position
    QPoint* newPos = new QPoint(newX, newY);
    cell.setPos(newPos);
    cell.setChecked(true);
    killCell(x,y);
    setCell(cell);
}

void PredatorPrey::clear(){
    /*
     * clears the game
     * and fills the field with
     * dead cells
     */
    field.clear();
    field.reserve(gameSize*gameSize);
    this->amountOfPredators=0;
    this->amountOfPrey=0;
    this->amountOfFood=0;
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            Cell deadCell(new QPoint(x,y));
            field.push_back(deadCell);
        }
    }
}

void PredatorPrey::newGame(){
    /*
     * initializes a new game
     * with the amount of cells of one type
     * linked to the board size and its
     * specific spawn rate
     */
    clear();
    int dim= gameSize*gameSize;
    this->amountOfPredators = this->predatorSpawnRate*dim;
    this->amountOfPrey = this->preySpawnRate*dim;
    this->amountOfFood = this->foodSpawnRate*dim;
    srand((int) time(0));
    newGameCellPosition(-1,FOOD,amountOfFood);
    newGameCellPosition(maxLifetime,PREY,amountOfPrey);
    newGameCellPosition(maxLifetime,PREDATOR,amountOfPredators);
}

void PredatorPrey::newGameCellPosition(int lifetime, int type, int amount){
    /*
     * random positions cells of
     * one specific type
     * onto the board.
     */
    int count = 0;
    while(count < amount){
        int x = rand() % gameSize;
        int y = rand() % gameSize;
        if(!field[y*gameSize+x].isDead()) continue;
        Cell cell(new QPoint(x,y),lifetime,type);
        field[y*gameSize+x] = cell;
        count++;
    }
}

void PredatorPrey::killCell(int x, int y){
    /*
     * sets cell on given x,y to a dead cell
     */
    setCell(Cell(new QPoint(x,y)));
}

bool PredatorPrey::finish(bool endText){
    /*
     * evaluates if one type has won.
     * endText->true if the win message
     * should be shown
     */
    QMessageBox msg;
    if((amountOfPrey + amountOfPredators) == 0){
        msg.setText("Draw... Neither Predator nor Prey have won!");
    } else if(amountOfPrey == 0){
        msg.setText("Predators win, long live the Predators!");
    } else if(amountOfPredators == 0){
        msg.setText("The Prey has won, shall they never be eaten again");
    } else{
        return false;
    }
    if(endText)
        msg.exec();
    return true;
}

void PredatorPrey::uncheckCells(){
    /*
     * frees every cell on the board
     * so they can be checked again
     * in the next tick
     */
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            field[y * gameSize + x].setChecked(false);
        }
    }
}

void PredatorPrey::increasePredatorCount(){
    this->amountOfPredators++;
}

void PredatorPrey::increasePreyCount(){
    this->amountOfPrey++;
}

void PredatorPrey::decreasePredatorCount(){
    this->amountOfPredators--;
}

void PredatorPrey::decreasePreyCount(){
    this->amountOfPrey--;
}

void PredatorPrey::setGameSize(int gm){
    this->gameSize = gm;
}

void PredatorPrey::setCell(Cell newCell){
    field[newCell.getPos()->y() * gameSize + newCell.getPos()->x()] = newCell;
}

void PredatorPrey::setMaxLifetime(int maxLifetime){
    this->maxLifetime = maxLifetime;
}

int PredatorPrey::getMaxLifetime(){
    return this->maxLifetime;
}

int PredatorPrey::getGamesize(){
    return this->gameSize;
}

Cell PredatorPrey::getCell(const int x, const int y){
    return field[y * gameSize + x];
}
