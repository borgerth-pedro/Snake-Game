#include <iostream>
#include <raylib.h>
#include "rlgl.h"
#include "raymath.h"
#include "Node.h"
#include "Snake.h"
#include "Grid.hpp"

using namespace std;

int main(void)
{
    //Inicialization
    //--------------------------------------------------------------------------------------
    const int screenWidth  = 800;
    const int screenHeight = 448;
    const float oneSize    = 32.0f;

    int currentFPS = 60;
    SetTargetFPS(currentFPS);

    Snake snake;


    float timeMove         = 0.0f;
    float timeMoveInterval = 0.2f;


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



        timeMove += GetFrameTime();


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

            EndMode2D();
        EndDrawing();
    }
    CloseWindow();


    return 0;
}
