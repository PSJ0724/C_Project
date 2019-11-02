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

char playerCh[] = "��";
char ballCh[] = "��";
char holeCh[] = "��";
char finishCh[] = "��";

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
	random3 = rand()%9+1;//�� �ϰ� ���۰��� 
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

int movePlayer(int dx, int dy)	//�÷��̾ �̵���Ű�� �Լ� (�̵�������1, �������� 0 ��ȯ)
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
		printf("���� �� : %d", holeNum);
		gotoxy(MAPSIZE + 3, 4);
		printf("�̵� �� : %d", count);
		gotoxy(MAPSIZE + 3, 6);
		printf("%d ��������", gameCnt);
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

int countHole() //���� ������ ��ȯ�ϴ� �Լ�
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
			case WALL:printf("��"); break;
			case SPACE:printf("  "); break;
			case BALL:printf(ballCh); break;
			case HOLE:printf(holeCh); break;
			case FINISH:printf(finishCh); break;
			case PLAYER:printf(playerCh); break;
			}
		}
		printf("\n");
	}
	//�� �ѹ� ���
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
	printf("	             ������ : �ڽ���\n");
	printf("                   ���� �帣 : ���ֱ� ����\n\n\n");
	printf("    �̵�Ű: ȭ��ǥ (��)��, (�Ʒ�)��, (������)��, (����)�� \n");
	printf("        �����̽��ٸ� ������ ���� ȭ������ ���ư��ϴ�.\n");
	while (1) {
		int n = getch();
		if (n==32) {//�����̽��ٸ� ������ ����ȭ������ �̵�
			break;//�Լ� ����
		}
	}
}

int menu() {//����ȭ�� ����Լ�
	int x = 20;
	int y = 12;//���ڵ��� ��ġ�� ���ϱ����� x=25, y=12�� ����
	gotoxy(x-2, y);
	printf("> �� �� �� ��");
	gotoxy(x, y + 1);
	printf("�� �� �� ��");
	gotoxy(x, y + 2);
	printf("   �� ��   ");
	while (1) {
		int n = getch();
		switch (n) {
		case 72: {// WŰ
			if (y > 12) {//���ӽ��� �� �ƴ϶�� ���� �� �� �ְ���
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);//�ֿܼ����� ���� ��ǥ���� �۱� ������ y--������ 
				printf(">");//x-2�� ����� �ٽ�>�� ��������ν� >�� ���Ʒ��� �����̴� ��ó�����̰���.
			}
			break; //if���� �������� ���� �� caseŻ��
		}

		case 80: {// SŰ
			if (y < 14) {//�շ� �� �ƴ϶�� �ؿ��� ������ �� �ְ���
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);//�ֿܼ����� �Ʒ��� ��ǥ���� ũ�� ������ y++�� ����
				printf(">");//x-2�� ����� �ٽ�>�� ��������ν� >�� ���Ʒ��� �����̴� ��ó�����̰���.
			}
			break;//if���� �������� ���� �� caseŻ��
		}

		case 32: {//�����̽���
			return y - 12; //�����̽��ٸ� ������ ���ӽ���, ��������, ���� �� �ϳ��� �����ϰԵǰ� �װ��� �������� ��Ÿ��
		}
		}
	}
}
/*
void mapcolor(int i) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
	/*
	0 = ������,		1 = �Ķ���,		2 = �ʷϻ�,		3 = ����		
	4 = ������,		5 = ���ֻ�,		6 = �����,		7 = ���
	8 = ȸ��,		9 = ���� �Ķ���,	10 = ���� �ʷϻ�,	11 = ���� ����
	12 = ���� ������,	13 = ���� ���ֻ�,	14 = ���� �����,	15 = ���� ���
	
}
*/