#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include "Main.h"

class SymbolTable
{
public:
	vector<SYNBL_TYPE>SYNBL;//符号表总表
	vector<TAPEL_TYPE>TAPEL;//类型表
	vector<AINFL_TYPE>AINFL;//数组表
	vector<RINFL_TYPE>RINFL;//结构表
	vector<PFINFL_TYPE>PFINFL;//函数信息表
	vector<double>CONSL;//常量表
	vector<int>LENL;//长度表
	
	//构造函数，初始化类型表已有的类型
	SymbolTable()
	{
		TAPEL_TYPE node;
		for (int i = 0; i < 6; i++)
			TAPEL_TYPE node={ (TVAL_TYPE)i, -1 };
			TAPEL.push_back(node);
	}

	//符号表总表表尾插入名为name、其他为空的表项，返回当前插入位置
	int InsertSYNBL(string name)
	{   SYNBL_TYPE node = { name, (TVAL_TYPE)-1, (CAT_TYPE)-1, -1 };
		SYNBL.push_back(node);
		return(SYNBL.size() - 1);
	}

	//符号表总表搜索名为name的表项，返回所在位置
	int SearchSYNBL(string name)
	{
		int i = 0;
		vector<SYNBL_TYPE>::iterator it;
		for (it = SYNBL.begin(); it != SYNBL.end(); it++, i++)
			if (name == (*it).name)
				return i;
		return -1;
	}

	//常数表插入x，返回插入位置
	int InsertCONSL(double x)
	{
		CONSL.push_back(x);
		return CONSL.size() - 1;
	}

	//常数表搜索x，返回所在位置
	int SearchCONSL(double x)
	{
		int i = 0;
		vector<double>::iterator it;
		for (it = CONSL.begin(); it != CONSL.end(); it++, i++)
			if ((*it) == x)
				return i;
		return -1;
	}

	//函数信息表插入level，off=3的表项
	int InsertPFINFL(int level)
	{   PFINFL_TYPE node ={level, 3, -1, -1, -1};
		PFINFL.push_back(node);
		return(PFINFL.size() - 1);
	}

	//输出所有的符号表
	void printFHB()
	{
		//将TYP、CAT转换为易懂的类型输出，而非数字表示的
		char *TYP[] = { "_", "i", "r", "ch", "b", "a", "s" };
		char *CAT[] = { "_", "p", "c", "t", "d", "v", "vn", "vf" };

		//符号总表输出
		vector<SYNBL_TYPE>::iterator it;
		cout << "SYNBL:" << endl << setw(8) << "NAME" << setw(8) << "TYP" << setw(8) << "CAT" << setw(8) << "ADDR" << endl;
		for (it = SYNBL.begin(); it != SYNBL.end(); it++)
			cout << setw(8) << (*it).name << setw(8) << TYP[(*it).TYP + 1] << setw(8) << CAT[(*it).CAT + 1] << setw(8) << (*it).ADDR << endl;

		//类型表输出
		vector<TAPEL_TYPE>::iterator it1;
		cout << "TAPEL:" << endl << setw(8) << "TVAL" << setw(8) << "TPOINT" << endl;
		for (it1 = TAPEL.begin(); it1 != TAPEL.end(); it1++)
			cout << setw(8) << TYP[(*it1).TVAL + 1] << setw(8) << (*it1).TPOINT << endl;
		
		//常量表输出
		vector<double>::iterator it2;
		cout << "CONSL:" << endl << setw(8) << "CONS" << endl;
		for (it2 = CONSL.begin(); it2 != CONSL.end(); it2++)
			cout << setw(8) << (*it2) << endl;

		//函数信息表输出
		vector<PFINFL_TYPE>::iterator it3;
		cout << "PFINFL:" << endl << setw(8) << "LEVEL" << setw(8) << "OFF" << setw(8) << "FN" << setw(8) << "ENTRY" << setw(8) << "PARAM" << endl;
		for (it3 = PFINFL.begin(); it3 != PFINFL.end(); it3++)
			cout << setw(8) << (*it3).LEVEL << setw(8) << (*it3).OFF << setw(8) << (*it3).FN << setw(8) << (*it3).ENTRY << setw(8) << (*it3).PARAM << endl;

	}
};


#endif
