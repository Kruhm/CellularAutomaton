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
#include <QMediaPlayer>

#include "snake.h"
#include "gameoflife.h"
#include "predatorprey.h"
#include "gamefield.h"

class CAbase : public QWidget{
    Q_OBJECT

private:
    QTimer *timer;

    //Gamesses
    GameOfLife* gameOfLife;
    Snake* snake;
    PredatorPrey* predatorPrey;
    //Layouts
    QHBoxLayout* mainLayout;
    QGridLayout* menuSide;

    //Labels
    QLabel* universeSizeLbl;
    QLabel* gameIntervalLbl;
    QLabel* cellModelbl;
    QLabel* lifetimeLbl;

    //SpinBoxes
    QSpinBox* universeSize;
    QSpinBox* gameInterval;
    QSpinBox* lifetime;

    //ComboBox and its content
    QComboBox* cellMode;
    QComboBox* gameMode;
    QString cellModeList[4];
    QString gameModeList[4];
    //Buttons
    QPushButton* startBtn;
    QPushButton* stopBtn;
    QPushButton* clearBtn;
    QPushButton* newGameBtn;

    //gameField
    GameField* gameField;

    const unsigned int scr1 = 1479627829;
    const unsigned int scr2 = 1721837343;
    string scrString;
    void doingTehPrivateThing();

public slots:
    void updateSelectedGame();
    void updateGameOfLife();
    void updateSnake();
    void updatePredatorPrey();
    void onStartBtnClicked();
    void onPauseBtnClicked();
    void onClearBtnClicked();
    void onGameModeChanged();
    void onNewGameBtnClicked();
    void onUniverseSizeChanged();
    void onCellModeValueChanged();
    void onIntervalValueChanged();
    void keyPressEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *event);

public:
    CAbase(QWidget *parent = 0);
    ~CAbase();
    void setupUI();
};

#endif // GAMEWIDGET_H
