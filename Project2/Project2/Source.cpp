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
int size_wall;
int snake_index[size_snake_max];
POINT Snake[size_snake_max];
POINT Old_Snake[size_snake_max];
POINT food;
POINT gate_index[5];
POINT Wall[1000];
int state;
// state = 0 <=> snake_die
// state = 1 <=> play game
// state = 2 <=> before_change_level ( gate appear )
// state = 3 <=> up_level
// state = 4 <=> END GAME ( completed )

int main(void)
{
	ShowConsoleCursor(false);
RESET:
	//tạo rắn
	size_snake = size_snake_auto + 2;
	// tạo điểm 
	int point = 0;
	int level = 1;
	int SPEED = 1;
UP_LEVEL:
	char movekey = 'd';
	system("cls");
	//Clean_console(); // xoa man hinh cu
	Create_Board(level);
	DrawBoard();
	Create_Snakeindex();
	Create_newSnake();
	Save_Snake();
	//tạo thức ăn
	Create_food();
	DrawFood();
	// tạo trạng thái
	state = 1;
	while (true) {
		GotoXY(0, 21);
		cout << "point : " << point << endl;
		cout << "Level : " << level << endl;
		if (_kbhit()) {
			movekey = _getch();
			Move(movekey);
		}
		else {
			Move(movekey);
		}
		if (Snake[0].x == food.x && Snake[0].y == food.y)
		{ // eat
			if ((size_snake + 1) % 8 != 0) {
				eat(point);
				Create_food();
				DrawFood();
			}
			else
			{
				eat(point);
				Create_Gate();
				DrawGate();
				state = 2;
			}
		}
		switch (state)
		{
		case 0:
			GotoXY(0, 23);
			cout << "Choi ngu qua, con ran nay chet roi" << endl;
			cout << "Nhap 'y' de choi tiep " << endl;
			cout << "Nhap 'n' de choi thoat " << endl;
			cout << "Ban co muon choi tiep khong : ";
			char option;
			cin >> option;
			switch (option)
			{
			case 'y':
				goto RESET;
			case 'n':
				return 0;
			}
			return 0;
		case 1: // play game
			Delete_Old_Snake();
			DrawSnake();
			Save_Snake();
			Sleep(200 / SPEED);
			/*if (Snake[0].x == 0 || Snake[0].x == width_wall)
			{
				state = 0;
				break;
			} // đụng height_wall
			else if (Snake[0].y == 0 || Snake[0].y == height_wall)
			{
				state = 0;
				break;
			} // đụng width_wall*/
			for (int i = 0; i < size_wall; i++)
			{
				if (Snake[0].x == Wall[i].x && Snake[0].y == Wall[i].y)
				{
					state = 0;
					break;
				}
			}
			break;
		case 2:  // change_level
			Delete_Old_Snake();
			DrawSnake();
			Save_Snake();
			Sleep(200 / SPEED);
			/*if (Snake[0].x == 0 || Snake[0].x == width_wall)
			{
				state = 0;
				break;
			}// đụng height_wall
			else if (Snake[0].y == 0 || Snake[0].y == height_wall)
			{
				state = 0;
				break;
			} // đụng width_wall*/
			for (int i = 0; i < size_wall; i++)
			{
				if (Snake[0].x == Wall[i].x && Snake[0].y == Wall[i].y)
				{
					state = 0;
					break;
				}
			}
			if (Snake[0].x == gate_index[0].x && Snake[0].y == gate_index[0].y + 1)
			{
				changelevel();
				level++;
				goto UP_LEVEL;
				break;
			}
			for (int i = 1; i < 5; i++)
			{
				if (Snake[0].x == gate_index[i].x && Snake[0].y == gate_index[i].y)
				{
					state = 0;
					break;
				} // đụng gate
			}
			break;
		}
	}
	ShowCursor(false);
	_getch();
}