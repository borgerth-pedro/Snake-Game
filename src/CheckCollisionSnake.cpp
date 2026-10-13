#include "CheckCollisionSnake.hpp"

bool CheckCollisionSnake(Vector2 position1, Vector2 position2){
    if((position1.x == position2.x) && (position1.y == position2.y))
        return true;
    return false;
}
