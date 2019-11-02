#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>

#define HEIGHT 25
#define WIDTH 12

#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define SPACE 32
#define SPECIAL 1111

#define EMPTY 0
#define EMPTY_BLOCK 1
#define FULL_BLOCK 2
#define WALL 3
#define CEIL 4

void game();
void cursor();
void gotoxy(int x, int y);
void printMap(int map[HEIGHT][WIDTH], int map_org[HEIGHT][WIDTH]);
void moveBlock(int map_org[HEIGHT][WIDTH], int keyValue);
void checkKey(int map_org[HEIGHT][WIDTH]);
void draw(int map[HEIGHT][WIDTH], int map_org[HEIGHT][WIDTH]);
void lineClear(int map_org[HEIGHT][WIDTH]);
void setFullblock(int map_org[HEIGHT][WIDTH]);
void readyBlockprint();
void gameinformation();

int ceilCheck(int map_org[HEIGHT][WIDTH]);
int printBlock(int map_org[HEIGHT][WIDTH]);
int interruptCheck(int key);
int menu();

int block[7][4][4][4] = {
	{{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}}, {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}}, {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}}, 
	{{{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}, {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}}, 
	{{{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
	{{{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}},
	{{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
	{{{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}, {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}, {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
	{{{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}, {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}} 
};

int leftX = 5, rightX= 8, topY = 0, bottomY = 3;
int blockType, blockSpin;
int spaceFlag = 0;

int main() {
	

	cursor();
	while (1) {
		int menuCode = menu();//�޴�ȭ���� ����ϰ� �� ���ϰ��� ������.
		if (menuCode == 0) {//menuCode�� ���� 0�̸� ���ӽ��� 
			system("cls");
			game(); //���ӽ����Լ�
		}
		else if (menuCode == 1) {//menuCode�� ���� 1�̸� �������� ��� 
			gameinformation();//�������� ����Լ�
			
		}
		else if (menuCode == 2) {//menuCode�� ���� 2�̸� �ܼ�����
			system("cls");//ȭ���� ����
			//���α׷� ����� ����ϴ� �ΰ�
			return 0;//����
		}
	}
}


void readyBlockprint(int arr[4][4]) {
	
}

int menu() {//����ȭ�� ����Լ�
	int x = 25;
	int y = 12;//���ڵ��� ��ġ�� ���ϱ����� x=25, y=12�� ����


	gotoxy(x - 2 , y);
	printf("> �� �� �� ��");
	gotoxy(x, y + 1);
	printf("�� �� �� ��");
	gotoxy(x, y + 2);
	printf("�� ��");

	while (1) {
		int n = getch();
		switch (n) {
		case UP: {// WŰ
			if (y > 12) {//���ӽ��� �� �ƴ϶�� ���� �� �� �ְ���
				gotoxy(x - 2, y);
				printf("  ");
				gotoxy(x-2, --y);//�ֿܼ����� ���� ��ǥ���� �۱� ������ --y������ 
				printf(">");//x-2�� ����� �ٽ�>�� ��������ν� >�� ���Ʒ��� �����̴� ��ó�����̰���.
			}
			break;//if���� �������� ���� �� caseŻ��
		}
		case DOWN: {// SŰ
			if (y < 14) {//�շ� �� �ƴ϶�� �ؿ��� ������ �� �ְ���
				gotoxy(x - 2, y);
				printf("  ");
				gotoxy(x-2, ++y);//�ֿܼ����� �Ʒ��� ��ǥ���� ũ�� ������ ++y�� ����
				printf("> ");//x-2�� ����� �ٽ�>�� ��������ν� >�� ���Ʒ��� �����̴� ��ó�����̰���.
			}
			break;//if���� �������� ���� �� caseŻ��
		}
		case SPACE: {//�����̽���
			return y - 12; //�����̽��ٸ� ������ ���ӽ���, ��������, ���� �� �ϳ��� �����ϰԵǰ� �װ��� �������� ��Ÿ��
		}
		}
	}
}
void game() {
	int map_org[HEIGHT][WIDTH];
	int map[HEIGHT][WIDTH];
	//map_org�� ���� Ȯ���ϸ鼭 ����ϸ� �����Ƿ� map �� ���Ͽ� �ٲ� �κи� ����

	printMap(map, map_org);
	printBlock(map_org);
	
	while (1) {
		for (int i = 0; i < 15000; i++) {
			
			checkKey(map_org);
			if (spaceFlag) {
				leftX = 5, rightX = 8, topY = 0, bottomY = 3;
				printBlock(map_org);
			}
			lineClear(map_org);
			draw(map, map_org);	
		
			if (ceilCheck(map_org)) {
				system("cls");
				gotoxy(10, 10);
				printf("Game over");
				exit(1);
			}
		}
		
		moveBlock(map_org, DOWN);
		draw(map, map_org);
	}
}

int ceilCheck(int map_org[HEIGHT][WIDTH]) {
	int cnt = 0;
	for (int i = 1; i < WIDTH; i++) {
		if (map_org[CEIL][i] == FULL_BLOCK) cnt++;
		if (cnt > 0) {
			return 1;
		}
	}
	return 0;
}

void printMap(int map[HEIGHT][WIDTH], int map_org[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i == HEIGHT - 1 || j == WIDTH -1 || j == 0) {
				map[i][j] = WALL;
				map_org[i][j] = WALL;
				gotoxy(j * 2, i);
				printf("��");
			}
			else {
				map[i][j] = EMPTY;
				map_org[i][j] = EMPTY;
				gotoxy(j * 2, i);
				printf("  ");
			}

		}		
	}
}
int printBlock(int map_org[HEIGHT][WIDTH]) {
	int arr[4] = { LEFT, RIGHT, SPECIAL };
	int x = 0, y = 0;
	int overLap;
	srand(time(NULL));

	if (spaceFlag) {
		spaceFlag = 0;
		do {
			overLap = ((rand() + 3) * 9) % 7;

		} while (blockType == overLap);

		blockType = overLap;
	}

	for (int i = topY; i <= bottomY; i++) {
		x = 0;
		for (int j = leftX; j <= rightX; j++) {
			if ((map_org[i][j] == WALL && block[blockType][blockSpin][y][x] == EMPTY_BLOCK) || (map_org[i][j] == FULL_BLOCK && block[blockType][blockSpin][y][x] == EMPTY_BLOCK)) {
				blockSpin--;
				return 1;
			}
			x++;
		}
		y++;
	}

	x = 0, y = 0;

	
	for (int i = topY; i <= bottomY; i++) {
		x = 0;
		for (int j = leftX; j <= rightX; j++) {
			
			if ((map_org[i][j] == WALL && block[blockType][blockSpin][y][x] == EMPTY) || (map_org[i][j] == FULL_BLOCK && block[blockType][blockSpin][y][x] == EMPTY)) {
				x++;
				continue;
			}
			map_org[i][j] = block[blockType][blockSpin][y][x];
			x++;
		}
		y++;
	}

}

void lineClear(int map_org[HEIGHT][WIDTH]) {
	int cnt = 0;

	for (int i = 0; i < HEIGHT - 1; i++) {
		cnt = 0;
		for (int j = 1; j < WIDTH - 1; j++) {
			if (map_org[i][j] == FULL_BLOCK) {
				cnt++;
			}
		}

		if (cnt == 10) {
			
			for (int k = 1; k < WIDTH - 1; k++) {
				map_org[i][k] = EMPTY;
			}

			for (int k = i - 1; k >= 0; k--) {
				for (int l = 1; l < WIDTH - 1; l++) {
					if (map_org[k][l] == FULL_BLOCK) {
						map_org[k][l] = EMPTY;
						map_org[k + 1][l] = FULL_BLOCK;
					}
				}
			}
		}
	}

	
}

void checkKey(int map_org[HEIGHT][WIDTH]) {
	if (kbhit()) {
		int keyValue = getch();
		switch (keyValue) {
		case UP: { moveBlock(map_org, UP); break; }
		case DOWN: { moveBlock(map_org, DOWN); break; }
		case RIGHT: { moveBlock(map_org, RIGHT); break; }
		case LEFT: { moveBlock(map_org, LEFT); break; }
		case SPACE: { moveBlock(map_org, SPACE); break; }
		//case 'm': { moveBlock(map_org, SPECIAL); break; }
		}
	}
}

void moveBlock(int map_org[HEIGHT][WIDTH],int keyValue) {
	switch (keyValue) {
	case LEFT: {
		for (int i = topY; i <= bottomY; i++) {
			for (int j = leftX; j <= rightX; j++) {
				if (map_org[i][j] == EMPTY_BLOCK) {
					if (interruptCheck(map_org[i][j - 1])) {
						return;
					}
				}
			}
		}

		for (int i = topY; i <= bottomY; i++) {
			for (int j = leftX; j <= rightX; j++) {
				if (map_org[i][j] == EMPTY_BLOCK) {
					map_org[i][j] = EMPTY;
					map_org[i][j - 1] = EMPTY_BLOCK;

				}
			}
		}
		leftX--;
		rightX--;
		break;
	}
	case RIGHT: {
		for (int i = topY; i <= bottomY; i++) {
			for (int j = rightX; j >= leftX; j--) {
				if (map_org[i][j] == EMPTY_BLOCK) {
					if (interruptCheck(map_org[i][j + 1])) {
						return;
					}
				}
			}
		}

		for (int i = topY; i <= bottomY; i++) {
			for (int j = rightX; j >= leftX; j--) {
				if (map_org[i][j] == EMPTY_BLOCK) {
					map_org[i][j] = EMPTY;
					map_org[i][j + 1] = EMPTY_BLOCK;
				}
			}
		}
		leftX++;
		rightX++;
		break;
	}
	case DOWN: {
		for (int i = bottomY; i >= topY; i--) {
			for (int j = leftX; j <= rightX; j++) {
				if (map_org[i][j] == EMPTY_BLOCK) {
					if (interruptCheck(map_org[i + 1][j])) {
						moveBlock(map_org, SPACE);
						return;
					}
				}
			}
		}

		for (int i = bottomY; i >= topY; i--) {
			for (int j = leftX; j <= rightX; j++) {
				if (map_org[i][j] == EMPTY_BLOCK) {
					map_org[i][j] = EMPTY;
					map_org[i + 1][j] = EMPTY_BLOCK;

				}
			}
		}
		topY++;
		bottomY++;
		break;
	}
	case SPACE: {
		while (1) {
			for (int i = bottomY; i >= topY; i--) {
				for (int j = leftX; j <= rightX; j++) {
					if (map_org[i][j] == EMPTY_BLOCK) {
						if (interruptCheck(map_org[i + 1][j])) {
							setFullblock(map_org);
							spaceFlag = 1;
							return;
						}
					}
				}
			}
			moveBlock(map_org, DOWN);
		}
		break;
	}
	case UP: {
		blockSpin++;
		if (blockSpin == 4) {
			blockSpin = 0;
		}
		printBlock(map_org);
		break;
	}
	case SPECIAL: {
		for (int i = topY; i <= bottomY; i++) {
			for (int j = leftX; j <= rightX; j++) {
				if (map_org[i][j] == EMPTY_BLOCK) {
					map_org[i][j] = EMPTY;
					map_org[i - 1][j] = EMPTY_BLOCK;
				}
			}
		}
		topY--;
		bottomY--;
		break;
	}
	}
}

void setFullblock(int map_org[HEIGHT][WIDTH]) {
	for (int i = topY; i <= bottomY; i++) {
		for (int j = leftX; j <= rightX; j++) {
			if (map_org[i][j] == EMPTY_BLOCK) {
				map_org[i][j] = FULL_BLOCK;
			}
		}
	}
}

int interruptCheck(int key) {
	if (key == WALL || key == FULL_BLOCK) {
		return 1;
	}
	else {
		return 0;
	}

}

void draw(int map[HEIGHT][WIDTH], int map_org[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (map[i][j] != map_org[i][j]) {
				switch (map_org[i][j]) {
				case EMPTY_BLOCK: { map[i][j] = map_org[i][j]; gotoxy(j * 2, i); printf("��"); break; }
				case EMPTY: { map[i][j] = map_org[i][j]; gotoxy(j * 2, i); printf("  "); break; }
				case FULL_BLOCK: { map[i][j] = map_org[i][j]; gotoxy(j * 2, i); printf("��"); break; }
				}
			}
		}
	}
}

void cursor() {

	system("mode con cols=60 lines=30 | title ��Ʈ����");

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {//�ܼ� ��ǥ���� �̿��ϴ� �Լ�
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void gameinformation() {
	system("cls");
	printf("\n\n\n\n");
	printf("	             ������ : �ڽ���\n");
	printf("                   ���� �帣 : ��Ʈ����\n\n\n");
	printf("    �̵�Ű: ȭ��ǥ (��)��, (�Ʒ�)��, (������)��, (����)�� \n\n\n");
	printf("	         e-mail : payj0724@naver.com \n\n\n");
	printf("        �����̽��ٸ� ������ ���� ȭ������ ���ư��ϴ�.\n");
	while (1) {
		int key = getch();
		if (key == SPACE) {//�����̽��ٸ� ������ ����ȭ������ �̵�
			system("cls");
			break;//�Լ� ����
		}
	}
}