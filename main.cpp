#include"cjh.h"
#include"cyh.h"
#include"qk.h"

int main() {
	int choice;
	cout << "---------------------------欢迎使用软件实习综合项目---------------------------" << endl;
	cout << " 1. 五子棋     2.汇编器    3.反汇编器     4.exit" << endl;
	while (cin >> choice) {

		switch (choice) {
		case 1:
			game();
			break;

		case 2:
			menu();
			break;

		case 3:
			Disassemble();
			break;

		case 4:
			exit(EXIT_SUCCESS);

		default:
			cout << "Invalid input!" << endl;
			break;
		 }
		cout << "1. 五子棋     2.汇编器    3.反汇编器   4.exit" << endl;
	}
	return 0;
}