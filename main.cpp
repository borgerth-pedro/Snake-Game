#include <iostream>
#include <raylib.h>
#include "Rabo.h"

using namespace std;

int main(void)
{
    //Inicialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    int currentFPS = 60;
    SetTargetFPS(currentFPS);

    Camera2D camera = {0};

    Rabo head({0,0}, 32.0f);

    float timeMove     = 0.0f;
    float timeMoveInterval = 0.2f;



    InitWindow(screenWidth, screenHeight, "Snake Game - Pedro Borgerth");

    //Main Game loop
    while(WindowShouldClose() == false){
        // Update
        //----------------------------------------------------------------------------------

        if(IsKeyDown(KEY_W)) {head.setSpeedY(-32.0f); head.setSpeedX(0.0f);}
        if(IsKeyDown(KEY_A)) {head.setSpeedX(-32.0f); head.setSpeedY(0.0f);}
        if(IsKeyDown(KEY_S)) {head.setSpeedY( 32.0f); head.setSpeedX(0.0f);}
        if(IsKeyDown(KEY_D)) {head.setSpeedX( 32.0f); head.setSpeedY(0.0f);}

        Vector2 currentPos = head.getPosition();

        timeMove += GetFrameTime();

        if(timeMove >= timeMoveInterval){
            currentPos.x += head.getSpeedX();
            currentPos.y += head.getSpeedY();
            timeMove -= timeMoveInterval;
        }


        if(currentPos.x > screenWidth)  currentPos.x = 0.0f;
        if(currentPos.x < 0)            currentPos.x = screenWidth - head.getSize().x;
        if(currentPos.y > screenHeight) currentPos.y = 0.0f;
        if(currentPos.y < 0)            currentPos.y = screenHeight - head.getSize().y;


        head.setPosition(currentPos);
        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleV(head.getPosition(), head.getSize(), GREEN);
            BeginMode2D(camera);
                DrawGrid(100, 50);
            EndMode2D();

        EndDrawing();
    }
    CloseWindow();


    return 0;
}
