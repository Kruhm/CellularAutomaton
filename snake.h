#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>

class snake
{
private:
    QPoint *pos;
    snake *parent;
public:
    snake(QPoint *pos, snake *parent=nullptr);
    void setPos(QPoint *pos);
    QPoint getPos();
    void setParent(QPoint *parent);
    QPoint getParent();
};

#endif // SNAKE_H
