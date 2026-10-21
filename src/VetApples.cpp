#include "VetApples.h"
#include "Apple.h"

VetApples::VetApples(int applesMax)
{
    if(applesMax > 0){
        vet = new Apple [applesMax];
        maxApples = applesMax;
    }
}

VetApples::~VetApples()
{
    if(vet != nullptr)
        delete [] vet;
}

void VetApples::addApple(Vector2 applePos)
{
    if(apples <= maxApples){
        Apple *newApple = new Apple(applePos);
        vet[apples] = *newApple;
        apples++;
    }
}

void VetApples::removeApple(Vector2 applePos)
{
    int p = findApple(applePos);
    if(p == -1 ){return;}
    if(p + 1 == apples){apples--;}

    for(int i = p; i<apples-1; i++){
        vet[i] = vet[i+1];
    }
    apples--;
}

int VetApples::findApple(Vector2 applePos)
{
    for(int i = 0; i < apples; i++){
        if((vet[i].getPosition().x == applePos.x) && (vet[i].getPosition().y == applePos.y))
            return i;
    }
    return -1;
}

int VetApples::getNumApples(){
    return apples;
}

Apple VetApples::getApple(int inx){
    return vet[inx];
}

void VetApples::reset(){
    apples = 0;
}
