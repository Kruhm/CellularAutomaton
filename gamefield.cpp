#include "gamefield.h"

GameField::GameField(QGraphicsView *parent): QGraphicsView(parent){
    field = new QGraphicsScene(this);
    brush = new QBrush(Qt::white);
    bgBrush = new QBrush(Qt::lightGray);
    pen = new QPen(Qt::black);
    this->setScene(field);
}

GameField::~GameField(){
    /*
     * Destroys every not otherwise destroyed pointer
     */
    delete pen;
    delete bgBrush;
    delete brush;
}

void GameField::clear(){
    /*
     * clears the given scene of any rectangles
     */
    this->field->clear();
}

void GameField::showField(){
    /*
     * makes scene visible
     */
    this->setScene(field);
}

void GameField::drawFieldCell(int x, int y, int rectSize, bool cellState){
    /*
     * Draws a rectangle on a given x and y position with a given size.
     * Rect will be filled blue if cellState is true, otherwise it's white
     */

    field->setBackgroundBrush(*bgBrush);    // Make the background grey
    QRect rect(rectSize*x,rectSize*y,rectSize,rectSize); //creates a rect on the given x and y with the given size
    if(cellState){ // if cell is alive, fill rect blue
        brush->setColor(Qt::blue);
        this->field->addRect(rect,*pen,*brush);
    }else{  // otherwise cell is dead, fill rect white
        brush->setColor(Qt::white);
        this->field->addRect(rect,*pen,*brush); //add rect to the scene
    }
}


void GameField::mousePressEvent(QMouseEvent *e){
    /*
     * Gets the x and y pos of the mouseclick on the field and fills the associated rect blue
     */
    QPoint origin = mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = mapToScene(origin);
    qDebug() << "x: " << int(relativeOrigin.x()/10) << " y: " << int(relativeOrigin.y()/10);
}
