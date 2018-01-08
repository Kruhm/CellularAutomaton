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

public:
    PredatorVictim(int gameSize);
    void createRandomGame();
    void fillField();
    void moveCell();
    void uncheckCells();
    void preyMovement(Cell currentCell);
    void predatorMovement(Cell currentCell);
    void moveToNewCell(Cell currentCell, vector<vector<int>> nourishment, vector<vector<int>> freeSpace);
    Cell getCell(int x, int y);
    void setCell(Cell newCell);
};

#endif // PREDATORVICTIM_H
