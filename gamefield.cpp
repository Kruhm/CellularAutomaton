#include "gamefield.h"

GameField::GameField(QGraphicsView *parent): QGraphicsView(parent){
    field = new QGraphicsScene(this);
    brush = new QBrush(Qt::white);
    bgBrush = new QBrush(Qt::lightGray);
    pen = new QPen(Qt::black);
    this->setScene(field);
}

GameField::~GameField(){
    delete field;
    delete pen;
    delete bgBrush;
    delete brush;
}

void GameField::clear(){
    this->field->clear();
}

void GameField::showField(){
    this->setScene(field);
}

void GameField::drawFieldCell(int x, int y, int rectSize, bool cellState){
    field->setBackgroundBrush(*bgBrush);
    QRect rect(rectSize*x,rectSize*y,rectSize,rectSize); //
    if(cellState){ // if cell is alive, fill rect black
        brush->setColor(Qt::blue);
        this->field->addRect(rect,*pen,*brush);
    }else{
        brush->setColor(Qt::white);
        this->field->addRect(rect,*pen,*brush);
    }
}


void GameField::mousePressEvent(QMouseEvent *e){
    QPoint origin = mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = mapToScene(origin);
    //this->x = relativeOrigin.toPoint().x();
}
