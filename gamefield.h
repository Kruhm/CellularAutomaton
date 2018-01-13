#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "gameoflife.h"
#include "snake.h"
#include "predatorprey.h"
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
    PredatorPrey* predatorPrey;
    QBrush* brush;
    QBrush* bgBrush;
    QPen* pen;
    int rectSize;
    int currentCellMode;
    int currentGameMode;
    bool mouseDrag;

    void adjustingPredPreyCounter(Cell cell);
public:
    GameField(QGraphicsView *parent = 0);
    GameField(GameOfLife* gol,Snake* snake, PredatorPrey* pP, QGraphicsView *parent = 0);
    ~GameField();
    void addGame(GameOfLife* gameOfLife);
    void addGame(Snake* snake);
    void addGame(PredatorPrey* predatorPrey);
    void addGame(GameOfLife* gameOfLife, Snake* snake, PredatorPrey* predatorPrey);
    void drawSnakeField(int gameSize);
    void drawGameOfLifeField();
    void drawPedatorPreyField();
    void drawRandom();
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
