#pragma once
#include "setting.h"

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void textcolor(int x)
{
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, x);
}
void Clean_console()
{
    HANDLE a;
    COORD Pos;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    Pos.X = 0;
    Pos.Y = 0;
    SetConsoleCursorPosition(a, Pos);
}

