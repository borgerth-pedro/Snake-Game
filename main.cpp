#include <iostream>
#include <raylib.h>
#include <random>
#include "rlgl.h"
#include "raymath.h"
#include "Node.h"
#include "Snake.h"
#include "Grid.hpp"
#include "CheckCollisionSnake.hpp"
#include "Apple.h"
#include "VetApples.h"


using namespace std;

int main(void)
{
    //Inicialization
    //--------------------------------------------------------------------------------------
    const float oneSize    = 32.0f;
    const int screenBlocksX = 25;
    const int screenBlocksY = 14;
    int screenSize = screenBlocksX * screenBlocksY;

    const int screenWidth  = screenBlocksX*oneSize;
    const int screenHeight = screenBlocksY*oneSize;




    int currentFPS = 60;
    SetTargetFPS(currentFPS);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rtv(20, 30);
    uniform_int_distribution<int> randPosX(0, screenBlocksX - 1);
    uniform_int_distribution<int> randPosY(0, screenBlocksY - 1);

    Snake snake;
    const int maxApples = 5;
    VetApples vetApples(maxApples);


    float timeMove          = 0.0f;
    float timeMoveInterval  = 0.5f;
    float timeApple         = 0.0f;
    float timeBonusApple    = 0.0005f;
    float timeBonusMovement = 0.0f;
    float randowTimeApple   = rtv(gen) * timeMoveInterval;


    InitWindow(screenWidth, screenHeight, "Snake Game - Pedro Borgerth");

    Camera2D camera = {0};
    camera.zoom = 1.0f;

    //Main Game loop
    while(WindowShouldClose() == false){
        // Update
        //----------------------------------------------------------------------------------


        if(IsKeyDown(KEY_W)) {snake.getHead()->setSpeedY(-oneSize); snake.getHead()->setSpeedX(0);}
        if(IsKeyDown(KEY_A)) {snake.getHead()->setSpeedX(-oneSize); snake.getHead()->setSpeedY(0);}
        if(IsKeyDown(KEY_S)) {snake.getHead()->setSpeedY( oneSize); snake.getHead()->setSpeedX(0);}
        if(IsKeyDown(KEY_D)) {snake.getHead()->setSpeedX( oneSize); snake.getHead()->setSpeedY(0);}


        float deltaTime = GetFrameTime();
        timeMove  += (deltaTime+timeBonusMovement);
        timeApple += (deltaTime+timeBonusApple);


        if(timeMove >= timeMoveInterval){

                Vector2 prevPos = snake.getHead()->getPosition();

                for(Node* i = snake.getHead(); i != nullptr; i = i->getProx()){
                    Vector2 currentPos = i->getPosition();
                    i->setPosition(prevPos);
                    prevPos = currentPos;
                }

                Vector2 posHead = snake.getHead()->getPosition();
                posHead.x += snake.getHead()->getSpeedX();
                posHead.y += snake.getHead()->getSpeedY();
                snake.getHead()->setPosition(posHead);


            timeMove -= timeMoveInterval;
        }
        if(IsKeyPressed(KEY_R)){snake.addNode();}


        if(timeApple >= randowTimeApple){
            Vector2 randomPosApple;
            bool appleErroCollision;

            do{
                appleErroCollision = false;

                randomPosApple = {
                    static_cast<float>(randPosX(gen) * (int)oneSize),
                    static_cast<float>(randPosY(gen) * (int)oneSize)
                };

                for(Node* i = snake.getHead(); i != nullptr; i = i->getProx()){
                    if(CheckCollisionSnake(randomPosApple, i->getPosition())){
                        appleErroCollision = true;
                        break;
                    }
                }
                if (!appleErroCollision){
                    for(int i = 0; i<vetApples.getNumApples(); i++){
                        if(CheckCollisionSnake(randomPosApple, vetApples.getApple(i).getPosition())){
                            appleErroCollision = true;
                            break;
                        }
                    }
                }

            }while(appleErroCollision);

            vetApples.addApple(randomPosApple);

            timeApple = 0.0f;
            randowTimeApple = rtv(gen) * timeMoveInterval;
        }


        bool snakeCollision = false;
        for(Node* i = snake.getHead(); i->getProx() != nullptr; i = i->getProx()){
            if(CheckCollisionSnake(snake.getHead()->getPosition(), i->getProx()->getPosition()))
                snakeCollision = true;
        }


        bool snakeCollisionApple = false;
        Vector2 appleEatPos = {-1, -1};
        for(Node* i = snake.getHead(); i != nullptr; i = i->getProx()){
            for(int j = 0; j<vetApples.getNumApples(); j++){
                if(CheckCollisionSnake(i->getPosition(), vetApples.getApple(j).getPosition())){
                    snakeCollisionApple = true;
                    appleEatPos = vetApples.getApple(j).getPosition();
                    break;
                }
            }
        }
        if(snakeCollisionApple){
            snake.addNode();
            vetApples.removeApple(appleEatPos);
            timeBonusApple += 0.00025f;
        }


        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

                DrawGrid2D(camera, screenWidth, screenHeight, oneSize, 1, BLACK);
                for (Node* i = snake.getHead(); i != nullptr; i = i->getProx()) {
                    Color color;
                    if(i == snake.getTail()){
                        color = RED;
                    }else if(i == snake.getHead()){
                        color = DARKGREEN;
                    }else{
                        color = GREEN;
                    }
                    DrawRectangleV(i->getPosition(), i->getSize(), color);
                }
                if(snakeCollision == true){
                    DrawText("Colisão detectada", 11*oneSize, 6*oneSize, 20, GRAY);
                }
                for(int i =0; i<vetApples.getNumApples(); i++){
                    DrawRectangleV(vetApples.getApple(i).getPosition(), {oneSize,oneSize}, YELLOW);
                }

            EndMode2D();
        EndDrawing();
    }
    CloseWindow();


    return 0;
}
