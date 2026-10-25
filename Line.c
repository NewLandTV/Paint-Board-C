#include <stdio.h>
#include <math.h>
#include <Windows.h>

#define CONSOLE_WIDTH 40
#define CONSOLE_HEIGHT 20

int cursorX = 0;
int cursorY = CONSOLE_HEIGHT - 1;

void Init();
void Update();
void Gotoxy(int x, int y);

int main(void)
{
	Init();
	
	while (1)
	{
		Update();
	}
	
	return 0;
}

void Init()
{
	system("title Line");
	system("mode con cols=40 lines=20");
	
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
}

void Update()
{
	Gotoxy(cursorX, cursorY);
	printf("+");
	
	cursorX += (cursorY & 1);
	cursorY -= (cursorX & 1) * (cursorX >> 1) - 2;
	
	if (cursorX >= CONSOLE_WIDTH)
	{
		cursorX = 0;
		
		system("cls");
	}
	if (cursorY >= CONSOLE_HEIGHT || cursorY < 0)
	{
		cursorY = CONSOLE_HEIGHT - 1;
	}
	
	Sleep(50);
}

void Gotoxy(int x, int y)
{
	COORD position = { x, y };
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
