#include"cjh.h"
#include"cyh.h"
#include"qk.h"

int main() {
	int choice;
	cout << "---------------------------��ӭʹ�����ʵϰ�ۺ���Ŀ---------------------------" << endl;
	cout << " 1. ������     2.�����    3.�������     4.exit" << endl;
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
		cout << "1. ������     2.�����    3.�������   4.exit" << endl;
	}
	return 0;
}