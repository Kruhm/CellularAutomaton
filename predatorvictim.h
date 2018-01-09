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

public:
    PredatorVictim(int gameSize, int maxLifetime);
    void createRandomGame();
    void cellDies(int x, int y);
    void moveCell();
    void uncheckCells();
    void preyMovement(Cell currentCell);
    void predatorMovement(Cell currentCell);
    void moveToNewCell(Cell currentCell, vector<vector<int>> nourishment, vector<vector<int>> freeSpace);
    void clearField();
    bool finish(bool endText=true);
    int getMaxLifetime();
    void setGameSize(int gm);
    int getGamesize();
    Cell getCell(int x, int y);
    void setCell(Cell newCell);
    void setMaxLifetime(int maxLifetime);
};

#endif // PREDATORVICTIM_H
