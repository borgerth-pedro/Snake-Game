#include "Rabo.h"

Rabo::Rabo(Vector2 recPosition, float sizeRec)
{
    rectanglePosition = recPosition;
    speedRectangleX = 0.0f;
    speedRectangleY = 0.0f;
    sizeRectangle = {sizeRec, sizeRec};
}

Rabo::~Rabo()
{
    //dtor
}

float Rabo::getSpeedX(){
    return speedRectangleX;
}
float Rabo::getSpeedY(){
    return speedRectangleY;
}

void Rabo::setSpeedX(float speedX){
    speedRectangleX = speedX;
}

void Rabo::setSpeedY(float speedY){
    speedRectangleY = speedY;
}

Vector2 Rabo::getPosition(){
    return rectanglePosition;
}

void Rabo::setPosition(Vector2 recPosition){
    rectanglePosition = recPosition;
}

Vector2 Rabo::getSize(){
    return sizeRectangle;
}

void Rabo::setSize(Vector2 sizeRec){
    sizeRectangle = sizeRec;
}

