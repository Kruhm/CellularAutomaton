#include "cabase.h"

CAbase::CAbase(QWidget *parent): QWidget(parent){
    //Initialize Attributes
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

    gameOfLife = new GameOfLife(50,500,true);
    snakeTail = new Snake(new QPoint(0,0),0);
    snakeHead = snakeTail;

    gameField = new GameField(gameOfLife);

    //setup UI
    this->setupUI();
    timer->start(50);

    //Connect Objects with SLOTS
    connect(startBtn,SIGNAL(clicked()),this,SLOT(onStartBtnClicked()));
    connect(stopBtn,SIGNAL(clicked()),this,SLOT(onPauseBtnClicked()));
    connect(clearBtn,SIGNAL(clicked()),this,SLOT(onClearBtnClicked()));
    connect(universeSize,SIGNAL(valueChanged(int)),this,SLOT(onUniverseSizeChanged()));
    connect(gameInterval,SIGNAL(valueChanged(int)),this,SLOT(onIntervalValueChanged()));
    connect(changeSizeBtn,SIGNAL(clicked()),this,SLOT(onChangeBtnClicked()));
    connect(timer,SIGNAL(timeout()),this,SLOT(evolutionChoice()));

    //creating the games

}

CAbase::~CAbase(){
    /*
     * destroy every not otherwise destroyed pointer
     */
    delete gameField;
}

void CAbase::evolutionChoice(){
    /*
     *  decides which game should be progressing, based on the game mode SpinBox
     */
    update();
    if(gameMode->currentText()=="Snake"){
        this->doTheSnakeThing();
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
    for(int i = 0; i < dim*dim; i++){   // for every cell in the GoL
        gameField->drawFieldCell(i%dim,i/dim,10,gameOfLife->getCellState(i%dim,i/dim)); // draw cell with given state of the GoL Board
    }
    gameField->showField(); // make board visible
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
    snakeHead = current;    // Remember the last element of the list
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
