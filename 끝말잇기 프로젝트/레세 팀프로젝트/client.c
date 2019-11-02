#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<Windows.h>
#include<string.h>

#define WIN32_LEAN_AND_MEAN
#define PRINT_WORD_CHAIN_X 50

DWORD WINAPI ThreadFunc(LPVOID);

// DWORD�� ������� == long
// WINAPI �����쿡���� API
//LPVOID ms���� ����ϴ� void������

typedef struct _packet {
	int type; // 1�̸� �ܾ��Է�, 2�̸� ä��
	char buffer[101];
}Packet;

void ErrorHandling(char* message);
void gotoxy(int x, int y);
void Clear_line(x, y);
void Print_Word(LPVOID n);
void Chating(LPVOID n);

int Chating_line = 0, Player_life = 3;
char Chat[101];
HANDLE hThrd_Word, hThrd_Chating;
DWORD threadId_Word, threadId_Chating;
WSADATA wsaData;
SOCKET hSocket;
SOCKADDR_IN servAddr;
Packet packet;

// ��µ� ä��â �ʱ�ȭ
char Chatingchang[20][32] =
{
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  "
};

int main(int argc, char *argv[]) {
	int strLen;

	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("connect() error!");
	}

	//�����带 ����
	hThrd_Chating = CreateThread(NULL, 0, (DWORD WINAPI)Chating, 0, 0, &threadId_Chating);
	hThrd_Word = CreateThread(NULL, 0, (DWORD WINAPI)Print_Word, 0, 0, &threadId_Word);

	//�����ձ� �Լ��� ������ ���μ��� ����
	WaitForSingleObject(hThrd_Word, INFINITE);

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc("\n", stderr);
	exit(1);
}

//x,y��ġ ȭ�� �ʱ�ȭ
void Clear_line(x, y)
{
	gotoxy(x, y);
	printf("                                        ");
}

//Ŀ�� �̵� �Լ�
void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Print_Word(LPVOID n)
{
	int k, strLen;

	while (recv(hSocket, (char*)&packet, sizeof(Packet), 0) != -1)
	{
		if (Player_life == 0)
			break;

		if (packet.type == 1)
		{
			if (!strcmp(packet.buffer, "0"))
			{
				Clear_line(PRINT_WORD_CHAIN_X, 9);
				gotoxy(PRINT_WORD_CHAIN_X, 9);
				printf("�ܾ �����ϴ�");
				Clear_line(1, 23);
				gotoxy(1, 23);
			}
			else if (!strcmp(packet.buffer, "1"))
			{
				Clear_line(PRINT_WORD_CHAIN_X, 9);
				gotoxy(PRINT_WORD_CHAIN_X, 9);
				printf("�̹� ���� �ܾ��Դϴ�.");
				Clear_line(1, 23);
				gotoxy(1, 23);
			}
			else if (!strcmp(packet.buffer, "-1"))
			{
				Clear_line(PRINT_WORD_CHAIN_X, 9);
				gotoxy(PRINT_WORD_CHAIN_X, 9);
				printf("�� �ܾ�� �� �ܾ��� ��, �ڰ� �ٸ��ϴ�.");
				Clear_line(1, 23);
				gotoxy(1, 23);
			}
			else if (!strcmp(packet.buffer, "error"))
			{
				// �ƹ� ó���� �����ֱ����� �Ϻη� �������ϴ�.
			}
			else
			{
				Clear_line(PRINT_WORD_CHAIN_X, 9);
				gotoxy(PRINT_WORD_CHAIN_X, 9);
				printf("�ܾ �����մϴ�.");
				Clear_line(PRINT_WORD_CHAIN_X, 14);
				gotoxy(PRINT_WORD_CHAIN_X, 14);
				printf("�� �ܾ� : %s", packet.buffer);
				Clear_line(1, 23);
				gotoxy(1, 23);
			}
		}
		else if (packet.type == 2)
		{
			for (k = 19; k >= 0; k--)
			{
				if (k == 0) // �� �Ʒ� ä��â�� �迭�� �Էµ� ���ڿ��� ����
					strcpy(Chatingchang[k], packet.buffer);
				else // �ƴҰ�� ä��â �迭�� ��ĭ�� �ø�
					strcpy(Chatingchang[k], Chatingchang[k - 1]);

				//���� ��ġ�� ȭ�� �ʱ�ȭ �� �̵�, ���� ���� ���
				Clear_line(1, 20 - k);
				gotoxy(1, 20 - k);
				printf("%s", Chatingchang[k]);
			}
			gotoxy(1, 23);
		}
		else if (packet.type == 3)
		{
			if ((!strcmp(packet.buffer, "0")) || (!strcmp(packet.buffer, "1")) || (!strcmp(packet.buffer, "-1")))
				Player_life--;
		}

		Clear_line(PRINT_WORD_CHAIN_X, 5);
		gotoxy(PRINT_WORD_CHAIN_X, 5);
		printf("Player Life : %d", Player_life);
		Clear_line(1, 23);
		gotoxy(1, 23);
	}

	SetEvent(hThrd_Word);
}

void Chating(LPVOID n)
{
	int flag;
	char Player_input[101], dump;

	system("cls");
	while (1)
	{
		Clear_line(1, 23);
		gotoxy(1, 23);
		scanf("%d%c", &flag, &dump);

		switch (flag)
		{
		case 1:packet.type = 1; break;
		case 2:packet.type = 2; break;
		default:break;
		}
		Clear_line(1, 23);
		gotoxy(1, 23);
		printf("�Է� : ");

		gets_s(packet.buffer, 30);

		send(hSocket, (char*)&packet, sizeof(Packet), 0);
	}
}