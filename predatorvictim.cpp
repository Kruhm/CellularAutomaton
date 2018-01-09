#include "predatorvictim.h"

PredatorVictim::PredatorVictim(const int gameSize, const int lifetime){
    field.reserve(gameSize*gameSize); // allocate memory to fit the field size
    this->gameSize = gameSize;
    this->maxLifetime = lifetime;
    this->amountOfPredators = 25;
    this->amountOfFood = 100;
    this->amountOfPrey = 75;
    clearField();
}

void PredatorVictim::clearField(){
    vector<Cell> newField;
    newField.reserve(gameSize*gameSize);
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            Cell deadCell(new QPoint(x,y));
            newField.push_back(deadCell);
        }
    }
    field = newField;
}

bool PredatorVictim::finish(bool endText){
    QMessageBox msg;
    int countPrey = 0;
    int countPred = 0;
    for(int i = 0; i < field.size();i++){
        if(field[i].isPrey()){
            countPrey++;
        }else if(field[i].isPredator()){
            countPred++;
        }
    }
    if((countPrey + countPred) == 0){
        msg.setText("Draw... Neither Predator or Prey have won!");
    } else if(countPrey == 0){
        msg.setText("Predators win, long live the Predators!");
    } else if(countPred == 0){
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

    int pred = 0;
    while(pred < this->amountOfPredators){
        int predatorX = rand() % dim;
        int predatorY = rand() % dim;
        if(!field[predatorY*gameSize+predatorX].isDead()) {continue;}
        Cell predator(new QPoint(predatorX,predatorY),maxLifetime,1);
        field[predatorY*gameSize+predatorX] = predator;
        pred++;
    }
}

void PredatorVictim::cellDies(int x, int y){
    field[y * gameSize + x] = Cell(new QPoint(x,y));
}

void PredatorVictim::moveCell(){
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            Cell currentCell = getCell(x,y);
            if(!currentCell.isChecked() && !currentCell.isDead() && !currentCell.isFood()){
                srand((int) time(0) + rand());
                if(currentCell.isPredator()){
                    predatorMovement(currentCell);
                } else if(currentCell.isPrey()){
                    preyMovement(currentCell);
                }
            }
        }
    } // end top for
}

void PredatorVictim::predatorMovement(Cell currentCell){
    const int x = currentCell.getPos()->x();
    const int y = currentCell.getPos()->y();
    vector<vector<int>> hasPrey;
    vector<vector<int>> freeNeighbour;
    for(int j = -1; j < 2;j++){ // look at neighbours
        if(y + j < 0 || j + y >= gameSize) continue; // y boundaries
        for(int i = -1; i < 2;i++){
            if(j == 0 && i == 0){continue;}
            else if(i + x < 0 || i + x >= gameSize) continue; // x boundaries
            Cell neighbour = getCell(x+i,y+j);
            if(neighbour.isPrey()){
                vector<int> relNeighbour = {i,j};
                hasPrey.push_back(relNeighbour);
            }else if(neighbour.isDead()){
                vector<int> relFreeSpace = {i,j};
                freeNeighbour.push_back(relFreeSpace);
            }
        }
    }
    moveToNewCell(currentCell,hasPrey,freeNeighbour);
}

void PredatorVictim::preyMovement(Cell currentCell){
    const int x = currentCell.getPos()->x();
    const int y = currentCell.getPos()->y();
    bool hasPredator = false;
    vector<vector<int>> hasFoods;
    vector<vector<int>> freeNeighbour;
    for(int j = -1; j < 2;j++){ // look at neighbours
        if(y + j < 0 || j + y >= gameSize) continue; // y boundaries
        for(int i = -1; i < 2;i++){
            if(j == 0 && i == 0){continue;}
            else if(i + x < 0 || i + x >= gameSize) continue; // x boundaries
            Cell neighbour = getCell(x+i,y+j);
            if(neighbour.isPredator()){
                hasPredator = true;
            }else if(neighbour.isFood()){
                vector<int> food = {i,j};
                hasFoods.push_back(food);
            } else if(neighbour.isDead()){
                vector<int> relNeighbour = {i,j};
                freeNeighbour.push_back(relNeighbour);
            }
        }
    } // end mid for
    if(!hasPredator){
        moveToNewCell(currentCell,hasFoods,freeNeighbour);
    }
    //dont move
}

void PredatorVictim::moveToNewCell(Cell currentCell, vector<vector<int>> nourishment, vector<vector<int>> freeSpace){
    int x = currentCell.getPos()->x();
    int y = currentCell.getPos()->y();
    int newX = 0;
    int newY = 0;
    bool moves = true;
    if(!nourishment.empty()){
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
