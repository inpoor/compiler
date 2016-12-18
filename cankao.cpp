#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<Windows.h>
#include <cmath>
#include <iomanip>
using namespace std;
#define FUNCTION_NUM 10 //�������Ŀ
#define KEYWORD_NUM 39 //�ؼ��ֱ���

//�ؼ��ֱ�
char *Key[KEYWORD_NUM] = { "program", "var", "integer", "real", "char", "begin", "end", "if", "then", "else", "while", "do", "ifend", "whend", "const", "procedure", "call", "param", "ret", "endp",
",", ":", ";", ":=", "*", "/", "+", "-", ".", "(", ")", "\'", ">", "<", "==", ">=", "<=", "!=", "=" };

//���������״̬ת������
int CSCLStatus[9][5] = { {}, { 2, 0, 0, 0, 0 }, { 2, 3, 5, 0, 8 }, { 4, 0, 0, 0, 0 }, { 4, 0, 5, 0, 8 }, { 7, 0, 0, 6, 0 }, { 7, 0, 0, 0, 0 }, { 7, 0, 0, 0, 8 }, { 0, 0, 0, 0, 0 } };

//TYP��i���Σ�rʵ�ͣ�ch�ַ��ͣ�b�����ͣ�a�����ͣ�s�ṹ��
enum TVAL_TYPE{ i, r, ch, b, a, s };	

//CAT��p���̣�c������t���ͣ�d������v������vn�����βΣ�vf��ֵ�β�
enum CAT_TYPE{ p, c, t, d, v, vn, vf };

//Token����
struct Token
{
	int type, pointer;

	int belongFHB;
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
	TVAL_TYPE TVAL;
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

//���ű���
class FuHaoBiao
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
	FuHaoBiao()
	{
		for (int i = 0; i < 6; i++)
			TAPEL.push_back({ (TVAL_TYPE)i, -1 });
	}

	//���ű��ܱ��β������Ϊname������Ϊ�յı�����ص�ǰ����λ��
	int InsertSYNBL(string name)
	{
		SYNBL.push_back({ name, (TVAL_TYPE)-1, (CAT_TYPE)-1, -1 });
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
	{
		PFINFL.push_back({ level, 3, -1, -1, -1 });
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

//�����������
class ChangShuChuLi
{
public:
	int Status[9][5];//״̬ת�ƾ���
	int N, p, m, e;//N��β����p��ָ����m��С��λ����e��ָ��+Ϊ1��-Ϊ-1
	double num;//����ת���ɵ�double�ͳ���

	//��״̬ת�ƾ�����г�ʼ��
	ChangShuChuLi()
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 5; j++)
				Status[i][j] = CSCLStatus[i][j];
	}

	//���������������
	double StrToDouble(char *Str)
	{
		N = 0; p = 0; m = 0; e = 1; num = 0;//��ʼ��
		int s = 1;//��ʼ״̬
		char ch;//��ǰ�ַ�
		ch = Str[0];//�ӵ�0���ַ���ʼ
		int Pointer = 0;//ָ���ַ���ָ��
		while (s != 8 && s != 0)
		{
			Act(s, ch);//��ǰ״̬����
			ch = Str[Pointer++];//����һ���ַ�
			s = move(s, ch);//״̬ת��
		}

		//���������ֵ
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

	//״̬ת�ƺ���
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

	//��ǰ״̬����
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

//�ʷ�ɨ������
class SaoMiaoQi
{
public:
	char *Keyword[KEYWORD_NUM];//�ؼ��ֱ�
	FuHaoBiao FHB[1 + FUNCTION_NUM];//���ű�ÿ��������Ӧһ�����ű�

	ChangShuChuLi CSCL;//�������������

	Token token[1000];//token����
	int tokenlen = 0;//��ǰtoken���г���

	char FileName[20];//Ҫɨ����ļ�

	char cache[20];//�ַ�������
	int cachelen = 0;//��ǰ���泤��

	int state = 1;//�Զ�����ʼ״̬

	//�������
	int proc_type;//�ؼ���procedure�ڹؼ��ֱ��е�λ��
	int endp_type;//�ؼ���endp�ڹؼ��ֱ��е�λ��
	int level = 0;//��ǰlevel
	stack<int>lastFHB;//ջ����մ�����ķ��ű��
	int curFHB = 0;//��ǰ����ķ��ű�
	int totalFHB = 0;//�ܹ���ռ�õķ��ű�

	//�ļ�����ʼ�����ؼ��ֱ��ʼ�������õ�procedure��endp��λ�õĳ�ʼ��
	SaoMiaoQi()
	{
		strcpy_s(FileName, "..\\main.txt");
		for (int i = 0; i < KEYWORD_NUM; i++)
			Keyword[i] = Key[i];
		proc_type = SearchKeyword("procedure");
		endp_type = SearchKeyword("endp");

	}

	//�Ƿ���ĸ
	int isletter(char ch)
	{
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
			return 1;
		else
			return 0;
	}

	//�Ƿ�����
	int isdigit(char ch)
	{
		if (ch >= '0'&&ch <= '9')
			return 1;
		else
			return 0;
	}

	//��ؼ��ֱ�
	int SearchKeyword(char *str)
	{
		for (int i = 0; i < KEYWORD_NUM; i++)
			if (!strcmp(Keyword[i], str))
				return i + 4;
		return -1;
	}

	//����һ��token
	int AddToken(int type, int pointer)
	{
		token[tokenlen].belongFHB = curFHB;
		token[tokenlen].type = type;
		token[tokenlen].pointer = pointer;
		tokenlen++;

		//��ջ�����ַ���
		memset(cache, 0, sizeof(cache));
		cachelen = 0; 
		
		//�Զ���״̬�ָ�0
		state = 1;

		return 1;
	}

	//�ļ�ָ����ˣ������ַ�������һλ
	void fpback(FILE *fp)
	{
		fseek(fp, -1, SEEK_CUR);
		cache[cachelen - 1] = '\0';
		cachelen--;
	}

	//���token����
	void printToken()
	{
		cout << "Token:1-��ʶ����2-������3-�ַ�������-�ؼ���" << endl;
		for (int i = 0; i < tokenlen; i++)
			cout << setw(2) << "(" << setw(2) << token[i].type << setw(2) << "," << setw(2) << token[i].pointer << setw(2) << ")" << setw(2);
		cout << endl;
	}

	//ɨ�����Զ�����ʵ��
	void Scan()
	{
		FILE *fp;

		char ch;//��ǰ�ַ�ch

		if ((fp = fopen(FileName, "r")) == NULL)
		{
			cout << "file not exists!" << endl;
			return;
		}

		//����ַ��ж�
		while (!feof(fp))
		{
			ch = fgetc(fp);//��ȡ��ǰ�ַ�

			//��ȥ�ո񡢻��С�ˮƽ�Ʊ��
			if ((ch == ' ' || ch == '\n' || ch == '\t') && state == 1)
				continue;

			cache[cachelen++] = ch;//��ǰ�ַ����뻺��

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
					   fpback(fp);//���ˣ�ȥ����������Ҳ������ĸ�ĵ��ʵĺ�̷�
					   int type;
					   if ((type = SearchKeyword(cache)) != -1)//�ǹؼ��ֵ����
					   {
						   AddToken(type, -1);

						   //����procedure�ؼ��֣���ǰ����ķ��ű����ѹջ�������µķ��ű�
						   if (type == proc_type)
						   {
							   level++;
							   lastFHB.push(curFHB);
							   totalFHB++;
							   curFHB = totalFHB;
						   }

						   //��endp�ؼ��֣���ǰ���ű�����ϣ�����֮ǰ�ķ��ű�
						   if (type == endp_type&&level != 0)
						   {
							   level--;
							   curFHB = lastFHB.top();
							   lastFHB.pop();
						   }
					   }
					   else//���ǹؼ���������Ϊ��ʶ��
					   {
						   int pointer;
						   if ((pointer = FHB[curFHB].SearchSYNBL(cache)) != -1)//��ʶ���Ѵ���
							   AddToken(1, pointer);
						   else//��ʶ�����µ��������ű�ĩβ
							   AddToken(1, FHB[curFHB].InsertSYNBL(cache));
					   }
				   }
				   break;
			case 3:if (ch == '.'){ state = 4; break; }
				   if (isdigit(ch)) break;
				   {
					   fpback(fp);//���ˣ�ȥ�������ĺ�̷�

					   ///*cache���ɳ������������*/double d = strtod(cache, NULL);
					   double d = CSCL.StrToDouble(cache);

					   int pointer;
					   if ((pointer = FHB[curFHB].SearchCONSL(d)) != -1)//�������ڳ�������
						   AddToken(2, pointer);
					   else//�������µ�����볣����
					   {
						   AddToken(2, FHB[curFHB].InsertCONSL(d));
					   }
				   }

				   break;
			case 4:if (isdigit(ch)){ state = 5; break; };
				   break;
			case 5:if (isdigit(ch)){ break; }
				   {
					   fpback(fp);//���ˣ�ȥ�������ĺ�̷�

					   ///*cache���ɳ������������*/double d = strtod(cache, NULL);
					   double d = CSCL.StrToDouble(cache);

					   int pointer;
					   if ((pointer = FHB[curFHB].SearchCONSL(d)) != -1)//�������ڳ�������
						   AddToken(2, pointer);
					   else//�������µ�����볣����
						   AddToken(2, FHB[curFHB].InsertCONSL(d));
				   }
				   break;
			case 10:state = 11; break;
			case 11:if (ch == '\''){ AddToken(3, FHB[curFHB].InsertCONSL(cache[1])); }
					break;
			case 6:
			case 19:
			case 21:
			case 23:if (ch == '='){ AddToken(SearchKeyword(cache), -1); break; }//>=,<=,==,!=��token�����
					{//����>,<,=�ŵ�token���
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

//�﷨������
class YuFaFenXi
{
public:
	SaoMiaoQi SMQ;//�ʷ�ɨ����
	int pos = 0;//��ǰ�ǵ�pos��token����token����������
	Token w, e;//��ʱ�洢��ǰ������token

	vector<SiYuanShi_Type>SiYuanShi;//��Ԫʽ�洢�ṹ
	stack<Token>SEM;//����ջ
	stack<Token>SYN;//���ջ

	int addr = 0;//���ű�ADDR����
	stack<int>addrstk;//�����µķ��ű�ʱ����Ҫ����һ�����ű�addr��ջ����

	int bzfNUM;//������������У�ͳ�Ʊ�����Ŀ
	int xingcanNUM = 0;//�β���������У�ͳ���β���Ŀ
	int order = 0;//�м������ţ����ɵ��м������Ŵ�0��ʼ����

	int level = 0;//��ǰ����level
	stack<int>lastFHB;//ջ����մ�����ķ��ű����
	int curFHB = 0;//��ǰ����ķ��ű�
	int totalFHB = 0;//�ܹ��ķ��ű���

	//��ʼ����Ҫ����ɨ����ɨ�赥��
	YuFaFenXi()
	{
		SMQ.Scan();
		SMQ.printToken();
	}

	//����������еķ��ű�
	void printFHB()
	{
		for (int i = 0; i <= totalFHB; i++)
		{
			cout << "���ű�" << i << ":" << endl;
			SMQ.FHB[i].printFHB();
			cout << endl;
		}
	}

	//�����������ʽ��Ԫʽ
	int Produce_EXP()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };

		//�򵥵��м������������
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
			//�м�������Ĳ���
			char name[6] = "_t", num[4];
			_itoa(order++, num, 10);
			for (int k = 0; k < 4; k++)
			{
				name[k + 2] = num[k];
			}
			tmp.res.type = 1;
			tmp.res.pointer = SMQ.FHB[curFHB].InsertSYNBL(name);//�м����������ű�
			tmp.res.belongFHB = curFHB;

			//�ж�ARG1��ARG2�����м����������
			if ((*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP != -1 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP != -1)
				(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.res.pointer)).TYP = (TVAL_TYPE)TYPUP[(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP][(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP];
			if ((*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP != -1 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP >= 0 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP <= 2)
				(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.res.pointer)).TYP = r;
			if ((*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg2.pointer)).TYP != -1 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP >= 0 && (*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.arg1.pointer)).TYP <= 2)
				(*(SMQ.FHB[curFHB].SYNBL.begin() + tmp.res.pointer)).TYP = r;

			//����ű�
			TianSYNBL((TVAL_TYPE)-2, v, addr, tmp.res.pointer);

			//addr����
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

	//������������в������ʽ����Ԫʽ
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
			//�������ʽ�м��������
			char name[6] = "_b", i[4];
			_itoa(order++, i, 10);
			for (int k = 0; k < 4; k++)
			{
				name[k + 2] = i[k];
			}
			tmp.res.type = 1;
			tmp.res.pointer = SMQ.FHB[curFHB].InsertSYNBL(name);//������ű�
			tmp.res.belongFHB = curFHB;

			TianSYNBL(b, v, addr, tmp.res.pointer); 
			addr += 1;//���貼�����ʽ���ռ1�ֽ�

			SEM.push(tmp.res);
		}

		SiYuanShi.push_back(tmp);
		return 1;
	}

	//����Program��Ԫʽ����
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

	//����procedure��Ԫʽ����
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

		//�����д��Ԫʽ��λ��
		(*SMQ.FHB[curFHB].PFINFL.begin()).ENTRY = SiYuanShi.size();

		SiYuanShi.push_back(tmp);
		return 1;
	}

	//��ֵ���ʽ��Ԫʽ����
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

		/*if (tmp.arg1.type == 1)//��V�ķ��ű�ADDR��
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

	//�������Then��Ԫʽ����
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

		return SiYuanShi.size() - 1;//���������Ԫʽ��λ�����ڵ�ַ����
	}

	//�������Else��Ԫʽ�Ĳ���
	int Produce_Else()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//���������Ԫʽ��λ�����ڵ�ַ����
	}

	//�������Ifend��Ԫʽ�Ĳ���
	int Produce_IfEnd()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		tmp.op.type = SMQ.SearchKeyword("ifend");
		tmp.op.belongFHB = curFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//���������Ԫʽ��λ�����ڵ�ַ����
	}

	//ѭ�����While��Ԫʽ�Ĳ���
	int Produce_While()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		e = SYN.top(); SYN.pop();
		tmp.op.type = e.type;
		tmp.op.pointer = e.pointer;
		tmp.op.belongFHB = e.belongFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//���������Ԫʽ��λ�����ڵ�ַ����
	}

	//ѭ�����Do��Ԫʽ�Ĳ���
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

		return SiYuanShi.size() - 1;//���������Ԫʽ��λ�����ڵ�ַ����
	}

	//ѭ�����WhEnd��Ԫʽ�Ĳ���
	int Produce_WhEnd()
	{
		SiYuanShi_Type tmp = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		//OP
		tmp.op.type = SMQ.SearchKeyword("whend");
		tmp.op.belongFHB = curFHB;

		SiYuanShi.push_back(tmp);

		return SiYuanShi.size() - 1;//���������Ԫʽ��λ�����ڵ�ַ����
	}

	//���̵������CALL��Ԫʽ
	int Produce_Call()
	{
		int i;//��ѯ�����ù��������ڵķ��ű��
		for (i = 0; i <= totalFHB; i++)
			if ((*SMQ.FHB[i].SYNBL.begin()).name == (*(SMQ.FHB[w.belongFHB].SYNBL.begin() + w.pointer)).name)
				break;

		if (i == totalFHB+1)//�Ҳ����������򱨴�
		{
			system("cls"); cout << "���ú��������ڣ�" << endl; system("pause"); exit(0);
			return -1;
		}

		//�������������ű���д
		(*(SMQ.FHB[w.belongFHB].SYNBL.begin() + w.pointer)).CAT = p;

		//Call��Ԫʽ����
		SiYuanShi_Type tmp = { SYN.top(), { 1, 0, i }, { 2, SMQ.FHB[i].InsertCONSL((*SMQ.FHB[i].PFINFL.begin()).ENTRY), i }, { -1, -1 } };
		SiYuanShi.push_back(tmp);
		SYN.pop();

		return i;//�������ڷ��ű��
	}

	//���̵��õ���������Ԫʽ����
	int Produce_Param()
	{
		//�������ʽ��Ϊ����
		if (SuanShuBiaoDaShi() > 0)
		{
			SiYuanShi_Type tmp = { { SMQ.SearchKeyword("param"), -1, curFHB }, SEM.top(), { -1, -1 }, { -1, -1 } };
			SiYuanShi.push_back(tmp);
			SEM.pop();
			return 1;
		}
		else
		{
			system("cls"); cout << "�������ʹ���" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//���̵��÷�����Ԫʽ����
	int Produce_Ret()
	{
		SiYuanShi_Type tmp = { { SMQ.SearchKeyword("ret"), -1, curFHB }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
		SiYuanShi.push_back(tmp);
		return 1;
	}

	//�����Ԫʽ
	void PrintSiYuanShi()
	{
		cout << "��Ԫʽ��" << endl;
		int i = 0;
		vector<SiYuanShi_Type>::iterator it;
		for (it = SiYuanShi.begin(); it != SiYuanShi.end(); it++)
		{
			//������
			cout << setw(2) << i++ << '.';

			//���OP
			if ((*it).op.type != -1)
				cout << '(' << Key[(*it).op.type - 4] << ',';
			else
				cout << "( ,";

			//���ARG1
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

			//���ARG2
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

			//���RES
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

	//����ű��ܱ�ĳһ����޸�ʱ������Ϊ-2
	void TianSYNBL(TVAL_TYPE TYP, CAT_TYPE CAT, int ADDR, int pointer)
	{
		if (TYP != -2)(*(SMQ.FHB[curFHB].SYNBL.begin() + pointer)).TYP = TYP;
		if (CAT != -2)(*(SMQ.FHB[curFHB].SYNBL.begin() + pointer)).CAT = CAT;
		if (ADDR != -2)(*(SMQ.FHB[curFHB].SYNBL.begin() + pointer)).ADDR = ADDR;
	}

	//�����Ϣ��ĳһ����޸�ʱ������Ϊ-2
	void TianPFINFL(int LEVEL, int	OFF, int FN, int ENTRY, int PARAM, int pointer)
	{
		if (LEVEL != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).LEVEL = LEVEL;
		if (OFF != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).OFF = OFF;
		if (FN != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).FN = FN;
		if (ENTRY != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).ENTRY = ENTRY;
		if (PARAM != -2)(*(SMQ.FHB[curFHB].PFINFL.begin() + pointer)).PARAM = PARAM;
	}

	//��һ��token��w
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

	//�﷨�������
	int Analyze()
	{
		read(w);
		if (ChengXu() > 0)
			return 1;
		else
			return -1;
	}

	//�ݹ��½��ӳ��򡪡�����
	int ChengXu()
	{
		if (w.type == SMQ.SearchKeyword("program"))
		{
			SYN.push(w);//����0
			read(w);
			if (w.type == 1)
			{
				SEM.push(w); SEM.push(w); TianSYNBL((TVAL_TYPE)-1, p, -1, w.pointer); Produce_FunBound();//����1
				read(w);
				if (FenChengXu() > 0)
					return 1;
				else
					return -1;
			}
			else
			{
				system("cls"); cout << "���������Ϸ���" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
		{
			system("cls"); cout << "�Ҳ��������program��ڣ�" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//�ݹ��½��ӳ��򡪡��ֳ���
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

	//�ݹ��½��ӳ��򡪡�����
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
			SYN.push(w);//����0
			read(w);
			if (w.type == 1)
			{
				int pfinflen = SMQ.FHB[curFHB].InsertPFINFL(level);//�����Ϣ��level
				TianSYNBL((TVAL_TYPE)-1, p, -1, w.pointer);
				SEM.push(w); SEM.push(w);//����2
				Produce_ProcBound();

				read(w);
				if (w.type == SMQ.SearchKeyword("("))
				{
					read(w);
					if (XingCanLieBiao() > 0)
					{
						TianPFINFL(-2, -2, xingcanNUM, -2, 1, pfinflen);//�����ϢFN��PARAM
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
									//SYN.push(endtmp);//����0
									if (w.type == SMQ.SearchKeyword("endp"))
									{
										SYN.push(w);
										read(w);
									}
									else
									{
										system("cls"); cout << "����Ӧ��endp��β��" << endl; system("pause"); exit(0);
										return -1;
									}
									Produce_FunBound();//����4
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
							system("cls"); cout << "��������ȱ�������ţ�" << endl; system("pause"); exit(0);
							return -1;
						}
					}
					else
						return -1;
				}
				else
				{
					system("cls"); cout << "��������ȱ�������ţ�" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				system("cls"); cout << "���������Ϸ���" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
			return -1;
	}

	//�ݹ��½��ӳ��򡪡��β��б�
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

	//�ݹ��½��ӳ��򡪡��β�˵��
	int XingCanShuoMing()
	{
		if (w.type == SMQ.SearchKeyword("var"))
		{
			xingcanNUM++;
			read(w);
			if (w.type == 1)
			{
				SEM.push(w);//����2
				read(w);
				if (w.type == SMQ.SearchKeyword(":"))
				{
					read(w);
					int type;
					if ((type = LeiXing()) != -1)
					{
						w = SEM.top(); SEM.pop();//����15
						TianSYNBL((TVAL_TYPE)type, vn, addr, w.pointer);
						addr += 2;//�����β�Ϊ+2
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
						system("cls"); cout << "�β�����δ֪��" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					system("cls"); cout << "�β�Ӧ����:�������ͣ�" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				//system("cls"); cout << "�����β������Ϸ���" << endl; system("pause"); exit(0);
				//return -1;
				return 1;
			}
		}
		else
		{
			if (w.type == 1)
			{
				xingcanNUM++;
				SEM.push(w);//����2
				read(w);
				if (w.type == SMQ.SearchKeyword(":"))
				{
					read(w);
					TVAL_TYPE type;
					if ((type = LeiXing()) != -1)
					{
						w = SEM.top(); SEM.pop();//����5
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
						system("cls"); cout << "�β�����δ֪��" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					system("cls"); cout << "�β�Ӧ����:�������ͣ�" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				//system("cls"); cout << "��ֵ�β������Ϸ���" << endl; system("pause"); exit(0);
				//return -1;
				return 1;
			}
		}
	}

	//�ݹ��½��ӳ��򡪡�����˵��
	int ChangLiangShuoMing()
	{
		if (w.type == SMQ.SearchKeyword("const"))
		{
			read(w);
			if (w.type == 1)
			{
				SEM.push(w);//����2
				read(w);
				if (w.type == SMQ.SearchKeyword("="))
				{
					read(w);
					if (w.type == 2)
					{
						e = SEM.top(); SEM.pop();//����14
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
						system("cls"); cout << "����Ӧ��Ϊ���֣�" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					system("cls"); cout << "��������Ӧ��=�ţ�" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				system("cls"); cout << "���������Ϸ���" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
			return 1;
	}

	//�ݹ��½��ӳ��򡪡�����˵��
	int BianLiangShuoMing()
	{
		if (w.type == SMQ.SearchKeyword("var"))
		{
			read(w);
			bzfNUM = 0;//����������
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
						}//����3

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
						system("cls"); cout << "��������δ֪��" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					system("cls"); cout << "��������δ������" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
		{
			system("cls"); cout << "��������ȱ��var��" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//�ݹ��½��ӳ��򡪡��������
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
					if (pos == SMQ.tokenlen)//���һ��end����procedure��Ӧ��end������(end,program, , )
					{
						SYN.push(w);//����0
						Produce_FunBound();//����4
					}
					read(w);
					return 1;

				}
				else
				{
					system("cls"); cout << "�������ȱ��end��" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
		{
			system("cls"); cout << "�������ȱ��begin��" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//�ݹ��½��ӳ��򡪡�����
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

	//�ݹ��½��ӳ��򡪡���ʶ����
	int BiaoZhiFuBiao()
	{
		if (w.type == 1)
		{
			bzfNUM++;
			SEM.push(w);//����2
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
			system("cls"); cout << "��ʶ�����Ʋ��Ϸ���" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//�ݹ��½��ӳ��򡪡�����
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

	//�ݹ��½��ӳ��򡪡����
	int YuJu()
	{
		if (FuZhiYuJu() > 0 || TiaoJianYuJu() > 0 || XunHuanYuJu() > 0 || DiaoYongYuJu() > 0)
			return 1;
		else
			return -1;
	}

	//�ݹ��½��ӳ��򡪡���ֵ���
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
					Produce_Asign();//����6
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

	//�ݹ��½��ӳ��򡪡��������
	int TiaoJianYuJu()
	{
		int thenpos, elsepos, thengoto, elsegoto;//��ַ������
		if (w.type == SMQ.SearchKeyword("if"))
		{
			read(w);
			if (TiaoJian() > 0)
			{
				if (w.type == SMQ.SearchKeyword("then"))
				{
					SYN.push(w);//����0
					thenpos = Produce_Then();//����8
					read(w);
					if (YuJu() > 0 || FuHeYuJu() > 0)
					{
						if (w.type == SMQ.SearchKeyword("else"))
						{
							SYN.push(w);//����0
							elsepos = Produce_Else();// ����8
							thengoto = elsepos + 1;
							read(w);
							if (YuJu() > 0 || FuHeYuJu() > 0)
							{
								elsegoto = Produce_IfEnd();//����10
								//��ַ����
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
							thengoto = Produce_IfEnd();//����10
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
					system("cls"); cout << "�������ȱ��then��" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
			return -1;
	}

	//�ݹ��½��ӳ��򡪡������������ʽ
	int TiaoJian()
	{
		if (SuanShuBiaoDaShi() > 0)
		{
			if (GuanXiFu() > 0)
			{
				if (SuanShuBiaoDaShi() > 0)
				{
					Produce_BoolEXP();//����7
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

	//�ݹ��½��ӳ��򡪡���ϵ��
	int GuanXiFu()
	{
		if (w.type >= SMQ.SearchKeyword(">") && w.type <= SMQ.SearchKeyword("!="))
		{
			SYN.push(w);//����0
			read(w);
			return 1;
		}
		else
		{
			system("cls"); cout << "��ϵ������" << endl; system("pause"); exit(0);
			return -1;
		}

	}

	//�ݹ��½��ӳ��򡪡�ѭ�����
	int XunHuanYuJu()
	{
		int dopos, whendpos, dogoto, whendgoto;//������
		if (w.type == SMQ.SearchKeyword("while"))
		{
			SYN.push(w);//����0
			whendgoto = Produce_While();//����11
			read(w);
			if (TiaoJian() > 0)
			{
				if (w.type == SMQ.SearchKeyword("do"))
				{
					SYN.push(w);//����0
					dopos = Produce_Do();//����12
					read(w);
					if (YuJu() > 0 || FuHeYuJu() > 0)
					{
						whendpos = Produce_WhEnd();//����13
						dogoto = whendpos + 1;
						//��ַ����
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
					system("cls"); cout << "ѭ�����ȱ��do��" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
			return -1;
	}

	//�ݹ��½��ӳ��򡪡����̵������
	int DiaoYongYuJu()
	{
		if (w.type == SMQ.SearchKeyword("call"))
		{
			SYN.push(w);
			read(w);
			if (w.type == 1)
			{
				int i = Produce_Call();//����������Ԫʽ
				read(w);
				if (w.type == SMQ.SearchKeyword("("))
				{
					read(w);
					int j;
					for (j = 0; j < (*SMQ.FHB[i].PFINFL.begin()).FN; j++)
					{
						Produce_Param();//����������Ԫʽ
						if (w.type == SMQ.SearchKeyword(","))
							read(w);
						else
							break;
					}
					if (j != (*SMQ.FHB[i].PFINFL.begin()).FN - 1)
					{
						system("cls"); cout << "����������ƥ�䣡" << endl; system("pause"); exit(0);
						return -1;
					}
					if (w.type == SMQ.SearchKeyword(")"))
					{
						Produce_Ret();//����������Ԫʽ
						read(w);
						return 1;
					}
					else
					{
						system("cls"); cout << "����������ƥ�䣡" << endl; system("pause"); exit(0);
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

	//�ݹ��½��ӳ��򡪡��������ʽ
	int SuanShuBiaoDaShi()
	{

		if (E() > 0)
			return 1;
		else
		{
			system("cls"); cout << "�������ʽ����" << endl; system("pause"); exit(0);
			return -1;
		}
		if (w.type == SMQ.SearchKeyword(";"))
		{
			//read(w);
			return 1;
		}
		else
		{
			system("cls"); cout << "�������ʽӦ�ԣ�������" << endl; system("pause"); exit(0);
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
			SYN.push(w);//����0
			read(w);
			if (T() > 0)
			{
				Produce_EXP();//����7
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
			SYN.push(w);//����0
			read(w);
			if (F() > 0)
			{
				Produce_EXP();//����7
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
			SEM.push(w);//����5
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

//Ŀ�����������
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

