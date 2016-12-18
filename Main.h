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


char *kt[20]={ "program", "var", "integer", "real", "char", "begin", "end", "if", "then", "else", "while", "do", "ifend", "whend", "const", "procedure", "call", "param", "ret", "endp"};		//kt表的内容
char *pt[19]={",", ":", ";", ":=", "*", "/", "+", "-", ".", "(", ")", "\'", ">", "<", "==", ">=", "<=", "!=", "=" };		//pt表的内容
//常数处理机状态转换矩阵
int CSCLStatus[9][5] = { {}, { 2, 0, 0, 0, 0 }, { 2, 3, 5, 0, 8 }, { 4, 0, 0, 0, 0 }, { 4, 0, 5, 0, 8 }, { 7, 0, 0, 6, 0 }, { 7, 0, 0, 0, 0 }, { 7, 0, 0, 0, 8 }, { 0, 0, 0, 0, 0 } };

//TYP：i整形，r实型，ch字符型，b布尔型，a数组型，s结构型
enum TVAL_TYPE{ i, r, ch, b, a, s };	

//CAT：p过程，c常量，t类型，d域名，v变量，vn换名形参，vf赋值形参
enum CAT_TYPE{ p, c, t, d, v, vn, vf };

//Token类型
struct Token
{
string state;
int token,pointer;
};

//四元式类型
struct SiYuanShi_Type
{
	Token op;
	Token arg1;
	Token arg2;
	Token res;
};

//类型表类型
struct TAPEL_TYPE
{
	TVAL_TYPE  TVAL;
	int TPOINT;
};

//符号表总表类型
struct SYNBL_TYPE
{
	string name;
	TVAL_TYPE TYP;
	CAT_TYPE CAT;
	int ADDR;
};

//函数信息表类型
struct PFINFL_TYPE
{
	int LEVEL;
	int	OFF;
	int FN;
	int ENTRY;
	int PARAM;
};

//数组信息表类型
struct AINFL_TYPE
{
	int LOW;
	int UP;
	int CTP;
	int CLEN;
};

//结构信息表类型
struct RINFL_TYPE
{
	string ID;
	int OFF;
	int TP;
};

#endif