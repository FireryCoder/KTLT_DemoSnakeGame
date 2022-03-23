#include "control_snake.h"
#include <stdio.h>
#include <iostream>
using namespace std;

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void MoveRight() {
	for (int i = size_snake; i > 0; i--) {
		Snake[i] = Snake[i - 1];
	}
	Snake[0].x++;
}

void MoveLeft() {
	for (int i = size_snake; i > 0; i--) {
		Snake[i] = Snake[i - 1];
	}
	Snake[0].x--;
}

void MoveUp() {
	for (int i = size_snake; i > 0; i--) {
		Snake[i] = Snake[i - 1];
	}
	Snake[0].y--;
}

void MoveDown() {
	for (int i = size_snake; i > 0; i--) {
		Snake[i] = Snake[i - 1];
	}
	Snake[0].y++;
}

void Move(char WASD) {
	switch (WASD) {
	case 119:
		MoveUp();
		break;
	case 97:
		MoveLeft();
		break;
	case 115:
		MoveDown();
		break;
	case 100:
		MoveRight();
		break;
	}
}

void DrawBoard() {
	//hàng ngang
	for (int i = 0; i <= width_wall; i++) {
		GotoXY(i, 0);
		printf("X");
		GotoXY(i, 20);
		printf("X");
	}
	//hàng dọc
	for (int i = 0; i < height_wall; i++) {
		GotoXY(90, i);
		printf("X");
		GotoXY(0, i);
		printf("X");
	}
}
void Create_newSnake() {
	int Xcoord = 4, Ycoord;
	srand(time(NULL)); // random appear 
	Ycoord = 3 + rand() % (((height_wall - 1) - 3) - 1) + (1);
	//size_snake = size_snake_auto;
	for (int i = 0; i < size_snake; i++) {
		Snake[i].x = Xcoord;
		Snake[i].y = Ycoord;
		Xcoord--;
	}
	GotoXY(0, Ycoord);
	printf(" ");
	GotoXY(0, Ycoord - 1);
	printf("=");
	GotoXY(0, Ycoord + 1);
	printf("=");
	// moi them ///////
	/*for (int i = 0; i <= size_snake; i++)
	{
		for (int j = i; j >= 0; j--)
		{
			if (i == j) {
				if (i == 0) {
					break;
				}
				else {
					GotoXY(Snake[size_snake - i].x, Snake[size_snake - i].y);
					printf("H");
					Sleep(1000);
					GotoXY(Snake[size_snake - i].x, Snake[size_snake - i].y);
					printf(" ");
				}
			}
			else
			{
				GotoXY(Snake[size_snake - i].x, Snake[size_snake - i].y);
				printf("o");
			}
		}
	}*/
	for (int i = 0; i < size_snake_auto; i++)
	{
		GotoXY(0, Ycoord);
		for (int j = i; j >= 0; j--)
		{
			cout << snake_index[j];
		}
		Sleep(500);
	}
}
void Create_Snakeindex()
{
	int MSSV1[4][8] = { {2,1,1,2,7,6,3,4},
						{2,1,1,2,7,0,7,8},
						{2,1,1,2,7,6,0,0},
						{2,1,1,2,7,7,2,3} };
	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++)
		{
			snake_index[k] = MSSV1[i][j];
			k++;
		}
	}
}
void DrawSnake() {
	for (int i = 0; i < size_snake; i++) {
		GotoXY(Snake[i].x, Snake[i].y);
		cout << snake_index[i];
	}
}

void Delete_Old_Snake() {
	for (int i = 0; i < size_snake; i++) {
		GotoXY(Old_Snake[i].x, Old_Snake[i].y);
		printf(" ");
	}
}

void Save_Snake() {
	for (int i = 0; i < size_snake; i++) {
		Old_Snake[i] = Snake[i];
	}
}

void Create_food()
{
	int x, y;
	bool ok; 
	for (int i = 0; i < 1; i++) {
		srand(time(NULL));
		x = rand() % (85 - 5 + 1) + 5;
		y = rand() % (18 - 3 + 1) + 3;
		// kiem tra co trung voi ran khong
		for (int j = 0; j < size_snake; j++)
		{
			if (x == Snake[j].x && y == Snake[j].y)
			{
				ok = false;
				break;
			}
			else
			{
				ok = true;
			}
		}
		if (ok == true)
		{
			food.x = x;
			food.y = y;
		}
		else
		{
			i--;
		}
	}
}

void DrawFood()
{
	GotoXY(food.x, food.y);
	printf("F");
}

void eat()
{
	size_snake++;
}

bool checkgate(POINT a)
{
	for (int i = 0; i < size_snake_max; i++)
	{
		if (a.x == Snake[i].x && a.y == Snake[i].y)
		{
			return false;
		}
	}
	if (a.x == food.x && a.y == food.y)
	{
		return false;
	}
	return true;
}

void Create_Gate()
{
	srand(time(NULL));
	for (int i = 0; i < 1; i++) {
		gate_index[0].x = rand() % (85 - 40 + 1) + 40;
		gate_index[0].y = rand() % (14 - 6 + 1) + 6;
		if (checkgate(gate_index[0]) == false)
		{
			i--;
			break;
		}

		gate_index[1].x = gate_index[0].x + 1;
		gate_index[1].y = gate_index[0].y;
		//GotoXY(gate_index[1].X, gate_index[1].Y);
		//printf("#");
		if (checkgate(gate_index[1]) == false)
		{
			i--;
			break;
		}

		gate_index[2].x = gate_index[0].x + 1;
		gate_index[2].y = gate_index[0].y + 1;
		//GotoXY(gate_index[2].X, gate_index[2].Y);
		//printf("#");
		if (checkgate(gate_index[2]) == false)
		{
			i--;
			break;
		}

		gate_index[3].x = gate_index[0].x - 1;
		gate_index[3].y = gate_index[0].y + 1;
		//GotoXY(gate_index[3].X, gate_index[3].Y);
		//printf("#");
		if (checkgate(gate_index[3]) == false)
		{
			i--;
			break;
		}

		gate_index[4].x = gate_index[0].x - 1;
		gate_index[4].y = gate_index[0].y;
		//GotoXY(gate_index[0].X - 1, gate_index[0].Y);
		//printf("#");
		if (checkgate(gate_index[4]) == false)
		{
			i--;
			break;
		}
	}
}
void eat( int &point )
{
	point += 10;
	size_snake++;
	Snake[size_snake - 1] = food;
}

void changelevel()
{
	for (int j = size_snake; j >= 0 ; j--)
	{
		GotoXY(Snake[j].x, Snake[j].y);
		cout << " ";
		Sleep(100);
	}
}
void DrawGate()
{
	for (int i = 0; i < 5; i++)
	{
		GotoXY(gate_index[i].x, gate_index[i].y);
		cout << "G";
	}
}