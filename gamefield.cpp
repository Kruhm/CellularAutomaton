#include "gamefield.h"

GameField::GameField(QGraphicsView *parent): QGraphicsView(parent){
    /*
     * GraphicsView holding a cellular grid
     * GameMode 1: Game of Life | 2: Predator Prey
     * CellMode 1: Predator | 2: Prey | 3: Food | 4: Dead
     */
    field = new QGraphicsScene(this);
    this->currentCellMode = 1;
    this->currentGameMode = 0;
    this->mouseDrag = false;
    this->rectSize = 10;
    brush = new QBrush(Qt::white);
    bgBrush = new QBrush(Qt::lightGray);
    pen = new QPen(Qt::darkGray);
    this->setScene(field);
}

GameField::GameField(GameOfLife* gameOfLife, Snake* snake, PredatorPrey* predatorPrey, QGraphicsView *parent): QGraphicsView(parent){
    /*
     * GraphicsView holding a cellular grid
     * GameMode 1: Game of Life | 2: Predator Prey
     * CellMode 1: Predator | 2: Prey | 3: Food | 4: Dead
     */
    field = new QGraphicsScene(this);
    this->gameOfLife = gameOfLife;
    this->snake = snake;
    this->predatorPrey = predatorPrey;
    this->currentCellMode = 1;
    this->currentGameMode = 0;
    this->mouseDrag = false;
    this->rectSize = 10;
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
void GameField::addGame(GameOfLife *gameOfLife){
    this->gameOfLife = gameOfLife;
}
void GameField::addGame(Snake* snake){
    this->snake = snake;
}
void GameField::addGame(PredatorPrey* predatorPrey){
    this->predatorPrey = predatorPrey;
}
void GameField::addGame(GameOfLife* gameOfLife, Snake* snake, PredatorPrey* predatorPrey){
    this->gameOfLife = gameOfLife;
    this->snake = snake;
    this->predatorPrey = predatorPrey;
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

void GameField::drawSnakeField(const int fieldSize){
    /*
     * Draws the field for the game Snake
     * Green - Snake
     * Red - Food
     * otherwise - empty cell
     */
    field->setBackgroundBrush(*bgBrush);    // Make the background grey
    SnakeBodyPart* tail = this->snake->getTail();
    QPoint* food = this->snake->getFood();
    for(int y = 0; y < fieldSize;y++){
        for(int x = 0; x < fieldSize;x++){
            bool isSnakeCell = false;
            QRect rect(rectSize*x,rectSize*y,rectSize,rectSize); //creates a rect on the given x and y with the given size
            SnakeBodyPart* current = tail;

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

void GameField::drawPedatorPreyField(){
    /*
     * Draws the field for the Game Predator - Prey
     * Green -> Food Cell
     * Red -> Predator Cell
     * Yellow -> Prey Cell
     * otherwise -> Dead Cell
     */
    const int gameSize = predatorPrey->getGamesize();
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

void GameField::drawGameOfLifeField(){
    /*
     * Draws a rectangle on a given x and y position with a given size.
     * Rect will be filled blue if cellState is true, otherwise it's white
     */
    const int dim = gameOfLife->getDim();
    const int gameSize = dim*dim;
    for(int i = 0; i < gameSize; i++){
        int x = i / dim;
        int y = i % dim;
        bool cellState = gameOfLife->getCellState(i/dim,i%dim);
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
}

void GameField::drawRandom(){
    /*
     * this does melt your pc
     */
    const int gameSize = 50;
    srand(time(0) + rand());
    for(int y = 0; y < gameSize; y++){
        for(int x = 0; x < gameSize; x++){
            QColor c(rand()%256,rand()%256,rand()%256);
            QRect rect(rectSize*x,rectSize*y,rectSize,rectSize);
            brush->setColor(c);
            this->field->addRect(rect,*pen,*brush); //add rect to the board
        }

    }
}

void GameField::cellUpdate(){
    /*
     * Updates the cell under the cursor
     * for the current selected game.
     */
    QPoint origin = mapFromGlobal(QCursor::pos());  // get mouse pos
    QPointF relOrigin = mapToScene(origin);    // map x,y to the current board
    int x = relOrigin.x()/rectSize; // pixel to column
    int y = relOrigin.y()/rectSize; // pixel to row
    if(x < 0 || y < 0 || x >= predatorPrey->getGamesize() || y >= predatorPrey->getGamesize()) return; // If x or y is outOfBounds

    if(this->currentGameMode == 1){ // Game on focus: Predator Prey
        Cell cell = predatorPrey->getCell(x,y);
        if(cell.getStatus() != currentCellMode){
            predatorPrey->setCell(Cell(new QPoint(x,y),predatorPrey->getMaxLifetime(),currentCellMode));
            adjustingPredPreyCounter(cell);
        }
        if(currentCellMode == 4) predatorPrey->killCell(x,y);

    }else if(currentGameMode == 0){ // Game on focus: Game of Life
        this->gameOfLife->setCellState(x,y,true); //toggle cell state
    }
}

void GameField::adjustingPredPreyCounter(Cell cell){
    /*
     * adjust the counters
     * in the PredatorPrey Game
     * when the given cell is overwritten.
     */
    if(currentCellMode == 1){                   //CellMode is Predator
        predatorPrey->increasePredatorCount();
        if(cell.isPrey()){
            predatorPrey->decreasePreyCount();
        }
    }else if(currentCellMode == 2){             //CellMode is Prey
        predatorPrey->increasePreyCount();
        if(cell.isPredator()){
            predatorPrey->decreasePredatorCount();
        }
    }else{                                      //CellMode is either Food or Dead
        if(cell.isPrey()){
            predatorPrey->decreasePreyCount();
        } else if(cell.isPredator()){
            predatorPrey->decreasePredatorCount();
        }
    }
}

void GameField::setCurrentCellMode(int cm){
    this->currentCellMode = cm;
}

void GameField::setCurrentGameMode(int gm){
    this->currentGameMode = gm;
}

void GameField::mousePressEvent(QMouseEvent *e){
    this->mouseDrag = true;
    cellUpdate();
}

void GameField::mouseMoveEvent(QMouseEvent *event){
    if(mouseDrag) cellUpdate();
}

void GameField::mouseReleaseEvent(QMouseEvent *event){
    this->mouseDrag = false;
}
