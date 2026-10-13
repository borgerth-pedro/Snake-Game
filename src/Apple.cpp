#include "Apple.h"

Apple::Apple(){}

Apple::Apple(Vector2 applePos)
{
    applePosition = applePos;
}

Apple::~Apple()
{
    //dtor
}

Vector2 Apple::getPosition()
{
    return applePosition;
}

void Apple::setPosition(Vector2 applePos)
{
    applePosition = applePos;
}
