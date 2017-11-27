#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>

class snake
{
private:
    QPoint *pos;
    snake *parent;
public:
    snake(QPoint *pos, snake *parent);
    void setPos(QPoint *pos);
    QPoint getPos();
    void setParent(snake *parent);
    snake getParent();
    void evolve();
};

#endif // SNAKE_H
