#include "cell.h"

Cell::Cell(QPoint* pos){
    /*
     * Definition of a dead Cell
     */
    this->pos = pos;
    this->lifetime = -2;
    this->status = 4;
}

Cell::Cell(QPoint* pos, int lifetime, int status){
    /*
     * Definition of a Cell for the game Predator - Victim;
     * pos -> position of cell
     * lifetime -> lifetime of cell, -1 for infinite lifetime
     * Status -> 1: Predator, 2: Prey, 3: Food
     */
    this->pos = pos;
    this->lifetime = lifetime;
    this->status = status;
}

void Cell::setPos(QPoint *pos){
    this->pos = pos;
}

void Cell::setLiftime(int lifetime){
    this->lifetime = lifetime;
}

void Cell::setstate(int status){
    this->status = status;
}

QPoint *Cell::getPos(){
    return pos;
}

int Cell::getLiftime(){
    return lifetime;
}

bool Cell::isPredator(){
    return status == 1;
}

bool Cell::isPrey(){
    return status == 2;
}

bool Cell::isFood(){
    return status == 3;
}


