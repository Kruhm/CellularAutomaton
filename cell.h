#ifndef CELL_H
#define CELL_H

#include <QPoint>

class Cell
{
private:
    QPoint* pos;
    int lifetime;
    int status;

public:
    Cell(QPoint* pos, int lifetime, int status);

    void setPos(QPoint* pos);
    void setLiftime(int lifetime);
    void setstate(int status);
    QPoint* getPos();
    int getLiftime();
    int getStatus();
};

#endif // CELL_H
