#include "snakeBodyPart.h"

SnakeBodyPart::SnakeBodyPart(QPoint *pos, SnakeBodyPart *parent=nullptr){
    this->pos = pos;
    this->parent = parent;
}

void SnakeBodyPart::moveToParent(){
    /*
     * Moves snake part to the position of its parent
     */
    this->pos = this->parent->pos;
}

void SnakeBodyPart::setParent(SnakeBodyPart *parent){
    this->parent = parent;
}

SnakeBodyPart* SnakeBodyPart::getParent(){
    return parent;
}

QPoint SnakeBodyPart::getPos(){
    return *pos;
}

void SnakeBodyPart::setPos(QPoint *pos){
    this->pos = pos;
}
