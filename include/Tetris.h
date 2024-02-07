#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 24
#define TETROMINO_SIZE 4
#define SCREENWIDTH 700
#define SCREENHEIGHT 600
#include "Tetromini.h"
#include "raylib.h"
int CheckCollision(const int tetrominoStartX, const int tetrominoStartY, const int *tetromino);
void drawTetromino(tetromino *tetr, const int *type, Color color);
void ResetLines(int startLineY);
void DeleteLines(int *points, float *speed,tetromino *tetr);
int CheckGameover();
void Gameover();
void DrawAll(tetromino *tetr);
void PlayAnimation(int startLineY,tetromino *tet);