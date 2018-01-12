#include "gamefield.h"

GameField::GameField(GameOfLife* gol, PredatorVictim* pP, QGraphicsView *parent): QGraphicsView(parent){
    /*
     * GraphicsView holding a cellular grid
     * GameMode 1: Game of Life | 2: Predator Prey
     * CellMode 1: Predator | 2: Prey | 3: Food | 4: Dead
     */
    field = new QGraphicsScene(this);
    this->gameOfLife = gol;
    this->predatorPrey = pP;
    this->currentCellMode = 1;
    this->currentGameMode = 0;
    this->mouseDrag = false;
    brush = new QBrush(Qt::white);
    bgBrush = new QBrush(Qt::lightGray);
    pen = new QPen(Qt::darkGray);
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

void GameField::drawSnakeField(const int fieldSize, SnakeBodyPart* snakeTail, QPoint* food){
    field->setBackgroundBrush(*bgBrush);    // Make the background grey
    int rectSize = 10;
    for(int y = 0; y < fieldSize;y++){
        for(int x = 0; x < fieldSize;x++){
            bool isSnakeCell = false;
            QRect rect(rectSize*x,rectSize*y,rectSize,rectSize); //creates a rect on the given x and y with the given size
            SnakeBodyPart* current = snakeTail;
            while(current){ // loop through snake
                QPoint pos = current->getPos();
                if(pos.x() == x && pos.y() == y){ // if (x,y) pos is the current snake pos
                    isSnakeCell = true;
                    break;
                }
                current = current->getParent();
            }
            if(isSnakeCell){    // cell is a snake body part
                brush->setColor(Qt::green);
                this->field->addRect(rect,*pen,*brush); //add rect to the board
            }else if(x == food->x() && y == food->y()){ // cell is food
                brush->setColor(Qt::red);
                this->field->addRect(rect,*pen,*brush); //add rect to the board
            }else{  // cell is empty
                brush->setColor(Qt::white);
                this->field->addRect(rect,*pen,*brush); //add rect to the board
            }
        }
    }
}

void GameField::setCurrentCellMode(int cm){
    this->currentCellMode = cm;
}

void GameField::setCurrentGameMode(int gm){
    this->currentGameMode = gm;
}

void GameField::drawPedatorPreyField(const int gameSize, PredatorVictim* predatorPrey){
    /*
     * Draws the field for the Game Predator - Prey
     * Green -> Food Cell
     * Red -> Predator Cell
     * Yellow -> Prey Cell
     * otherwise -> Dead Cell
     */
    int rectSize = 10;
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            QRect rect(rectSize*x,rectSize*y,rectSize,rectSize);
            Cell current = predatorPrey->getCell(x,y);
            float lifetimeRatio = ((float) current.getLiftime()/ (float) predatorPrey->getMaxLifetime());
            if(current.isFood()){
                brush->setColor(QColor(0,255,0));
                this->field->addRect(rect,*pen,*brush); //add rect to the board
            }else if(current.isPrey()){
                brush->setColor(QColor(255,255,0,100+155*lifetimeRatio));
                this->field->addRect(rect,*pen,*brush); //add rect to the board
            }else if(current.isPredator()){
                brush->setColor(QColor(255,0,0,100+155*lifetimeRatio));
                this->field->addRect(rect,*pen,*brush); //add rect to the board
            }else{
                brush->setColor(Qt::white);
                this->field->addRect(rect,*pen,*brush); //add rect to the board
            }
        }

    }
}

void GameField::drawGameOfLifeCell(int x, int y, int rectSize, bool cellState){
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
    this->mouseDrag = true;
    mouseIsDragged();
}

void GameField::mouseIsDragged(){
    QPoint origin = mapFromGlobal(QCursor::pos());  // get mouse pos
    QPointF relativeOrigin = mapToScene(origin);    // map x,y to the current board
    int x = relativeOrigin.x()/10; // pixel to column
    int y = relativeOrigin.y()/10; // pixel to row
    if(x < 0 || y < 0 || x >= predatorPrey->getGamesize() || y >= predatorPrey->getGamesize()){return;}
    if(this->currentGameMode == 1){
        Cell currentCell = predatorPrey->getCell(x,y);
        if(currentCell.getStatus() != currentCellMode){
            predatorPrey->setCell(Cell(new QPoint(x,y),predatorPrey->getMaxLifetime(),currentCellMode));
            if(currentCellMode == 1){
                predatorPrey->increasePredatorCount();
                if(currentCell.isPrey()){
                    predatorPrey->decreasePreyCount();
                }
            }else if(currentCellMode == 2){
                predatorPrey->increasePreyCount();
                if(currentCell.isPredator()){
                    predatorPrey->decreasePredatorCount();
                }
            }else if(currentCellMode == 3){
                if(currentCell.isPrey()){
                    predatorPrey->decreasePreyCount();
                } else if(currentCell.isPredator()){
                    predatorPrey->decreasePredatorCount();
                }
            }else{
                if(currentCell.isPredator()){
                    predatorPrey->decreasePredatorCount();
                }else if(currentCell.isPrey()){
                    predatorPrey->decreasePreyCount();
                }
                predatorPrey->setCell(Cell(new QPoint(x,y)));
            }
        }
    }else if(currentGameMode == 0){
        this->gameOfLife->setCellState(x,y,true); //toggle cell state
    }
}

void GameField::mouseMoveEvent(QMouseEvent *event){
    if(mouseDrag){
        mouseIsDragged();
    }
}

void GameField::mouseReleaseEvent(QMouseEvent *event){
    this->mouseDrag = false;
}
