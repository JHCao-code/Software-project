#ifndef QK_H_
#define QK_H_
/*
*功能：模拟实现反汇编器
*参数：机器指令
*返回值：汇编指令
*作者：191172-钱凯
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>
using namespace std;
enum BinIns;

int IsError = 0;//全局变量IsError判断机器指令是否合法并锁定出错行
// 二进制指令结构体
// 指令码+操作数
struct Instruction
{
	BinIns op;  // 指令码只占一个字节
	int    arg; // 操作数，占四个字节
};

// 枚举类型的二进制指令集
enum BinIns
{
	binHalt, binIn, binOut, binAdd, binSub, binMul, binDiv,
	binDup,
	binLd, binSt, binLdc, binJlt, binJle, binJgt, binJge, binJeq, binJne, binJmp,
	binInvalid
};
// 枚举类型说明：
// enum后面定义的是枚举类型名
// 花括号内部是该枚举类型可以取的值

// 初始化汇编指令集
void InitAssembleInstructions(vector<string>& assIns)
{
	assIns.clear();
	assIns.push_back("HALT");
	assIns.push_back("IN");
	assIns.push_back("OUT");
	assIns.push_back("ADD");
	assIns.push_back("SUB");
	assIns.push_back("MUL");
	assIns.push_back("DIV");
	assIns.push_back("DUP");
	assIns.push_back("LD");
	assIns.push_back("ST");
	assIns.push_back("LDC");
	assIns.push_back("JLT");
	assIns.push_back("JLE");
	assIns.push_back("JGT");
	assIns.push_back("JGE");
	assIns.push_back("JEQ");
	assIns.push_back("JNE");
	assIns.push_back("JMP");
}

// 初始化
// 机器指令操作数个数
void InitInstrctionArgNumber(map<BinIns, int>& insArgNum)
{
	insArgNum.clear();
	insArgNum[binHalt] = 0;
	insArgNum[binIn] = 0;
	insArgNum[binOut] = 0;
	insArgNum[binAdd] = 0;
	insArgNum[binSub] = 0;
	insArgNum[binMul] = 0;
	insArgNum[binDiv] = 0;
	insArgNum[binDup] = 0;
	insArgNum[binLd] = 0;
	insArgNum[binSt] = 0;
	insArgNum[binLdc] = 1;
	insArgNum[binJlt] = 1;
	insArgNum[binJle] = 1;
	insArgNum[binJgt] = 1;
	insArgNum[binJge] = 1;
	insArgNum[binJeq] = 1;
	insArgNum[binJne] = 1;
	insArgNum[binJmp] = 1;
	insArgNum[binInvalid] = 0;
}

// 建立二进制指令到汇编指令的映射
// 初始化
void InitBinaryToAssemble(const vector<string>& assIns, map<BinIns, string>& binToIns)
{
	binToIns.clear();
	int count = 0;
	printf("机器指令和汇编指令对应关系(十进制):\n");
	for (auto i = 0; i != assIns.size(); ++i)
	{
		// assIns和BinIns的指令次序一致
		binToIns[static_cast<BinIns>(i)] = assIns[i];
		if (count >= 10) printf("%d <---> %s\n", count++, assIns[i].c_str());
		else printf("%d  <---> %s\n", count++, assIns[i].c_str());
	}
}

// 读入二进制指令
void ReadBinary(vector<string>& bin)
{
	bin.clear();
	string line;
	while (getline(cin, line) && line!="#")
	{
		bin.push_back(line);
	}
}
// 显示汇编指令
void DisplayIns(const vector<string>& bar)
{
	if (IsError != 0)
	{
		printf("机器指令%d非法，转换结束\n", IsError);//两种非法情况，当操作码和操作数非整数时报错
		return;
	}
	int count = 0;
	for (auto i = 0; i != bar.size(); ++i)
	{
		printf("机器指令%d->汇编指令:", ++count);
		cout << bar[i] << endl;
	}
	cout << endl;
}

bool IsNumber(string s, int& t)//判断机器指令是否为整数
{
	stringstream sin(s);
	char p = NULL;
	if (!(sin >> t))
		return false;
	return true;
}
// 将读入的二进制指令转换为Instruction形式
void BinaryToAssemble(const vector<string>& bin, vector<string>& ass, const map<BinIns, string>& binToIns, map<BinIns, int>& insArgNum)
{
	ass.clear();
	string binLine;
	for (auto i = 0; i != bin.size(); ++i)
	{
		binLine += bin[i] + '\t';
	}
	istringstream sin(binLine);
	string strOp, strArg;	//strOp为操作码，strArg为操作数
	string op;
	string arg;
	string assIns;
	BinIns opBin;
	int count = 0;
	while (sin >> strOp)
	{
		int temp;
		if (IsNumber(strOp, temp))
			opBin = static_cast<BinIns>(temp);
		else
		{
			IsError = count + 1;
			break;
		}
		auto cit = binToIns.find(opBin);
		if (cit == binToIns.end())//opBin无对应汇编指令
		{
			// 非法二进制指令报错
			IsError = count + 1;
			printf("error:无效的机器指令%d\n", count + 1);
			break;
		}
		op = cit->second;//提取出汇编指令
		int argNum = insArgNum[cit->first];
		if (argNum)	//如果操作数不为0，则再读取一个字符串
		{
			sin >> strArg;
			arg = strArg;
			int temp;
			if (IsNumber(strArg, temp)) cout << "机器指令" << ++count << "->二进制:" << bitset<8>(temp) << " " << bitset<8>(temp) << endl;
			else
			{
				IsError = count + 1;
				break;
			}
		}
		else
		{
			arg = "";
			printf("机器指令%d->二进制:", ++count);
			cout << bitset<8>(atoi(strOp.c_str())) << " " << endl;;
		}
		assIns = op + '\t' + arg;
		ass.push_back(assIns);
	}
}
void Disassemble()	//反汇编
{
	IsError = 0;
	printf("<------------欢迎使用模拟反汇编器！----------->\n");
	/****初始化机器指令和汇编指令集****/
	// 汇编指令集
	vector<string> assIns;
	InitAssembleInstructions(assIns);
	// 二进制指令-操作数个数
	map<BinIns, int> insArgNum;
	InitInstrctionArgNumber(insArgNum);
	// 汇编指令到二进制的映射
	map<BinIns, string> binToAss;
	InitBinaryToAssemble(assIns, binToAss);
	printf("使用说明:输入正确机器指令(十进制),一行一指令\n");
	printf("请输入指令集,以'#'结束\n");
	/****读入机器指令并转换****/
	vector<string> bin; // 保存读入的二进制指令
	ReadBinary(bin);
	vector<string> ass; // 保存转换后的汇编指令
	BinaryToAssemble(bin, ass, binToAss, insArgNum);
	DisplayIns(ass);	//输出转换结果
}

#endif // !QK_H_
