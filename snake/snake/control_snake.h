#pragma once
#include <Windows.h>
#include <time.h>
#include <wtypes.h>

#define size_snake_max 32
#define size_snake_auto 5
#define width_wall 90
#define height_wall 20
#define size_gate_max 6
#define height_console 27
#define width_console 100
extern int size_snake;
extern int state;
extern int size_wall;
extern int snake_index[size_snake_max];
extern POINT gate_index[size_gate_max];
extern POINT Old_Snake[size_snake_max];
extern POINT Snake[size_snake_max];
extern POINT Wall[1000];
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
void Draw_setup(int x, int y,int speed);

bool checkgate(POINT a);

void Create_newSnake();
void Create_Snakeindex();
void Create_food();
void Create_Gate();
void Create_Board(int level, int x, int y);

void Delete_Old_Snake();
void Save_Snake();
void eat(int& point, int& speed);
void changelevel();
