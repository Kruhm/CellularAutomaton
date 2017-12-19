#ifndef PREDATORVICTIM_H
#define PREDATORVICTIM_H

#include <ctime>
#include <vector>
#include <random>
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
    Cell getCell(int x, int y);
};

#endif // PREDATORVICTIM_H
