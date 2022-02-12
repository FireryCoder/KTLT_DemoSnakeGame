#include <wtypes.h>
#include <Windows.h>
#include <time.h>

#define MAX_SIZE_SNAKE 10
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 3

extern POINT snake[10];
extern POINT food[4];
extern int CHAR_LOCK;
extern int MOVING;
extern int SPEED;
extern int HEIGHT_CONSOLE, WIDTH_CONSOLE;
extern int FOOD_INDEX;
extern int SIZE_SNAKE;
extern int STATE;

void FixWindow();
void Goto(int x, int y);
bool CheckSnake(int x, int y);
void GenerateFood();
void StartGame();
void ExitGame(HANDLE t);
void PauseGame(HANDLE t);
void DrawBoard(int x, int y, int width, int height);
void DrawSnakeAndFood(const char* str);