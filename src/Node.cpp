#include "Node.h"

Node::Node(Vector2 recPosition, float sizeRec)
{
    rectanglePosition = recPosition;
    speedRectangleX = 0.0f;
    speedRectangleY = 0.0f;
    sizeRectangle = {sizeRec, sizeRec};
}

Node::~Node()
{
    //dtor
}

float Node::getSpeedX(){
    return speedRectangleX;
}
float Node::getSpeedY(){
    return speedRectangleY;
}

void Node::setSpeedX(float speedX){
    speedRectangleX = speedX;
}

void Node::setSpeedY(float speedY){
    speedRectangleY = speedY;
}

Vector2 Node::getPosition(){
    return rectanglePosition;
}

void Node::setPosition(Vector2 recPosition){
    rectanglePosition = recPosition;
}

Vector2 Node::getSize(){
    return sizeRectangle;
}

void Node::setSize(Vector2 sizeRec){
    sizeRectangle = sizeRec;
}

Node* Node::getProx(){
    return prox;
}

void Node::setProx(Node *p){
    prox = p;
}


