#include "setting.h"
#include "control_snake.h"
#include <string.h>
#include <conio.h>
#include <iostream>
#include "mylib.h"

using namespace std;

#define size_snake_max 32
#define size_snake_auto 5
#define width_wall 90 
#define height_wall 20
#define size_gate_max 6
#define height_console 27
#define width_console 100
int size_snake;
int size_wall;
int snake_index[size_snake_max];
POINT Snake[size_snake_max];
POINT Old_Snake[size_snake_max];
POINT food;
POINT gate_index[6];
POINT Wall[1000];
char option;
int state;
// state = 0 <=> snake_die
// state = 1 <=> play game
// state = 2 <=> before_change_level ( gate appear )
// state = 3 <=> END GAME ( completed )

int main(void)
{
	ShowConsoleCursor(false);
	resizeConsole(width_console, height_console);
RESET:
	//tạo rắn
	size_snake = size_snake_auto;
	// tạo điểm 
	int point = 0;
	int level = 0;
	// tạo map
	Create_Board(level,0,0);
	DrawBoard();
UP_LEVEL:
	int SPEED = 0;
	level++; SPEED++;
	char movekey = 'd';
	system("cls");
	Draw_setup(0, 0,SPEED);
	Create_Board(level,0,0);
	DrawBoard();
	// tạo điểm
	GotoXY(1, 21);
	cout << "    point : " << point << "         " << "Level : " << level;
	//tạo tốc độ
	GotoXY(width_wall + 0 + 2, 0 + 5);
	cout << "SPEED:" << SPEED;
	// tạo màn;
	Create_Snakeindex();
	Create_newSnake();
	Save_Snake();// tạo rắn
	//tạo thức ăn
	Create_food();
	DrawFood();
	// tạo trạng thái
	state = 1;
	while (true) {
		DrawBoard();
		Draw_setup(0, 0, SPEED);
		GotoXY(1, 21);
		cout << "    point : " << point << "         " << "Level : " << level;
		if (_kbhit()) {
			movekey = _getch();
			Move(movekey);
		}
		else {
			Move(movekey);
		}
		if (Snake[0].x == food.x && Snake[0].y == food.y)
		{ // eat
			//if ((size_snake + 1) % 8 != 0) {
			if((SPEED + 1)!= 5){
				eat(point,SPEED);
				Create_food();
				DrawFood();
				GotoXY(0, 0);
				setBackgroundColor(9);
				cout << " ";
				setBackgroundColor(0);
			}
			else
			{
				if (size_snake == size_snake_max)
				{
					eat(point, SPEED);
					state = 4;
				}
				else
				{
					eat(point, SPEED);
					Create_Gate();
					DrawGate();
					state = 2;
				}
			}
		}
		switch (state)
		{
		case 0:  // rắn chết
			GotoXY(1, 22);
			cout << "Choi ngu qua, con ran nay chet roi";
			GotoXY(1, 23);
			cout << "Nhap 'y' de choi tiep " ;
			GotoXY(1, 24);
			cout << "Nhap 'n' de choi thoat ";
			GotoXY(1, 25);
			cout << "Ban co muon choi tiep khong : ";
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
			}// đụng tường
			break;
		case 2:  // tạo cổng, không tạo thức ăn
			GotoXY(1, 23);
			cout << "     Hay vao cong ";
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
				goto UP_LEVEL;
				break;
			}// vào cổng
			for (int i = 1; i < 5; i++)
			{
				if (Snake[0].x == gate_index[i].x && Snake[0].y == gate_index[i].y)
				{
					state = 0;
					break;
				} // đụng gate
			}
			break;
		case 3: // end game
			GotoXY(1, 22);
			cout << "Da hoan thanh tat ca cac man choi";
			GotoXY(1, 23);
			cout << "Nhap 'y' de choi lai " ;
			GotoXY(1, 24);
			cout << "Nhap 'n' de choi thoat ";
			GotoXY(1, 25);
			cout << "Ban co muon choi tiep khong : ";
			cin >> option;
			switch (option)
			{
			case 'y':
				goto RESET;
			case 'n':
				return 0;
			}
			return 0;
		}
	}
	ShowCursor(false);
	_getch();
}