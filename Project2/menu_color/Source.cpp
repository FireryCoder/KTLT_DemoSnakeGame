#include <iostream>
#include <Windows.h>

using namespace std;

void textcolor(int x)
{
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, x);
}

int main(void)
{
    for (int i = 0; i < 255; i++)
    {
        textcolor(i);
        cout << "text" << endl;
    }
}