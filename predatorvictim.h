#ifndef PREDATORVICTIM_H
#define PREDATORVICTIM_H

#include <ctime>
#include <vector>
#include <random>
#include <QDebug>
#include "cell.h"

using namespace std;
class PredatorVictim{

private:
    vector<Cell> field;
    int gameSize;
    int maxLifetime;

public:
    PredatorVictim(int gameSize, int maxLifetime);
    void createRandomGame();
    void fillField();
    void cellDies(int x, int y);
    void moveCell();
    void uncheckCells();
    void preyMovement(Cell currentCell);
    void predatorMovement(Cell currentCell);
    void moveToNewCell(Cell currentCell, vector<vector<int>> nourishment, vector<vector<int>> freeSpace);
    void clearField();
    Cell getCell(int x, int y);
    void setCell(Cell newCell);
    void setMaxLifetime(int maxLifetime);
};

#endif // PREDATORVICTIM_H
