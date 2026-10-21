#include "ResetGame.hpp"
#include "Snake.h"
#include "VetApples.h"

void ResetGame(Snake& snake, VetApples& vetApples, bool& gamePause, float& timeMove, float& timeApple)
{
    snake.reset();
    vetApples.reset();

    timeMove = 0.0f;
    timeApple = 0.0f;
    gamePause = false;
}
