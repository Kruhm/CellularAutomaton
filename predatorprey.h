#ifndef PREDATORPREY_H
#define PREDATORPREY_H

#include <ctime>
#include <vector>
#include <random>
#include <QDebug>
#include <QMessageBox>
#include "cell.h"

using namespace std;
class PredatorPrey{

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
    const int PREDATOR = 1;
    const int PREY = 2;
    const int FOOD= 3;
    const int DEAD= 4;

    vector<vector<vector<int>>> possibleCellMoves(Cell cell);
    Cell repositionCell(Cell currentCell, vector<vector<int>> nourishment, vector<vector<int>> freeSpace);

public:
    PredatorPrey(int gameSize, int maxLifetime);
    void moveCells();
    void clear();
    void newGame();
    void newGameCellPosition(int liftime, int cellState, int count);
    void cellIsDying(Cell cell);
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

#endif // PREDATORPREY_H
