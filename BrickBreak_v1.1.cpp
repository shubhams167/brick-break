#include<iostream>
#include<windows.h>
#include<conio.h>

#define SCORE_BOARD_X 50
#define SCORE_BOARD_Y 0

using namespace std;

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

bool exitScreen()
{
	char ch;
	system("cls");
	gotoxy(50,10);
	cout<<"Quit?(y or n)";
	ch = getch();
	if(ch == 'y' || ch == 'Y')
		return true;
	if(ch == 'n' || ch == 'N')
		return false;
}

float calculateScore(int steps, int x, int y, int target_x, int target_y)
{
	int min_steps = abs(x - target_x) + abs(y - target_y);
	if(steps == min_steps)
		return 0;
	else
		return (steps - min_steps)/100.0;
}

bool BrickBreakIntro()
{
	char option;
	int n = 75;
	gotoxy(20,15);
	while(n--)
	{
		cout<<"|";
		Sleep(100);
	}
	system("cls");
	gotoxy(50,10);	
	cout<<"WELCOME TO BRICK BREAK";
	Sleep(5000);
	gotoxy(50,12);
	cout<<"   Press P to Play";
	option = getch();
	switch(option)
	{
		case 'p':	return true;break;
			
		case 27:	return false;break;	
	}
	
}


int main()
{
	if(!BrickBreakIntro())
		exit(0);
	system("cls");
	int x = 50, y = 15, target_x, target_y, steps = 0,temp_x = x, temp_y = y;
	float score = 0, redundant_steps = 0;
	char option, player = 111, target = 219;
	gotoxy(SCORE_BOARD_X,SCORE_BOARD_Y);
	cout<<"SCORE: "<<score<<" STEPS: "<<steps;
	target_x = rand()%120;
	target_y = rand()%30;
	gotoxy(target_x, target_y);
	cout<<target;
	gotoxy(x,y);
	cout<<player;
	while(1)
	{
		option = getch();
		
		switch(option)
		{
			
			case 'a':	x--;steps++;break;
				
			case 's':	y++;steps++;break;
				
			case 'd':	x++;steps++;break;
				
			case 'w':	y--;steps++;break;
				
			case 27:	if(exitScreen())
						{
							system("cls");
							gotoxy(50,10);
							cout<<"\a Your Final Score is "<<score - redundant_steps;
							gotoxy(50,12);
							cout<<"*****Score BreakDown*****";
							gotoxy(50,13);
							cout<<"(+)Bricks hitpoints: "<<score;
							gotoxy(50,14);
							cout<<"(-)Redundant steps penalty: "<<redundant_steps;
							gotoxy(50,15);
							cout<<"Final Score: "<<score - redundant_steps;
							exit(0);
						}
						else
						{
							gotoxy(x,y);
							cout<<player;
						}
		}		
		system("cls");
		if(x == target_x && y == target_y)
		{
			cout<<"\a";
			score++;
			redundant_steps = redundant_steps + calculateScore(steps, temp_x, temp_y, target_x, target_y);
			temp_x = x;
			temp_y = y;
			target_x = rand()%120;
			target_y = rand()%30;
			steps = 0;
		}
		gotoxy(x,y);
		cout<<player;
		gotoxy(target_x, target_y);
		cout<<target;
		gotoxy(SCORE_BOARD_X,SCORE_BOARD_Y);
		cout<<"SCORE: "<<score<<" STEPS: "<<steps;		
	}
	return 0;
}

