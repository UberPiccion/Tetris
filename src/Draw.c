#include "Tetris.h"
#include <raylib.h>
#include "Draw.h"
#include <stdio.h>
extern int stage[];
extern const Color colorTypes[8];
extern const int *tetrominoTypes[7][4];
Texture2D backgroundGame;
Texture2D backgroundOver;
Image bgOver;
Image bgGame;
Font fontTtf;
char msg[5] = "";
extern int points;
void drawTetromino(tetromino *tetr, const int *type, Color color)
{
    for(int y = 0; y < TETROMINO_SIZE; y++)
    {
        for(int x = 0; x < TETROMINO_SIZE; x++)
        {
            const int offset = y * TETROMINO_SIZE + x;

            if(type[offset] == 1)
            {
                DrawRectangle((x + tetr->tetrominoX) * TILE_SIZE + tetr->startOffsetX, (y + tetr->tetrominoY) * TILE_SIZE + tetr->startOffsetY, TILE_SIZE, TILE_SIZE, color);
                
            }
        }
    }
}

void DrawAll(tetromino *tetr){
    sprintf(msg,"%d",points);
    BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawTexture(backgroundGame, SCREENWIDTH/2 - backgroundGame.width/2,SCREENHEIGHT/2 - backgroundGame.height/2,WHITE);
        DrawTextEx(fontTtf, msg,(Vector2){10.0f,10.0f},(float)fontTtf.baseSize,2.0f,BLACK);
        for(int y = 0; y < STAGE_HEIGHT; y++)
        {
            for(int x = 0; x < STAGE_WIDTH; x++)
            {
                const int offset = y * STAGE_WIDTH + x;
                const int color = stage[offset];

                if(stage[offset] != 0)
                {
                    DrawRectangle(x * TILE_SIZE + tetr->startOffsetX, y * TILE_SIZE + tetr->startOffsetY, TILE_SIZE, TILE_SIZE, colorTypes[color-1]);
                }
                else{
                    DrawRectangle(x * TILE_SIZE + tetr->startOffsetX, y * TILE_SIZE + tetr->startOffsetY, TILE_SIZE, TILE_SIZE, (Color){100,100,100,100});
                }

                DrawRectangleLines(x * TILE_SIZE + tetr->startOffsetX, y * TILE_SIZE + tetr->startOffsetY, TILE_SIZE, TILE_SIZE, BLACK);
            }
        }
        
        drawTetromino(tetr, tetrominoTypes[tetr->tetrominoType][tetr->rotation], colorTypes[tetr->color]);
        
    EndDrawing();
}
void DrawGameover(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(backgroundOver, SCREENWIDTH/2 - backgroundGame.width/2,SCREENHEIGHT/2 - backgroundGame.height/2,WHITE);
    DrawRectangle(0,0,SCREENWIDTH,200,(Color){100,100,100,150});
    DrawTextEx(fontTtf,"GAMEOVER",(Vector2){10,10},(float)72,4.0f,LIGHTGRAY);
    DrawTextEx(fontTtf, msg,(Vector2){10.0f,100},(float)72,4.0f,LIGHTGRAY);
    EndDrawing();
}
void LoadTextures(){
    bgGame = LoadImage("resources/game.png");
    backgroundGame = LoadTextureFromImage(bgGame);
    bgOver = LoadImage("resources/gameover.png");
    backgroundOver = LoadTextureFromImage(bgOver);
    fontTtf = LoadFontEx("resources/ka1.ttf",32,0,100);
}
void UnloadTextures(){
    UnloadTexture(backgroundGame);
    UnloadTexture(backgroundOver);
    UnloadImage(bgGame);
    UnloadImage(bgOver);
    UnloadFont(fontTtf);
}