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
    float preySpawnRate;
    float predatorSpawnRate;
    float foodSpawnRate;
    int gameSize;
    int maxLifetime;
    int amountOfPrey;
    int amountOfPredators;
    int amountOfFood;

    vector<vector<vector<int>>> possibleCellMoves(Cell cell);
    void repositionCell(Cell currentCell, vector<vector<int>> nourishment, vector<vector<int>> freeSpace);

public:
    PredatorVictim(int gameSize, int maxLifetime);
    void moveCells();
    void clear();
    void newGame();
    void cellDies(Cell cell);
    void killCell(int x, int y);
    bool finish(bool endText=true);
    void uncheckCells();
    void increasePreyCount();
    void increasePredatorCount();
    void decreasePreyCount();
    void decreasePredatorCount();
    void setGameSize(int gm);
    void setCell(Cell newCell);
    void setMaxLifetime(int maxLifetime);
    int getGamesize();
    int getMaxLifetime();
    Cell getCell(int x, int y);
};

#endif // PREDATORVICTIM_H
