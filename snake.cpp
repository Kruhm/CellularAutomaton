#include "snake.h"

Snake::Snake(QPoint *pos, Snake *parent=nullptr)
{
    this->pos = pos;
    this->parent = parent;
}

Snake* Snake::getParent(){
    return parent;
}

void Snake::evolve(){
    this->pos = this->parent->pos;
}

void Snake::setParent(Snake *parent){
    this->parent = parent;
}

QPoint Snake::getPos(){
    return *pos;
}

void Snake::setPos(QPoint *pos){
    this->pos = pos;
}
