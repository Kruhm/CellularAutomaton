#ifndef SNAKE_H
#define SNAKE_H
#include "snakeBodyPart.h"

class snake{
private:
    int direction;
    bool movedOnTick;

    SnakeBodyPart* tail;
    SnakeBodyPart* head;

    QPoint food;

public:
    snake();
    void eat();
    void move();
    void spawnFood();
    void die();
    void destroy();
    void create();
    void reset();
    bool collision();
};

#endif // SNAKE_H
