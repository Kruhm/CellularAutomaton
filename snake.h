#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>

class Snake
{
private:
    QPoint *pos;
    Snake *parent;
public:
    Snake(QPoint *pos, Snake *parent);

    void setPos(QPoint *pos);
    void setParent(Snake *parent);
    void evolve();
    QPoint getPos();
    Snake* getParent();
};

#endif // SNAKE_H
