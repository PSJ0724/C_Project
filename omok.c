#include<stdio.h> //입출력
#include<Windows.h> //커서 이동 
#include<conio.h> //getch()함수

// 키보드 값

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 //스페이스바
#define ESC 27

void exitprint(); //프로그램을 종료했을시 출력하는 로고
void countstone(); //현재까지 둔 돌의 갯수를 출력하는 함수
void maplogo(); //메인화면에 출력하는 게임 로고
void backboard(); //오목게임을 할 판을 출력하는 함수
void draw_put_stone(int Board[20][20]); //판에 놓은 돌을 출력하는 함수
void Erase_stone(int x, int y); // 돌을 이동시킬 때 출력되어있는 돌을 없애는 함수
void Put_stone(int Board[20][20], int x, int y); //돌을 놓을 때 백돌 흑돌이 바뀌어야하므로 location전역 변수를 이용해서 흑돌 백돌을 바꿈
void Put_key(int Board[20][20], char move_key, int *x, int *y);//화살표 키를 이용해서 움직임, 스페이스바를 누르면 Put_stone함수로 넘어감
int win_check(int Board[20][20]);//흑돌이 이겼는지 백돌이 이겼는지 확인하는 함수
void gotoxy(int x, int y);//콘솔의 좌표값을 이용한 함수
int key();//메인화면에서 쓰는 A,W,S,D키를 리턴해주는 함수
int menu();//메인화면 출력함수, 리턴값에 따라 어떤것을 실행할지 달라짐
void gameinformation();//게임정보 출력함수
void console();//콘솔의 크기,이름을 정하고 커서의 깜빡임을 없애주는 함수
void game();//게임출력 함수
void draw_stone();//전역변수 location의 값을 이용해서 현재 이용하고있는 돌의 색깔을 출력
int location = 0;//돌의 색깔을 나누기위한 전역변수 1=백돌 2=흑돌
int stonecnt = 0;//돌의 갯수를 세기위한 전역변수

int main() { //메인함수
	while (1) { //while문을 이용한 무한 루프
		console();//콘솔 크기 정해줌
		int menuCode = menu();//메뉴화면을 출력하고 그 리턴값을 저장함.
		if (menuCode == 0) {//menuCode의 값이 0이면 게임실행 
			game(); //게임실행함수
		}
		else if (menuCode == 1) {//menuCode의 값이 1이면 게임정보 출력 
			gameinformation();//게임정보 출력함수
		}
		else if (menuCode == 2) {//menuCode의 값이 2이면 콘솔종료
			system("cls");//화면을 지움
			exitprint(); //프로그램 종료시 출력하는 로고
			return 0;//종료
		}
	}
}

void gameinformation() {
	system("cls");
	printf("\n\n\n\n");
	printf("	             개발자 : 박승진\n");
	printf("                   게임 장르 : 오목게임\n\n\n");
	printf("                  메뉴화면키 : A, S, W, D\n\n");
	printf("    이동키: 화살표 (위)↑, (아래)↓, (오른쪽)→, (왼쪽)← \n");
	printf("	         바둑돌 두기 : 스페이스바\n\n\n");
	printf("        스페이스바를 누르면 메인 화면으로 돌아갑니다.\n");
	while (1) {
		if (key() == SUBMIT) {//스페이스바를 누르면 메인화면으로 이동
			break;//함수 종료
		}
	}
}

void gotoxy(int x, int y) {//콘솔 좌표값을 이용하는 함수
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int key() {
	char temp = getch(); //getch()로 키값을 받음

	if (temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') {
		return SUBMIT;
	}
	else if (temp == 27) {
		return ESC;
	}
}

int menu() {//메인화면 출력함수
	int x = 25;
	int y = 12;//글자들의 위치를 정하기위해 x=25, y=12로 정함
	
	maplogo();
	gotoxy(x - 2, y);
	printf("> 게 임 시 작");
	gotoxy(x, y + 1);
	printf("게 임 정 보");
	gotoxy(x, y + 2);
	printf("   종 료   ");
	
	while (1) {
		int n = key();
		switch (n) {
		case UP: {// W키
			if (y > 12) {//게임실행 이 아니라면 위로 갈 수 있게함
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y--);//콘솔에서는 위가 좌표값이 작기 때문에 y--를해줌 
				printf(">");//x-2를 지우고 다시>를 출력함으로써 >가 위아래로 움직이는 것처럼보이게함.
			}
			break;//if문을 만족하지 않을 시 case탈출
		}
		case DOWN: {// S키
			if (y < 14) {//죵료 가 아니라면 밑에로 내려갈 수 있게함
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y++);//콘솔에서는 아래가 좌표값이 크기 때문에 y++를 해줌
				printf(">");//x-2를 지우고 다시>를 출력함으로써 >가 위아래로 움직이는 것처럼보이게함.
			}
			break;//if문을 만족하지 않을 시 case탈출
		}
		case SUBMIT: {//스페이스바
			return y - 12; //스페이스바를 누르면 게임실행, 게임정보, 종료 중 하나를 선택하게되고 그값을 리턴으로 나타냄
		}
		}
	}
}

void console() {//콘솔크기, 이름 지정 커서깜빡거림을 없애는 함수
	system("mode con cols=60 lines=20 | title 오목게임");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

}

void backboard() { //오목판 출력 함수
	system("cls");
	int i, j;

	printf("┌");
	for (i = 0; i < 17; ++i) {
		printf(" ┬");
	}
	printf(" ┐\n");

	for (i = 0; i <17; ++i) {
		printf("├");
		for (j = 0; j < 17; ++j) {
			printf(" ┼");
		}
		printf(" ┤\n");
	}
	printf("└");
	for (i = 0; i < 17; ++i) {
		printf(" ┴");
	}
	printf(" ┘\n");
	gotoxy(42, 2);
	printf("19줄 바둑판");
	gotoxy(41, 5);
	printf("ESC = 메인화면");
	//특수문자는 두개가 한칸이기 떄문에 띄어쓰기를 해줌.
}

void draw_stone() {//전역변수를 이용한 돌 색깔 출력
	if (location == 1) {
		printf("●");
	}
	else {
		printf("○");
	}
}

int win_check(int Board[20][20]) {//어떤돌이 이겼는지 체크하는 함수 백돌이 이기면 1를 리턴 흑돌이 이기면 2를 리턴
	int i;
	int j;
	for (i = 2; i < 18; i++) {
		for (j = 0; j < 20; j++) {
			if (Board[j][i - 2] == 1 && Board[j][i - 1] == 1 && Board[j][i] == 1 && Board[j][i + 1] == 1 && Board[j][i + 2] == 1) {
				gotoxy(40, 10);
				printf("*** 백돌 승리 ***");
				getch();
				return 1;
			}
			else if (Board[j][i - 2] == 2 && Board[j][i - 1] == 2 && Board[j][i] == 2 && Board[j][i + 1] == 2 && Board[j][i + 2] == 2) {
				gotoxy(40, 10);
				printf("*** 흑돌 승리 ***");
				getch();
				return 2;
			}

			else if (Board[i - 2][j] == 1 && Board[i - 1][j] == 1 && Board[i][j] == 1 && Board[i + 1][j] == 1 && Board[i + 2][j] == 1) {
				gotoxy(40, 10);
				printf("*** 백돌 승리 ***");
				getch();
				return 1;
			}
			else if (Board[i - 2][j] == 2 && Board[i - 1][j] == 2 && Board[i][j] == 2 && Board[i + 1][j] == 2 && Board[i + 2][j] == 2) {
				gotoxy(40, 10);
				printf("*** 흑돌 승리 ***");
				getch();
				return 2;
			}
		}
	}

	for (i = 2; i < 18; i++) {
		for (j = 2; j < 18; j++) {
			if (Board[j - 2][i - 2] == 1 && Board[j - 1][i - 1] == 1 && Board[j][i] == 1 && Board[j + 1][i + 1] == 1 && Board[j + 2][i + 2] == 1) {
				gotoxy(40, 10);
				printf("*** 백돌 승리 ***");
				getch();
				return 1;
			}
			else if (Board[j - 2][i - 2] == 2 && Board[j - 1][i - 1] == 2 && Board[j][i] == 2 && Board[j + 1][i + 1] == 2 && Board[j + 2][i + 2] == 2) {
				gotoxy(40, 10);
				printf("*** 흑돌 승리 ***");
				getch();
				return 2;
			}

			else if (Board[j + 2][i - 2] == 1 && Board[j + 1][i - 1] == 1 && Board[j][i] == 1 && Board[j - 1][i + 1] == 1 && Board[j - 2][i + 2] == 1) {
				gotoxy(40, 10);
				printf("*** 백돌 승리 ***");
				getch();
				return 1;
			}
			else if (Board[j + 2][i - 2] == 2 && Board[j + 1][i - 1] == 2 && Board[j][i] == 2 && Board[j - 1][i + 1] == 2 && Board[j - 2][i + 2] == 2) {
				gotoxy(40, 10);
				printf("*** 흑돌 승리 ***");
				getch();
				return 2;
			}
		}
	}
	return 0;
}

void Erase_stone(int x, int y) {//좌표값에 따라서 돌을 옮길때 이전좌표에 돌이 출력되어있는데 그 출력된 돌을 지우는 함수
	gotoxy(x, y);

	if (x == 0 && y == 0) {
		printf("┌");
	}
	else if (x == 36 && y == 0) {
		printf("┐");
	}
	else if (x == 0 && y == 18) {
		printf("└");
	}
	else if (x == 36 && y == 18) {
		printf("┘");
	}
	else if (x == 0) {
		printf("├");
	}
	else if (y == 0) {
		printf("┬");
	}
	else if (x == 36) {
		printf("┤");
	}
	else if (y == 18) {
		printf("┴");
	}
	else {
		printf("┼");
	}
}

void Put_key(int Board[20][20], char move_key, int *x, int *y) {//커서이동을 처리하는 함수 
	switch (move_key) {
	case 72://위쪽 방향키
		if (*y - 1 < 0) {
			break;
		}
		else {
			*y -= 1;
			break;
		}
	case 80://아래쪽 방향키
		if (*y + 1 > 18) {
			break;
		}
		else {
			*y += 1;
			break;
		}
	case 75://왼쪽 방향키
		if (*x - 2 < 0) {
			break;
		}
		else {
			*x -= 2;
			break;
		}
	case 77://오른쪽 방향키
		if (*x + 2 > 36) {
			break;
		}
		else {
			*x += 2;
			break;
		}
	case 32://스페이스바
		Put_stone(Board, *x, *y);//돌 놓는 함수 호출, 현재 Board와 좌표 x, y를 매개변수로 보냄
		break;
	default:
		break; //나머지는 처리하지 않음
	}
}

void Put_stone(int Board[20][20], int x, int y) { //돌 놓는 함수
	if (Board[y][x / 2] == 0) {
		if (location == 1) {//전역변수 location이 1일 경우 
			Board[y][x / 2] = 1; //Board[y][x/2]=1를 넣음. Board[세로][가로], 가로는 2바이트가 한칸이기 때문에 나누기 2를 함
			location = 2; //전역변수 location를 2로 초기화
			stonecnt++;
		}
		else {//1이 아닐경우
			Board[y][x / 2] = 2; //Board[y][x/2]=1를 넣음. Board[세로][가로], 가로는 2바이트가 한칸이기 때문에 나누기 2를 함
			location = 1; //전역변수 location를 1로 초기화
			stonecnt++;
		}
	}
}

void draw_put_stone(int Board[20][20]) {//돌을 출력하는 함수
	int i;
	int j;
	for (i = 0; i < 20; ++i) {//이중for문으로 Board전체를 검사
		for (j = 0; j < 20; ++j) {
			if (Board[j][i] == 1) {
				gotoxy(i * 2, j); //가로는 2바이트가 한칸이기 때문에 i*2를 해줌
				printf("●"); //Board에서 1이 나오면 백돌 출력
			}
			else if (Board[j][i] == 2) {
				gotoxy(i * 2, j); //가로는 2바이트가 한칸이기 때문에 i*2를 해줌
				printf("○"); //Board에서 2가 나오면 흑돌 출력
			}
		}
	}
}

void game() {//게임함수
	int arr[20][20] = { 0, }; //오목판을 활용하기위한 배열 선언 19*19(줄)
	int x = 0, y = 0; //좌표값 및 배열의 위치를 나타내기위한 변수 선언
	char move_key;// 화살표키를 받을 변수 선언
	int win;//win_check함수의 리턴값을 저장하는 지역변수 선언
	
	stonecnt = 0; //게임을 계속할 경우 전판에 했던 값이 남아있으므로 게임을 다시 실행시킬시 돌 갯수 초기화.
	backboard(); //오목판 출력 19*19(줄)
	gotoxy(x, y);//돌의 위치를 초기화 시켜줌
	draw_stone();//처음 돌을 그려줌 location이 1이면 백돌 2이면 흑돌
	countstone();//놓은 돌이 0개일때 화면에 출력해줌

	do {//do~while문을 이용하여 ESC키를 누르지 않는한 계속 실행시킴
		move_key = getch();//화살표 키를 받음
		Erase_stone(x, y);//돌을 이동시킬때 출력되어 있는 이전의 돌을 지움
		Put_key(arr, move_key, &x, &y);//좌표값의 따라 돌을 이동시킴
		draw_put_stone(arr);//돌을 출력
		countstone();//현재까지 둔 돌의 갯수를 출력
		if (win = win_check(arr)) {//돌을 출력하고나서 이겼는지 졌는지 체크하는 함수, 리턴값이 1이면 if문 진행 0이면 진행하지않음
			return 0;//게임 종료
		}
		gotoxy(x, y);//이동된 자표값을 따라감
		draw_stone();//돌을 놓고나서 그 자리에서 부터 다음돌을 움직이게함
	} while (move_key != 27);//move_key가 ESC(27)이면 게임 종료 메인화면으로 이동함
}

void maplogo() {
	printf("\n\n");
	printf("	                                       _/\n");
	printf("	    _/_/    _/_/_/  _/_/      _/_/    _/  _/\n");
	printf("	 _/    _/  _/    _/    _/  _/    _/  _/_/\n");
	printf("	_/    _/  _/    _/    _/  _/    _/  _/  _/\n");
	printf("	 _/_/    _/    _/    _/    _/_/    _/    _/\n\n\n");
	printf("			●   vs   ○\n\n\n\n\n\n\n\n");
	printf("		     A W S D 로 움직이고\n");
	printf("		스페이스를 눌러서 들어가세요.");
}

void countstone() {//현재까지의 돌을 세는 함수
	gotoxy(43, 7);
	printf("돌 갯수: %d", stonecnt);
}

void exitprint() {
	printf("\n\n\n\n\n");
	printf("	       .########..##....##.########\n");
	printf("	       .##.....##..##..##..##......\n");
	printf("	       .##.....##...####...##......\n");
	printf("	       .########.....##....######..\n");
	printf("	       .##.....##....##....##......\n");
	printf("	       .##.....##....##....##......\n");
	printf("	       .########.....##....########\n\n\n\n\n");
	getch();
}