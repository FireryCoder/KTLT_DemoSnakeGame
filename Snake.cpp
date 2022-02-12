#include "Snake.h"
#include "UI.h"
#include <stdio.h>

void ResetData()
{
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 1; FOOD_INDEX = 0, WIDTH_CONSOLE = 70, HEIGHT_CONSOLE = 20, SIZE_SNAKE = 6;
	snake[0] = { 10, 5 }; 
	snake[1] = { 11, 5 };
	snake[2] = { 12, 5 }; 
	snake[3] = { 13, 5 };
	snake[4] = { 14, 5 }; 
	snake[5] = { 15, 5 };
	GenerateFood();
}

void ProcessDead()
{
	STATE = 0;
	Goto(0, HEIGHT_CONSOLE + 2);
	printf("SNAKE DIED, PRESS Y TO CONTINUE OR N TO EXIT");
}

void Eat()
{
	snake[SIZE_SNAKE] = food[FOOD_INDEX];
	if (FOOD_INDEX == MAX_SIZE_FOOD - 1)
	{
		FOOD_INDEX = 0;
		SIZE_SNAKE = 6;
		if (SPEED == MAX_SPEED) SPEED = 1;
		else SPEED++;
		GenerateFood();
	}
	else
	{
		FOOD_INDEX++;
		SIZE_SNAKE++;
	}
}
void MoveRight()
{
	if (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_CONSOLE)
	{
		ProcessDead();
	}
	else
	{
		if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
		{
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i] = snake[i + 1];
		}
		snake[SIZE_SNAKE - 1].x++;
	}
}

void MoveLeft()
{
	if (snake[SIZE_SNAKE - 1].x + 1 == 0)
	{
		ProcessDead();
	}
	else
	{
		if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
		{
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i] = snake[i + 1];
		}
		snake[SIZE_SNAKE - 1].x--;
	}
}

void MoveDown()
{
	if (snake[SIZE_SNAKE - 1].y + 1 == HEIGHT_CONSOLE)
	{
		ProcessDead();
	}
	else
	{
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y)
		{
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i] = snake[i + 1];
		}
		snake[SIZE_SNAKE - 1].y++;
	}
}

void MoveUp()
{
	if (snake[SIZE_SNAKE - 1].y + 1 == 0)
	{
		ProcessDead();
	}
	else
	{
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y)
		{
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i] = snake[i + 1];
		}
		snake[SIZE_SNAKE - 1].y--;
	}
}

void ThreadFunc()
{
	while (1)
	{
		if (STATE == 1)
		{
			DrawSnakeAndFood(" ");
			switch (MOVING)
			{
			case 'A':
				MoveLeft();
				break;
			case 'D':
				MoveRight();
				break;
			case 'W':
				MoveUp();
				break;
			case 'S':
				MoveDown();
				break;
			}
			DrawSnakeAndFood("0");
		}
		Sleep(1000 / SPEED);
	}
}