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

    int getLiftime();
    void decrementLifetime();
    void setPos(QPoint* pos);
    void setLiftime(int lifetime);
    void setstate(int status);
    void setChecked(bool checked);
    bool lostItsLife();
    bool isChecked();
    bool isDead();
    bool isPredator();
    bool isPrey();
    bool isFood();
    QPoint* getPos();
};

#endif // CELL_H
