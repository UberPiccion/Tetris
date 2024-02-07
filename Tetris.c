
#include <time.h>
#include <string.h>
#include "Tetris.h"
#include "Sound.h"
#include <stdio.h>
#include "Draw.h"
extern int stage[];

extern const Color colorTypes[8];
extern const int *tetrominoTypes[7][4];
extern Music music_intro;
extern Music music_main;
extern Music music_gameover;



int points = 0;
float speed = 1.0f;


int main(int argc, char** argv, char** environ)
{
    tetromino *tetr = MemAlloc(sizeof(tetromino));
    InitializeAudioSystem();
    PlayMusic(music_main);
    tetr->startOffsetX = (SCREENWIDTH / 2) - ((STAGE_WIDTH * TILE_SIZE) / 2);
    tetr->startOffsetY = (SCREENHEIGHT / 2) - ((STAGE_HEIGHT * TILE_SIZE) / 2);

    tetr->StartX = STAGE_WIDTH / 2;
    tetr->StartY = 0;

    tetr->tetrominoX = tetr->StartX;
    tetr->tetrominoY = tetr->StartY;

    
    time_t unixTime;

    time(&unixTime);

    SetRandomSeed(unixTime);

    tetr->tetrominoType = GetRandomValue(0, 6);
    tetr->rotation = 0;

    const float moveTetrominoDownTimer = 1.f;
    float timeToMoveTetrominoDown = moveTetrominoDownTimer;
    tetr->color = GetRandomValue(0, 7);

    TraceLog(LOG_INFO, "Number of arguments : %d", argc);

    for(int i = 0; i < argc; i++)
    {
        TraceLog(LOG_INFO, "Argument : %d = %s", i, argv[i]);
    }

    while(*environ != 0)
    {
        TraceLog(LOG_INFO, "Argument : %s", *environ);
        environ++;
    }

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "TetrissozzoDiDio");

    SetTargetFPS(60);
    LoadTextures();
    
    

    while(!WindowShouldClose())
    {
        timeToMoveTetrominoDown -= GetFrameTime() * speed;
        LoopMusic(music_main);
        
        
        
        
        if (IsKeyPressed(KEY_SPACE))
        {
            const int lastRotation = tetr->rotation;

            tetr->rotation++;

            if (tetr->rotation > 3)
            {
                tetr->rotation = 0;
            }

            if (CheckCollision(tetr->tetrominoX,tetr->tetrominoY,tetrominoTypes[tetr->tetrominoType][tetr->rotation]))
            {
                tetr->rotation = lastRotation;
            }
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            // No need to check overflow, wall is your protector
            if (!CheckCollision(tetr->tetrominoX+1,tetr->tetrominoY,tetrominoTypes[tetr->tetrominoType][tetr->rotation]))
            {
                tetr->tetrominoX++;
            }
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            // No need to check overflow, wall is your protector
            if (!CheckCollision(tetr->tetrominoX-1,tetr->tetrominoY,tetrominoTypes[tetr->tetrominoType][tetr->rotation]))
            {
                tetr->tetrominoX--;
            }
        }

        if(timeToMoveTetrominoDown <= 0 || IsKeyPressed(KEY_DOWN))
        {            
            if(!CheckCollision(tetr->tetrominoX,tetr->tetrominoY+1,tetrominoTypes[tetr->tetrominoType][tetr->rotation]))
            {
                tetr->tetrominoY++;
                timeToMoveTetrominoDown = moveTetrominoDownTimer;
            }

            else
            {
                // const int currentTetrominoOffset = tetr.tetrominoY * STAGE_WIDTH + tetr.tetrominoX;
                
                // stage[currentTetrominoOffset] = 1;

                for(int y = 0; y < TETROMINO_SIZE; y++)
                {
                    for(int x = 0; x < TETROMINO_SIZE; x++)
                    {
                        const int offset = y * TETROMINO_SIZE + x;

                        const int *tetromino = tetrominoTypes[tetr->tetrominoType][tetr->rotation];

                        if(tetromino[offset] == 1)
                        {
                            const int offset_stage = (y + tetr->tetrominoY) * STAGE_WIDTH + (x + tetr->tetrominoX);
                            stage[offset_stage] = tetr->color  +1;
                        }
                    }
                }
                DeleteLines(&points, &speed,tetr);

                tetr->tetrominoX = tetr->StartX;
                tetr->tetrominoY = tetr->StartY;

                tetr->tetrominoType = GetRandomValue(0, 6);
                tetr->rotation = 0;
                tetr->color = GetRandomValue(0, 7);
            }
           
        }
        if(CheckGameover()){
            Gameover();
            break;
        }
        DrawAll(tetr);
    }
    UnloadTextures();
    UnloadAudioSystem(); 
    return 0;
}

void Gameover(){
    PlayMusic(music_gameover);
    while(!WindowShouldClose())
    {
        LoopMusic(music_gameover);
        DrawGameover();
    }
}