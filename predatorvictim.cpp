#include "predatorvictim.h"

PredatorVictim::PredatorVictim(const int gameSize){
    field.reserve(gameSize*gameSize); // allocate memory to fit the field size
    this->gameSize = gameSize;
    fillField();
    createRandomGame();
}

void PredatorVictim::fillField(){
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            Cell deadCell(new QPoint(x,y));
            field.push_back(deadCell);
        }
    }
}

void PredatorVictim::createRandomGame(){
    int dim = gameSize;
    int amountOfPreyAndPredator = 0;
    int amountOfFood = 0;
    srand((int) time(0));
    while(amountOfFood < 50){
        int x = rand() % dim;
        int y = rand() % dim;
        Cell food(new QPoint(x,y),-1,3);
        field[y*gameSize+x] = food;
        amountOfFood++;
        qDebug() << amountOfFood;
    }

    while (amountOfPreyAndPredator < 100) {
        int preyX = rand() % dim;
        int preyY = rand() % dim;
        int predatorX = rand() % dim;
        int predatorY = rand() % dim;
        int predatorLife = (rand() % 100) + 1;
        int preyLife = (rand() % 100) + 1;
        Cell prey(new QPoint(preyX, preyY),preyLife,2);
        Cell predator(new QPoint(predatorX,predatorY),predatorLife,1);
        field[preyY*gameSize+preyX] = prey;
        field[predatorY*gameSize+predatorX] = predator;
        amountOfPreyAndPredator++;
        qDebug() << amountOfPreyAndPredator;
    }
}

void PredatorVictim::moveCell(){
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            Cell currentCell = getCell(x,y);
            if(!currentCell.isChecked()){
                if(currentCell.isPrey()){
                    bool hasPredator = false;
                    vector<vector<int>> hasFoods;
                    for(int j = -1; j < 2;j++){
                        if(y + j < 0 || j + y >= gameSize) continue; // y boundaries
                        for(int i = -1; i < 2;i++){
                            if(j == 0 || i == 0){continue;}
                            else if(i + x < 0 || i + x >= gameSize) continue; // x boundaries
                            Cell neighbour = getCell(x+j,y+i);
                            if(neighbour.isPredator()){
                                hasPredator = true;
                            } else if(neighbour.isFood()){
                                vector<int> food = {j,i};
                                hasFoods.push_back(food);
                            }
                        }
                    } // end mid for
                    if(!hasPredator){
                        if(hasFoods.empty()){

                        }else{
                            srand((int) time(0));
                            bool hasMoved = false;
                            while(!hasMoved){
                                int i = rand() % 3 - 1;
                                int j = rand() % 3 - 1;
                                if(x + i < 0 || x + i >= gameSize || y + j < 0 || y + j >= gameSize || (i == 0 && j == 0)) continue; // Borders and same position
                                int newX = currentCell.getPos()->x() + i;
                                int newY = currentCell.getPos()->y() + j;
                                QPoint* newPos = new QPoint(newX, newY);
                                currentCell.setPos(newPos);
                                hasMoved = true;
                            }
                        }
                        currentCell.setChecked(true);
                        setCell(currentCell);
                    }
                    //dont move
                }
            }
        }
    } // end top for
}


void PredatorVictim::uncheckCells(){
    qDebug() << "uncheck";
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
