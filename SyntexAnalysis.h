#ifndef _SYNTEXANALYSIS_H_
#define _SYNTEXANALYSIS_H_
#include "Main.h"


class  LexicalAnalysis;

class SyntexAnalysis{
private:
	LexicalAnalysis LA;
	int pos;//当前是第pos个token，即token读到哪里了
	int var_num;
	int addr;
	Token w, e;//临时存储当前读出的token
	stack<Token>SEM;//对象栈
	stack<Token>SYN;//算符栈




	int read(Token &w);
	
	int analysis();
	int FenChengXu();
	int GuoHan();
	int ChangLiangShuoMing();
	int BianLiangShuoMing();
	int FuHeYuJu();
	int LeiXing();
	int BiaoZhiFuBiao();
	int YuJuBiao();
	int YuJu();
	int SuanShuBiaoDaShi();
	int XingCanLieBiao();
	int BiaoZhiFu();
	int FuZhiYuJu();
	int TiaoJianYuJu();
	int XunHuanYuJu();
	int TiaoJian();
	int GuanXiFu();
	int DiaoYongYuJu();
	int XingCanShuoMing();
	int ShiCanLieBiao();
	int E();
	int E1();
	int T();
	int T1();
	int F();
public:
	
	SyntexAnalysis()
	{   pos=0;
		LA.Scanning();
	//	LA.print_Token();

	}
	int Parser(){
	{
		read(w);
		if (analysis() > 0)
			return 1;
		else
			return -1;
	}
	}

};
int SyntexAnalysis::read(Token &w)
	{
		if (pos < LA.GetTokenLen())
		{
			w = LA.GetTokenById(pos++);
			cout<<w.token<<"---"<<w.state<<endl;
			return 1;
		}
		else
			return -1;
	}
	
	//语法分析入口
/*	int SyntexAnalysis::Parser()
	{  
		read(w);
		if (analysis() > 0)
			return 1;
		else
			return -1;
	}
	*/
	//递归下降子程序——程序
	int SyntexAnalysis::analysis()
	{
		if (w.token == LA.SearchKt("program"))
		{
		/*	SYN.push(w);//语义0*/
			read(w);
			if (w.token == 0)
			{
			/*	SEM.push(w); SEM.push(w);// TianSYNBL((TVAL_TYPE)-1, p, -1, w.pointer);	Produce_FunBound();//语义1*/
				read(w);
				if (FenChengXu() > 0)
					return 1;
				else
					return -1;
			}
			else
			{
			//	system("cls");
				cout << "程序名不合法！" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
		{
		//	system("cls"); 
			cout << "找不到程序的program入口！" << endl; system("pause"); exit(0);
			return -1;
		}
	}
		//递归下降子程序——分程序
	int SyntexAnalysis::FenChengXu()
	{
		if (BianLiangShuoMing() > 0)
		{
			if (ChangLiangShuoMing() > 0)
			{
				while (GuoHan() > 0);

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
	int SyntexAnalysis::GuoHan()
	{
		if (w.token ==LA.SearchKt("procedure")||w.token ==LA.SearchKt("function"))
		{
		/*	addrstk.push(addr);
			addr = 0;
			level++;
			lastFHB.push(curFHB);
			totalFHB++;               /* 
			curFHB = totalFHB;
			SYN.push(w);//语义0*/
			read(w);
			if (w.token == 0)
			{
				/*int pfinflen = SMQ.FHB[curFHB].InsertPFINFL(level);//填函数信息表level
				TianSYNBL((TVAL_TYPE)-1, p, -1, w.pointer);
				SEM.push(w); SEM.push(w);//语义2
				Produce_ProcBound();*/

				read(w);
				if (w.token == LA.SearchPt("("))
				{
					read(w);
					if (XingCanLieBiao() > 0)
					{
					/*	TianPFINFL(-2, -2, xingcanNUM, -2, 1, pfinflen);//填函数信息FN和PARAM
						xingcanNUM = 0;*/
						if (w.token == LA.SearchPt(")"))
						{
							read(w);
							if (BianLiangShuoMing() > 0)
							{
								while (GuoHan() > 0);

								if (FuHeYuJu() > 0)
								{
									//Token_Type endtmp = { SMQ.SearchKeyword("end"), -1 };
									//SYN.push(endtmp);//语义0
									if (w.token == LA.SearchKt("endp")||w.token == LA.SearchKt("endf"))
									{
									/*	SYN.push(w);*/
										read(w);
									}
									else
									{
									//	system("cls"); 
										cout << "过程应以endp结尾！" << endl; system("pause"); exit(0);
										return -1;
									}
							/*		Produce_FunBound();//语义4
									addr = addrstk.top();
									addrstk.pop();
									level--;
									curFHB = lastFHB.top();
									lastFHB.pop();*/
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
							//system("cls"); 
							cout << "函数声明缺少右括号！" << endl; system("pause"); exit(0);
							return -1;
						}
					}
					else
						return -1;
				}
				else
				{
					//system("cls"); 
					cout << "函数声明缺少左括号！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
			//	system("cls");
				cout << "函数名不合法！" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
			return -1;
	}

		//递归下降子程序——形参列表
	int SyntexAnalysis::XingCanLieBiao()
	{
		if (XingCanShuoMing() > 0)
		{
			//xingcanNUM++;
			if (w.token == LA.SearchPt(";"))
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
	int SyntexAnalysis::XingCanShuoMing()
	{
		if (w.token == LA.SearchKt("var"))
		{
		/*	xingcanNUM++;*/
			read(w);
			if (w.token == 0) /*标识符*/
			{
			/*	SEM.push(w);//语义2*/
				read(w);
				if (w.token == LA.SearchPt(":"))
				{
					read(w);
					int type;
					if ((type = LeiXing()) != -1)
					{
					/*	w = SEM.top(); SEM.pop();//语义15
						TianSYNBL((TVAL_TYPE)type, vn, addr, w.pointer);
						addr += 2;//换名形参为+2*/
						
						read(w);
						return 1;
					}
					else
					{
						//system("cls"); 
						cout << "形参类型未知！" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					//system("cls"); 
					cout << "形参应当用:声明类型！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				
				return 1;
			}
		}
		else
		{
			if (w.token == 0)
			{
			/*	xingcanNUM++;
				SEM.push(w);//语义2*/
				read(w);
				if (w.token == LA.SearchPt(":"))
				{
					read(w);
					TVAL_TYPE type;
					if ((type = (TVAL_TYPE)LeiXing()) != -1)
					{
				/*		w = SEM.top(); SEM.pop();//语义5
						TianSYNBL(type, vf, addr, w.pointer);
						if (type == i)
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
					//	system("cls");
						cout << "形参类型未知！" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
				//	system("cls"); 
					cout << "形参应当用:声明类型！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				
				return 1;
			}
		}
	}



	//递归下降子程序——常量说明
	int SyntexAnalysis::ChangLiangShuoMing()
	{
		if (w.token == LA.SearchKt("const"))
		{
			read(w);
			if (w.token == 0)
			{
			/*	SEM.push(w);//语义2*/
				read(w);
				if (w.token == LA.SearchPt("="))
				{
					read(w);
					if (w.token == 3)
					{
					/*	e = SEM.top(); SEM.pop();//语义14
					//	TianSYNBL(r, c, w.pointer, e.pointer);//////////////////////////////////*/
						read(w);

						if (w.token == LA.SearchPt(";"))
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
					//	system("cls");
						cout << "常量应当为数字！" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					//system("cls"); 
					cout << "常量声明应用=号！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				//system("cls"); 
				cout << "常量名不合法！" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
			return 1;
	}

	int SyntexAnalysis::BianLiangShuoMing()
	{
		if (w.token == LA.SearchKt("var"))
		{
			read(w);
			/*var_num = 0;//变量数清零*/
			if ((BiaoZhiFuBiao()) > 0)
			{
				if (w.token == LA.SearchPt(":"))
				{
					read(w);
					TVAL_TYPE type;
					if ((type = (TVAL_TYPE)LeiXing()) != -1)
					{
					/*	for (int j = 0; j < var_num; j++)
						{
							w = SEM.top(); SEM.pop();
							TianSYNBL(type, v, addr, w.pointer);
							if (type == i)
								addr += 4;
							if (type == r)
								addr += 8;
							if (type == ch)
								addr += 1;
						}//语义3*/

						read(w);

						if (w.token == LA.SearchPt(";"))
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
						//system("cls");
						cout << "变量类型未知！" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					//system("cls"); 
					cout << "变量类型未声明！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
		{
			//system("cls");
			cout << "变量声明缺少var！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

		//递归下降子程序——复合语句
	int SyntexAnalysis::FuHeYuJu()
	{   //cout<<w.token<<"/"<<LA.SearchKt("begin")<<endl;
		if (w.token== LA.SearchKt("begin"))
		{//cout<<"---------------------------------1"<<endl;
			read(w);
			
			if (YuJuBiao() > 0)
			{   //cout<<"---------------------------------2"<<endl;
				if (w.token == LA.SearchKt("end"))
				{ //cout<<"---------------------------------3"<<endl;
				/*	//pos == SMQ.tokenlen||SEM.top().type==SMQ.proc_type  SEM.size()!=0&&SEM.top().pointer==0
					if (pos == LA.GetTokenLen())//最后一个end和与procedure对应的end才生成(end,program, , )
					{
						SYN.push(w);//语义0       //////////////////////////////////////////???
					//	Produce_FunBound();//语义4       ///////////////////////
					}*/
					read(w);
					return 1;

				}
				else
				{
					//system("cls"); 
					cout << "复合语句缺少end！" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				//system("cls"); 
					cout << "复合语句中的语句错误！" << endl; system("pause"); exit(0);
				return -1;
		}
		else
		{
			//system("cls"); 
			cout << "复合语句缺少begin！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

int  SyntexAnalysis::LeiXing()
	{
		if (w.token == LA.SearchKt("integer"))
			return 0;
		else
			if (w.token == LA.SearchKt("real"))
				return 1;
			else
				if (w.token == LA.SearchKt("char"))
					return 2;
				else
					return -1;
	}

	//递归下降子程序——标识符表
int SyntexAnalysis::BiaoZhiFuBiao()
	{
		if (w.token== 0)
		{
		/*	var_num++;
			SEM.push(w);//语义2*/
			read(w);
			// cout<<"我进来了"<<LA.SearchPt(",")<<"/"<<w.token;
			if (w.token == LA.SearchPt(","))
			{ //  cout<<"我进来了";
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
			//system("cls"); 
			cout << "标识符名称不合法！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//递归下降子程序——语句表
	int SyntexAnalysis::YuJuBiao()
	{
		//cout<<"---------------------------------4"<<endl;
		if (YuJu() > 0)
		{   //cout<<"---------------------------------5"<<endl;
		//cout<<w.token <<LA.SearchPt(";")<<endl;
			if (w.token == LA.SearchPt(";"))
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
	int SyntexAnalysis::YuJu()
	{ // cout<<"---------------------------------6"<<endl;
		if (FuZhiYuJu() > 0 || TiaoJianYuJu() > 0 || XunHuanYuJu() > 0 || DiaoYongYuJu() > 0)
			return 1;
		else
			return -1;
	}

	//递归下降子程序——赋值语句
	int SyntexAnalysis::FuZhiYuJu()
	{
		if (w.token == 0)
		{
		/*	SEM.push(w);*/
			read(w);
		//	cout<<w.token<<"进入复制语句"<<LA.SearchKt(":=");
			if (w.token == LA.SearchPt(":="))
			{
			/*	SYN.push(w);*/
				read(w);
				if (SuanShuBiaoDaShi() > 0)
				{
			//		Produce_Asign();//语义6                     ???
				//	read(w);
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
	int SyntexAnalysis::TiaoJianYuJu()
	{
		int thenpos, elsepos, thengoto, elsegoto;//地址回填用
		if (w.token == LA.SearchKt("if"))
		{
			read(w);
			if (TiaoJian() > 0)
			{
				if (w.token == LA.SearchKt("then"))
				{
				/*	SYN.push(w);//语义0
			//////		thenpos = Produce_Then();//语义8                ??????????????????*/
					read(w);
					if (YuJu() > 0 || FuHeYuJu() > 0)
					{    // cout<<"w jin lai le ";
						if (w.token == LA.SearchKt("else"))
						{
						/*	SYN.push(w);//语义0
				//////			elsepos = Produce_Else();// 语义8                ????
							thengoto = elsepos + 1;*/
							read(w);
							if (YuJu() > 0 || FuHeYuJu() > 0)
							{
							/*	elsegoto = Produce_IfEnd();//语义10
								//地址回填
								(*(SiYuanShi.begin() + thenpos)).res.type = 2;
								(*(SiYuanShi.begin() + thenpos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(thengoto);
								(*(SiYuanShi.begin() + thenpos)).res.belongFHB = curFHB;
								(*(SiYuanShi.begin() + elsepos)).res.type = 2;
								(*(SiYuanShi.begin() + elsepos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(elsegoto);
								(*(SiYuanShi.begin() + elsepos)).res.belongFHB = curFHB;*/
								return 1;
							}
							else
								return -1;
						}
						else
						{
						/*	thengoto = Produce_IfEnd();//语义10
							(*(SiYuanShi.begin() + thenpos)).res.type = 2;
							(*(SiYuanShi.begin() + thenpos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(thengoto);
							(*(SiYuanShi.begin() + thenpos)).res.belongFHB = curFHB;*/
							return 1;
						}
					}
					else
						return -1;

				}
				else
				{
					//system("cls"); 
					cout << "条件语句缺少then！" << endl; system("pause"); exit(0);
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
	int SyntexAnalysis::TiaoJian()
	{
		if (SuanShuBiaoDaShi() > 0)
		{
			if (GuanXiFu() > 0)
			{
				if (SuanShuBiaoDaShi() > 0)
				{
				/*	Produce_BoolEXP();//语义7*/
					
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
	int SyntexAnalysis::GuanXiFu()
	{
		//if (w.token >= LA.SearchPt(">") && w.token <= LA.SearchPt("!="))
		
		if (w.token == LA.SearchPt(">") || w.token == LA.SearchPt("!=")|| w.token == LA.SearchPt("==")|| w.token == LA.SearchPt(">")|| w.token == LA.SearchPt(">=")|| w.token == LA.SearchPt("<="))
		{
		/*	SYN.push(w);//语义0*/
			read(w);
			return 1;
		}
		else
		{
			//system("cls"); 
			cout << "关系符错误！" << endl; system("pause"); exit(0);
			return -1;
		}

	}

	//递归下降子程序——循环语句
	int SyntexAnalysis::XunHuanYuJu()
	{
		int dopos, whendpos, dogoto, whendgoto;//回填用
		if (w.token == LA.SearchKt("while"))
		{
			/*SYN.push(w);//语义0
			whendgoto = Produce_While();//语义11*/
			read(w);
			if (TiaoJian() > 0)
			{
				if (w.token == LA.SearchKt("do"))
				{
				/*	SYN.push(w);//语义0
					dopos = Produce_Do();//语义12*/
					read(w);
					if (YuJu() > 0 || FuHeYuJu() > 0)
					{
						/*whendpos = Produce_WhEnd();//语义13
						dogoto = whendpos + 1;
						//地址回填
						(*(SiYuanShi.begin() + dopos)).res.type = 2;
						(*(SiYuanShi.begin() + dopos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(dogoto);
						(*(SiYuanShi.begin() + dopos)).res.belongFHB = curFHB;
						(*(SiYuanShi.begin() + whendpos)).res.type = 2;
						(*(SiYuanShi.begin() + whendpos)).res.pointer = SMQ.FHB[curFHB].InsertCONSL(whendgoto);
						(*(SiYuanShi.begin() + dopos)).res.belongFHB = curFHB;*/
						return 1;
					}
					else
						return -1;
				}
				else
				{
					//system("cls");
					cout << "循环语句缺少do！" << endl; system("pause"); exit(0);
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
	int SyntexAnalysis::DiaoYongYuJu()
	{
		if (w.token == LA.SearchKt("call"))
		{
			read(w);
			if (w.token == 0)
			{
				read(w);
				if (w.token == LA.SearchPt("("))
				{
					read(w);	
					if(ShiCanLieBiao()>0) {
					//	cout<<"ShiCanLieBiao success";

						if (w.token == LA.SearchPt(")"))
					{
				
						read(w);
						return 1;
					}
					else{
					//system("cls"); 
					cout << "cuwu4！" << endl; system("pause"); exit(0);
					return -1;
					}
					
					}else{
					//system("cls"); 
					cout << "cuwu4！" << endl; system("pause"); exit(0);
					return -1;
					}
				}else{
					//system("cls"); 
					cout << "cuwu4！" << endl; system("pause"); exit(0);
					return -1;
					}
			}else{
					//system("cls"); 
					cout << "cuwu4！" << endl; system("pause"); exit(0);
					return -1;
					}
		}
			return -1;	
		
	}
	int SyntexAnalysis::ShiCanLieBiao(){
		if(SuanShuBiaoDaShi()>0){
			if (w.token == LA.SearchPt(",")){
				read(w);
				
				if(ShiCanLieBiao()>0){
					
					return 1;
				}
			}else{
				
		//	cout << "参数，缺少！" << endl; system("pause"); exit(0);
			return 1;			
			}
		}else{
			return -1;		
		}

	
	}
	//递归下降子程序——算术表达式
	int SyntexAnalysis::SuanShuBiaoDaShi()
	{
		
		if (E() > 0)
			return 1;
		else
		{
			//system("cls");
			cout << "算术表达式错误！" << endl; system("pause"); exit(0);
			return -1;
		}
		if (w.token == LA.SearchPt(";"))
		{
			read(w);
			return 1;
		}
		else
		{
			//system("cls");
			cout << "算术表达式应以；结束！" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	int SyntexAnalysis::E()
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

	int SyntexAnalysis::E1()
	{
		if (w.token == LA.SearchPt("+") || w.token == LA.SearchPt("-"))
		{
		/*	SYN.push(w);//语义0*/
			read(w);
			if (T() > 0)
			{
			/*	Produce_EXP();//语义7*/
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

	int SyntexAnalysis::T()
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

	int SyntexAnalysis::T1()
	{
		if (w.token == LA.SearchPt("*") || w.token == LA.SearchPt("/"))
		{
		/*	SYN.push(w);//语义0*/
			read(w);
			if (F() > 0)
			{
			/*	Produce_EXP();//语义7*/
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

	int SyntexAnalysis::F()
	{
		if (w.token== 1 || w.token == 0 || w.token == 3)
		{
		/*	SEM.push(w);//语义5*/
			read(w);
			return 1;
		}
		else
		{
			if (w.token == LA.SearchPt("("))
			{
				read(w);
				if (E() > 0)
				{
					if (w.token == LA.SearchPt(")"))
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


















/*
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

	*/

#endif