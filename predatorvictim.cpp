#include "predatorvictim.h"

PredatorVictim::PredatorVictim(const int gameSize, const int lifetime){
    field.reserve(gameSize*gameSize); // allocate memory to fit the field size
    this->gameSize = gameSize;
    this->maxLifetime = lifetime;
    clearField();
}

void PredatorVictim::clearField(){
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

bool PredatorVictim::finish(bool endText){
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

void PredatorVictim::createRandomGame(){
    clearField();
    int dim = gameSize;
    this->amountOfPredators = (gameSize*gameSize)*0.01;
    this->amountOfFood = (gameSize*gameSize)*0.1;
    this->amountOfPrey = (gameSize*gameSize)*0.05;
    srand((int) time(0));
    int foodIdx = 0;
    while(foodIdx < this->amountOfFood){
        int x = rand() % dim;
        int y = rand() % dim;
        Cell food(new QPoint(x,y),-1,3);
        if(!field[y*gameSize+x].isDead()) {continue;}
        field[y*gameSize+x] = food;
        foodIdx++;
    }
    int preyIdx = 0;
    while(preyIdx < this->amountOfPrey){
        int preyX = rand() % dim;
        int preyY = rand() % dim;
        if(!field[preyY*gameSize+preyX].isDead()){continue;}
        Cell prey(new QPoint(preyX, preyY),maxLifetime,2);
        field[preyY*gameSize+preyX] = prey;
        preyIdx++;
    }

    int predIdx = 0;
    while(predIdx < this->amountOfPredators){
        int predatorX = rand() % dim;
        int predatorY = rand() % dim;
        if(!field[predatorY*gameSize+predatorX].isDead()) {continue;}
        Cell predator(new QPoint(predatorX,predatorY),maxLifetime,1);
        field[predatorY*gameSize+predatorX] = predator;
        predIdx++;
    }
}

void PredatorVictim::cellDies(int x, int y){
    if(field[y * gameSize + x].isPredator())
        amountOfPredators--;
    else if(field[y * gameSize + x].isPrey())
        amountOfPrey--;
    field[y * gameSize + x] = Cell(new QPoint(x,y));
}

void PredatorVictim::moveCell(){
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            Cell currentCell = getCell(x,y);
            if(!currentCell.isChecked() && !currentCell.isDead() && !currentCell.isFood()){
                srand((int) time(0) + rand());
                movement(currentCell);
            }
        }
    } // end top for
}

void PredatorVictim::movement(Cell cell){
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
            if(predCanEat || preyCanEat){ // Predator eats Prey
                vector<int> relNeighbour = {i,j};
                nourishment.push_back(relNeighbour);
            }else if(cell.isPrey() && neighbour.isPredator()){
                cell.decrementLifetime();
                return;
            }else if(neighbour.isDead()){
                vector<int> relFreeSpace = {i,j};
                freeNeighbours.push_back(relFreeSpace);
            }
        }
    }
    moveToNewCell(cell,nourishment,freeNeighbours);
}

void PredatorVictim::moveToNewCell(Cell currentCell, vector<vector<int>> nourishment, vector<vector<int>> freeSpace){
    int x = currentCell.getPos()->x();
    int y = currentCell.getPos()->y();
    int newX = 0;
    int newY = 0;
    bool moves = true;
    if(!nourishment.empty()){
        if(currentCell.isPredator()) amountOfPrey--;
        int relFoodPosIndex = rand() % nourishment.size();
        newX = x + nourishment[relFoodPosIndex][0];
        newY = y + nourishment[relFoodPosIndex][1];
        currentCell.setLifetime(this->maxLifetime);
    }else if(!freeSpace.empty()){
        int relFreeNeighbourPos = rand() % freeSpace.size();
        newX = x + freeSpace[relFreeNeighbourPos][0];
        newY = y + freeSpace[relFreeNeighbourPos][1];
        currentCell.decrementLifetime();
    } else {
        moves = false;
        currentCell.decrementLifetime();
    }
    if(moves){
        QPoint* newPos = new QPoint(newX, newY);
        currentCell.setPos(newPos);
        currentCell.setChecked(true);
        setCell(Cell(new QPoint(x,y)));
        setCell(currentCell);
    }
    if(currentCell.lostItsLife()){
        cellDies(newX,newY);
    }
}

void PredatorVictim::uncheckCells(){
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            field[y * gameSize + x].setChecked(false);
        }
    }
}

Cell PredatorVictim::getCell(const int x, const int y){
    return field[y * gameSize + x];
}

void PredatorVictim::setCell(Cell newCell){
    field[newCell.getPos()->y() * gameSize + newCell.getPos()->x()] = newCell;
}

void PredatorVictim::setMaxLifetime(int maxLifetime){
    this->maxLifetime = maxLifetime;
}

int PredatorVictim::getMaxLifetime(){
    return this->maxLifetime;
}

int PredatorVictim::getGamesize(){
    return this->gameSize;
}

void PredatorVictim::setGameSize(int gm){
    this->gameSize = gm;
}

void PredatorVictim::decreasePredatorCount(){
    this->amountOfPredators--;
}

void PredatorVictim::decreasePreyCount(){
    this->amountOfPrey--;
}

void PredatorVictim::incrementPredatorCount(){
    this->amountOfPredators++;
}

void PredatorVictim::incrementPreyCount(){
    this->amountOfPrey++;
}
