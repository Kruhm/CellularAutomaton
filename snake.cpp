#include "snake.h"

Snake::Snake(const int DIM){
    /*
     * A C++ implementation of the game
     * Snake
     */
    create();
    spawnFood(DIM);

    movedOnTick = false;
    isEating = false;
}

bool Snake::collision(int dim){
    /*
     * checks if snake is moving out of bounds or is eating himself
     * returns false if head is in bounds and not eating himself
     * returns true otherwise
     */
    QPoint headPos = head->getPos();
    bool outOfBounds = headPos.x() < 0 || headPos.y() < 0 || headPos.x() >= dim || headPos.y() >= dim; // is head out of bounds
    bool canibalism = false; // is snake eating itself
    SnakeBodyPart* current = tail;
    while(current != head){ //loop through snake
        if(headPos == current->getPos()){ // if head is on the same field as a snake Part
            canibalism = true;
            break;
        }
        current = current->getParent();
    }
    return (outOfBounds || canibalism);
}

void Snake::eat(){
    /*
     * checks if head is on the same cell as the food
     */
    QPoint headPos = head->getPos();
    isEating = false;
    if(food->y() == headPos.y() && food->x() == headPos.x()){
        isEating = true;
    }

}

void Snake::spawnFood(const int DIM){
    /*
     * creates on a free cell a new food item
     */
    int foodX;
    int foodY;
    bool isPossible = false;
    std::srand((int) time(0));  //make random position more random
    while(!isPossible){ // as long as food is not in a free cell
        isPossible = true;
        foodX = std::rand() % DIM;  // 0 < x < DIM
        foodY = std::rand() % DIM;  // 0 < y < DIM
        SnakeBodyPart* current = tail;
        while (current) { //loops through snake
            if(current->getPos().x() == foodX && current->getPos().y() == foodY){ // if food lands on a snake body part
                isPossible = false;
                break;
            }
            current = current->getParent();
        }
    }
    food = new QPoint(foodX,foodY); // set new food position
}

void Snake::move(const int DIM){
    /*
     * Moves the snake in a given direction specified by a KeyPress
     */
    if (isEating){  // if snake should be growing instead of moving
        head->setParent(new SnakeBodyPart(new QPoint(food->x(),food->y()),nullptr)); //grow a new head
        head = head->getParent();   // change old head to new head
        spawnFood(DIM); // spawn new food on field
    } else {
        SnakeBodyPart* current = tail;
        while(current->getParent()){ // As long as the current SnakePart has a Parent
            current->moveToParent();      // Move BodyPart
            current = current->getParent(); // go to the next BodyPart
        }
    }
    int headX = head->getPos().x();
    int headY = head->getPos().y();
    QPoint* newPos;
    switch(direction){
    case 2: //move down
        newPos = new QPoint(headX,headY+1);
        head->setPos(newPos);
        break;
    case 4: //move left
        newPos = new QPoint(headX-1,headY);
        head->setPos(newPos);
        break;
    case 6: //move right
        newPos = new QPoint(headX+1,headY);
        head->setPos(newPos);
        break;
    case 8: //move up
        newPos = new QPoint(headX,headY-1);
        head->setPos(newPos);
        break;
    default:
        break;
    }
}

void Snake::die(){
    /*
     * spawns a dying message and resets the game
     */
    QMessageBox obituary;
    obituary.setText("Snake died... you lose");
    obituary.exec();    // show dying message
    reset();
}

void Snake::reset(){
    /*
     * resets the snake
     */
    destroy();
    create();
}

void Snake::destroy(){
    /*
     * free memory from snake body part list
     */
    delete head;
    delete tail;
}

void Snake::create(){
    /*
     * creates 3 snake body parts with a head and a tail, going from (0,0) to (0,2)
     * standard direction when starting the game is set to moving down
     */
    tail = new SnakeBodyPart(new QPoint(0,0),new SnakeBodyPart(new QPoint(0,1),new SnakeBodyPart(new QPoint(0,2),nullptr))); // create snake with 3 body parts
    head = tail;
    while(head->getParent()){ // As long as the current SnakePart has a Parent
        head = head->getParent(); // go to the next BodyPart
    }
    direction = 2; // standard direction, down
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

SnakeBodyPart *Snake::getTail() const{
    return tail;
}

QPoint *Snake::getFood() const{
    return food;
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

