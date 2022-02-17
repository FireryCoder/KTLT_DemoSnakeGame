
// KTLT_DemoSnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "UI.h"
#include "Snake.h"
#include <thread>
#include <conio.h>

#define MAX_SIZE_SNAKE 8
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 3

POINT snake[10];
POINT food[4];
int CHAR_LOCK;
int MOVING;
int SPEED;
int HEIGHT_CONSOLE, WIDTH_CONSOLE;
int FOOD_INDEX;
int SIZE_SNAKE;
int STATE;

void main()
{
    FixWindow();
    int temp;
    StartGame();
    std::thread t1(ThreadFunc);
    HANDLE handle_t1 = t1.native_handle();
    while (1)
    {
        temp = toupper(_getch());
        if (STATE == 1)
        {
            if (temp == 'P')
            {
                PauseGame(handle_t1);
            }
            else
                if (temp == 27)
                {
                    ExitGame(handle_t1);
                    return;
                }
                else
                {
                    ResumeThread(handle_t1);
                    if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S'))
                    {
                        switch (temp)
                        {
                        case 'D':
                            CHAR_LOCK = 'A';
                            break;
                        case 'A':
                            CHAR_LOCK = 'D';
                            break;
                        case 'W':
                            CHAR_LOCK = 'S';
                            break;
                        case 'S':
                            CHAR_LOCK = 'W';
                            break;
                        }
                        MOVING = temp;
                    }
                }
        }
        else
            if (temp == 'Y')
                StartGame();
            else
            {
                ExitGame(handle_t1);
                return;
            }
    }
    return;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
