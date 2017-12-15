#include "cell.h"

Cell::Cell(QPoint* pos, int lifetime, int status){
    this->pos = pos;
    this->lifetime = lifetime;
    this->status = status;
}
