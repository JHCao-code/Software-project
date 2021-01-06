#ifndef CYH_H_
#define CYH_H_
#include <iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

/*
*功能：五子棋算法引擎
*参数：棋盘二维数组
*返回值；游戏结果
*作者：陈宇航
*/

typedef struct Board {	//二维数组表示棋盘，棋盘元素为0表示空，1表示黑子，-1表示白子
	int board[19][19] = {};
}Board;

int initial(Board* a) {	//初始化棋盘，将棋盘元素置0
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

int print(Board* a) {	//打印棋盘信息
	if (a == NULL) {
		return -1;
	}
	//char* num[19] = { "⒈","⒉","⒊","⒋","⒌","⒍","⒎","⒏","⒐","⒑","⒒","⒓","⒔","⒕","⒖","⒗","⒘","⒙","⒚" };
	cout << "\n  ⒈⒉⒊⒋⒌⒍⒎⒏⒐⒑⒒⒓⒔⒕⒖⒗⒘⒙⒚\n";
	for (int i = 0; i < 19; i++) {
		//cout << num[i];
		for (int j = 0; j < 19; j++) {
			if (i == 0 && j == 0 && a->board[i][j] == 0) cout << "┌ ";
			else if (i == 0 && j == 18 && a->board[i][j] == 0) cout << "┐";
			else if (i == 18 && j == 0 && a->board[i][j] == 0) cout << "└ ";
			else if (i == 18 && j == 18 && a->board[i][j] == 0) cout << "┘";
			else if ((i == 0 || i == 18) && a->board[i][j] == 0) cout << "─ ";
			else if (j == 0 && a->board[i][j] == 0) cout << "│ ";
			else if (j == 18 && a->board[i][j] == 0) cout << "│";
			else if (a->board[i][j] == 0) cout << "┼ ";
			else if (a->board[i][j] == 1) cout << "○";
			else if (a->board[i][j] == -1) cout << "●";
			else return -2;
			if (j == 18) cout << "\n";
		}
	}
	cout << "\n";
	return 1;
}

int play(Board* a, int color, int x, int y) {	//根据棋子信息改变对应数组元素
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

int win(Board* a, int color, int x, int y, int direction) {	//检测指定位置棋子最大相连数
	if (a == NULL) {
		return -1;
	}
	int count = 0;
	int max = -1;
	int i = 0;
	if (direction == 2 || direction == 1) {
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19; i++) {	//	横向
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
		for (i = (y - 4 > 0) ? y - 4 : 0; i <= y + 4 && i < 19; i++) {	//	纵向
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
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y + i - x < 19; i++) {	//左斜向
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
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y - i + x > 0; i++) {	//右斜向
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

int is_four(Board* a, int color, int x, int y, int direction) {	//判断指定位置是否为活四或冲四
	if (a == NULL) {
		return -1;
	}
	int i = 0, count = 0;
	int x1, y1, x2, y2;
	if (direction == 2) {
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19; i++) {	//	横向
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
		for (i = (y - 4 > 0) ? y - 4 : 0; i <= y + 4 && i < 19; i++) {	//	纵向
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
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y + i - x < 19; i++) {	//左斜向
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
		for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y - i + x > 0; i++) {	//右斜向
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


int is_three(Board* a, int color, int x, int y) {	//判断指定位置是否为活三
	if (a == NULL) {
		return -1;
	}
	int i = 0, count = 0;
	for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19; i++) {	//	横向
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

	for (i = (y - 4 > 0) ? y - 4 : 0; i <= y + 4 && i < 19; i++) {	//	纵向
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
	for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y + i - x < 19; i++) {	//左斜向
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
	for (i = (x - 4 > 0) ? x - 4 : 0; i <= x + 4 && i < 19 && y - i + x > 0; i++) {	//右斜向
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

int forbidden(Board* a, int x, int y) {	//判断落子处是否触发禁手
	if (a == NULL) {
		return -1;
	}
	int three = 0, four = 0;
	three = is_three(a, a->board[y][x], x, y);	//检测活三数量
	for (int i = 2; i < 6; i++) {
		switch (is_four(a, a->board[y][x], x, y, i)) {	//检测活四及冲四数量
		case 1:
		case 3:
			four++;
			break;
		case 2:
			four += 2;
			break;
		}
	}
	if (three == 2) {	//若活三数量为二，则触发三三禁手
		return 1;
	}
	else if (four == 2) {	//若活四及冲四数量为2，则触发四四禁手
		return 2;
	}
	else if (three + four >= 3) {	//若活三，活四及冲四数量大于3，则触发禁手
		return 3;
	}
	return 0;
}

int set(Board* a) {	//在对应位置落子，检测禁手及获胜情况
	if (a == NULL) {
		return -1;
	}
	int color, x, y, num, forbid;
	cout << "输入棋子信息:颜色(-1白子,1黑子),x坐标,y坐标\n";
	cin >> color >> x >> y;
	if (play(a, color, x - 1, y - 1) != 1) {
		cout << "输入错误\n";
		return -2;
	}
	forbid = forbidden(a, x - 1, y - 1);	//检测禁手情况
	if (forbid == 1) {
		cout << "黑方三三禁手，白方获胜\n";
		return 0;
	}
	else if (forbid == 2) {
		cout << "黑方四四禁手，白方获胜\n";
		return 0;
	}
	else if (forbid == 3) {
		cout << "黑方禁手，白方获胜\n";
		return 0;
	}
	num = win(a, color, x - 1, y - 1, 1);	//检测获胜情况
	if (num >= 5) {
		if (color == -1) {
			cout << "白方五子相连，白方获胜\n";
			return 0;
		}
		else if (color == 1 && num > 5) {
			cout << "黑方长连禁手，白方获胜\n";
			return 0;
		}
		else {
			cout << "黑方五子相连，黑方获胜\n";
			return 0;
		}
	}
}

void game() {	//开始游戏
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

