#include <stdlib.h>
#include <stdio.h>
#include "../../src/raylib.h"
#include "../../src/raymath.h"

#define COLS 50
#define ROWS 50
#define SCREENWIDTH 600
#define SCREENHEIGHT 600
#define CELLWIDTH SCREENWIDTH / COLS
#define CELLHEIGHT SCREENHEIGHT / ROWS
#define FPS 120

int main() {
  int mat[ROWS][COLS];
  int buffer[ROWS][COLS];
  SetTargetFPS(FPS);
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Random tetris rain");
  int score = 0;

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      mat[i][j] = 0;
      buffer[i][j] = 0;
    }
  }

  while (!WindowShouldClose()) {
    DrawText(TextFormat("SCORE:%d", score / 100), 40, 160, 100, BLUE);
    DrawText(TextFormat("SCORE:%d", score / 100), 40, 160, 100, BLUE);
    int row = rand() % ROWS;
    int col = rand() % COLS;
    mat[row][col] = 1;

    for (int i = ROWS - 2; i >= 0; i--) {
      for (int j = 0; j < COLS; j++) {
        if (mat[i][j] == 1 && mat[i + 1][j] == 0) {
        //original value to 0
          buffer[i][j] = 0;
        //moving pixel down
          buffer[i+1][j] = 1; 
        }
      }
    }

    int rowSum = 0;
    for (int j = 0; j < ROWS; j++) {
      rowSum += mat[ROWS - 1][j];
    }
    printf("\n%d", rowSum);

    if (rowSum == COLS) {
      printf("BOOM:\n\n%d", rowSum);
      for (int j = 0; j < COLS; j++) {
        buffer[ROWS - 1][j] = 0;
        score++;
      }
    }

    // COPY THE CONTENT TO BUFFER
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        mat[i][j] = buffer[i][j];
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int row = 0; row < ROWS; row++) {
      for (int col = 0; col < COLS; col++) {
        if (mat[row][col] != 0) {
          DrawRectangle(col * CELLWIDTH, row * CELLHEIGHT, CELLWIDTH, CELLHEIGHT,(Color){  GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255});
        }
        DrawRectangleLines(col * CELLWIDTH, row * CELLHEIGHT, CELLWIDTH, CELLHEIGHT, GRAY);
      }
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
