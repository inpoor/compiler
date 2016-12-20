#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include "Main.h"

class SymbolTable
{
public:
	vector<SYNBL_TYPE>SYNBL;//���ű��ܱ�
	vector<TAPEL_TYPE>TAPEL;//���ͱ�
	vector<AINFL_TYPE>AINFL;//�����
	vector<RINFL_TYPE>RINFL;//�ṹ��
	vector<PFINFL_TYPE>PFINFL;//������Ϣ��
	vector<double>CONSL;//������
	vector<int>LENL;//���ȱ�
	
	//���캯������ʼ�����ͱ����е�����
	SymbolTable()
	{
		TAPEL_TYPE node;
		for (int i = 0; i < 6; i++)
			TAPEL_TYPE node={ (TVAL_TYPE)i, -1 };
			TAPEL.push_back(node);
	}

	//���ű��ܱ��β������Ϊname������Ϊ�յı�����ص�ǰ����λ��
	int InsertSYNBL(string name)
	{   SYNBL_TYPE node = { name, (TVAL_TYPE)-1, (CAT_TYPE)-1, -1 };
		SYNBL.push_back(node);
		return(SYNBL.size() - 1);
	}

	//���ű��ܱ�������Ϊname�ı����������λ��
	int SearchSYNBL(string name)
	{
		int i = 0;
		vector<SYNBL_TYPE>::iterator it;
		for (it = SYNBL.begin(); it != SYNBL.end(); it++, i++)
			if (name == (*it).name)
				return i;
		return -1;
	}

	//���������x�����ز���λ��
	int InsertCONSL(double x)
	{
		CONSL.push_back(x);
		return CONSL.size() - 1;
	}

	//����������x����������λ��
	int SearchCONSL(double x)
	{
		int i = 0;
		vector<double>::iterator it;
		for (it = CONSL.begin(); it != CONSL.end(); it++, i++)
			if ((*it) == x)
				return i;
		return -1;
	}

	//������Ϣ�����level��off=3�ı���
	int InsertPFINFL(int level)
	{   PFINFL_TYPE node ={level, 3, -1, -1, -1};
		PFINFL.push_back(node);
		return(PFINFL.size() - 1);
	}

	//������еķ��ű�
	void printFHB()
	{
		//��TYP��CATת��Ϊ�׶�������������������ֱ�ʾ��
		char *TYP[] = { "_", "i", "r", "ch", "b", "a", "s" };
		char *CAT[] = { "_", "p", "c", "t", "d", "v", "vn", "vf" };

		//�����ܱ����
		vector<SYNBL_TYPE>::iterator it;
		cout << "SYNBL:" << endl << setw(8) << "NAME" << setw(8) << "TYP" << setw(8) << "CAT" << setw(8) << "ADDR" << endl;
		for (it = SYNBL.begin(); it != SYNBL.end(); it++)
			cout << setw(8) << (*it).name << setw(8) << TYP[(*it).TYP + 1] << setw(8) << CAT[(*it).CAT + 1] << setw(8) << (*it).ADDR << endl;

		//���ͱ����
		vector<TAPEL_TYPE>::iterator it1;
		cout << "TAPEL:" << endl << setw(8) << "TVAL" << setw(8) << "TPOINT" << endl;
		for (it1 = TAPEL.begin(); it1 != TAPEL.end(); it1++)
			cout << setw(8) << TYP[(*it1).TVAL + 1] << setw(8) << (*it1).TPOINT << endl;
		
		//���������
		vector<double>::iterator it2;
		cout << "CONSL:" << endl << setw(8) << "CONS" << endl;
		for (it2 = CONSL.begin(); it2 != CONSL.end(); it2++)
			cout << setw(8) << (*it2) << endl;

		//������Ϣ�����
		vector<PFINFL_TYPE>::iterator it3;
		cout << "PFINFL:" << endl << setw(8) << "LEVEL" << setw(8) << "OFF" << setw(8) << "FN" << setw(8) << "ENTRY" << setw(8) << "PARAM" << endl;
		for (it3 = PFINFL.begin(); it3 != PFINFL.end(); it3++)
			cout << setw(8) << (*it3).LEVEL << setw(8) << (*it3).OFF << setw(8) << (*it3).FN << setw(8) << (*it3).ENTRY << setw(8) << (*it3).PARAM << endl;

	}
};


#endif
