#include "Snake.h"


const float oneSize = 32.0f;

Snake::Snake()
{
    Vector2 initialPos = {11*oneSize, 6*oneSize};
    Node* newNode1 = new Node(initialPos, oneSize);
    headSnake = newNode1;
    tailSnake = headSnake;
    newNode1->setSpeedX(0);
    newNode1->setSpeedY(-oneSize);

    Node* newNode2 = new Node({11*oneSize, 7*oneSize}, oneSize);
    tailSnake = newNode2;
    headSnake->setProx(tailSnake);

    sizeSnake = 2;

}

Snake::~Snake()
{
    if(headSnake->getProx() == nullptr){
        delete headSnake;
        return;
    }
    Node *p;
    for(Node *i = headSnake; i != nullptr; i->getProx()){
        p = headSnake;
        headSnake = headSnake->getProx();
        delete p;
    }
}

int Snake::getSize(){
    return sizeSnake;
}
void Snake::addNode(){

    Node* newNode = new Node(tailSnake->getPosition(), tailSnake->getSize().x);
    tailSnake->setProx(newNode);
    tailSnake = newNode;
    sizeSnake++;
}
void Snake::removeNode(){

}

Node* Snake::getHead(){
    return headSnake;
}

Node* Snake::getTail(){
    return tailSnake;
}
