#include "snake.h"

Snake::Snake(QPoint *pos, Snake *parent=nullptr){
    this->pos = pos;
    this->parent = parent;
}

void Snake::evolve(){
    /*
     * Moves snake part to the position of its parent
     */
    this->pos = this->parent->pos;
}

void Snake::setParent(Snake *parent){
    this->parent = parent;
}

Snake* Snake::getParent(){
    return parent;
}

QPoint Snake::getPos(){
    return *pos;
}

void Snake::setPos(QPoint *pos){
    this->pos = pos;
}
