#include "predatorvictim.h"

PredatorVictim::PredatorVictim(const int gameSize){
    field.reserve(gameSize*gameSize);
    this->gameSize = gameSize;
}

void PredatorVictim::createRandomGame(){
    int dim = gameSize*2;
    int amountOfPreyAndPredator = 0;
    int amountOfFood = 0;
    srand((int) time(0));
    while(amountOfFood < 50){
        int x = rand() % dim;
        int y = rand() % dim;
        Cell food(new QPoint(x,y),-1,3);
        field.at(y*gameSize+x) = food;
        amountOfFood++;
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
        field.at(preyY*gameSize+preyX) = prey;
        field.at(predatorY*gameSize+predatorX) = predator;
        amountOfPreyAndPredator++;
    }
}
