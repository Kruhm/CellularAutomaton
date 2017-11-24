#ifndef CABASE_H
#define CABASE_H

#include "snake.h"
#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>
#include <QApplication>
#include <iostream>


namespace Ui {
class CAbase;
}

class CAbase : public QMainWindow
{
    Q_OBJECT

public:
    explicit CAbase(QWidget *parent = 0);
    ~CAbase();

    void setNx(int Nx);
    int getNx();
    void setNy(int Ny);
    int getNy();
    void setSize(int x, int y);
    void setCellState(int x, int y, bool state);
    bool getCellState(int x, int y);
    bool getnewCellState(int x, int y);

public slots:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

private slots:
    void evolve();

    void on_stopButton_clicked();

    void on_startButton_clicked();

    void on_changeUniverseSizeButton_clicked();

    void on_clearButton_clicked();

    void on_changeCellButton_clicked();

    void on_intervalBox_valueChanged(int arg1);

private:
    Ui::CAbase *ui;

    //ATTRIBUTES
    int Nx; // length of Field in x
    int Ny; // length of Field in y
    int dim;
    bool *currentState = new bool[0];
    bool *newState = new bool[0];
    QTimer *timer;
    QPoint *originOfCs;

    //PRIVATE METHODS
    bool apply_rules(int x, int y);
    void setNewCellState(int x, int y, bool state);
    bool field_exists(int x, int y);
    void wipe();
    int convertToOneDimension(int x, int y);

};

#endif // CABASE_H
