#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define CONSOLE_WIDTH 230
#define CONSOLE_HEIGHT 60

void Init();
void Gotoxy(int x, int y);

int main(void)
{
	Init();
	
	int x;
	int y;
	
	for (y = 0; y < CONSOLE_HEIGHT; y++)
	{
		for (x = 0; x < CONSOLE_WIDTH; x++)
		{
			if (y & x - y >> 2)
			{
				Gotoxy(x, y);
				printf("+");
			}
		}
	}
	
	return 0;
}

void Init()
{
	system("mode con cols=230 lines=60");
}

void Gotoxy(int x, int y)
{
	COORD position = { x, y };
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
