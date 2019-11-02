#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define MAPSIZE 20
#define SPACE 0
#define WALL 1
#define BALL 2
#define HOLE 3
#define FINISH 4
#define PLAYER 9

char playerCh[] = "★";
char ballCh[] = "●";
char holeCh[] = "○";
char finishCh[] = "♡";

int map[MAPSIZE][MAPSIZE] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

int map1[MAPSIZE][MAPSIZE] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

int playerX, playerY;
int gameCnt=1;

void gameinformation();
int menu();
void Initialization();
void game();
void randomMap();
void gotoxy(int x, int y);
void printxy(int x, int y, char c[]);
void clearxy(int x, int y);
void printMap();
int movePlayer(int dx, int dy);
int countHole();

int main()
{
	char menu_key;
	while (1) {
		system("mode con: cols=100 lines=30");
		int menuCode = menu();
		if (menuCode==0) {
			while (1) {
				game();
			}
		}
		else if (menuCode==1) {
			gameinformation();
		}
		else if (menuCode==2) {
			return 0;
		}
	}
}

void randomMap() {
	int i,j,cnt = 0, cnt1=0;
	int tmp = WALL, random1, random2, random3;
	srand((unsigned int)time(NULL));
	random3 = rand()%9+1;//공 하고 구멍갯수 
	cnt = random3;
	do {
		random1 = rand() % 20;
		random2 = rand() % 20;
		if (map[random1][random2] == PLAYER || map[random1][random2]==WALL || map[random1+1][random2] == WALL || map[random1-1][random2] == WALL || map[random1][random2-1]==WALL || map[random1][random2+1]) {
			continue;
		}
		else {
			map[random1][random2] = BALL;
			cnt--;
		}
	} while (cnt != 0);
	cnt1 = random3;
	do {
		random1 = rand() % 19;
		random2 = rand() % 19;
		if (map[random1][random2] == WALL || map[random1][random2] == BALL || map[random1][random2] == PLAYER) {
			continue;
		}
		else {
			map[random1][random2] = HOLE;
			cnt1--;
		}
	} while (cnt1 != 0);
}

int movePlayer(int dx, int dy)	//플레이어를 이동시키는 함수 (이동했으면1, 못했으면 0 반환)
{
	if (map[playerY + dy][playerX + dx] == SPACE)
	{
		map[playerY][playerX] = SPACE;
		clearxy(playerX, playerY);
		map[playerY + dy][playerX + dx] = PLAYER;
		printxy(playerX + dx, playerY + dy, playerCh);
		playerX += dx;
		playerY += dy;
		return 1;
	}
	else if (map[playerY + dy][playerX + dx] == BALL && (map[playerY + (dy * 2)][playerX + (dx * 2)] == SPACE || map[playerY + (dy * 2)][playerX + (dx * 2)] == HOLE))
	{
		map[playerY][playerX] = SPACE;
		clearxy(playerX, playerY);
		map[playerY + dy][playerX + dx] = PLAYER;
		printxy(playerX + dx, playerY + dy, playerCh);
		if (map[playerY + (dy * 2)][playerX + (dx * 2)] == HOLE) {
			map[playerY + (dy * 2)][playerX + (dx * 2)] = FINISH;
			printxy(playerX + (dx * 2), playerY + (dy * 2), finishCh);
		}
		else {
			map[playerY + (dy * 2)][playerX + (dx * 2)] = BALL;
			printxy(playerX + (dx * 2), playerY + (dy * 2), ballCh);
		}
		playerX += dx;
		playerY += dy;
		return 1;
	}
	else
		return 0;
}

void game() {
	system("cls");
	int i, j, holeNum, count = 0;
	char playerInput;
	randomMap();
	printMap();
	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
		{
			if (map[i][j] == 9)
			{
				playerX = j;
				playerY = i;
			}
		}
	}
	while (1)
	{
		holeNum = countHole();
		gotoxy(MAPSIZE + 3, 3);
		printf("남은 공 : %d", holeNum);
		gotoxy(MAPSIZE + 3, 4);
		printf("이동 수 : %d", count);
		gotoxy(MAPSIZE + 3, 6);
		printf("%d 스테이지", gameCnt);
		if (holeNum == 0)
			break;

		playerInput = getch();
		if (playerInput == 75)//left
			count += movePlayer(-1, 0);
		else if (playerInput == 77)//right
			count += movePlayer(1, 0);
		else if (playerInput == 72)//up
			count += movePlayer(0, -1);
		else if (playerInput == 80)//down
			count += movePlayer(0, 1);
	}
	Initialization();
	gameCnt++;
	printxy((MAPSIZE + 26) / 2, MAPSIZE / 2, "Stage Clear!");
	getch();
	return 0;
}

int countHole() //구멍 갯수를 반환하는 함수
{
	int i, j, cnt = 0;

	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < MAPSIZE; j++) {
			if (map[i][j] == HOLE) {
			cnt++;
			}
		}
	}
	return cnt;
}

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void printMap()
{
	int i, j;
	
	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < MAPSIZE; j++) {
			switch (map[i][j]) {
			case WALL:printf("■"); break;
			case SPACE:printf("  "); break;
			case BALL:printf(ballCh); break;
			case HOLE:printf(holeCh); break;
			case FINISH:printf(finishCh); break;
			case PLAYER:printf(playerCh); break;
			}
		}
		printf("\n");
	}
	//맵 한번 출력
}

void printxy(int x, int y, char c[])
{
	gotoxy(x, y);
	printf("%s", c);
}

void clearxy(int x, int y)
{
	gotoxy(x, y);
	printf("  ");
}

void Initialization() {
	int i, j;

	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < MAPSIZE; j++) {
			map[i][j] = map1[i][j];
		}
	}
}

void gameinformation() {
	system("cls");
	printf("\n\n\n\n");
	printf("	             개발자 : 박승진\n");
	printf("                   게임 장르 : 공넣기 게임\n\n\n");
	printf("    이동키: 화살표 (위)↑, (아래)↓, (오른쪽)→, (왼쪽)← \n");
	printf("        스페이스바를 누르면 메인 화면으로 돌아갑니다.\n");
	while (1) {
		int n = getch();
		if (n==32) {//스페이스바를 누르면 메인화면으로 이동
			break;//함수 종료
		}
	}
}

int menu() {//메인화면 출력함수
	int x = 20;
	int y = 12;//글자들의 위치를 정하기위해 x=25, y=12로 정함
	gotoxy(x-2, y);
	printf("> 게 임 시 작");
	gotoxy(x, y + 1);
	printf("게 임 정 보");
	gotoxy(x, y + 2);
	printf("   종 료   ");
	while (1) {
		int n = getch();
		switch (n) {
		case 72: {// W키
			if (y > 12) {//게임실행 이 아니라면 위로 갈 수 있게함
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);//콘솔에서는 위가 좌표값이 작기 때문에 y--를해줌 
				printf(">");//x-2를 지우고 다시>를 출력함으로써 >가 위아래로 움직이는 것처럼보이게함.
			}
			break; //if문을 만족하지 않을 시 case탈출
		}

		case 80: {// S키
			if (y < 14) {//죵료 가 아니라면 밑에로 내려갈 수 있게함
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);//콘솔에서는 아래가 좌표값이 크기 때문에 y++를 해줌
				printf(">");//x-2를 지우고 다시>를 출력함으로써 >가 위아래로 움직이는 것처럼보이게함.
			}
			break;//if문을 만족하지 않을 시 case탈출
		}

		case 32: {//스페이스바
			return y - 12; //스페이스바를 누르면 게임실행, 게임정보, 종료 중 하나를 선택하게되고 그값을 리턴으로 나타냄
		}
		}
	}
}
/*
void mapcolor(int i) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
	/*
	0 = 검정색,		1 = 파란색,		2 = 초록색,		3 = 옥색		
	4 = 빨간색,		5 = 자주색,		6 = 노란색,		7 = 흰색
	8 = 회색,		9 = 연한 파란색,	10 = 연한 초록색,	11 = 연한 옥색
	12 = 연한 빨간색,	13 = 연한 자주색,	14 = 연한 노란색,	15 = 진한 흰색
	
}
*/