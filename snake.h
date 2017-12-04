#ifndef SNAKE_H
#define SNAKE_H

#include <ctime>
#include <QMessageBox>
#include "snakeBodyPart.h"

class Snake{
private:
    int direction;
    bool movedOnTick;
    bool isEating;

    SnakeBodyPart* tail;
    SnakeBodyPart* head;

    QPoint* food;

public:
    Snake(int DIM);
    void eat();
    void move(int DIM);
    void spawnFood(int DIM);
    void die();
    void destroy();
    void create();
    void reset();
    void setDirection(int direction);
    void setIsEating(bool isEating);
    void setMovedOnTick(bool movedOnTick);

    SnakeBodyPart* getTail() const;
    QPoint* getFood() const;
    int getDirection();
    bool getIsEating();
    bool getMovedOnTick();
    bool collision(int dim);

};

#endif // SNAKE_H
