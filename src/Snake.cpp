#include "Snake.h"


const float oneSize = 32.0f;

Snake::Snake()
{
    Vector2 initialPos = {11*oneSize, 6*oneSize};
    headSnake = new Node(initialPos, oneSize);
    tailSnake = headSnake;
    sizeSnake = 1;
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

    if(headSnake == nullptr){

        Node* newNode = new Node(tailSnake->getPosition(), tailSnake->getSize().x);
        tailSnake->setProx(newNode);
        tailSnake = newNode;
    }else{
        Vector2 newPos = {0.0f, 0.0f};
        newPos = tailSnake->getPosition();
        Node* newNode = new Node(newPos, tailSnake->getSize().x);
        tailSnake->setProx(newNode);
        tailSnake = newNode;
    }
    sizeSnake++;
}
void Snake::removeNode(){

}

Node* Snake::getHead(){
    return headSnake;
}
