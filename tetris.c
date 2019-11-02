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
		int menuCode = menu();//메뉴화면을 출력하고 그 리턴값을 저장함.
		if (menuCode == 0) {//menuCode의 값이 0이면 게임실행 
			system("cls");
			game(); //게임실행함수
		}
		else if (menuCode == 1) {//menuCode의 값이 1이면 게임정보 출력 
			gameinformation();//게임정보 출력함수
			
		}
		else if (menuCode == 2) {//menuCode의 값이 2이면 콘솔종료
			system("cls");//화면을 지움
			//프로그램 종료시 출력하는 로고
			return 0;//종료
		}
	}
}


void readyBlockprint(int arr[4][4]) {
	
}

int menu() {//메인화면 출력함수
	int x = 25;
	int y = 12;//글자들의 위치를 정하기위해 x=25, y=12로 정함


	gotoxy(x - 2 , y);
	printf("> 게 임 시 작");
	gotoxy(x, y + 1);
	printf("게 임 정 보");
	gotoxy(x, y + 2);
	printf("종 료");

	while (1) {
		int n = getch();
		switch (n) {
		case UP: {// W키
			if (y > 12) {//게임실행 이 아니라면 위로 갈 수 있게함
				gotoxy(x - 2, y);
				printf("  ");
				gotoxy(x-2, --y);//콘솔에서는 위가 좌표값이 작기 때문에 --y를해줌 
				printf(">");//x-2를 지우고 다시>를 출력함으로써 >가 위아래로 움직이는 것처럼보이게함.
			}
			break;//if문을 만족하지 않을 시 case탈출
		}
		case DOWN: {// S키
			if (y < 14) {//죵료 가 아니라면 밑에로 내려갈 수 있게함
				gotoxy(x - 2, y);
				printf("  ");
				gotoxy(x-2, ++y);//콘솔에서는 아래가 좌표값이 크기 때문에 ++y를 해줌
				printf("> ");//x-2를 지우고 다시>를 출력함으로써 >가 위아래로 움직이는 것처럼보이게함.
			}
			break;//if문을 만족하지 않을 시 case탈출
		}
		case SPACE: {//스페이스바
			return y - 12; //스페이스바를 누르면 게임실행, 게임정보, 종료 중 하나를 선택하게되고 그값을 리턴으로 나타냄
		}
		}
	}
}
void game() {
	int map_org[HEIGHT][WIDTH];
	int map[HEIGHT][WIDTH];
	//map_org를 전부 확인하면서 출력하면 느리므로 map 과 비교하여 바뀐 부분만 변경

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
				printf("▣");
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
				case EMPTY_BLOCK: { map[i][j] = map_org[i][j]; gotoxy(j * 2, i); printf("□"); break; }
				case EMPTY: { map[i][j] = map_org[i][j]; gotoxy(j * 2, i); printf("  "); break; }
				case FULL_BLOCK: { map[i][j] = map_org[i][j]; gotoxy(j * 2, i); printf("■"); break; }
				}
			}
		}
	}
}

void cursor() {

	system("mode con cols=60 lines=30 | title 테트리스");

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {//콘솔 좌표값을 이용하는 함수
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void gameinformation() {
	system("cls");
	printf("\n\n\n\n");
	printf("	             개발자 : 박승진\n");
	printf("                   게임 장르 : 테트리스\n\n\n");
	printf("    이동키: 화살표 (위)↑, (아래)↓, (오른쪽)→, (왼쪽)← \n\n\n");
	printf("	         e-mail : payj0724@naver.com \n\n\n");
	printf("        스페이스바를 누르면 메인 화면으로 돌아갑니다.\n");
	while (1) {
		int key = getch();
		if (key == SPACE) {//스페이스바를 누르면 메인화면으로 이동
			system("cls");
			break;//함수 종료
		}
	}
}