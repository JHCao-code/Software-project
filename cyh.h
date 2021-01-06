#ifndef CYH_H_
#define CYH_H_
#include <iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

/*
*���ܣ��������㷨����
*���������̶�ά����
*����ֵ����Ϸ���
*���ߣ����
*/

typedef struct Board {	//��ά�����ʾ���̣�����Ԫ��Ϊ0��ʾ�գ�1��ʾ���ӣ�-1��ʾ����
	int board[19][19] = {};
}Board;

int initial(Board* a) {	//��ʼ�����̣�������Ԫ����0
	if (a == NULL) {
		return -1;
	}
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			a->board[i][j] = 0;
		}
	}
	return 1;
}

int print(Board* a) {	//��ӡ������Ϣ
	if (a == NULL) {
		return -1;
	}
	//char* num[19] = { "��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��" };
	cout << "\n  �����������������������������������¢�\n";
	for (int i = 0; i < 19; i++) {
		//cout << num[i];
		for (int j = 0; j < 19; j++) {
			if (i == 0 && j == 0 && a->board[i][j] == 0) cout << "�� ";
			else if (i == 0 && j == 18 && a->board[i][j] == 0) cout << "��";
			else if (i == 18 && j == 0 && a->board[i][j] == 0) cout << "�� ";
			else if (i == 18 && j == 18 && a->board[i][j] == 0) cout << "��";
			else if ((i == 0 || i == 18) && a->board[i][j] == 0) cout << "�� ";
			else if (j == 0 && a->board[i][j] == 0) cout << "�� ";
			else if (j == 18 && a->board[i][j] == 0) cout << "��";
			else if (a->board[i][j] == 0) cout << "�� ";
			else if (a->board[i][j] == 1) cout << "��";
			else if (a->board[i][j] == -1) cout << "��";
			else return -2;
			if (j == 18) cout << "\n";
		}
	}
	cout << "\n";
	return 1;
}

int play(Board* a, int color, int x, int y) {	//����������Ϣ�ı��Ӧ����Ԫ��
	if (a == NULL) {
		return -1;
	}
	if (color != 1 && color != -1 && color != 0) {
		return -2;
	}
	if (x > 18 || x < 0 || y>18 || y < 0) {
		return -3;
	}
	if (a->board[y][x] != 0 && color != 0) {
		return -4;
	}
	a->board[y][x] = color;
	return 1;
}

int win(Board* a, int color, int x, int y, int direction) {	//���ָ��λ���������������
	if (a == NULL) {
		return -1;
	}
	int count = 0;
	int max = -1;
	int i = 0;
	if (direction == 2 || direction == 1) {
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19; i++) {	//	����
			if (a->board[y][i] == color) {
				count++;
			}
			else {
				if (count > max) {
					max = count;
				}
				count = 0;
			}
		}
		if (count > max) {
			max = count;
		}
		count = 0;
	}
	if (direction == 3 || direction == 1) {
		for (i = (y - 4 > 0) ? y - 4 : 0; i <= y + 4 && i < 19; i++) {	//	����
			if (a->board[i][x] == color) {
				count++;
			}
			else {
				if (count > max) {
					max = count;
				}
				count = 0;
			}
		}
		if (count > max) {
			max = count;
		}
		count = 0;
	}
	if (direction == 4 || direction == 1) {
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y + i - x < 19; i++) {	//��б��
			if (y + i - x < 0) {
				continue;
			}
			if (a->board[y + i - x][i] == color) {
				count++;
			}
			else {
				if (count > max) {
					max = count;
				}
				count = 0;
			}
		}
		if (count > max) {
			max = count;
		}
		count = 0;
	}
	if (direction == 5 || direction == 1) {
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y - i + x > 0; i++) {	//��б��
			if (y - i + x > 18) {
				continue;
			}
			if (a->board[y - i + x][i] == color) {
				count++;
			}
			else {
				if (count > max) {
					max = count;
				}
				count = 0;
			}
		}
		if (count > max) {
			max = count;
		}
	}
	return max;
}

int is_four(Board* a, int color, int x, int y, int direction) {	//�ж�ָ��λ���Ƿ�Ϊ���Ļ����
	if (a == NULL) {
		return -1;
	}
	int i = 0, count = 0;
	int x1, y1, x2, y2;
	if (direction == 2) {
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19; i++) {	//	����
			if (a->board[y][i] == 0) {
				play(a, color, i, y);
				if (win(a, color, i, y, direction) == 5) {
					count++;
					if (count == 1) {
						x1 = i;
					}
					else {
						x2 = i;
						if (x2 - x1 == 5) {
							count = 3;
						}
					}
				}
				play(a, 0, i, y);
			}
		}
	}
	if (direction == 3) {
		for (i = (y - 4 > 0) ? y - 4 : 0; i <= y + 4 && i < 19; i++) {	//	����
			if (a->board[i][x] == 0) {
				play(a, color, x, i);
				if (win(a, color, x, i, direction) == 5) {
					count++;
					if (count == 1) {
						y1 = i;
					}
					else {
						y2 = i;
						if (y2 - y1 == 5) {
							count = 3;
						}
					}
				}
				play(a, 0, x, i);
			}
		}
	}
	if (direction == 4) {
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y + i - x < 19; i++) {	//��б��
			if (y + i - x < 0) {
				continue;
			}
			if (a->board[y + i - x][i] == 0) {
				play(a, color, i, y + i - x);
				if (win(a, color, i, y + i - x, direction) == 5) {
					count++;
					if (count == 1) {
						x1 = i;
					}
					else {
						x2 = i;
						if (x2 - x1 == 5) {
							count = 3;
						}
					}
				}
				play(a, 0, i, y + i - x);
			}
		}
	}
	if (direction == 5) {
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y - i + x > 0; i++) {	//��б��
			if (y - i + x > 18) {
				continue;
			}
			if (a->board[y - i + x][i] == 0) {
				play(a, color, i, y - i + x);
				if (win(a, color, i, y - i + x, direction) == 5) {
					count++;
					if (count == 1) {
						x1 = i;
					}
					else {
						x2 = i;
						if (x2 - x1 == 5) {
							count = 3;
						}
					}
				}
				play(a, 0, i, y - i + x);
			}
		}
	}
	return count;
}


int is_three(Board* a, int color, int x, int y) {	//�ж�ָ��λ���Ƿ�Ϊ����
	if (a == NULL) {
		return -1;
	}
	int i = 0, count = 0;
	for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19; i++) {	//	����
		if (a->board[y][i] == 0) {
			play(a, color, i, y);
			if (is_four(a, color, i, y, 2) == 3) {
				count++;
				play(a, 0, i, y);
				break;
			}
			play(a, 0, i, y);
		}
	}

	for (i = (y - 4 > 0) ? y - 4 : 0; i <= y + 4 && i < 19; i++) {	//	����
		if (a->board[i][x] == 0) {
			play(a, color, x, i);
			if (is_four(a, color, x, i, 3) == 3) {
				count++;
				play(a, 0, x, i);
				break;
			}
			play(a, 0, x, i);
		}
	}
	for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y + i - x < 19; i++) {	//��б��
		if (y + i - x < 0) {
			continue;
		}
		if (a->board[y + i - x][i] == 0) {
			play(a, color, i, y + i - x);
			if (is_four(a, color, i, y + i - x, 4) == 3) {
				count++;
				play(a, 0, i, y + i - x);
				break;
			}
			play(a, 0, i, y + i - x);
		}
	}
	for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y - i + x > 0; i++) {	//��б��
		if (y - i + x > 18) {
			continue;
		}
		if (a->board[y - i + x][i] == 0) {
			play(a, color, i, y - i + x);
			if (is_four(a, color, i, y - i + x, 5) == 3) {
				count++;
				play(a, 0, i, y - i + x);
				break;
			}
			play(a, 0, i, y - i + x);
		}
	}
	return count;
}

int forbidden(Board* a, int x, int y) {	//�ж����Ӵ��Ƿ񴥷�����
	if (a == NULL) {
		return -1;
	}
	int three = 0, four = 0;
	three = is_three(a, a->board[y][x], x, y);	//����������
	for (int i = 2; i < 6; i++) {
		switch (is_four(a, a->board[y][x], x, y, i)) {	//�����ļ���������
		case 1:
		case 3:
			four++;
			break;
		case 2:
			four += 2;
			break;
		}
	}
	if (three == 2) {	//����������Ϊ�����򴥷���������
		return 1;
	}
	else if (four == 2) {	//�����ļ���������Ϊ2���򴥷����Ľ���
		return 2;
	}
	else if (three + four >= 3) {	//�����������ļ�������������3���򴥷�����
		return 3;
	}
	return 0;
}

int set(Board* a) {	//�ڶ�Ӧλ�����ӣ������ּ���ʤ���
	if (a == NULL) {
		return -1;
	}
	int color, x, y, num, forbid;
	cout << "����������Ϣ:��ɫ(-1����,1����),x����,y����\n";
	cin >> color >> x >> y;
	if (play(a, color, x - 1, y - 1) != 1) {
		cout << "�������\n";
		return -2;
	}
	forbid = forbidden(a, x - 1, y - 1);	//���������
	if (forbid == 1) {
		cout << "�ڷ��������֣��׷���ʤ\n";
		return 0;
	}
	else if (forbid == 2) {
		cout << "�ڷ����Ľ��֣��׷���ʤ\n";
		return 0;
	}
	else if (forbid == 3) {
		cout << "�ڷ����֣��׷���ʤ\n";
		return 0;
	}
	num = win(a, color, x - 1, y - 1, 1);	//����ʤ���
	if (num >= 5) {
		if (color == -1) {
			cout << "�׷������������׷���ʤ\n";
			return 0;
		}
		else if (color == 1 && num > 5) {
			cout << "�ڷ��������֣��׷���ʤ\n";
			return 0;
		}
		else {
			cout << "�ڷ������������ڷ���ʤ\n";
			return 0;
		}
	}
}

void game() {	//��ʼ��Ϸ
	Board* a = (Board*)malloc(sizeof(Board));
	initial(a);
	print(a);
	while (true) {
		if (set(a) == 0) {
			break;
		}
		print(a);
	}
}


#endif // !CYH_H_

