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

enum ComIns		   //汇编指令集
{
	In, Out, Add, Sub, Mul, Div, Dup,
	Ld, St, Ldc, Jlt, Jle, Jgt, Jge, Jeq, Jne,
	Jmp, Halt, Invalid
};


typedef struct instruction {
	string op;
	int op_num;
}Ins;

//定义的数据结构说明
//vector <Ins> In_ship;	//存储汇编指令集 (输入)
//vector <bitset<8>> Out_ship_op; //存储op转换后的二进制
//vector <bitset<8>> Out_ship_op_num;	 //转换op_num转换后的二进
//map<string, int> ys;		  //映射关系

/*
*功能：汇编器
*参数：汇编指令
*返回值：机器指令
*作者：191172-曹吉浩
*/

void Initial_Ins(vector <Ins>* In_ship, map<string, bitset<8>> ys) {		//初始化汇编指令集并存储
	cout << "Please Enter your operation code and operands:(such as 'jmp 123' Tip:'# 3' to quit) " << endl;		   //大小写均可
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


void init_cast(map<string, bitset<8>>* ys) {			 //初始化初始op对应的二进制 映射关系(map)
	ys->insert({ pair<string,bitset<8>>("halt",bitset<8>(Halt)),pair<string,bitset<8>>("in",bitset<8>(In)),pair<string,bitset<8>>("out",bitset<8>(Out)),pair<string,bitset<8>>("add",bitset<8>(Add)) });
	ys->insert({ pair<string,bitset<8>>("sub",bitset<8>(Sub)),pair<string,bitset<8>>("mul",bitset<8>(Mul)),pair<string,bitset<8>>("div",bitset<8>(Div)),pair<string,bitset<8>>("dup",bitset<8>(Dup)) });
	ys->insert({ pair<string,bitset<8>>("ld",bitset<8>(Ld)),pair<string,bitset<8>>("st",bitset<8>(St)),pair<string,bitset<8>>("ldc",bitset<8>(Ldc)),pair<string,bitset<8>>("jlt",bitset<8>(Jlt)) });
	ys->insert({ pair<string,bitset<8>>("jle",bitset<8>(Jle)),pair<string,bitset<8>>("jgt",bitset<8>(Jgt)),pair<string,bitset<8>>("jge",bitset<8>(Jge)),pair<string,bitset<8>>("jeq",bitset<8>(Jeq)) });
	ys->insert({ pair<string,bitset<8>>("jne",bitset<8>(Jne)),pair<string,bitset<8>>("jmp",bitset<8>(Jmp)),pair<string,bitset<8>>("invalid",bitset<8>(-1)) });
}

//将汇编指令统一格式化为小写
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
	cout << "请输入操作码 对应的机器码（十进制）:" << endl;
	cin >> op >> prior;
	if (op.empty() || isdigit(prior)) {
		return false;
	}
	transform(op.begin(), op.end(), op.begin(), tolower);
	ys->insert(pair<string, bitset<8>>(op, bitset<8>(prior)));
	Out_ship_op->push_back(bitset<8>(prior));
	return true;
}

void transform_op(map<string, bitset<8>> ys, vector <Ins> In_ship, vector <bitset<8>>* Out_ship_op) {	 //完成汇编op到二进制转换并存储转换后的二进制
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
	cout << "展示界面：" << endl;

	cout << "输入:" << endl;
	cout << "   op  " << "     op_num" << endl;
	for (vector <Ins>::iterator it = In_ship.begin(); it != In_ship.end(); it++) {
		//cout.setf(ios::right);
		cout.width(5);
		cout << it->op << "       " << it->op_num << endl;
	}
	cout << endl;
	cout << "映射关系:" << endl;
	int i = 0;
	cout << "   op  " << "    Binary code " << "    operands" << "    Binary code " << endl;
	for (vector <Ins>::iterator it = In_ship.begin(); it != In_ship.end(); it++,i++) {
		cout.width(5);
		cout << it->op << "        " << Out_ship_op[i] << "        " << it->op_num << "         " << Out_ship_op_num[i] << endl;
	}
}

void menu() {
	cout << "---------------欢迎使用汇编器---------------" << endl;
	//初始化映射关系表
	map<string, bitset<8>> ys;
	init_cast(&ys);
	vector<Ins> test;
	vector <bitset<8>> op, op_num;
	int choice;
	cout << "1. 初始汇编信息     2.增加新的操作码和机器码(op,oprands)     3.展示      4.退出" << endl;
	while (cin >> choice && choice!=4) {
		switch (choice) {
		case 1:
			//输入初始化汇编指令集
			Initial_Ins(&test, ys);
			//格式化(小写)
			transform_op(ys, test, &op);
			transform_op_num(test, &op_num);
			format(&test);
			break;
		case 2:
			if (insert_op(&ys,&op)) {
				cout << "插入成功!" << endl;
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
		cout << "1. 初始汇编信息     2.增加新的操作码和机器码(op,oprands)     3.展示      4.退出" << endl;
	}

}

#endif // !CJH_H_

