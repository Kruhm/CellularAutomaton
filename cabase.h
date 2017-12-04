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

#include "snake.h"
#include "snakeBodyPart.h"
#include "gameoflife.h"
#include "gamefield.h"

class CAbase : public QWidget
{
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

    //ComboBox
    QComboBox* gameMode;
    //QString gameModeList[] = new QString[2];

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
    void drawField(const int dim);
};

#endif // GAMEWIDGET_H
