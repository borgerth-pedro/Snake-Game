#include "Knot.h"

Knot::Knot(Vector2 recPosition, float sizeRec)
{
    rectanglePosition = recPosition;
    speedRectangleX = 0.0f;
    speedRectangleY = 0.0f;
    sizeRectangle = {sizeRec, sizeRec};
}

Knot::~Knot()
{
    //dtor
}

float Knot::getSpeedX(){
    return speedRectangleX;
}
float Knot::getSpeedY(){
    return speedRectangleY;
}

void Knot::setSpeedX(float speedX){
    speedRectangleX = speedX;
}

void Knot::setSpeedY(float speedY){
    speedRectangleY = speedY;
}

Vector2 Knot::getPosition(){
    return rectanglePosition;
}

void Knot::setPosition(Vector2 recPosition){
    rectanglePosition = recPosition;
}

Vector2 Knot::getSize(){
    return sizeRectangle;
}

void Knot::setSize(Vector2 sizeRec){
    sizeRectangle = sizeRec;
}

Knot* Knot::getProx(){
    return prox;
}

void Knot::setProx(Knot *p){
    prox = p;
}


