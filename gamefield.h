#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "cabase.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPointF>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>

class GameField : public QGraphicsView{

private:
    QGraphicsScene* field;
    CAbase* gameOfLife;
    QBrush* brush;
    QBrush* bgBrush;
    QPen* pen;
public:
    GameField(CAbase* gol, QGraphicsView *parent = 0);
    ~GameField();
    void drawFieldCell(int x,int y, int rectSize, bool cellState);
    void clear();
    void showField();
private slots:
    void mousePressEvent(QMouseEvent *event);
};

#endif // GAMEFIELD_H
