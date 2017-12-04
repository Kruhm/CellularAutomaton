#include "cabase.h"

CAbase::CAbase(QWidget *parent): QWidget(parent){
    /*
     * GUI for a cellular automaton with the games Convey's Game of Life and Snake
     */
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

    // initialize options for the game mode spin box
    gameModeList[0] = "Game of Life";
    gameModeList[1] = "Snake";
    gameModeList[2] = "MileStone3";
    gameModeList[3] = "MileStone4";

    //initialize game objects
    gameOfLife = new GameOfLife(50,500,false); // universeSize, intervall, doEvolution
    snake = new Snake(50);  // dim for placing food

    // initialize grid
    gameField = new GameField(gameOfLife);

    //setup UI
    this->setupUI();



    //Connect Objects with SLOTS
    connect(startBtn,SIGNAL(clicked()),this,SLOT(onStartBtnClicked()));
    connect(stopBtn,SIGNAL(clicked()),this,SLOT(onPauseBtnClicked()));
    connect(clearBtn,SIGNAL(clicked()),this,SLOT(onClearBtnClicked()));
    connect(universeSize,SIGNAL(valueChanged(int)),this,SLOT(onUniverseSizeChanged()));
    connect(gameInterval,SIGNAL(valueChanged(int)),this,SLOT(onIntervalValueChanged()));
    connect(timer,SIGNAL(timeout()),this,SLOT(evolutionChoice()));

    // timer to update the gamefield every 50ms
    QTimer* updateTimer = new QTimer(this);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(update()));
    updateTimer->start(50);
}

CAbase::~CAbase(){
    /*
     * destroy every not otherwise destroyed pointer
     */
    delete gameField;
}

void CAbase::paintEvent(QPaintEvent *event){
    /*
     * Draws the grid on the left side of the Window.
     * Currently only for Game of Life, Blue is an alive cell, White is a dead cell
     */
    gameField->clear(); //emptying field
    int dim = universeSize->value();
    if(gameMode->currentText()==gameModeList[1]){ // if Mode => Snake
        gameField->drawSnakeField(dim,snake->getTail(),snake->getFood()); // draw board for the snake game
    }else{  // Mode => Game of Life
        for(int i = 0; i < dim*dim; i++){   // for every cell in the GoL
            gameField->drawGameOfLifeCell(i%dim,i/dim,10,gameOfLife->getCellState(i%dim,i/dim)); // draw cell with given state of the GoL Board
        }
    }
     gameField->showField(); // make board visible
}

void CAbase::keyPressEvent(QKeyEvent *e){
    /*
     * Key Event Handler
     * evaluates the key pressed.
     */
    int snakeDirection = snake->getDirection();
    if(snake->getMovedOnTick()) // if snake already had a direction change on tick
        return;
    else if(e->key() == Qt::Key_2 && snakeDirection != 8) // down - 2 has been pressed and not moving up
        snake->setDirection(2);
    else if(e->key() == Qt::Key_4 && snakeDirection != 6) // left - 4 has been pressed and not moving right
        snake->setDirection(4);
    else if(e->key() == Qt::Key_6 && snakeDirection != 4) // right - 6 has been pressed and not moving left
        snake->setDirection(6);
    else if(e->key() == Qt::Key_8 && snakeDirection != 2) // up - 8 has been pressed and not moving down
        snake->setDirection(8);
    snake->setMovedOnTick(true); // snake can change direction only one time per tick
}

void CAbase::onStartBtnClicked(){
    /*
     * Starts the GameOfLife Thread with the given interval
     */
    if(gameMode->currentText() == gameModeList[1]){ //If snake
        timer->start(gameInterval->value());
    }else{                                          //Else Game of Life
        gameOfLife->setDoEvolution(true); // makes evolution in Game of Life possible
        gameOfLife->start();
        timer->start(50);
    }
}

void CAbase::onPauseBtnClicked(){
    /*
     * Stops the currently running GameOfLife Thread
     */
    gameOfLife->setDoEvolution(false);
    timer->stop();
}

void CAbase::onClearBtnClicked(){
    /*
     * Wipes the Board of every living cell
     */
    timer->stop();
    gameOfLife->wipe();
    snake->reset();
}

void CAbase::onUniverseSizeChanged(){
    /*
     * Wipes the board and changes the universe size
     */
    timer->stop();
    gameOfLife->setSize(universeSize->value());
    snake->reset();
    snake->spawnFood(universeSize->value());
}

void CAbase::onIntervalValueChanged(){
    /*
     * changes the refresh rate of the evolution done by the GameOfLife object
     */
    if(gameMode->currentText() == gameModeList[1]){ // If Snake
        timer->setInterval(gameInterval->value());
    }                                               // Game of Life
    gameOfLife->setSleepTime(gameInterval->value());

}

void CAbase::evolutionChoice(){
    /*
     *  decides which game should be progressing, based on the game mode SpinBox
     */
    if(gameMode->currentText()==gameModeList[1]){   // If Snake
        int dim = universeSize->value();
        snake->setMovedOnTick(false);   // new tick new direction possible
        snake->eat();       // checks for food
        snake->move(dim);   // move snake body
        if(snake->collision(dim)){  // if snake collides
            timer->stop();
            snake->die();   // open dying message
        }
    }else{                                          //Else game of Life
        if(!gameOfLife->isRunning()){   // if the thread isn't currently running
            gameOfLife->start();    // start the GoL thread
        }
    }
}

void CAbase::setupUI(){
    //Give buttons text
    startBtn->setText("start");
    stopBtn->setText("pause");
    clearBtn->setText("clear");

    //Give labels text    QPushButton* changeSizeBtn;
    universeSizeLbl->setText("Universe Size  (10 - 100)");
    gameIntervalLbl->setText("Generation Interval (100-10000)");

    //set boundaries of SpinBoxes
    gameInterval->setMaximum(10000);
    universeSize->setMaximum(100);
    gameInterval->setMinimum(100);
    universeSize->setMinimum(10);
    gameInterval->setSingleStep(50);

    //set SpinBoxes suffixes
    universeSize->setSuffix(" cells");
    gameInterval->setSuffix(" ms");

    //set SpinBoxes initial Values
    universeSize->setValue(50);
    gameInterval->setValue(500);

    //Add game mode tabs to ComboBox
    gameMode->addItem(gameModeList[0]);
    gameMode->addItem(gameModeList[1]);
    //gameMode->addItem(gameModeList[2]); // for the next MileStones!
    //gameMode->addItem(gameModeList[3]);

    //Remove vertical spacing of the labels
    universeSizeLbl->setFixedHeight(10);
    gameIntervalLbl->setFixedHeight(10);

    //Adding widgets to the right side of the window
    menuSide->addWidget(startBtn,0,0); //addWidget(widget,row,column,rowspan,columnspan,alignment) | First Row
    menuSide->addWidget(stopBtn,0,1);
    menuSide->addWidget(clearBtn,0,2);
    menuSide->addWidget(universeSizeLbl,1,0,1,3); // Second Row
    menuSide->addWidget(universeSize,2,0,1,3); //Third Row
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
    this->resize(1000,600);
}
