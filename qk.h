#ifndef QK_H_
#define QK_H_
/*
*���ܣ�ģ��ʵ�ַ������
*����������ָ��
*����ֵ�����ָ��
*���ߣ�191172-Ǯ��
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>
using namespace std;
enum BinIns;

int IsError = 0;//ȫ�ֱ���IsError�жϻ���ָ���Ƿ�Ϸ�������������
// ������ָ��ṹ��
// ָ����+������
struct Instruction
{
	BinIns op;  // ָ����ֻռһ���ֽ�
	int    arg; // ��������ռ�ĸ��ֽ�
};

// ö�����͵Ķ�����ָ�
enum BinIns
{
	binHalt, binIn, binOut, binAdd, binSub, binMul, binDiv,
	binDup,
	binLd, binSt, binLdc, binJlt, binJle, binJgt, binJge, binJeq, binJne, binJmp,
	binInvalid
};
// ö������˵����
// enum���涨�����ö��������
// �������ڲ��Ǹ�ö�����Ϳ���ȡ��ֵ

// ��ʼ�����ָ�
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

// ��ʼ��
// ����ָ�����������
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

// ����������ָ����ָ���ӳ��
// ��ʼ��
void InitBinaryToAssemble(const vector<string>& assIns, map<BinIns, string>& binToIns)
{
	binToIns.clear();
	int count = 0;
	printf("����ָ��ͻ��ָ���Ӧ��ϵ(ʮ����):\n");
	for (auto i = 0; i != assIns.size(); ++i)
	{
		// assIns��BinIns��ָ�����һ��
		binToIns[static_cast<BinIns>(i)] = assIns[i];
		if (count >= 10) printf("%d <---> %s\n", count++, assIns[i].c_str());
		else printf("%d  <---> %s\n", count++, assIns[i].c_str());
	}
}

// ���������ָ��
void ReadBinary(vector<string>& bin)
{
	bin.clear();
	string line;
	while (getline(cin, line) && line!="#")
	{
		bin.push_back(line);
	}
}
// ��ʾ���ָ��
void DisplayIns(const vector<string>& bar)
{
	if (IsError != 0)
	{
		printf("����ָ��%d�Ƿ���ת������\n", IsError);//���ַǷ��������������Ͳ�����������ʱ����
		return;
	}
	int count = 0;
	for (auto i = 0; i != bar.size(); ++i)
	{
		printf("����ָ��%d->���ָ��:", ++count);
		cout << bar[i] << endl;
	}
	cout << endl;
}

bool IsNumber(string s, int& t)//�жϻ���ָ���Ƿ�Ϊ����
{
	stringstream sin(s);
	char p = NULL;
	if (!(sin >> t))
		return false;
	return true;
}
// ������Ķ�����ָ��ת��ΪInstruction��ʽ
void BinaryToAssemble(const vector<string>& bin, vector<string>& ass, const map<BinIns, string>& binToIns, map<BinIns, int>& insArgNum)
{
	ass.clear();
	string binLine;
	for (auto i = 0; i != bin.size(); ++i)
	{
		binLine += bin[i] + '\t';
	}
	istringstream sin(binLine);
	string strOp, strArg;	//strOpΪ�����룬strArgΪ������
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
		if (cit == binToIns.end())//opBin�޶�Ӧ���ָ��
		{
			// �Ƿ�������ָ���
			IsError = count + 1;
			printf("error:��Ч�Ļ���ָ��%d\n", count + 1);
			break;
		}
		op = cit->second;//��ȡ�����ָ��
		int argNum = insArgNum[cit->first];
		if (argNum)	//�����������Ϊ0�����ٶ�ȡһ���ַ���
		{
			sin >> strArg;
			arg = strArg;
			int temp;
			if (IsNumber(strArg, temp)) cout << "����ָ��" << ++count << "->������:" << bitset<8>(temp) << " " << bitset<8>(temp) << endl;
			else
			{
				IsError = count + 1;
				break;
			}
		}
		else
		{
			arg = "";
			printf("����ָ��%d->������:", ++count);
			cout << bitset<8>(atoi(strOp.c_str())) << " " << endl;;
		}
		assIns = op + '\t' + arg;
		ass.push_back(assIns);
	}
}
void Disassemble()	//�����
{
	IsError = 0;
	printf("<------------��ӭʹ��ģ�ⷴ�������----------->\n");
	/****��ʼ������ָ��ͻ��ָ�****/
	// ���ָ�
	vector<string> assIns;
	InitAssembleInstructions(assIns);
	// ������ָ��-����������
	map<BinIns, int> insArgNum;
	InitInstrctionArgNumber(insArgNum);
	// ���ָ������Ƶ�ӳ��
	map<BinIns, string> binToAss;
	InitBinaryToAssemble(assIns, binToAss);
	printf("ʹ��˵��:������ȷ����ָ��(ʮ����),һ��һָ��\n");
	printf("������ָ�,��'#'����\n");
	/****�������ָ�ת��****/
	vector<string> bin; // �������Ķ�����ָ��
	ReadBinary(bin);
	vector<string> ass; // ����ת����Ļ��ָ��
	BinaryToAssemble(bin, ass, binToAss, insArgNum);
	DisplayIns(ass);	//���ת�����
}

#endif // !QK_H_
