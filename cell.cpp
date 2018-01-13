#include "cell.h"

Cell::Cell(QPoint* pos){
    /*
     * Definition of a dead Cell
     */
    this->pos = pos;
    this->lifetime = -2;
    this->status = 4;
    this->checked = false;
}

Cell::Cell(QPoint* pos, int lifetime, int status){
    /*
     * Definition of a Cell for the game Predator - Victim;
     * pos -> position of cell
     * lifetime -> lifetime of cell, -1 for infinite lifetime
     * Status -> 1: Predator, 2: Prey, 3: Food
     * Checked -> if cell is already looked at
     */
    this->pos = pos;
    this->lifetime = lifetime;
    this->status = status;
    this->checked = false;
}

bool Cell::isChecked(){
    return checked;
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

bool Cell::isDead(){
    return status == 4;
}

bool Cell::lostItsLife(){
    return lifetime == 0;
}

void Cell::decreaseLifetime(){
    this->lifetime--;
}

void Cell::setPos(QPoint *pos){
    this->pos = pos;
}

void Cell::setLifetime(int lifetime){
    this->lifetime = lifetime;
}

void Cell::setstate(int status){
    this->status = status;
}

void Cell::setChecked(bool checked){
    this->checked = checked;
}

int Cell::getX(){
    return this->pos->x();
}

int Cell::getY(){
    return this->pos->y();
}

int Cell::getStatus(){
    return this->status;
}

QPoint *Cell::getPos(){
    return pos;
}

int Cell::getLiftime(){
    return lifetime;
}
