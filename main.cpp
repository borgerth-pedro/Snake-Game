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
#include "ResetGame.hpp"


using namespace std;

int main(void)
{
    //Inicialization
    //--------------------------------------------------------------------------------------
    const float oneSize    = 32.0f;
    const int screenBlocksX = 20;
    const int screenBlocksY = 10;
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


    bool gamePause = false;

    float timeMove          = 0.0f;
    float timeMoveInterval  = 0.5f;
    float timeApple         = 0.0f;
    float timeBonusApple    = 0.0002f;
    float timeBonusMovement = 0.0002f;
    float randowTimeApple   = rtv(gen) * timeMoveInterval;

    bool moveW = 1, moveA, moveS, moveD;
    bool moveAuxW = 1, moveAuxA, moveAuxS, moveAuxD;

    InitWindow(screenWidth, screenHeight, "Snake Game - Pedro Borgerth");

    Camera2D camera = {0};
    camera.zoom = 1.0f;

    Image image2 = LoadImage("resources/image/gameOverYes.png");
    Image image3 = LoadImage("resources/image/gameOverNo.png");

    ImageResize(&image2, screenWidth, screenHeight);
    ImageResize(&image3, screenWidth, screenHeight);

    Texture2D texture2 = LoadTextureFromImage(image2);
    Texture2D texture3 = LoadTextureFromImage(image3);

    UnloadImage(image2);
    UnloadImage(image3);

    bool gameOverYes = false;

    InitAudioDevice();              // Initialize audio device

    Music gameMusic = LoadMusicStream("resources/audio/50s-bit.ogg");
    Sound deathMusic = LoadSound("resources/audio/Death6.wav");
    Sound moveMusic = LoadSound("resources/audio/air_move.wav");
    Sound eatMusic = LoadSound("resources/audio/apple_bite.ogg");

    PlayMusicStream(gameMusic);

    float timeMusic = 0.0f;        // Time played normalized [0.0f..1.0f]
    float panMusic = 0.0f;         // Default audio pan center [-1.0f..1.0f]
    float volumeMusic = 0.2f;      // Default audio volume [0.0f..1.0f]

    bool pauseMusic = false;
    SetMusicPan(gameMusic, panMusic);
    SetMusicVolume(gameMusic, volumeMusic);

    float timeMusicDeath = 2.0f;
    float panMusicDeath = 0.0f;         // Default audio pan center [-1.0f..1.0f]
    float volumeMusicDeath = 1.0f;      // Default audio volume [0.0f..1.0f]

    bool pauseMusicDeath = false;
    SetSoundPan(deathMusic, panMusicDeath);
    SetSoundVolume(deathMusic, volumeMusicDeath);
    SetSoundPitch(deathMusic, timeMusicDeath);

    float timeMoveMusic = 4.0f;        // Time played normalized [0.0f..1.0f]
    float panMusicMove = 0.0f;         // Default audio pan center [-1.0f..1.0f]
    float volumeMusicMove = 0.03f;      // Default audio volume [0.0f..1.0f]

    SetSoundPan(moveMusic, panMusicMove);
    SetSoundVolume(moveMusic, volumeMusicMove);
    SetSoundPitch(moveMusic, timeMoveMusic);

    float timeEatMusic = 1.5f;        // Time played normalized [0.0f..1.0f]
    float panMusicEat = 0.0f;         // Default audio pan center [-1.0f..1.0f]
    float volumeMusicEat = 1.0f;      // Default audio volume [0.0f..1.0f]

    SetSoundPan(eatMusic, panMusicEat);
    SetSoundVolume(eatMusic, volumeMusicEat);
    SetSoundPitch(eatMusic, timeEatMusic);

    bool death = false;

    //Main Game loop
    while(WindowShouldClose() == false){
        // Update
        //----------------------------------------------------------------------------------


        if(IsKeyDown(KEY_W) && moveS != true)
            {snake.getHead()->setSpeedY(-oneSize); snake.getHead()->setSpeedX(0);
            moveAuxW = 1; moveAuxA = 0; moveAuxS = 0; moveAuxD = 0;}

        if(IsKeyDown(KEY_A) && moveD != true)
            {snake.getHead()->setSpeedX(-oneSize); snake.getHead()->setSpeedY(0);
            moveAuxW = 0; moveAuxA = 1; moveAuxS = 0; moveAuxD = 0;}

        if(IsKeyDown(KEY_S) && moveW != true)
            {snake.getHead()->setSpeedY( oneSize); snake.getHead()->setSpeedX(0);
            moveAuxW = 0; moveAuxA = 0; moveAuxS = 1; moveAuxD = 0;}

        if(IsKeyDown(KEY_D) && moveA != true)
            {snake.getHead()->setSpeedX( oneSize); snake.getHead()->setSpeedY(0);
            moveAuxW = 0; moveAuxA = 0; moveAuxS = 0; moveAuxD = 1;}


        if(IsKeyDown(KEY_P)){
            if(gamePause){
                gamePause = 0;
            }
            else{
                gamePause = 1;
            }

            pauseMusic = !pauseMusic;

            if (pauseMusic) PauseMusicStream(gameMusic);
            else ResumeMusicStream(gameMusic);

        }

        UpdateMusicStream(gameMusic);

        if (IsKeyDown(KEY_DOWN))
        {
            volumeMusic -= 0.05f;
            if (volumeMusic < 0.0f) volumeMusic = 0.0f;
            SetMusicVolume(gameMusic, volumeMusic);
        }
        else if (IsKeyDown(KEY_UP))
        {
            volumeMusic += 0.05f;
            if (volumeMusic > 1.0f) volumeMusic = 1.0f;
            SetMusicVolume(gameMusic, volumeMusic);
        }

        float deltaTime = GetFrameTime();

        if(!gamePause){
            timeMove  += (deltaTime+timeBonusMovement);
            timeApple += (deltaTime+timeBonusApple);
        }else{PauseMusicStream(gameMusic);}



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

            if(moveAuxW){moveW = 1; moveA = 0; moveS = 0; moveD = 0;}
            if(moveAuxA){moveW = 0; moveA = 1; moveS = 0; moveD = 0;}
            if(moveAuxS){moveW = 0; moveA = 0; moveS = 1; moveD = 0;}
            if(moveAuxD){moveW = 0; moveA = 0; moveS = 0; moveD = 1;}

            PlaySound(moveMusic);

            timeMove -= timeMoveInterval;
        }


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

        if(snake.getHead()->getPosition().x < 0 || snake.getHead()->getPosition().x > screenWidth - 1)
            snakeCollision = true;
        if(snake.getHead()->getPosition().y < 0 || snake.getHead()->getPosition().y > screenHeight - 1)
            snakeCollision = true;

        if(snakeCollisionApple){
            PlaySound(eatMusic);
            snake.addNode();
            snake.addNode();
            vetApples.removeApple(appleEatPos);
            timeBonusApple    += 0.0002;
            timeBonusMovement += 0.0002;
            timeMoveMusic     += 0.1;
            SetSoundPitch(moveMusic, timeMoveMusic);
        }

        if(snakeCollision){gamePause = true;}

        if(snakeCollision && !death){PlaySound(deathMusic); death = true;}

        timeMusic = GetMusicTimePlayed(gameMusic)/GetMusicTimeLength(gameMusic);

        if (timeMusic > 1.0f) timeMusic = 1.0f;

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
                for(int i =0; i<vetApples.getNumApples(); i++){
                    DrawRectangleV(vetApples.getApple(i).getPosition(), {oneSize,oneSize}, YELLOW);
                }
                if(snakeCollision == true){
                    if(IsKeyDown(KEY_A)){gameOverYes = false;}
                    if(IsKeyDown(KEY_D)){gameOverYes = true;}

                    if(!gameOverYes){
                        DrawTexture(texture2, screenWidth/2 - texture2.width/2, screenHeight/2 - texture2.height/2, WHITE);
                        if(IsKeyDown(KEY_ENTER)){
                            ResetGame(snake, vetApples, gamePause, timeMove, timeApple);
                            moveW = 1; moveA = 0; moveS = 0; moveD = 0;
                            moveAuxW = 1; moveAuxA = 0; moveAuxS = 0; moveAuxD = 0;
                            WaitTime(1);
                            snakeCollision == false;
                            ResumeMusicStream(gameMusic);
                            death = false;
                            timeMoveMusic = 4.0f;
                        }
                    }else{
                        DrawTexture(texture3, screenWidth/2 - texture3.width/2, screenHeight/2 - texture3.height/2, WHITE);
                        if(IsKeyDown(KEY_ENTER)){
                            break;
                        }
                    }
                }
            EndMode2D();
        EndDrawing();
    }
    CloseWindow();


    return 0;
}
