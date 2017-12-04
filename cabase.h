#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <ctime>
#include <QThread>
#include <QPoint>
#include <QTimer>
#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

#include "snake.h"
#include "gameoflife.h"
#include "gamefield.h"

class CAbase : public QWidget{
    Q_OBJECT

private:
    QTimer *timer;

    //Gamesses
    GameOfLife* gameOfLife;
    Snake* snake;
    //Layouts
    QHBoxLayout* mainLayout;
    QGridLayout* menuSide;

    //Labels
    QLabel* universeSizeLbl;
    QLabel* gameIntervalLbl;

    //SpinBoxes
    QSpinBox* universeSize;
    QSpinBox* gameInterval;

    //ComboBox and its content
    QComboBox* gameMode;
    QString gameModeList[4];
    //Buttons
    QPushButton* startBtn;
    QPushButton* stopBtn;
    QPushButton* clearBtn;

    //gameField
    GameField* gameField;

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
};

#endif // GAMEWIDGET_H
