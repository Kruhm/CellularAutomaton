#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QThread>
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
#include <QTimer>

#include "snake.h"
#include "gameoflife.h"
#include "gamefield.h"

class CAbase : public QWidget
{
    Q_OBJECT


private:
    QTimer *timer;

    //Games
    GameOfLife* gameOfLife;
    Snake* snakeTail;
    Snake* snakeHead;

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

    //Buttons
    QPushButton* startBtn;
    QPushButton* stopBtn;
    QPushButton* clearBtn;
    QPushButton* changeSizeBtn;

    //gameField
    GameField* gameField;

    void test();

public slots:
    void paintEvent(QPaintEvent *event);
    void evolutionChoice();
    void onStartBtnClicked();
    void onPauseBtnClicked();
    void onClearBtnClicked();
    void onChangeBtnClicked();
    void onUniverseSizeChanged();
    void onIntervalValueChanged();

public:
    CAbase(QWidget *parent = 0);
    ~CAbase();
    void setupUI();
    void doTheSnakeThing();
    void drawField(const int dim);
};

#endif // GAMEWIDGET_H
