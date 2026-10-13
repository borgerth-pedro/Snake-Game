#ifndef APPLE_H
#define APPLE_H
#include <raylib.h>

class Apple
{
    public:
        Apple();
        Apple(Vector2 applePos);
        ~Apple();

        Vector2 getPosition();
        void setPosition(Vector2 applePos);

    private:
        Vector2 applePosition;
};

#endif // APPLE_H
