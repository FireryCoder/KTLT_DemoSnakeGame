#include "setting.h"
#include "control_snake.h"
#include <string.h>
#include <conio.h>
#include<iostream>

using namespace std;

#define size_snake_max 32
#define size_snake_auto 5
#define width_wall 90
#define height_wall 20
int size_snake;
int snake_index[size_snake_max];
POINT Snake[size_snake_max];
POINT Old_Snake[size_snake_max];
POINT food;
int state;
// state = 0 <=> snake_die
// state = 1 <=> play game
// state = 2 <=> change_level ( gate appear )
// state = 3 <=> END GAME ( completed )

int main(void)
{
	ShowConsoleCursor(false);
	DrawBoard();
	char movekey = 'd';
	//tạo rắn
	size_snake = size_snake_auto;
	Create_Snake();
	Create_newSnake();
	Save_Snake();
	//tạo thức ăn
	Create_food();
	DrawFood();
	//
	int point = 0;
	while (true) {
		GotoXY(0, 21);
		cout << "point : " << point;
		if (_kbhit()) {
			movekey = _getch();
			Move(movekey);
		}
		else {
			Move(movekey);
		}
		if (Snake[0].x == food.x && Snake[0].y == food.y)
		{ // eat
			if (size_snake % 8 != 0) {
				size_snake++;
				Create_food();
				DrawFood();
				point += 10;
				Snake[size_snake - 1] = food;
				for (int i = 1; i < size_snake; i++)
				{
					Snake[i] = Snake[i - 1];
				}
				Snake[0] = Snake[size_snake - 1];
			}
			else
			{
				size_snake++;
				//Create_food();
				//DrawFood();
				point += 10;
				Snake[size_snake - 1] = food;
				for (int i = 1; i < size_snake; i++)
				{
					Snake[i] = Snake[i - 1];
				}
				Snake[0] = Snake[size_snake - 1];
			}
		}
		Delete_Old_Snake();
		DrawSnake();
		Save_Snake();
		Sleep(200);
	}
	ShowCursor(false);
	_getch();
}