#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "gameoflife.h"
#include "snakeBodyPart.h"
#include "predatorvictim.h"
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
    GameOfLife* gameOfLife;
    QBrush* brush;
    QBrush* bgBrush;
    QPen* pen;
public:
    GameField(GameOfLife* gol, PredatorVictim* pP, QGraphicsView *parent = 0);
    ~GameField();
    void drawSnakeField(int gameSize, SnakeBodyPart* snakeTail, QPoint* food);
    void drawGameOfLifeCell(int x,int y, int rectSize, bool cellState);
    void drawPedatorPreyField(int gameSize, PredatorVictim* predatorPrey);
    void clear();
    void showField();
private slots:
    void mousePressEvent(QMouseEvent *event);
};

#endif // GAMEFIELD_H
