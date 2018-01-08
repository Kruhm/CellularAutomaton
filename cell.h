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

    void setPos(QPoint* pos);
    void setLiftime(int lifetime);
    void setstate(int status);
    void setChecked(bool checked);
    QPoint* getPos();
    int getLiftime();
    bool isChecked();
    bool isDead();
    bool isPredator();
    bool isPrey();
    bool isFood();
};

#endif // CELL_H
