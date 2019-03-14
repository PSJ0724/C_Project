#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 100 //����ũ�⸦ ����
char input[SIZE] = { 0, }; //������ �Է��� ����
int length = 0; //�Է¹��� ������ ���̸� ������ ����
int Operation(char ARRAY[SIZE], int count); //�Է¹��� ������ ����ϰ� �� ���� �����ϴ� �Լ�
int main() {
	int i;
	while (1) { //���� �Է� ���� �ݺ���
		printf("���� �Է� : ");
		scanf("%s", input);
		for (i = 0; i < SIZE; i++) {
			if (input[i] == 0) {
				length = i; //���� ���̸� length�� ����
				break;
			}
			else if (input[i] == 'q') {
				exit(1); //���� q�� �Է¹����� ���α׷��� �����Ų��.
			}
		}
		int result = Operation(input, length); //�Է¹��� ���Ĺ��ۿ� ���̸� ���İ�� �Լ��� ���ڷ� �Ѱ��ش�.
		if (result == NULL) {
			printf("ERROR\n"); //  result�� NULL�̸�  error �� ����ϰ� �ٽ� ���� �ݺ������� ���ư�
		}
		else {
			printf("%d\n", result); // ��� ���
		}
	}
	return 0;
}
int Operation(char ARRAY[SIZE], int count) {
	int num[SIZE] = { 0, }; // ���ڸ� �����ϴ� �迭
	int n_index = 0;		// num �迭�� ���� ������ ������ �������� ����
	char sign[SIZE] = { 0, }; //���ı�ȣ�� �����ϴ� ����
	int s_index = 0;		// sign �迭�� ���� ������ ������ �������� ����
	int mid = 0;		    // ���ڵ��� ����ϱ� ���� �߰������� �ϴ� ����
	int i, k; //�ݺ������� ����� �Ϲ� ������
	int check = 0; //���ϱ⳪ �����⸦ �Է¹޾��� �� ǥ�����ִ� ����
	for (i = 0; i < count; i++) {
		for (k = 0; k < count; k++) {
			if (input[0] == '-' || (input[k]=='/'&&input[k+1]=='0')) { 
				return NULL; // ���̳ʽ� ��ȣ�� �ްų� 0���� ������ NULL�� ������.
			}
		}
		if ('0' <= ARRAY[i] && ARRAY[i] <= '9') {
			mid *= 10;
			mid += ARRAY[i] - '0';
		}
		else if (ARRAY[i] == '-' || ARRAY[i] == '+') { // - + �������� ���
			num[n_index] = mid;      // ������ ���� ���ڸ� num�迭�� �߰��ϰ�,
			mid = 0;            // mid�� �ʱ�ȭ�Ѵ�.
			n_index++;

			if (check) { // ���ϱ⳪ �����⸦ ������ ������ Ȯ���� ���¶��
				int tmp = 0;
				if (sign[s_index - 1] == '*') {
					//                     printf("���� ���");
					tmp = num[n_index - 2] * num[n_index - 1];
				}
				else if (sign[s_index - 1] == '/') {
					//printf("������ ���");
					tmp = num[n_index - 2] / num[n_index - 1];
				}
				//printf(" %d\n", tmp);
				check = 0;
				// ����� ������ �迭���� �������ش�.
				sign[s_index - 1] = 0;
				s_index--;

				num[n_index - 1] = 0;
				num[n_index - 2] = 0;
				n_index -= 2; // �迭���� �������� ��ŭ num�迭�� �ε������� ���ش�.

				num[n_index] = tmp;
				n_index++;
			}
			sign[s_index] = ARRAY[i]; // ���ĵ� �迭�� �߰��Ѵ�.
			s_index++;
		}
		else if (ARRAY[i] == '*' || ARRAY[i] == '/') { // * / �������� ���,
			num[n_index] = mid;  // ������ ���� ���ڸ� num�迭�� �߰��ϰ�,
			mid = 0;     // mid�� �ʱ�ȭ�Ѵ�.
			n_index++;     // �迭�� ũ�⸦ ����ϱ� ���� n_index�� 1�� �����ش�.

			if (check) { // ������ �����̳� ������ ������ �޾Ƶа� �ִٸ�
				int tmp = 0;
				if (sign[s_index - 1] == '*') {
					//printf("���� ���");
					tmp = num[n_index - 2] * num[n_index - 1];
				}
				else if (sign[s_index - 1] == '/') {
					//printf("������ ���");
					tmp = num[n_index - 2] / num[n_index - 1];
				}
				//printf(" %d\n", tmp);
				sign[s_index - 1] = 0;
				s_index--;

				num[n_index - 1] = 0;
				num[n_index - 2] = 0;
				n_index -= 2;		//�迭���� �������� ��ŭ num�迭�� �ε������� ���ش�.

				num[n_index] = tmp;
				n_index++;
			}

			sign[s_index] = ARRAY[i]; // ���ĵ� �迭�� �߰��Ѵ�.
			s_index++;

			check = 1; // ���ϱ⳪ �����⸦ �Է¹޾����� ǥ���صд�.
		}

		if (i == count - 1) { // ������ �� �Է¹��� ����, ���ϱ⳪ �����⸦ �Է� ���� ���¶��
			num[n_index] = mid;      // ������ ���� ���ڸ� num�迭�� �߰��ϰ�,
			mid = 0;            // mid�� �ʱ�ȭ�Ѵ�.
			n_index++;             // �迭�� ũ�⸦ ����ϱ� ���� n_index�� 1�� �����ش�.

			if (check) {
				int tmp = 0;
				if (sign[s_index - 1] == '*') {
					//printf("���� ���");
					tmp = num[n_index - 2] * num[n_index - 1];
				}
				else if (sign[s_index - 1] == '/') {
					//printf("������ ��� %d, %d", num[n_index-2], num[n_index-1]);
					tmp = num[n_index - 2] / num[n_index - 1];
				}
				//printf(" %d\n", tmp);
				check = 0;
				// ����� ������ �迭���� �������ش�.
				sign[s_index - 1] = 0;
				s_index--;

				num[n_index - 1] = 0;
				num[n_index - 2] = 0;
				n_index -= 2;		//�迭���� �������� ��ŭ num�迭�� �ε������� ���ش�.

				num[n_index] = tmp;
				n_index++;
			}
		}
	}

	//������ ���ĵ��� ���� + �Ǵ� - ���ش�.
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
