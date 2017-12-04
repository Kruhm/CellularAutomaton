#include "snake.h"

snake::snake(){
    create();
}

bool snake::collision(int dim){
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

void snake::eat(){
    QPoint headPos = head->getPos();
    bool isEating = false;
    if(direction == 2){
        if(headPos.x() == food->x() && headPos.y()+1 == food->y()){
            isEating = true;
        }
    }else if(direction == 4){
        if(headPos.x()-1 == food->x() && headPos.y() == food->y()){
            isEating = true;
        }
    }else if(direction == 6){
        if(headPos.x()+1 == food->x() && headPos.y() == food->y()){
            isEating = true;
        }
    }else if(direction == 8){
        if(headPos.x() == food->x() && headPos.y()-1 == food->y()){
            isEating = true;
        }
    }
    if(isEating){
        head->setParent(new SnakeBodyPart(new QPoint(food->x(),food->y()),nullptr));
        head = head->getParent();
        spawnFood();
    }
}

void snake::spawnFood(const int DIM){
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

void snake::move(){
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

void snake::die(){
    QMessageBox obituary;
    obituary.setText("Snake died... you lose");
    obituary.exec();
    reset();
}

void snake::reset(){
    destroy();
    create();
}

void snake::destroy(){
    delete head;
    delete tail;
}

void snake::create(){
    tail = new SnakeBodyPart(new QPoint(0,0),new SnakeBodyPart(new QPoint(0,1),new SnakeBodyPart(new QPoint(0,2),nullptr))); // create snake with 3 body parts
    // get to the snake head
    head = tail;
    while(head->getParent()){ // As long as the current SnakePart has a Parent
        head = head->getParent(); // go to the next BodyPart
    }
    direction = 2;
}
