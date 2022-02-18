#pragma once
#include <Windows.h>
#include <time.h>
#include <wtypes.h>

#define size_snake_max 32
#define size_snake_auto 5
#define width_wall 90
#define height_wall 20
extern int size_snake;
extern int state;
extern int snake_index[size_snake_max];
extern POINT gate_index[5];
extern POINT Snake[size_snake_max];
extern POINT Old_Snake[size_snake_max];
extern POINT food;

void GotoXY(int x, int y);

void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();
void Move(char WASD);

void DrawBoard();
void DrawSnake();
void DrawFood();
void DrawGate();

bool checkgate(POINT a);

void Create_newSnake();
void Create_Snakeindex();
void Create_food();
void Create_Gate();

void Delete_Old_Snake();
void Save_Snake();
void eat(int& point);
void changelevel();
