#ifndef PREDATORVICTIM_H
#define PREDATORVICTIM_H

#include <ctime>
#include <vector>
#include <random>
#include <QDebug>
#include <QMessageBox>
#include "cell.h"

using namespace std;
class PredatorVictim{

private:
    vector<Cell> field;
    int gameSize;
    int maxLifetime;
    int amountOfPrey;
    int amountOfPredators;
    int amountOfFood;

    void movement(Cell cell);
    void moveToNewCell(Cell currentCell, vector<vector<int>> nourishment, vector<vector<int>> freeSpace);

public:
    PredatorVictim(int gameSize, int maxLifetime);
    void createRandomGame();
    void cellDies(int x, int y);
    void moveCell();
    void uncheckCells();
    void preyMovement(Cell currentCell);
    void predatorMovement(Cell currentCell);
    void clearField();
    bool finish(bool endText=true);
    int getMaxLifetime();
    void setGameSize(int gm);
    int getGamesize();
    void incrementPreyCount();
    void incrementPredatorCount();
    void decreasePreyCount();
    void decreasePredatorCount();
    Cell getCell(int x, int y);
    void setCell(Cell newCell);
    void setMaxLifetime(int maxLifetime);
};

#endif // PREDATORVICTIM_H
