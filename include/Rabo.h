#ifndef RABO_H
#define RABO_H

#include <raylib.h>
class Rabo
{
    public:
        Rabo(Vector2 recPosition, float sizeRec);
        ~Rabo();
        //Metodos
        float getSpeedX();
        float getSpeedY();
        void setSpeedX(float speedX);
        void setSpeedY(float speedY);
        Vector2 getPosition();
        void setPosition(Vector2 recPosition);
        Vector2 getSize();
        void setSize(Vector2 sizeRec);

    private:
        Vector2 rectanglePosition;
        float speedRectangleX;
        float speedRectangleY;
        Vector2 sizeRectangle;
};

#endif // RABO_H
