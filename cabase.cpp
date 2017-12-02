#include "cabase.h"

CAbase::CAbase(QWidget *parent): QWidget(parent){
    //Initialize Attributesses
    timer = new QTimer(this);
    mainLayout = new QHBoxLayout(this);
    menuSide = new QGridLayout(this);
    universeSizeLbl = new QLabel(this);
    gameIntervalLbl = new QLabel(this);
    universeSize = new QSpinBox(this);
    gameInterval = new QSpinBox(this);
    gameMode = new QComboBox(this);
    startBtn = new QPushButton(this);
    stopBtn = new QPushButton(this);
    clearBtn = new QPushButton(this);
    changeSizeBtn = new QPushButton(this);
    snakeDirection = 6;

    gameOfLife = new GameOfLife(50,500,false); // universeSize, intervall, doEvolution
    snakeTail = new Snake(new QPoint(0,0),new Snake(new QPoint(0,1),new Snake(new QPoint(0,2),nullptr))); // create snake with 3 body parts
    // get to the snake head
    snakeHead = snakeTail;
    while(snakeHead->getParent()){ // As long as the current SnakePart has a Parent
        snakeHead = snakeHead->getParent(); // go to the next BodyPart
    }
    qDebug() << snakeHead->getPos();
    gameField = new GameField(gameOfLife,snakeTail); //todo accept food as parameter

    //setup UI
    this->setupUI();
    timer->start(100);

    //Connect Objects with SLOTS
    connect(startBtn,SIGNAL(clicked()),this,SLOT(onStartBtnClicked()));
    connect(stopBtn,SIGNAL(clicked()),this,SLOT(onPauseBtnClicked()));
    connect(clearBtn,SIGNAL(clicked()),this,SLOT(onClearBtnClicked()));
    connect(universeSize,SIGNAL(valueChanged(int)),this,SLOT(onUniverseSizeChanged()));
    connect(gameInterval,SIGNAL(valueChanged(int)),this,SLOT(onIntervalValueChanged()));
    connect(changeSizeBtn,SIGNAL(clicked()),this,SLOT(onChangeBtnClicked()));
    connect(timer,SIGNAL(timeout()),this,SLOT(evolutionChoice()));

    //creating the games
    spawnFood();

}

CAbase::~CAbase(){
    /*
     * destroy every not otherwise destroyed pointer
     */
    delete gameField;
}

void CAbase::eatFood(){
    QPoint headPos = snakeHead->getPos();
    bool isEating = false;
    if(snakeDirection == 2){
        if(headPos.x() == food->x() && headPos.y()+1 == food->y()){
            isEating = true;
        }
    }else if(snakeDirection == 4){
        if(headPos.x()-1 == food->x() && headPos.y() == food->y()){
            isEating = true;
        }
    }else if(snakeDirection == 6){
        if(headPos.x()+1 == food->x() && headPos.y() == food->y()){
            isEating = true;
        }
    }else if(snakeDirection == 8){
        if(headPos.x() == food->x() && headPos.y()-1 == food->y()){
            isEating = true;
        }
    }
    if(isEating){
        snakeHead->setParent(new Snake(new QPoint(food->x(),food->y()),nullptr));
        snakeHead = snakeHead->getParent();
        spawnFood();
    }
}

void CAbase::evolutionChoice(){
    /*
     *  decides which game should be progressing, based on the game mode SpinBox
     */
    update();
    if(gameMode->currentText()=="Snake"){
        this->doTheSnakeThing();
        eatFood();
    }else{
        if(!gameOfLife->isRunning()){   // if the thread isn't currently running
            gameOfLife->start();    // start the GoL thread
        }
    }
}

void CAbase::paintEvent(QPaintEvent *event){
    /*
     * Draws the grid on the left side of the Window.
     * Currently only for Game of Life, Blue is an alive cell, White is a dead cell
     */
    gameField->clear();
    int dim = universeSize->value();
    if(gameMode->currentText()=="Snake"){
        gameField->drawSnakeField(dim,snakeTail,food);
    }else{
        for(int i = 0; i < dim*dim; i++){   // for every cell in the GoL
            gameField->drawFieldCell(i%dim,i/dim,10,gameOfLife->getCellState(i%dim,i/dim)); // draw cell with given state of the GoL Board
        }
    }
     gameField->showField(); // make board visible
}

void CAbase::spawnFood(){
    const int DIM = universeSize->value();
    int foodX;
    int foodY;
    bool isPossible = false;
    std::srand((int) time(0));
    while(!isPossible){
        isPossible = true;
        foodX = std::rand() % DIM;
        foodY = std::rand() % DIM;
        Snake* current = snakeTail;
        while (current) {
            if(current->getPos().x() == foodX && current->getPos().y() == foodY){
                isPossible = false;
                break;
            }
            current = current->getParent();
        }
    }

    qDebug() << foodX << foodY;
    food = new QPoint(foodX,foodY);
}

void CAbase::doTheSnakeThing(){
    /*
     * Moves the snake in a given direction specified by a KeyPress
     */
    Snake* current = snakeTail;
    while(current->getParent()){ // As long as the current SnakePart has a Parent
        current->evolve();      // Move BodyPart
        current = current->getParent(); // go to the next BodyPart
    }
    int xPos = snakeHead->getPos().x();
    int yPos = snakeHead->getPos().y();
    QPoint* newPos;
    switch(snakeDirection){
    case 2: //move down
        newPos = new QPoint(xPos,yPos+1);
        snakeHead->setPos(newPos);
        break;
    case 4: //move left
        newPos = new QPoint(xPos-1,yPos);
        snakeHead->setPos(newPos);
        break;
    case 6: //move right
        newPos = new QPoint(xPos+1,yPos);
        snakeHead->setPos(newPos);
        break;
    case 8: //move up
        newPos = new QPoint(xPos,yPos-1);
        snakeHead->setPos(newPos);
        break;
    }
    update();
}

void CAbase::onStartBtnClicked(){
    /*
     * Starts the GameOfLife Thread with the given interval
     */
    gameOfLife->setDoEvolution(true);
    gameOfLife->start();
}

void CAbase::onPauseBtnClicked(){
    /*
     * Stops the currently running GameOfLife Thread
     */
    gameOfLife->setDoEvolution(false);
}

void CAbase::onClearBtnClicked(){
    /*
     * Wipes the Board of every living cell
     */
    gameOfLife->wipe();
    update();
}

void CAbase::onChangeBtnClicked(){
    /*
     * Wipes the board and changes the universe size
     */
    gameOfLife->setSize(universeSize->value());
    update();
}

void CAbase::onUniverseSizeChanged(){
    /*
     * Wipes the board and changes the universe size
     */
    gameOfLife->setSize(universeSize->value());
    update();
}

void CAbase::onIntervalValueChanged(){
    /*
     * changes the refresh rate of the evolution done by the GameOfLife object
     */
    gameOfLife->setSleepTime(gameInterval->value());
}

void CAbase::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_2 && snakeDirection != 8)
        snakeDirection = 2;
    else if(e->key() == Qt::Key_4 && snakeDirection != 6)
        snakeDirection = 4;
    else if(e->key() == Qt::Key_6 && snakeDirection != 4)
        snakeDirection = 6;
    else if(e->key() == Qt::Key_8 && snakeDirection != 2)
        snakeDirection = 8;
}

void CAbase::setupUI(){
    //Give buttons text
    startBtn->setText("start");
    stopBtn->setText("pause");
    clearBtn->setText("clear");
    changeSizeBtn->setText("change");

    //Give labels text
    universeSizeLbl->setText("Universe Size  (1 - 50)");
    gameIntervalLbl->setText("Generation Interval (100-10000)");

    //set boundaries of SpinBoxes
    gameInterval->setMaximum(10000);
    universeSize->setMaximum(100);
    gameInterval->setMinimum(100);
    universeSize->setMinimum(1);
    gameInterval->setSingleStep(50);

    //set SpinBoxes suffixes
    universeSize->setSuffix(" cells");
    gameInterval->setSuffix(" ms");

    //set SpinBoxes initial Values
    universeSize->setValue(50);
    gameInterval->setValue(500);

    //Add game mode tabs to ComboBox
    gameMode->addItem("Game of Life");
    gameMode->addItem("Snake");

    //Remove vertical spacing of the labels
    universeSizeLbl->setFixedHeight(10);
    gameIntervalLbl->setFixedHeight(10);

    //Adding widgets to the right side of the window
    menuSide->addWidget(startBtn,0,0); //addWidget(widget,row,column,rowspan,columnspan,alignment) | First Row
    menuSide->addWidget(stopBtn,0,1);
    menuSide->addWidget(clearBtn,0,2);
    menuSide->addWidget(universeSizeLbl,1,0,1,3); // Second Row
    menuSide->addWidget(universeSize,2,0,1,3); //Third Row
    menuSide->addWidget(changeSizeBtn,3,2);    //Fourth Row
    menuSide->addWidget(gameIntervalLbl,4,0,1,2); //Fifth Row
    menuSide->addWidget(gameInterval,5,0,1,3); //Sixth Row

    //Adding Widgets to the main windows layout
    menuSide->addWidget(gameMode,6,0,1,3,Qt::AlignBottom); // Seventh Row
    mainLayout->addWidget(gameField);
    mainLayout->addLayout(menuSide);
    mainLayout->setAlignment(Qt::AlignTop);

    //setting Layout of Window
    this->setLayout(mainLayout);

    //start the initial timer

    //set size of window
    this->resize(800,550);
}
