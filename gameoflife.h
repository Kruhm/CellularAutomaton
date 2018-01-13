#ifndef CABASE_H
#define CABASE_H

#include <QThread>
#include <QDebug>
#include <vector>

using namespace std;
class GameOfLife : public QThread{
private:
    //ATTRIBUTES
    int dim;
    int sleepTime;
    bool doEvolution;
    bool* currentState = new bool[0];
    bool* newState = new bool[0];

public:
    explicit GameOfLife(int dim, int sleepTime, bool doEvolution);
    ~GameOfLife();

    void run();
    void wipe();
    void createGlider();
    void setDim(int dim);
    void resize(int dim);
    void setDoEvolution(bool doEvolution);
    void setSleepTime(int sleepTime);
    void setCellState(int x, int y, bool state);
    void setNewCellState(int x, int y, bool state);
    int getDim();
    int convertToOneDimension(int x, int y);
    bool applyRules(int x, int y);
    bool inBounds(int x, int y);
    bool getCellState(int x, int y);
    bool getnewCellState(int x, int y);

signals:
    void evolve();
};

#endif // CABASE_H
