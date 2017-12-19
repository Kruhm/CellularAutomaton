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
};

#endif // PREDATORVICTIM_H
