#include "UI.h"
#include "Snake.h"
#include <stdio.h>

void FixWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	long style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void Goto(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool CheckSnake(int x, int y)
{
	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		if (snake[i].x == x && snake[i].y == y)
			return false;
		else
			return true;
	}
}

void GenerateFood()
{
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE_FOOD; i++)
	{
		do {
			x = rand() % (WIDTH_CONSOLE - 1) + 1;
			y = rand() % (HEIGHT_CONSOLE - 1) + 1;
		} while (CheckSnake(x, y) == false);
		food[i] = { x,y };
	}
}

void StartGame()
{
	system("cls");
	ResetData();
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
	STATE = 1;
}

void ExitGame(HANDLE t)
{
	system("cls");
	TerminateThread(t, 0);
}

void PauseGame(HANDLE t)
{
	printf("GAME PAUSED...");
	SuspendThread(t);
}

void DrawBoard(int x, int y, int width, int height) 
{
	int curPosX = 0;
	int curPosY = 0;
	Goto(x, y);
	printf("X");
	for (int i = 1; i < width; i++)
		printf("X");
	printf("X");
	Goto(x, height + y);
	printf("X");
	for (int i = 1; i < width; i++)
		printf("X");
	printf("X");
	for (int i = y + 1; i < height + y; i++)
	{
		Goto(x, i);
		printf("X");
		Goto(x + width, i);
		printf("X");
	}

	Goto(curPosX, curPosY);
}

void DrawSnakeAndFood(const char *str)
{
	Goto(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
	printf(str);
	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		Goto(snake[i].x, snake[i].y);
		printf(str);
	}
}