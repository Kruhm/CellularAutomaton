#include "snake.h"

Snake::Snake(const int DIM){
    create();
    spawnFood(DIM);

    movedOnTick = false;
    isEating = false;
}

bool Snake::collision(int dim){
    QPoint headPos = head->getPos();
    bool outOfBounds = headPos.x() < 0 || headPos.y() < 0 || headPos.x() >= dim || headPos.y() >= dim;
    bool canibalism = false;
    SnakeBodyPart* current = tail;
    while(current != head){
        if(headPos == current->getPos()){
            canibalism = true;
            break;
        }
        current = current->getParent();
    }
    return (outOfBounds || canibalism);
}

void Snake::eat(){
    QPoint headPos = head->getPos();
    bool isEating = false;

}

void Snake::spawnFood(const int DIM){
    int foodX;
    int foodY;
    bool isPossible = false;
    std::srand((int) time(0));
    while(!isPossible){
        isPossible = true;
        foodX = std::rand() % DIM;
        foodY = std::rand() % DIM;
        SnakeBodyPart* current = tail;
        while (current) {
            if(current->getPos().x() == foodX && current->getPos().y() == foodY){
                isPossible = false;
                break;
            }
            current = current->getParent();
        }
    }

    //qDebug() << foodX << foodY;
    food = new QPoint(foodX,foodY);
}

void Snake::move(){
    /*
     * Moves the snake in a given direction specified by a KeyPress
     */
    SnakeBodyPart* current = tail;
    while(current->getParent()){ // As long as the current SnakePart has a Parent
        current->moveToParent();      // Move BodyPart
        current = current->getParent(); // go to the next BodyPart
    }
    int xPos = head->getPos().x();
    int yPos = head->getPos().y();
    QPoint* newPos;
    switch(direction){
    case 2: //move down
        newPos = new QPoint(xPos,yPos+1);
        head->setPos(newPos);
        break;
    case 4: //move left
        newPos = new QPoint(xPos-1,yPos);
        head->setPos(newPos);
        break;
    case 6: //move right
        newPos = new QPoint(xPos+1,yPos);
        head->setPos(newPos);
        break;
    case 8: //move up
        newPos = new QPoint(xPos,yPos-1);
        head->setPos(newPos);
        break;
    default:
        break;
    }
}

void Snake::die(){
    QMessageBox obituary;
    obituary.setText("Snake died... you lose");
    obituary.exec();
    reset();
}

void Snake::reset(){
    destroy();
    create();
}

void Snake::destroy(){
    delete head;
    delete tail;
}

void Snake::create(){
    tail = new SnakeBodyPart(new QPoint(0,0),new SnakeBodyPart(new QPoint(0,1),new SnakeBodyPart(new QPoint(0,2),nullptr))); // create snake with 3 body parts
    // get to the snake head
    head = tail;
    while(head->getParent()){ // As long as the current SnakePart has a Parent
        head = head->getParent(); // go to the next BodyPart
    }
    direction = 2;
}

void Snake::setDirection(const int direction){
    this->direction = direction;
}

void Snake::setIsEating(const bool isEating){
    this->isEating = isEating;
}

void Snake::setMovedOnTick(const bool movedOnTick){
    this->movedOnTick = movedOnTick;
}

SnakeBodyPart Snake::getTail(){
    return *tail;
}

QPoint Snake::getFood(){
    return *food;
}

int Snake::getDirection(){
    return direction;
}

bool Snake::getIsEating(){
    return isEating;
}

bool Snake::getMovedOnTick(){
    return movedOnTick;
}

