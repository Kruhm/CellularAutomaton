#include "cabase.h"
#include "ui_cabase.h"


CAbase::CAbase(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::CAbase)
{
    /*
     * Conveys Game of Life
     */
    ui->setupUi(this);
    dim = ui->universeSize->value();
    originOfCs = new QPoint(10,20);
    setSize(dim,dim);
    tail = new snake(new QPoint(0,0),0);
    head = tail;

    // beginning the field with the glider example
    setCellState(0,0,1);
    setCellState(2,0,1);
    setCellState(1,1,1);
    setCellState(2,1,1);
    setCellState(1,2,1);
    connect(timer, SIGNAL(timeout()),SLOT(evolve()));
    timer->start(ui->intervalBox->value());
}

CAbase::~CAbase()
{
    /*
     * Destroys every manual created pointer to clear the memory
     */
    delete[] currentState;
    delete[] newState;
    delete ui;
    delete timer;
}

void CAbase::paintEvent(QPaintEvent *e){
    /*
     * Paints the grid on the window.
     */
    QPainter painter(this);
    painter.setPen(Qt::white);
    for(int i = 0; i < dim*dim; i++){
        int posInXDir = originOfCs->x()+10*(i/dim);
        int posInYDir = originOfCs->y()+10*(i%dim);
        QRect rect(posInXDir,posInYDir,10,10); //

        if(getCellState((i/dim),(i%dim))) // if cell is alive, fill rect black
            painter.fillRect(rect,Qt::black);

        painter.drawRect(rect);
    }
}

void CAbase::mousePressEvent(QMouseEvent* event) {
    /*
     * Changes the state of the clicked cell on the grid to on or off
     */

    QPoint p(event->pos());              // position of mouse
    int x = originOfCs->x();             //       x position of Grid | Grid is drawn at (10,20)
    int y = originOfCs->y();             //       y position of Grid
    bool isX = false;
    bool isY = false;

    // check for pos in x direction
    if(p.x() <= originOfCs->x() + dim * 10 && p.x() >= originOfCs->x()){ // If mouseclick is in grid
        while(x <= p.x() && x<= originOfCs->x() + dim * 10){
            x += 10;
        }
        x -= originOfCs->x();
        x /= 10;
        isX = true;
    }

    // check for pos in y direction
    if(p.y() <= originOfCs->y() + dim * 10 && p.y() >= originOfCs->y()){ // If mouseclick is in grid
        while(y <= p.y() && y <= originOfCs->y() + dim * 10){
            y += 10;
        }

        y -= originOfCs->y();
        y /= 10;
        isY = true;
    }

    if(isY && isX){ // if click was truly on grid
        setCellState(x-1,y-1,!getCellState(x-1,y-1));
        update();
    }
}

int CAbase::convertToOneDimension(const int x, const int y) {
    /*
     * Converts 2D iteration to 1D iteration
     */
    return ((y * getNx()) + x);
}

int CAbase::getNy() {
    return Ny;
}

void CAbase::setNy(const int Ny) {
    this->Ny = Ny;
}

int CAbase::getNx() {
    return Nx;
}

void CAbase::setNx(const int Nx) {
    this->Nx = Nx;
}

void CAbase::wipe() {
    /*
     * Resets the dyn arrays, every entry set to False
     */
    for (int y = 0; y < getNy(); y++) {
        for (int x = 0; x < getNx(); x++) {
            setCellState(x, y, false);
            setNewCellState(x, y, false);
        }
    }
}

void CAbase::setSize(const int x, const int y) {
    /*
     * resizes the dynamic arrays
     */
    setNx(x);
    setNy(y); //new x and y values
    delete[] currentState;
    delete[] newState;
    currentState = new bool[getNx() * getNy()];
    newState = new bool[getNx() * getNy()];
    wipe();
}

void CAbase::evolve() {
    /*
     * Applies the rules of the game to every instance of the field
     */
    for (int y = 0; y < getNy(); y++) {
        for (int x = 0; x < getNx(); x++) {
            setNewCellState(x, y, apply_rules(x, y));
        }
    }

    //copy new state to current state
    for (int y = 0; y < getNy(); y++) {
        for (int x = 0; x < getNx(); x++) {
            setCellState(x, y, getnewCellState(x, y));
            setNewCellState(x, y, false);
        }
    }
    update();
}

bool CAbase::field_exists(const int x, const int y) {
    /*
     * Returns true if x and y is in the grids boundaries
     */
    return (x < getNx() && x >= 0) && (y >= 0 && y < getNy());
}

bool CAbase::apply_rules(const int x, const int y) {
    /*
     * Checks for a given instance, if any rule has to be applied
     */
    int up = (y - 1);
    int down = (y + 1);
    int left = (x - 1);
    int right = (x + 1);

    int amountOfNeighbours = 0;

    //checks if surrounding cell exist and is alive
    if (field_exists(left, up) && getCellState(left, up)) { amountOfNeighbours++; }     // dia left up
    if (field_exists(left, down) && getCellState(left, down)) { amountOfNeighbours++; }  // dia left down
    if (field_exists(right, down) && getCellState(right, down)) { amountOfNeighbours++; } // dia right down
    if (field_exists(right, up) && getCellState(right, up)) { amountOfNeighbours++; }    // dia right up
    if (field_exists(left, y) && getCellState(left, y)) { amountOfNeighbours++; }        // left
    if (field_exists(right, y) && getCellState(right, y)) { amountOfNeighbours++; }       // right
    if (field_exists(x, up) && getCellState(x, up)) { amountOfNeighbours++; }          // up
    if (field_exists(x, down) && getCellState(x, down)) { amountOfNeighbours++; }       // down

    if (amountOfNeighbours > 3 || amountOfNeighbours < 2) { // not enough or too many neighbors
        return false;
    } else if (getCellState(x, y) && (amountOfNeighbours == 2 || amountOfNeighbours == 3)) { // 2 or 3 neighbors to stay alive
        return true;
    } else if (!getCellState(x, y) && amountOfNeighbours == 3) { // 3 neighbors reproduced
        return true;
    }
}

void CAbase::setNewCellState(const int x, const int y, const bool state) {
    /*
     * Changes one instance of the newCellState Array
     */
    int address = convertToOneDimension(x, y);
    newState[address] = state;
}

void CAbase::setCellState(const int x, const int y, const bool state) {
    /*
     * Changes one instance of the currentCellState Array
     */
    int address = convertToOneDimension(x, y);
    currentState[address] = state;
}

bool CAbase::getCellState(const int x, const int y) {
    int address = convertToOneDimension(x, y);
    return currentState[address];
}

bool CAbase::getnewCellState(const int x, const int y) {
    int address = convertToOneDimension(x, y);
    return newState[address];
}

void CAbase::on_stopButton_clicked()
{
    timer->stop();
}

void CAbase::on_startButton_clicked()
{
    int interval = ui->intervalBox->value();
    timer->start(interval);
}

void CAbase::on_changeUniverseSizeButton_clicked()
{
    this->dim = ui->universeSize->value();
    setSize(dim,dim);
    update();
}

void CAbase::on_clearButton_clicked()
{
    wipe();
    timer->stop();
    update();
}

void CAbase::on_changeCellButton_clicked()
{

    int x = ui->xBox->value();
    int y = ui->yBox->value();

    if(field_exists(x,y)){
        timer->stop();
        setCellState(x,y,!getCellState(x,y));
        update();
    }
}

void CAbase::on_intervalBox_valueChanged(int arg1)
{
    timer->stop();
    timer->start(ui->intervalBox->value());
}
