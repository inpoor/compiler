#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<Windows.h>
#include <cmath>
#include <iomanip>
using namespace std;
#define FUNCTION_NUM 10 //最大函数数目
#define KEYWORD_NUM 39 //关键字表长度

//关键字表
char *Key[KEYWORD_NUM] = { "program", "var", "integer", "real", "char", "begin", "end", "if", "then", "else", "while", "do", "ifend", "whend", "const", "procedure", "call", "param", "ret", "endp",
",", ":", ";", ":=", "*", "/", "+", "-", ".", "(", ")", "\'", ">", "<", "==", ">=", "<=", "!=", "=" };

//常数处理机状态转换矩阵
int CSCLStatus[9][5] = { {}, { 2, 0, 0, 0, 0 }, { 2, 3, 5, 0, 8 }, { 4, 0, 0, 0, 0 }, { 4, 0, 5, 0, 8 }, { 7, 0, 0, 6, 0 }, { 7, 0, 0, 0, 0 }, { 7, 0, 0, 0, 8 }, { 0, 0, 0, 0, 0 } };

//TYP：i整形，r实型，ch字符型，b布尔型，a数组型，s结构型
enum TVAL_TYPE{ i, r, ch, b, a, s };	

//CAT：p过程，c常量，t类型，d域名，v变量，vn换名形参，vf赋值形参
enum CAT_TYPE{ p, c, t, d, v, vn, vf };

//Token类型
struct Token
{
	int type, pointer;

	int belongFHB;
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
	TVAL_TYPE TVAL;
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

//符号表类
class FuHaoBiao
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
	FuHaoBiao()
	{
		for (int i = 0; i < 6; i++)
			TAPEL.push_back({ (TVAL_TYPE)i, -1 });
	}

	//符号表总表表尾插入名为name、其他为空的表项，返回当前插入位置
	int InsertSYNBL(string name)
	{
		SYNBL.push_back({ name, (TVAL_TYPE)-1, (CAT_TYPE)-1, -1 });
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
	{
		PFINFL.push_back({ level, 3, -1, -1, -1 });
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

//常数处理机类
class ChangShuChuLi
{
public:
	int Status[9][5];//状态转移矩阵
	int N, p, m, e;//N：尾数，p：指数，m：小数位数，e：指数+为1，-为-1
	double num;//最终转换成的double型常数

	//对状态转移矩阵进行初始化
	ChangShuChuLi()
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 5; j++)
				Status[i][j] = CSCLStatus[i][j];
	}

	//常数处理的主函数
	double StrToDouble(char *Str)
	{
		N = 0; p = 0; m = 0; e = 1; num = 0;//初始化
		int s = 1;//初始状态
		char ch;//当前字符
		ch = Str[0];//从第0个字符开始
		int Pointer = 0;//指向字符的指针
		while (s != 8 && s != 0)
		{
			Act(s, ch);//当前状态动作
			ch = Str[Pointer++];//读下一个字符
			s = move(s, ch);//状态转移
		}

		//计算出常数值
		if (s == 8)
		{
			Act(s, ch);
			return num;
		}
		else
		{
			cout << "error!" << endl;
			system("pause");
		}

	}

	//状态转移函数
	int move(int t, char c)
	{
		switch (c)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return Status[t][0];
		case '.':
			return Status[t][1];
		case 'e':
		case 'E':
			return Status[t][2];
		case '+':
		case '-':
			return Status[t][3];
		case 0:
			return Status[t][4];
		}
		return 0;
	}

	//当前状态动作
	void Act(int t, char c)
	{
		switch (t)
		{
		case 1:
			p = 0; m = 0; num = 0;

			e = 1;
			break;
		case 2:
			N = 10 * N + c - '0';
			break;
		case 4:
			N = 10 * N + c - '0';
			m++;
			break;
		case 6:
			if (c == '-')e = -1;
			break;
		case 7:
			p = 10 * p + c - '0';
			break;
		case 8:
			num = N*pow(10, e*p - m);
			break;
		}
	}
};

//词法扫描器类
class SaoMiaoQi
{
public:
	char *Keyword[KEYWORD_NUM];//关键字表
	FuHaoBiao FHB[1 + FUNCTION_NUM];//符号表，每个函数对应一个符号表

	ChangShuChuLi CSCL;//常数处理机对象

	Token token[1000];//token序列
	int tokenlen = 0;//当前token序列长度

	char FileName[20];//要扫描的文件

	char cache[20];//字符串缓存
	int cachelen = 0;//当前缓存长度

	int state = 1;//自动机初始状态

	//函数相关
	int proc_type;//关键字procedure在关键字表中的位置
	int endp_type;//关键字endp在关键字表中的位置
	int level = 0;//当前level
	stack<int>lastFHB;//栈保存刚处理过的符号表号
	int curFHB = 0;//当前处理的符号表
	int totalFHB = 0;//总共已占用的符号表

	//文件名初始化，关键字表初始化，常用的procedure和endp的位置的初始化
	SaoMiaoQi()
	{
		strcpy_s(FileName, "..\\main.txt");
		for (int i = 0; i < KEYWORD_NUM; i++)
			Keyword[i] = Key[i];
		proc_type = SearchKeyword("procedure");
		endp_type = SearchKeyword("endp");

	}

	//是否字母
	int isletter(char ch)
	{
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
			return 1;
		else
			return 0;
	}

	//是否数字
	int isdigit(char ch)
	{
		if (ch >= '0'&&ch <= '9')
			return 1;
		else
			return 0;
	}

	//查关键字表
	int SearchKeyword(char *str)
	{
		for (int i = 0; i < KEYWORD_NUM; i++)
			if (!strcmp(Keyword[i], str))
				return i + 4;
		return -1;
	}

	//增加一个token
	int AddToken(int type, int pointer)
	{
		token[tokenlen].belongFHB = curFHB;
		token[tokenlen].type = type;
		token[tokenlen].pointer = pointer;
		tokenlen++;

		//清空缓存的字符串
		memset(cache, 0, sizeof(cache));
		cachelen = 0; 
		
		//自动机状态恢复0
		state = 1;

		return 1;
	}

	//文件指针回退，缓存字符串回退一位
	void fpback(FILE *fp)
	{
		fseek(fp, -1, SEEK_CUR);
		cache[cachelen - 1] = '\0';
		cachelen--;
	}

	//输出token序列
	void printToken()
	{
		cout << "Token:1-标识符，2-常数，3-字符，其他-关键字" << endl;
		for (int i = 0; i < tokenlen; i++)
			cout << setw(2) << "(" << setw(2) << token[i].type << setw(2) << "," << setw(2) << token[i].pointer << setw(2) << ")" << setw(2);
		cout << endl;
	}

	//扫描器自动机的实现
	void Scan()
	{
		FILE *fp;

		char ch;//当前字符ch

		if ((fp = fopen(FileName, "r")) == NULL)
		{
			cout << "file not exists!" << endl;
			return;
		}

		//逐个字符判断
		while (!feof(fp))
		{
			ch = fgetc(fp);//获取当前字符

			//略去空格、换行、水平制表符
			if ((ch == ' ' || ch == '\n' || ch == '\t') && state == 1)
				continue;

			cache[cachelen++] = ch;//当前字符加入缓存

			switch (state)
			{
			case 1:if (isletter(ch)){ state = 2; break; }
				   if (isdigit(ch)){ state = 3; break; }
				   if (ch == ':'){ state = 6; break; }
				   if (ch == ';'){ state = 8; AddToken(SearchKeyword(cache), -1); break; }
				   if (ch == ','){ state = 9; AddToken(SearchKeyword(cache), -1); break; }
				   if (ch == '\''){ state = 10; break; }
				   if (ch == '+'){ state = 13; AddToken(SearchKeyword(cache), -1); break; }
				   if (ch == '-'){ state = 14; AddToken(SearchKeyword(cache), -1); break; }
				   if (ch == '*'){ state = 15; AddToken(SearchKeyword(cache), -1); break; }
				   if (ch == '/'){ state = 16; AddToken(SearchKeyword(cache), -1); break; }
				   if (ch == '('){ state = 17; AddToken(SearchKeyword(cache), -1); break; }
				   if (ch == ')'){ state = 18; AddToken(SearchKeyword(cache), -1); break; }
				   if (ch == '>'){ state = 19; break; }
				   if (ch == '<'){ state = 21; break; }
				   if (ch == '='){ state = 23; break; }
				   if (ch == '!'){ state = 25; break; }
				   break;
			case 2:if (isletter(ch) || isdigit(ch)){ break; }
				   {
					   fpback(fp);//回退，去除不是数字也不是字母的单词的后继符
					   int type;
					   if ((type = SearchKeyword(cache)) != -1)//是关键字的情况
					   {
						   AddToken(type, -1);

						   //若是procedure关键字，当前处理的符号表序号压栈，处理新的符号表
						   if (type == proc_type)
						   {
							   level++;
							   lastFHB.push(curFHB);
							   totalFHB++;
							   curFHB = totalFHB;
						   }

						   //是endp关键字，当前符号表处理完毕，处理之前的符号表
						   if (type == endp_type&&level != 0)
						   {
							   level--;
							   curFHB = lastFHB.top();
							   lastFHB.pop();
						   }
					   }
					   else//不是关键字则增加为标识符
					   {
						   int pointer;
						   if ((pointer = FHB[curFHB].SearchSYNBL(cache)) != -1)//标识符已存在
							   AddToken(1, pointer);
						   else//标识符是新的则插入符号表末尾
							   AddToken(1, FHB[curFHB].InsertSYNBL(cache));
					   }
				   }
				   break;
			case 3:if (ch == '.'){ state = 4; break; }
				   if (isdigit(ch)) break;
				   {
					   fpback(fp);//回退，去除常数的后继符

					   ///*cache交由常数处理机处理*/double d = strtod(cache, NULL);
					   double d = CSCL.StrToDouble(cache);

					   int pointer;
					   if ((pointer = FHB[curFHB].SearchCONSL(d)) != -1)//常数已在常量表中
						   AddToken(2, pointer);
					   else//常数是新的则插入常量表
					   {
						   AddToken(2, FHB[curFHB].InsertCONSL(d));
					   }
				   }

				   break;
			case 4:if (isdigit(ch)){ state = 5; break; };
				   break;
			case 5:if (isdigit(ch)){ break; }
				   {
					   fpback(fp);//回退，去除常数的后继符

					   ///*cache交由常数处理机处理*/double d = strtod(cache, NULL);
					   double d = CSCL.StrToDouble(cache);

					   int pointer;
					   if ((pointer = FHB[curFHB].SearchCONSL(d)) != -1)//常数已在常量表中
						   AddToken(2, pointer);
					   else//常数是新的则插入常量表
						   AddToken(2, FHB[curFHB].InsertCONSL(d));
				   }
				   break;
			case 10:state = 11; break;
			case 11:if (ch == '\''){ AddToken(3, FHB[curFHB].InsertCONSL(cache[1])); }
					break;
			case 6:
			case 19:
			case 21:
			case 23:if (ch == '='){ AddToken(SearchKeyword(cache), -1); break; }//>=,<=,==,!=的token的添加
					{//单个>,<,=号的token添加
						fpback(fp);
						AddToken(SearchKeyword(cache), -1);
					}
					break;
			case 25:if (ch == '='){ AddToken(SearchKeyword(cache), -1); break; }

			}
		}

		fclose(fp);
	}
};

//语法分析类
class YuFaFenXi
{
public:
	SaoMiaoQi SMQ;//词法扫描器
	int pos = 0;//当前是第pos个token，即token读到哪里了
	Token w, e;//临时存储当前读出的token

	vector<SiYuanShi_Type>SiYuanShi;//四元式存储结构
	stack<Token>SEM;//对象栈
	stack<Token>SYN;//算符栈

	int addr = 0;//符号表ADDR计算
	stack<int>addrstk;//处理新的符号表时，需要将上一个符号表addr入栈保存

	int bzfNUM;//变量声明语句中，统计变量数目
	int xingcanNUM = 0;//形参声明语句中，统计形参数目
	int order = 0;//中间变量序号，生成的中间变量序号从0开始递增

	int level = 0;//当前函数level
	stack<int>lastFHB;//栈保存刚处理过的符号表序号
	int curFHB = 0;//当前处理的符号表
	int totalFHB = 0;//总共的符号表数

	//初始化需要调用扫描器扫描单词
	YuFaFenXi()
	{
		SMQ.Scan();
		SMQ.printToken();
	}

	//按序输出所有的符号表
	void printFHB()
	{
		for (int i = 0; i <= totalFHB; i++)
		{
			cout << "符号表" << i << ":" << endl;
			SMQ.FHB[i].printFHB();
			cout << endl;
		}
	}

	//产生算数表达式四元式
	int Produce_EXP()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };

		//简单的中间变量类型提升
		int TYPUP[6][6] = { i, r, i, -1, -1, -1,
							r, r, r, -1, -1, -1,
							i, r, i, -1, -1, -1,
							-1, -1, -1, -1, -1, -1,
							-1, -1, -1, -1, -1, -1,
							-1, -1, -1, -1, -1, -1, };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;
		//ARG1
		e = SEM.top(); SEM.pop();
		tmp.arg2.type = e.type;
		tmp.arg2.pointer = e.pointer;
		tmp.arg2.belongFHB = e.belongFHB;
		//ARG2
		e = SEM.top(); SEM.pop();
		tmp.arg1.type = e.type;
		tmp.arg1.pointer = e.pointer;
		tmp.arg1.belongFHB = e.belongFHB;
		//RES
		tmp.res.type = tmp.arg1.type;
		{
			//中间变量名的产生
			char name[6] = "_t", num[4];
			_itoa(order++, num, 10);
			for (int k = 0; k < 4; k++)
			{
				name[k + 2] = num[k];
			}
			tmp.res.type = 1;
			tmp.res.pointer = SMQ.FHB[curFHB].InsertSYNBL(name);//中间变量插入符号表
			tmp.res.belongFHB = curFHB;

			//判断ARG1和ARG2决定中间变量的类型
			if ((*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP != -1 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP != -1)
				(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.res.pointer)).TYP = (TVAL_TYPE)TYPUP[(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP][(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP];
			if ((*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP != -1 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP >= 0 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP <= 2)
				(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.res.pointer)).TYP = r;
			if ((*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP != -1 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP >= 0 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP <= 2)
				(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.res.pointer)).TYP = r;

			//填符号表
			TianSYNBL((TVAL_TYPE)-2, v, addr, tmp.res.pointer);

			//addr增加
			if ((*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.res.pointer)).TYP == i)
				addr += 4;
			if ((*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.res.pointer)).TYP == r)
				addr += 8;
			if ((*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.res.pointer)).TYP == ch)
				addr += 1;

			SEM.push(tmp.res);
		}

		SiYuanShi.push_back(tmp);
		return 1;
	}

	//产生条件语句中布尔表达式的四元式
	int Produce_BoolEXP()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;
		//ARG1
		e = SEM.top(); SEM.pop();
		tmp.arg2.type = e.type;
		tmp.arg2.pointer = e.pointer;
		tmp.arg2.belongFHB = e.belongFHB;
		//ARG2
		e = SEM.top(); SEM.pop();
		tmp.arg1.type = e.type;
		tmp.arg1.pointer = e.pointer;
		tmp.arg1.belongFHB = e.belongFHB;
		//RES
		tmp.res.type = tmp.arg1.type;
		{
			//布尔表达式中间变量产生
			char name[6] = "_b", i[4];
			_itoa(order++, i, 10);
			for (int k = 0; k < 4; k++)
			{
				name[k + 2] = i[k];
			}
			tmp.res.type = 1;
			tmp.res.pointer = SMQ.FHB[curFHB].InsertSYNBL(name);//填入符号表
			tmp.res.belongFHB = curFHB;

			TianSYNBL(b, v, addr, tmp.res.pointer); 
			addr += 1;//假设布尔表达式结果占1字节

			SEM.push(tmp.res);
		}

		SiYuanShi.push_back(tmp);
		return 1;
	}

	//程序Program四元式产生
	int Produce_FunBound()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;
		//ARG1
		e = SEM.top(); SEM.pop();
		tmp.arg1.type = e.type;
		tmp.arg1.pointer = e.pointer;
		tmp.arg1.belongFHB = e.belongFHB;

		SiYuanShi.push_back(tmp);
		return 1;
	}

	//过程procedure四元式产生
	int Produce_ProcBound()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;
		//ARG1
		e = SEM.top(); SEM.pop();
		tmp.arg1.type = e.type;
		tmp.arg1.pointer = e.pointer;
		tmp.arg1.belongFHB = e.belongFHB;

		//入口填写四元式的位置
		(*SMQ.FHB[curFHB].PFINFL.begin()).ENTRY = SiYuanShi.size();

		SiYuanShi.push_back(tmp);
		return 1;
	}

	//赋值表达式四元式产生
	int Produce_Asign()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;
		//ARG1
		e = SEM.top(); SEM.pop();
		tmp.arg1.type = e.type;
		tmp.arg1.pointer = e.pointer;
		tmp.arg1.belongFHB = e.belongFHB;
		//ARG2
		e = SEM.top(); SEM.pop();
		tmp.res.type = e.type;
		tmp.res.pointer = e.pointer;
		tmp.res.belongFHB = e.belongFHB;

		SiYuanShi.push_back(tmp);

		/*if (tmp.arg1.type == 1)//填V的符号表ADDR项
		{
		TianSYNBL((TVAL_TYPE)-2, (CAT_TYPE)v, -2, tmp.res.pointer);
		return 1;
		}

		if (tmp.arg1.type == 2)
		{
		TianSYNBL((TVAL_TYPE)-2, (CAT_TYPE)v, -2, tmp.res.pointer);
		return 1;
		}
		if (tmp.arg1.type == 3)
		{
		TianSYNBL((TVAL_TYPE)-2, (CAT_TYPE)c, -2, tmp.res.pointer);
		return 1;
		}*/

		return 1;
	}

	//条件语句Then四元式产生
	int Produce_Then()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;
		//ARG1
		e = SEM.top(); SEM.pop();
		tmp.arg1.type = e.type;
		tmp.arg1.pointer = e.pointer;
		tmp.arg1.belongFHB = e.belongFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//返回这个四元式的位置用于地址回填
	}

	//条件语句Else四元式的产生
	int Produce_Else()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//返回这个四元式的位置用于地址回填
	}

	//条件语句Ifend四元式的产生
	int Produce_IfEnd()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		tmp.op.type = SMQ.SearchKeyword("ifend");
		tmp.op.belongFHB = curFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//返回这个四元式的位置用于地址回填
	}

	//循环语句While四元式的产生
	int Produce_While()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//返回这个四元式的位置用于地址回填
	}

	//循环语句Do四元式的产生
	int Produce_Do()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;
		//ARG1
		e = SEM.top(); SEM.pop();
		tmp.arg1.type = e.type;
		tmp.arg1.pointer = e.pointer;
		tmp.arg1.belongFHB = e.belongFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//返回这个四元式的位置用于地址回填
	}

	//循环语句WhEnd四元式的产生
	int Produce_WhEnd()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		tmp.op.type = SMQ.SearchKeyword("whend");
		tmp.op.belongFHB = curFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//返回这个四元式的位置用于地址回填
	}

	//过程调用语句CALL四元式
	int Produce_Call()
	{
		int i;//查询被调用过程名所在的符号表号
		for (i = 0; i <= totalFHB; i++)
			if ((*SMQ.FHB[i].SYNBL.begin()).name == (*(SMQ.FHB[w.belongFHB].SYNBL.begin() + w.pointer)).name)
				break;

		if (i == totalFHB+1)//找不到过程名则报错
		{
			system("cls"); cout << "调用函数不存在！" << endl; system("pause"); exit(0);
			return -1;
		}

		//被调过程名符号表填写
		(*(SMQ.FHB[w.belongFHB].SYNBL.begin() + w.pointer)).CAT = p;

		//Call四元式生成
		SiYuanShi_Type tmp = { SYN.top(), { 1, 0, i }, { 2, SMQ.FHB[i].InsertCONSL((*SMQ.FHB[i].PFINFL.begin()).ENTRY), i }, { -1, -1 } };
		SiYuanShi.push_back(tmp);
		SYN.pop();

		return i;//返回所在符号表号
	}

	//过程调用单个参数四元式生成
	int Produce_Param()
	{
		//算术表达式作为参数
		if (SuanShuBiaoDaShi() > 0)
		{
			SiYuanShi_Type tmp = { { SMQ.SearchKeyword("param"), -1, curFHB }, SEM.top(), { -1, -1 }, { -1, -1 } };
			SiYuanShi.push_back(tmp);
			SEM.pop();
			return 1;
		}
		else
		{
			system("cls"); cout << "参数类型错误！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//过程调用返回四元式产生
	int Produce_Ret()
	{
		SiYuanShi_Type tmp = { { SMQ.SearchKeyword("ret"), -1, curFHB }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		SiYuanShi.push_back(tmp);
		return 1;
	}

	//输出四元式
	void PrintSiYuanShi()
	{
		cout << "四元式：" << endl;
		int i = 0;
		vector<SiYuanShi_Type>::iterator it;
		for (it = SiYuanShi.begin(); it != SiYuanShi.end(); it++)
		{
			//输出序号
			cout << setw(2) << i++ << '.';

			//输出OP
			if ((*it).op.type != -1)
				cout << '(' << Key[(*it).op.type - 4] << ',';
			else
				cout << "( ,";

			//输出ARG1
			if ((*it).arg1.type == 1)
				cout << (*(SMQ.FHB[(*it).arg1.belongFHB].SYNBL.begin() + (*it).arg1.pointer)).name << ',';
			else
				if ((*it).arg1.type == 2)
					cout << (*(SMQ.FHB[(*it).arg1.belongFHB].CONSL.begin() + (*it).arg1.pointer)) << ',';
				else
					if ((*it).arg1.type == 3)
						cout << (char)(*(SMQ.FHB[(*it).arg1.belongFHB].CONSL.begin() + (*it).arg1.pointer)) << ',';
					else
						cout << ' ' << ',';

			//输出ARG2
			if ((*it).arg2.type == 1)
				cout << (*(SMQ.FHB[(*it).arg2.belongFHB].SYNBL.begin() + (*it).arg2.pointer)).name << ',';
			else
				if ((*it).arg2.type == 2)
					cout << (*(SMQ.FHB[(*it).arg2.belongFHB].CONSL.begin() + (*it).arg2.pointer)) << ',';
				else
					if ((*it).arg2.type == 3)
						cout << (char)(*(SMQ.FHB[(*it).arg2.belongFHB].CONSL.begin() + (*it).arg2.pointer)) << ',';
					else
						cout << ' ' << ',';

			//输出RES
			if ((*it).res.type != -1)
			{
				if ((*it).res.type == 1)
					cout << (*(SMQ.FHB[(*it).res.belongFHB].SYNBL.begin() + (*it).res.pointer)).name << ')';
				else
					if ((*it).res.type == 2)
						cout << (*(SMQ.FHB[(*it).res.belongFHB].CONSL.begin() + (*it).res.pointer)) << ')';
					else
						if ((*it).res.type == 3)
							cout << (char)(*(SMQ.FHB[(*it).res.belongFHB].CONSL.begin() + (*it).res.pointer)) << ')';
						else
							cout << ' ' << ')';
			}
			else
				cout << ' ' << ')';
			cout << endl;
		}
	}

	//填符号表总表，某一项不做修改时，参数为-2
	void TianSYNBL(TVAL_TYPE TYP, CAT_TYPE CAT, int ADDR, int pointer)
	{
		if (TYP != -2)(*(SMQ.FHB[curFHB].SYNBL.begin() + pointer)).TYP = TYP;
		if (CAT != -2)(*(SMQ.FHB[curFHB].SYNBL.begin() + pointer)).CAT = CAT;
		if (ADDR != -2)(*(SMQ.FHB[curFHB].SYNBL.begin() + pointer)).ADDR = ADDR;
	}

	//填函数信息表，某一项不做修改时，参数为-2
	void TianPFINFL(int LEVEL, int	OFF, int FN, int ENTRY, int PARAM, int pointer)
	{
		if (LEVEL != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).LEVEL = LEVEL;
		if (OFF != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).OFF = OFF;
		if (FN != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).FN = FN;
		if (ENTRY != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).ENTRY = ENTRY;
		if (PARAM != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).PARAM = PARAM;
	}

	//读一个token到w
	int read(Token &w)
	{
		if (pos < SMQ.tokenlen)
		{
			w = SMQ.token[pos++];
			return 1;
		}
		else
			return -1;
	}

	//语法分析入口
	int Analyze()
	{
		read(w);
		if (ChengXu() > 0)
			return 1;
		else
			return -1;
	}

	//递归下降子程序——程序
	int ChengXu()
	{
		if (w.type == SMQ.SearchKeyword("program"))
		{
			SYN.push(w);//语义0
			read(w);
			if (w.type == 1)
			{
				SEM.push(w); SEM.push(w); TianSYNBL((TVAL_TYPE)-1, p, -1, w.pointer); Produce_FunBound();//语义1
				read(w);
				if (FenChengXu() > 0)
					return 1;
				else
					return -1;
			}
			else
			{
				system("cls"); cout << "程序名不合法！" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
		{
			system("cls"); cout << "找不到程序的program入口！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//递归下降子程序——分程序
	int FenChengXu()
	{
		if (BianLiangShuoMing() > 0)
		{
			if (ChangLiangShuoMing() > 0)
			{
				while (GuoCheng() > 0);

				if (FuHeYuJu() > 0)
					return 1;
				else
					return -1;
			}
		}
		else
			return -1;
	}

	//递归下降子程序——过程
	int GuoCheng()
	{
		if (w.type == SMQ.proc_type)
		{
			addrstk.push(addr);
			addr = 0;
			level++;
			lastFHB.push(curFHB);
			totalFHB++;
			curFHB = totalFHB;
			SYN.push(w);//语义0
			read(w);
			if (w.type == 1)
			{
				int pfinflen = SMQ.FHB[curFHB].InsertPFINFL(level);//填函数信息表level
				TianSYNBL((TVAL_TYPE)-1, p, -1, w.pointer);
				SEM.push(w); SEM.push(w);//语义2
				Produce_ProcBound();

				read(w);
				if (w.type == SMQ.SearchKeyword("("))
				{
					read(w);
					if (XingCanLieBiao() > 0)
					{
						TianPFINFL(-2, -2, xingcanNUM, -2, 1, pfinflen);//填函数信息FN和PARAM
						xingcanNUM = 0;
						if (w.type == SMQ.SearchKeyword(")"))
						{
							read(w);
							if (BianLiangShuoMing() > 0)
							{
								while (GuoCheng() > 0);

								if (FuHeYuJu() > 0)
								{
									//Token endtmp = { SMQ.SearchKeyword("end"), -1 };
									//SYN.push(endtmp);//语义0
									if (w.type == SMQ.SearchKeyword("endp"))
									{
										SYN.push(w);
										read(w);
									}
									else
									{
										system("cls"); cout << "过程应以endp结尾！" << endl; system("pause"); exit(0);
										return -1;
									}
									Produce_FunBound();//语义4
									addr = addrstk.top();
									addrstk.pop();
									level--;
									curFHB = lastFHB.top();
									lastFHB.pop();
									return 1;
								}
								else
									return -1;

							}
							else
								return -1;
						}
						else
						{
							system("cls"); cout << "函数声明缺少右括号！" << endl; system("pause"); exit(0);
							return -1;
						}
					}
					else
						return -1;
				}
				else
				{
					system("cls"); cout << "函数声明缺少左括号！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				system("cls"); cout << "函数名不合法！" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
			return -1;
	}

	//递归下降子程序——形参列表
	int XingCanLieBiao()
	{
		if (XingCanShuoMing() > 0)
		{
			//xingcanNUM++;
			if (w.type == SMQ.SearchKeyword(";"))
			{
				read(w);
				if (XingCanLieBiao() > 0)
					return 1;
				else
					return -1;
			}
			else
				return 1;
		}
		else
			return -1;
		//return 1;
	}

	//递归下降子程序——形参说明
	int XingCanShuoMing()
	{
		if (w.type == SMQ.SearchKeyword("var"))
		{
			xingcanNUM++;
			read(w);
			if (w.type == 1)
			{
				SEM.push(w);//语义2
				read(w);
				if (w.type == SMQ.SearchKeyword(":"))
				{
					read(w);
					int type;
					if ((type = LeiXing()) != -1)
					{
						w = SEM.top(); SEM.pop();//语义15
						TianSYNBL((TVAL_TYPE)type, vn, addr, w.pointer);
						addr += 2;//换名形参为+2
						/*if (type == i)
							addr += 4;
						if (type == r)
							addr += 8;
						if (type == ch)
							addr += 1;*/
						read(w);
						return 1;
					}
					else
					{
						system("cls"); cout << "形参类型未知！" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					system("cls"); cout << "形参应当用:声明类型！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				//system("cls"); cout << "换名形参名不合法！" << endl; system("pause"); exit(0);
				//return -1;
				return 1;
			}
		}
		else
		{
			if (w.type == 1)
			{
				xingcanNUM++;
				SEM.push(w);//语义2
				read(w);
				if (w.type == SMQ.SearchKeyword(":"))
				{
					read(w);
					TVAL_TYPE type;
					if ((type = LeiXing()) != -1)
					{
						w = SEM.top(); SEM.pop();//语义5
						TianSYNBL(type, vf, addr, w.pointer);
						if (type == i)
							addr += 4;
						if (type == r)
							addr += 8;
						if (type == ch)
							addr += 1;
						read(w);
						return 1;
					}
					else
					{
						system("cls"); cout << "形参类型未知！" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					system("cls"); cout << "形参应当用:声明类型！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				//system("cls"); cout << "赋值形参名不合法！" << endl; system("pause"); exit(0);
				//return -1;
				return 1;
			}
		}
	}

	//递归下降子程序——常量说明
	int ChangLiangShuoMing()
	{
		if (w.type == SMQ.SearchKeyword("const"))
		{
			read(w);
			if (w.type == 1)
			{
				SEM.push(w);//语义2
				read(w);
				if (w.type == SMQ.SearchKeyword("="))
				{
					read(w);
					if (w.type == 2)
					{
						e = SEM.top(); SEM.pop();//语义14
						TianSYNBL(r, c, w.pointer, e.pointer);
						read(w);

						if (w.type == SMQ.SearchKeyword(";"))
						{
							read(w);
							if (ChangLiangShuoMing() > 0)
								return 1;
							else
								return -1;
						}
						else
							return 1;
					}
					else
					{
						system("cls"); cout << "常量应当为数字！" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					system("cls"); cout << "常量声明应用=号！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				system("cls"); cout << "常量名不合法！" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
			return 1;
	}

	//递归下降子程序——变量说明
	int BianLiangShuoMing()
	{
		if (w.type == SMQ.SearchKeyword("var"))
		{
			read(w);
			bzfNUM = 0;//变量数清零
			if ((BiaoZhiFuBiao()) > 0)
			{
				if (w.type == SMQ.SearchKeyword(":"))
				{
					read(w);
					TVAL_TYPE type;
					if ((type = LeiXing()) != -1)
					{
						for (int j = 0; j < bzfNUM; j++)
						{
							w = SEM.top(); SEM.pop();
							TianSYNBL(type, v, addr, w.pointer);
							if (type == i)
								addr += 4;
							if (type == r)
								addr += 8;
							if (type == ch)
								addr += 1;
						}//语义3

						read(w);

						if (w.type == SMQ.SearchKeyword(";"))
						{
							read(w);
							if (BianLiangShuoMing() > 0)
								return 1;
							else
								return -1;
						}
						else
							return 1;
					}
					else
					{
						system("cls"); cout << "变量类型未知！" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					system("cls"); cout << "变量类型未声明！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
		{
			system("cls"); cout << "变量声明缺少var！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//递归下降子程序——复合语句
	int FuHeYuJu()
	{
		if (w.type == SMQ.SearchKeyword("begin"))
		{
			read(w);
			if (YuJuBiao() > 0)
			{
				if (w.type == SMQ.SearchKeyword("end"))
				{
					//pos == SMQ.tokenlen||SEM.top().type==SMQ.proc_type  SEM.size()!=0&&SEM.top().pointer==0
					if (pos == SMQ.tokenlen)//最后一个end和与procedure对应的end才生成(end,program, , )
					{
						SYN.push(w);//语义0
						Produce_FunBound();//语义4
					}
					read(w);
					return 1;

				}
				else
				{
					system("cls"); cout << "复合语句缺少end！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
		{
			system("cls"); cout << "复合语句缺少begin！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//递归下降子程序——类型
	TVAL_TYPE LeiXing()
	{
		if (w.type == SMQ.SearchKeyword("integer"))
			return i;
		else
			if (w.type == SMQ.SearchKeyword("real"))
				return r;
			else
				if (w.type == SMQ.SearchKeyword("char"))
					return ch;
				else
					return (TVAL_TYPE)-1;
	}

	//递归下降子程序——标识符表
	int BiaoZhiFuBiao()
	{
		if (w.type == 1)
		{
			bzfNUM++;
			SEM.push(w);//语义2
			read(w);
			if (w.type == SMQ.SearchKeyword(","))
			{
				read(w);
				if (BiaoZhiFuBiao() > 0)
					return 1;
				else
					return -1;
			}
			else
				return 1;
		}
		else
		{
			system("cls"); cout << "标识符名称不合法！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//递归下降子程序——语句表
	int YuJuBiao()
	{

		if (YuJu() > 0)
		{
			if (w.type == SMQ.SearchKeyword(";"))
			{
				read(w);
				if (YuJuBiao() > 0)
					return 1;
				else
					return -1;
			}
			else
				return 1;
		}
		else
			return -1;
	}

	//递归下降子程序——语句
	int YuJu()
	{
		if (FuZhiYuJu() > 0 || TiaoJianYuJu() > 0 || XunHuanYuJu() > 0 || DiaoYongYuJu() > 0)
			return 1;
		else
			return -1;
	}

	//递归下降子程序——赋值语句
	int FuZhiYuJu()
	{
		if (w.type == 1)
		{
			SEM.push(w);
			read(w);
			if (w.type == SMQ.SearchKeyword(":="))
			{
				SYN.push(w);
				read(w);
				if (SuanShuBiaoDaShi() > 0)
				{
					Produce_Asign();//语义6
					//read(w);
					return 1;
				}
				else
					return -1;
			}
			else
				return -1;

		}
		else
			return -1;
	}

	//递归下降子程序——条件语句
	int TiaoJianYuJu()
	{
		int thenpos, elsepos, thengoto, elsegoto;//地址回填用
		if (w.type == SMQ.SearchKeyword("if"))
		{
			read(w);
			if (TiaoJian() > 0)
			{
				if (w.type == SMQ.SearchKeyword("then"))
				{
					SYN.push(w);//语义0
					thenpos = Produce_Then();//语义8
					read(w);
					if (YuJu() > 0 || FuHeYuJu() > 0)
					{
						if (w.type == SMQ.SearchKeyword("else"))
						{
							SYN.push(w);//语义0
							elsepos = Produce_Else();// 语义8
							thengoto = elsepos + 1;
							read(w);
							if (YuJu() > 0 || FuHeYuJu() > 0)
							{
								elsegoto = Produce_IfEnd();//语义10
								//地址回填
								(*(SiYuanShi.begin() + thenpos)).res.type = 2;
								(*(SiYuanShi.begin() + thenpos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(thengoto);
								(*(SiYuanShi.begin() + thenpos)).res.belongFHB = curFHB;
								(*(SiYuanShi.begin() + elsepos)).res.type = 2;
								(*(SiYuanShi.begin() + elsepos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(elsegoto);
								(*(SiYuanShi.begin() + elsepos)).res.belongFHB = curFHB;
								return 1;
							}
							else
								return -1;
						}
						else
						{
							thengoto = Produce_IfEnd();//语义10
							(*(SiYuanShi.begin() + thenpos)).res.type = 2;
							(*(SiYuanShi.begin() + thenpos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(thengoto);
							(*(SiYuanShi.begin() + thenpos)).res.belongFHB = curFHB;
							return 1;
						}
					}
					else
						return -1;

				}
				else
				{
					system("cls"); cout << "条件语句缺少then！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
			return -1;
	}

	//递归下降子程序——条件布尔表达式
	int TiaoJian()
	{
		if (SuanShuBiaoDaShi() > 0)
		{
			if (GuanXiFu() > 0)
			{
				if (SuanShuBiaoDaShi() > 0)
				{
					Produce_BoolEXP();//语义7
					//read(w);
					return 1;
				}
				else
					return -1;
			}
			else
				return -1;
		}
		else
			return -1;
	}

	//递归下降子程序——关系符
	int GuanXiFu()
	{
		if (w.type >= SMQ.SearchKeyword(">") && w.type <= SMQ.SearchKeyword("!="))
		{
			SYN.push(w);//语义0
			read(w);
			return 1;
		}
		else
		{
			system("cls"); cout << "关系符错误！" << endl; system("pause"); exit(0);
			return -1;
		}

	}

	//递归下降子程序——循环语句
	int XunHuanYuJu()
	{
		int dopos, whendpos, dogoto, whendgoto;//回填用
		if (w.type == SMQ.SearchKeyword("while"))
		{
			SYN.push(w);//语义0
			whendgoto = Produce_While();//语义11
			read(w);
			if (TiaoJian() > 0)
			{
				if (w.type == SMQ.SearchKeyword("do"))
				{
					SYN.push(w);//语义0
					dopos = Produce_Do();//语义12
					read(w);
					if (YuJu() > 0 || FuHeYuJu() > 0)
					{
						whendpos = Produce_WhEnd();//语义13
						dogoto = whendpos + 1;
						//地址回填
						(*(SiYuanShi.begin() + dopos)).res.type = 2;
						(*(SiYuanShi.begin() + dopos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(dogoto);
						(*(SiYuanShi.begin() + dopos)).res.belongFHB = curFHB;
						(*(SiYuanShi.begin() + whendpos)).res.type = 2;
						(*(SiYuanShi.begin() + whendpos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(whendgoto);
						(*(SiYuanShi.begin() + dopos)).res.belongFHB = curFHB;
						return 1;
					}
					else
						return -1;
				}
				else
				{
					system("cls"); cout << "循环语句缺少do！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
			return -1;
	}

	//递归下降子程序——过程调用语句
	int DiaoYongYuJu()
	{
		if (w.type == SMQ.SearchKeyword("call"))
		{
			SYN.push(w);
			read(w);
			if (w.type == 1)
			{
				int i = Produce_Call();//产生调用四元式
				read(w);
				if (w.type == SMQ.SearchKeyword("("))
				{
					read(w);
					int j;
					for (j = 0; j < (*SMQ.FHB[i].PFINFL.begin()).FN; j++)
					{
						Produce_Param();//产生参数四元式
						if (w.type == SMQ.SearchKeyword(","))
							read(w);
						else
							break;
					}
					if (j != (*SMQ.FHB[i].PFINFL.begin()).FN - 1)
					{
						system("cls"); cout << "参数个数不匹配！" << endl; system("pause"); exit(0);
						return -1;
					}
					if (w.type == SMQ.SearchKeyword(")"))
					{
						Produce_Ret();//产生返回四元式
						read(w);
						return 1;
					}
					else
					{
						system("cls"); cout << "参数个数不匹配！" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
					return -1;
			}
			else
				return -1;
		}
		else
			return -1;
	}

	//递归下降子程序——算术表达式
	int SuanShuBiaoDaShi()
	{

		if (E() > 0)
			return 1;
		else
		{
			system("cls"); cout << "算术表达式错误！" << endl; system("pause"); exit(0);
			return -1;
		}
		if (w.type == SMQ.SearchKeyword(";"))
		{
			//read(w);
			return 1;
		}
		else
		{
			system("cls"); cout << "算术表达式应以；结束！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	int E()
	{
		if (T() > 0)
		{
			if (E1() > 0)
			{
				return 1;
			}
			else
				return -1;
		}
		else
			return -1;
	}

	int E1()
	{
		if (w.type == SMQ.SearchKeyword("+") || w.type == SMQ.SearchKeyword("-"))
		{
			SYN.push(w);//语义0
			read(w);
			if (T() > 0)
			{
				Produce_EXP();//语义7
				if (E1() > 0)
				{
					return 1;
				}
				else
					return -1;
			}
			else
				return -1;
		}
		else
			return 1;
	}

	int T()
	{
		if (F() > 0)
		{
			if (T1() > 0)
			{
				return 1;
			}
			else
				return -1;
		}
		else
			return -1;
	}

	int T1()
	{
		if (w.type == SMQ.SearchKeyword("*") || w.type == SMQ.SearchKeyword("/"))
		{
			SYN.push(w);//语义0
			read(w);
			if (F() > 0)
			{
				Produce_EXP();//语义7
				if (T1() > 0)
				{
					return 1;
				}
				else
					return -1;
			}
			else
				return -1;
		}
		else
			return 1;
	}

	int F()
	{
		if (w.type == 1 || w.type == 2 || w.type == 3)
		{
			SEM.push(w);//语义5
			read(w);
			return 1;
		}
		else
		{
			if (w.type == SMQ.SearchKeyword("("))
			{
				read(w);
				if (E() > 0)
				{
					if (w.type == SMQ.SearchKeyword(")"))
					{
						read(w);
						return 1;
					}
					else
						return -1;
				}
				else
					return -1;
			}
			else
				return -1;
		}
	}
};

//目标代码生成类
class MuBiaoDaiMa
{
public:
	YuFaFenXi YFFX;
	//char obj[1000];
	//int acc = 0;

	MuBiaoDaiMa()
	{
		YFFX.Analyze();
		YFFX.PrintSiYuanShi();
		YFFX.printFHB();
	}

	/*SiYuanShi_Type GetSiYuanShi(int i)
	{
		return (*(YFFX.SiYuanShi.begin() + i));
	}*/

};

int main()
{
	MuBiaoDaiMa MBDM;
	getchar();
	return 0;
}

