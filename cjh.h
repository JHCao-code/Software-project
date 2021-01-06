#ifndef CJH_H_
#define CJH_H_

#include<iostream>
#include<vector>
#include<string.h>
#include<string>
#include<bitset>
#include<map>
#include<algorithm>

using namespace std;

enum ComIns		   //���ָ�
{
	In, Out, Add, Sub, Mul, Div, Dup,
	Ld, St, Ldc, Jlt, Jle, Jgt, Jge, Jeq, Jne,
	Jmp, Halt, Invalid
};


typedef struct instruction {
	string op;
	int op_num;
}Ins;

//��������ݽṹ˵��
//vector <Ins> In_ship;	//�洢���ָ� (����)
//vector <bitset<8>> Out_ship_op; //�洢opת����Ķ�����
//vector <bitset<8>> Out_ship_op_num;	 //ת��op_numת����Ķ���
//map<string, int> ys;		  //ӳ���ϵ

/*
*���ܣ������
*���������ָ��
*����ֵ������ָ��
*���ߣ�191172-�ܼ���
*/

void Initial_Ins(vector <Ins>* In_ship, map<string, bitset<8>> ys) {		//��ʼ�����ָ����洢
	cout << "Please Enter your operation code and operands:(such as 'jmp 123' Tip:'# 3' to quit) " << endl;		   //��Сд����
	Ins input;
	while (cin >> input.op >> input.op_num && input.op != "#") {
		transform(input.op.begin(), input.op.end(), input.op.begin(), tolower);
		if (ys.count(input.op) > 0 && !isdigit(input.op_num) && input.op_num < 255) {
			In_ship->push_back(input);
		}
		else {
			cout << "Invalid input! Please enter again:" << endl;
			//exit(EXIT_FAILURE);
		}
	}
}


void init_cast(map<string, bitset<8>>* ys) {			 //��ʼ����ʼop��Ӧ�Ķ����� ӳ���ϵ(map)
	ys->insert({ pair<string,bitset<8>>("halt",bitset<8>(Halt)),pair<string,bitset<8>>("in",bitset<8>(In)),pair<string,bitset<8>>("out",bitset<8>(Out)),pair<string,bitset<8>>("add",bitset<8>(Add)) });
	ys->insert({ pair<string,bitset<8>>("sub",bitset<8>(Sub)),pair<string,bitset<8>>("mul",bitset<8>(Mul)),pair<string,bitset<8>>("div",bitset<8>(Div)),pair<string,bitset<8>>("dup",bitset<8>(Dup)) });
	ys->insert({ pair<string,bitset<8>>("ld",bitset<8>(Ld)),pair<string,bitset<8>>("st",bitset<8>(St)),pair<string,bitset<8>>("ldc",bitset<8>(Ldc)),pair<string,bitset<8>>("jlt",bitset<8>(Jlt)) });
	ys->insert({ pair<string,bitset<8>>("jle",bitset<8>(Jle)),pair<string,bitset<8>>("jgt",bitset<8>(Jgt)),pair<string,bitset<8>>("jge",bitset<8>(Jge)),pair<string,bitset<8>>("jeq",bitset<8>(Jeq)) });
	ys->insert({ pair<string,bitset<8>>("jne",bitset<8>(Jne)),pair<string,bitset<8>>("jmp",bitset<8>(Jmp)),pair<string,bitset<8>>("invalid",bitset<8>(-1)) });
}

//�����ָ��ͳһ��ʽ��ΪСд
void format(vector <Ins>* In_ship) {
	if (In_ship->empty()) {
		cout << "Empty input!" << endl;
		return;
	}
	for (vector <Ins>::iterator it = In_ship->begin(); it != In_ship->end(); it++) {
		transform(it->op.begin(), it->op.end(), it->op.begin(), tolower);
	}
}

bool insert_op(map<string, bitset<8>>* ys,vector <bitset<8>>* Out_ship_op) {
	string op;
	int prior;
	cout << "����������� ��Ӧ�Ļ����루ʮ���ƣ�:" << endl;
	cin >> op >> prior;
	if (op.empty() || isdigit(prior)) {
		return false;
	}
	transform(op.begin(), op.end(), op.begin(), tolower);
	ys->insert(pair<string, bitset<8>>(op, bitset<8>(prior)));
	Out_ship_op->push_back(bitset<8>(prior));
	return true;
}

void transform_op(map<string, bitset<8>> ys, vector <Ins> In_ship, vector <bitset<8>>* Out_ship_op) {	 //��ɻ��op��������ת�����洢ת����Ķ�����
	if (In_ship.empty()) {
		cout << "Warning: Without any Input!" << endl;
		return;
	}
	for (vector <Ins>::iterator it = In_ship.begin(); it != In_ship.end(); it++) {
		if (ys.count(it->op) > 0 && !count(Out_ship_op->begin(), Out_ship_op->end(), ys[it->op]) ) {
			Out_ship_op->push_back(ys[it->op]);
		}
	}
}

void  transform_op_num(vector <Ins> In_ship, vector <bitset<8>>* Out_ship_op_num) {
	if (In_ship.empty()) {
		cout << "Error:Without any Input!" << endl;
		return;
	}
	for (vector <Ins>::iterator it = In_ship.begin(); it != In_ship.end(); it++) {
		if (!count(Out_ship_op_num->begin(), Out_ship_op_num->end(), bitset<8>(it->op_num))) {
			Out_ship_op_num->push_back(bitset<8>(it->op_num));
		}
	}
}


void display(vector <Ins> In_ship, vector <bitset<8>> Out_ship_op, vector <bitset<8>> Out_ship_op_num,map<string, bitset<8>> ys) {
	cout << endl;
	cout << "չʾ���棺" << endl;

	cout << "����:" << endl;
	cout << "   op  " << "     op_num" << endl;
	for (vector <Ins>::iterator it = In_ship.begin(); it != In_ship.end(); it++) {
		//cout.setf(ios::right);
		cout.width(5);
		cout << it->op << "       " << it->op_num << endl;
	}
	cout << endl;
	cout << "ӳ���ϵ:" << endl;
	int i = 0;
	cout << "   op  " << "    Binary code " << "    operands" << "    Binary code " << endl;
	for (vector <Ins>::iterator it = In_ship.begin(); it != In_ship.end(); it++,i++) {
		cout.width(5);
		cout << it->op << "        " << Out_ship_op[i] << "        " << it->op_num << "         " << Out_ship_op_num[i] << endl;
	}
}

void menu() {
	cout << "---------------��ӭʹ�û����---------------" << endl;
	//��ʼ��ӳ���ϵ��
	map<string, bitset<8>> ys;
	init_cast(&ys);
	vector<Ins> test;
	vector <bitset<8>> op, op_num;
	int choice;
	cout << "1. ��ʼ�����Ϣ     2.�����µĲ�����ͻ�����(op,oprands)     3.չʾ      4.�˳�" << endl;
	while (cin >> choice && choice!=4) {
		switch (choice) {
		case 1:
			//�����ʼ�����ָ�
			Initial_Ins(&test, ys);
			//��ʽ��(Сд)
			transform_op(ys, test, &op);
			transform_op_num(test, &op_num);
			format(&test);
			break;
		case 2:
			if (insert_op(&ys,&op)) {
				cout << "����ɹ�!" << endl;
			}
			break;
		case 3:
			display(test, op, op_num,ys);
			break;
		case 4:
			break;
		default:
			cout << "Error input!" << endl;
			break;
		}
		cout << "1. ��ʼ�����Ϣ     2.�����µĲ�����ͻ�����(op,oprands)     3.չʾ      4.�˳�" << endl;
	}

}

#endif // !CJH_H_

