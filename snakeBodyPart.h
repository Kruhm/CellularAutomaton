#ifndef SNAKEBODYPART_H
#define SNAKEBODYPART_H

#include <QPoint>

class SnakeBodyPart{

private:
    QPoint *pos;
    SnakeBodyPart *parent;
public:
    SnakeBodyPart(QPoint *pos, SnakeBodyPart *parent);

    void setPos(QPoint *pos);
    void setParent(SnakeBodyPart *parent);
    void moveToParent();
    QPoint getPos();
    SnakeBodyPart* getParent();
};

#endif // SNAKEBODYPART_H
