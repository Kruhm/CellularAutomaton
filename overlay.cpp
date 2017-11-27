#include "overlay.h"

Overlay::Overlay(QWidget *parent): QWidget(parent){
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
    gameField = new GameField();


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
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));

    //create game objects
    gameOfLife = new CAbase(universeSize->value(),gameInterval->value(),true);
    snakeTail = new Snake(new QPoint(0,0),0);
    snakeHead = snakeTail;

    //start the evolution
    evolutionChoice();
}

Overlay::~Overlay(){
    delete gameField;
}

void Overlay::evolutionChoice(){
    if(gameMode->currentText()=="Snake"){
        this->doTheSnakeThing();
    }else
        gameOfLife->start();
}

void Overlay::paintEvent(QPaintEvent *event){
    gameField->clear();
    int dim = universeSize->value();
    for(int i = 0; i < dim*dim; i++){
        gameField->drawFieldCell(i/dim,i%dim,10,gameOfLife->getCellState(i%dim,i/dim));
    }
    gameField->showField();
}

void Overlay::doTheSnakeThing(){
    Snake* current = snakeTail;
    while(current->getParent()){
        current->evolve();
        current = current->getParent();
    }
    snakeHead = current;
}

void Overlay::onStartBtnClicked(){
    qDebug() <<gameInterval->value();
    gameOfLife->setStackSize(gameInterval->value());
    gameOfLife->setDoEvolution(true);
    gameOfLife->start();
}

void Overlay::onPauseBtnClicked(){
    gameOfLife->setDoEvolution(false);
}

void Overlay::onClearBtnClicked(){
    gameOfLife->wipe();
    update();
}

void Overlay::onChangeBtnClicked(){
    int newDim = universeSize->value();
    gameOfLife->setSize(newDim,newDim);
    update();
}

void Overlay::onUniverseSizeChanged(){
    int dim = universeSize->value();
    gameOfLife->setSize(dim,dim);
}

void Overlay::onIntervalValueChanged(){
    gameOfLife->setSleepTime(gameInterval->value());
}

void Overlay::setupUI(){
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
    universeSize->setMaximum(50);
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
    gameMode->addItem("snake");

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
    menuSide->setAlignment(Qt::AlignTop);
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
