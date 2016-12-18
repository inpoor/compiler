#ifndef _MAIN_H_
#define _MAIN_H_
#include<iostream>
#include"LexicalAnalysis.h"
#include<string>
#include<vector>
#include<stack>
#include<Windows.h>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include "stdlib.h"
#include "ctype.h"
#include<conio.h>
#include <string>
#include <sstream> 

using namespace std;


char *kt[20]={ "program", "var", "integer", "real", "char", "begin", "end", "if", "then", "else", "while", "do", "ifend", "whend", "const", "procedure", "call", "param", "ret", "endp"};		//kt�������
char *pt[19]={",", ":", ";", ":=", "*", "/", "+", "-", ".", "(", ")", "\'", ">", "<", "==", ">=", "<=", "!=", "=" };		//pt�������
//���������״̬ת������
int CSCLStatus[9][5] = { {}, { 2, 0, 0, 0, 0 }, { 2, 3, 5, 0, 8 }, { 4, 0, 0, 0, 0 }, { 4, 0, 5, 0, 8 }, { 7, 0, 0, 6, 0 }, { 7, 0, 0, 0, 0 }, { 7, 0, 0, 0, 8 }, { 0, 0, 0, 0, 0 } };

//TYP��i���Σ�rʵ�ͣ�ch�ַ��ͣ�b�����ͣ�a�����ͣ�s�ṹ��
enum TVAL_TYPE{ i, r, ch, b, a, s };	

//CAT��p���̣�c������t���ͣ�d������v������vn�����βΣ�vf��ֵ�β�
enum CAT_TYPE{ p, c, t, d, v, vn, vf };

//Token����
struct Token
{
string state;
int token,pointer;
};

//��Ԫʽ����
struct SiYuanShi_Type
{
	Token op;
	Token arg1;
	Token arg2;
	Token res;
};

//���ͱ�����
struct TAPEL_TYPE
{
	TVAL_TYPE  TVAL;
	int TPOINT;
};

//���ű��ܱ�����
struct SYNBL_TYPE
{
	string name;
	TVAL_TYPE TYP;
	CAT_TYPE CAT;
	int ADDR;
};

//������Ϣ������
struct PFINFL_TYPE
{
	int LEVEL;
	int	OFF;
	int FN;
	int ENTRY;
	int PARAM;
};

//������Ϣ������
struct AINFL_TYPE
{
	int LOW;
	int UP;
	int CTP;
	int CLEN;
};

//�ṹ��Ϣ������
struct RINFL_TYPE
{
	string ID;
	int OFF;
	int TP;
};

#endif