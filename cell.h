#ifndef CELL_H
#define CELL_H

#include <QPoint>

class Cell
{
private:
    QPoint* pos;
    int lifetime;
    int status;
    bool checked;
public:
    Cell(QPoint *pos);
    Cell(QPoint* pos, int lifetime, int status);

    bool isDead();
    bool isFood();
    bool isPrey();
    bool isPredator();
    bool isChecked();
    bool lostItsLife();
    void decreaseLifetime();
    int getX();
    int getY();
    int getStatus();
    int getLiftime();
    QPoint* getPos();
    void setPos(QPoint* pos);
    void setLifetime(int lifetime);
    void setstate(int status);
    void setChecked(bool checked);
};

#endif // CELL_H
