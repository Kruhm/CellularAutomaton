#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "gameoflife.h"
#include "snake.h"
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
    Snake* snake;
    PredatorVictim* predatorPrey;
    QBrush* brush;
    QBrush* bgBrush;
    QPen* pen;
    int rectSize;
    int currentCellMode;
    int currentGameMode;
    bool mouseDrag;

    void adjustingPredPreyCounter(Cell cell);
public:
    GameField(GameOfLife* gol,Snake* snake, PredatorVictim* pP, QGraphicsView *parent = 0);
    ~GameField();
    void drawSnakeField(int gameSize);
    void drawGameOfLifeCell();
    void drawPedatorPreyField();
    void clear();
    void setCurrentCellMode(int cm);
    void setCurrentGameMode(int gm);
    void showField();
    void cellUpdate();
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // GAMEFIELD_H
