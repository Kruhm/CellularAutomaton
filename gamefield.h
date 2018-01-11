#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "gameoflife.h"
#include "snakeBodyPart.h"
#include "predatorvictim.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QColor>
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
    PredatorVictim* predatorPrey;
    QBrush* brush;
    QBrush* bgBrush;
    QPen* pen;
    int currentCellMode;
    int currentGameMode;
    bool mouseDrag;
public:
    GameField(GameOfLife* gol, PredatorVictim* pP, QGraphicsView *parent = 0);
    ~GameField();
    void drawSnakeField(int gameSize, SnakeBodyPart* snakeTail, QPoint* food);
    void drawGameOfLifeCell(int x,int y, int rectSize, bool cellState);
    void drawPedatorPreyField(int gameSize, PredatorVictim* predatorPrey);
    void clear();
    void setCurrentCellMode(int cm);
    void setCurrentGameMode(int gm);
    void showField();
    void mouseIsDragged();
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // GAMEFIELD_H
