#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 100 //버퍼크기를 지정
char input[SIZE] = { 0, }; //수식을 입력할 버퍼
int length = 0; //입력받은 수식의 길이를 저장할 변수
int Operation(char ARRAY[SIZE], int count); //입력받은 수식을 계산하고 그 값을 리턴하는 함수
int main() {
	int i;
	while (1) { //수식 입력 무한 반복문
		printf("수식 입력 : ");
		scanf("%s", input);
		for (i = 0; i < SIZE; i++) {
			if (input[i] == 0) {
				length = i; //수식 길이를 length에 저장
				break;
			}
			else if (input[i] == 'q') {
				exit(1); //만약 q를 입력받으면 프로그램을 종료시킨다.
			}
		}
		int result = Operation(input, length); //입력받은 수식버퍼와 길이를 수식계산 함수의 인자로 넘겨준다.
		if (result == NULL) {
			printf("ERROR\n"); //  result가 NULL이면  error 를 출력하고 다시 무한 반복문으로 돌아감
		}
		else {
			printf("%d\n", result); // 결과 출력
		}
	}
	return 0;
}
int Operation(char ARRAY[SIZE], int count) {
	int num[SIZE] = { 0, }; // 숫자를 저장하는 배열
	int n_index = 0;		// num 배열에 들어가는 숫자의 갯수를 세기위한 변수
	char sign[SIZE] = { 0, }; //수식기호를 저장하는 공간
	int s_index = 0;		// sign 배열에 들어가는 수식의 갯수를 세기위한 변수
	int mid = 0;		    // 숫자들을 계산하기 위한 중간역할을 하는 변수
	int i, k; //반복문에서 사용할 일반 변수들
	int check = 0; //곱하기나 나누기를 입력받았을 때 표현해주는 변수
	for (i = 0; i < count; i++) {
		for (k = 0; k < count; k++) {
			if (input[0] == '-' || (input[k]=='/'&&input[k+1]=='0')) { 
				return NULL; // 마이너스 부호만 받거나 0으로 나누면 NULL을 리턴함.
			}
		}
		if ('0' <= ARRAY[i] && ARRAY[i] <= '9') {
			mid *= 10;
			mid += ARRAY[i] - '0';
		}
		else if (ARRAY[i] == '-' || ARRAY[i] == '+') { // - + 연산자일 경우
			num[n_index] = mid;      // 기존에 구한 숫자를 num배열에 추가하고,
			mid = 0;            // mid을 초기화한다.
			n_index++;

			if (check) { // 곱하기나 나누기를 가지고 있음을 확인한 상태라면
				int tmp = 0;
				if (sign[s_index - 1] == '*') {
					//                     printf("곱셈 계산");
					tmp = num[n_index - 2] * num[n_index - 1];
				}
				else if (sign[s_index - 1] == '/') {
					//printf("나눗셈 계산");
					tmp = num[n_index - 2] / num[n_index - 1];
				}
				//printf(" %d\n", tmp);
				check = 0;
				// 계산한 값들을 배열에서 제외해준다.
				sign[s_index - 1] = 0;
				s_index--;

				num[n_index - 1] = 0;
				num[n_index - 2] = 0;
				n_index -= 2; // 배열에서 제외해준 만큼 num배열의 인덱스값을 빼준다.

				num[n_index] = tmp;
				n_index++;
			}
			sign[s_index] = ARRAY[i]; // 수식도 배열에 추가한다.
			s_index++;
		}
		else if (ARRAY[i] == '*' || ARRAY[i] == '/') { // * / 연산자일 경우,
			num[n_index] = mid;  // 기존에 구한 숫자를 num배열에 추가하고,
			mid = 0;     // mid을 초기화한다.
			n_index++;     // 배열의 크기를 계산하기 위한 n_index는 1을 더해준다.

			if (check) { // 기존에 곱셈이나 나눗셈 수식을 받아둔게 있다면
				int tmp = 0;
				if (sign[s_index - 1] == '*') {
					//printf("곱셈 계산");
					tmp = num[n_index - 2] * num[n_index - 1];
				}
				else if (sign[s_index - 1] == '/') {
					//printf("나눗셈 계산");
					tmp = num[n_index - 2] / num[n_index - 1];
				}
				//printf(" %d\n", tmp);
				sign[s_index - 1] = 0;
				s_index--;

				num[n_index - 1] = 0;
				num[n_index - 2] = 0;
				n_index -= 2;		//배열에서 제외해준 만큼 num배열의 인덱스값을 빼준다.

				num[n_index] = tmp;
				n_index++;
			}

			sign[s_index] = ARRAY[i]; // 수식도 배열에 추가한다.
			s_index++;

			check = 1; // 곱하기나 나누기를 입력받았음을 표현해둔다.
		}

		if (i == count - 1) { // 수식을 다 입력받은 상태, 곱하기나 나누기를 입력 받은 상태라면
			num[n_index] = mid;      // 기존에 구한 숫자를 num배열에 추가하고,
			mid = 0;            // mid을 초기화한다.
			n_index++;             // 배열의 크기를 계산하기 위한 n_index는 1을 더해준다.

			if (check) {
				int tmp = 0;
				if (sign[s_index - 1] == '*') {
					//printf("곱셈 계산");
					tmp = num[n_index - 2] * num[n_index - 1];
				}
				else if (sign[s_index - 1] == '/') {
					//printf("나눗셈 계산 %d, %d", num[n_index-2], num[n_index-1]);
					tmp = num[n_index - 2] / num[n_index - 1];
				}
				//printf(" %d\n", tmp);
				check = 0;
				// 계산한 값들을 배열에서 제외해준다.
				sign[s_index - 1] = 0;
				s_index--;

				num[n_index - 1] = 0;
				num[n_index - 2] = 0;
				n_index -= 2;		//배열에서 제외해준 만큼 num배열의 인덱스값을 빼준다.

				num[n_index] = tmp;
				n_index++;
			}
		}
	}

	//정리한 수식들을 전부 + 또는 - 해준다.
	int result = num[0];
	for (int i = 0; i < s_index; i++) {
		if (sign[i] == '+') {
			result += num[i + 1];
		}
		else if (sign[i] == '-') {
			result -= num[i + 1];
		}
	}
	
	return result;
}
