#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <ctime>
#include <QThread>
#include <QKeyEvent>
#include <QtCore>
#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QSpinBox>
#include <QComboBox>
#include <QMessageBox>
#include <QTimer>

#include "snakeBodyPart.h"
#include "gameoflife.h"
#include "gamefield.h"

class CAbase : public QWidget
{
    Q_OBJECT


private:
    int snakeDirection;
    bool movedOnTick;

    QTimer *timer;

    //Gamesses
    GameOfLife* gameOfLife;
    SnakeBodyPart* snakeTail;
    SnakeBodyPart* snakeHead;
    QPoint* food;

    //Layouts
    QHBoxLayout* mainLayout;
    QGridLayout* menuSide;

    //Labels
    QLabel* universeSizeLbl;
    QLabel* gameIntervalLbl;

    //SpinBoxes
    QSpinBox* universeSize;
    QSpinBox* gameInterval;

    //ComboBox
    QComboBox* gameMode;
    //QString gameModeList[] = new QString[2];

    //Buttons
    QPushButton* startBtn;
    QPushButton* stopBtn;
    QPushButton* clearBtn;

    //gameField
    GameField* gameField;

    void test();

public slots:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void evolutionChoice();
    void onStartBtnClicked();
    void onPauseBtnClicked();
    void onClearBtnClicked();
    void onUniverseSizeChanged();
    void onIntervalValueChanged();

public:
    CAbase(QWidget *parent = 0);
    ~CAbase();
    void setupUI();
    void eatFood();
    void spawnFood();
    void doTheSnakeThing();
    void createSnake();
    void destroySnake();
    void snakeCollision();
    void snakeDied();
    void snakeReset();
    void drawField(const int dim);
};

#endif // GAMEWIDGET_H
