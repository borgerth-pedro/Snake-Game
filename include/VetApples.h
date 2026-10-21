#ifndef VETAPPLES_H
#define VETAPPLES_H
#include <raylib.h>
#include "Apple.h"

class VetApples
{
    public:
        VetApples(int applesMax);
        ~VetApples();

        void addApple(Vector2 applePos);
        void removeApple(Vector2 applePos);
        int findApple(Vector2 applePos);

        int getNumApples();
        Apple getApple(int inx);

        void reset();

    private:
        int apples = 0;
        int maxApples = 0;
        Apple *vet = nullptr;
};

#endif // VETAPPLES_H
