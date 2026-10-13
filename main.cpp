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
    uniform_int_distribution<int> randPosX(0, screenBlocksX);
    uniform_int_distribution<int> randPosY(0, screenBlocksY);

    Snake snake;
    Apple vetApples[screenSize];
    int apples = 0;


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




        int randomTimeValue = rtv(gen);
        if(timeMove >= randomTimeValue*timeMoveInterval){
            //pegar posição aleatória dentro das delimitações do mapa; feito
            Vector2 randomPosApple = {randPosX(gen),randPosY(gen)};
            bool appleErroCollision = false;
            do{
                randomPosApple = {randPosX(gen),randPosY(gen)};

                //checar se na posição já tem uma maça ou Snake;
                for(Node* i = snake.getHead(); i->getProx() != nullptr; i = i->getProx()){
                    if(CheckCollisionSnake(snake.getHead()->getPosition(), i->getProx()->getPosition())){
                        appleErroCollision = true;
                        break;
                    }
                }
                for(int i = 0; i<screenSize; i++){
                    if(CheckCollisionSnake(randomPosApple, vetApples[i].getPosition())){
                        appleErroCollision = true;
                        break;
                    }
                }
            }while(appleErroCollision);

            vetApples[apples] = Apple(randomPosApple);
            apples++;
                //se tiver, gera nova posição aleatoria e testa;
                //se não tiver, gera maça;
        }


        bool snakeCollision = false;
        for(Node* i = snake.getHead(); i->getProx() != nullptr; i = i->getProx()){
            if(CheckCollisionSnake(snake.getHead()->getPosition(), i->getProx()->getPosition()))
                snakeCollision = true;
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
                for(int i =0; i<screenSize; i++){
                    DrawRectangleV(vetApples[i].getPosition(), {oneSize,oneSize}, YELLOW);
                }

            EndMode2D();
        EndDrawing();
    }
    CloseWindow();


    return 0;
}
