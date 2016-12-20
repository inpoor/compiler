#ifndef _SYNTEXANALYSIS_H_
#define _SYNTEXANALYSIS_H_
#include "Main.h"


class  LexicalAnalysis;

class SyntexAnalysis{
private:
	LexicalAnalysis LA;
	int pos;//��ǰ�ǵ�pos��token����token����������
	int var_num;
	int addr;
	Token w, e;//��ʱ�洢��ǰ������token
	stack<Token>SEM;//����ջ
	stack<Token>SYN;//���ջ




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
	
	//�﷨�������
/*	int SyntexAnalysis::Parser()
	{  
		read(w);
		if (analysis() > 0)
			return 1;
		else
			return -1;
	}
	*/
	//�ݹ��½��ӳ��򡪡�����
	int SyntexAnalysis::analysis()
	{
		if (w.token == LA.SearchKt("program"))
		{
		/*	SYN.push(w);//����0*/
			read(w);
			if (w.token == 0)
			{
			/*	SEM.push(w); SEM.push(w);// TianSYNBL((TVAL_TYPE)-1, p, -1, w.pointer);	Produce_FunBound();//����1*/
				read(w);
				if (FenChengXu() > 0)
					return 1;
				else
					return -1;
			}
			else
			{
			//	system("cls");
				cout << "���������Ϸ���" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
		{
		//	system("cls"); 
			cout << "�Ҳ��������program��ڣ�" << endl; system("pause"); exit(0);
			return -1;
		}
	}
		//�ݹ��½��ӳ��򡪡��ֳ���
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
	
		//�ݹ��½��ӳ��򡪡�����
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
			SYN.push(w);//����0*/
			read(w);
			if (w.token == 0)
			{
				/*int pfinflen = SMQ.FHB[curFHB].InsertPFINFL(level);//�����Ϣ��level
				TianSYNBL((TVAL_TYPE)-1, p, -1, w.pointer);
				SEM.push(w); SEM.push(w);//����2
				Produce_ProcBound();*/

				read(w);
				if (w.token == LA.SearchPt("("))
				{
					read(w);
					if (XingCanLieBiao() > 0)
					{
					/*	TianPFINFL(-2, -2, xingcanNUM, -2, 1, pfinflen);//�����ϢFN��PARAM
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
									//SYN.push(endtmp);//����0
									if (w.token == LA.SearchKt("endp")||w.token == LA.SearchKt("endf"))
									{
									/*	SYN.push(w);*/
										read(w);
									}
									else
									{
									//	system("cls"); 
										cout << "����Ӧ��endp��β��" << endl; system("pause"); exit(0);
										return -1;
									}
							/*		Produce_FunBound();//����4
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
							cout << "��������ȱ�������ţ�" << endl; system("pause"); exit(0);
							return -1;
						}
					}
					else
						return -1;
				}
				else
				{
					//system("cls"); 
					cout << "��������ȱ�������ţ�" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
			//	system("cls");
				cout << "���������Ϸ���" << endl; system("pause"); exit(0);
				return -1;
			}
		}
		else
			return -1;
	}

		//�ݹ��½��ӳ��򡪡��β��б�
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

	//�ݹ��½��ӳ��򡪡��β�˵��
	int SyntexAnalysis::XingCanShuoMing()
	{
		if (w.token == LA.SearchKt("var"))
		{
		/*	xingcanNUM++;*/
			read(w);
			if (w.token == 0) /*��ʶ��*/
			{
			/*	SEM.push(w);//����2*/
				read(w);
				if (w.token == LA.SearchPt(":"))
				{
					read(w);
					int type;
					if ((type = LeiXing()) != -1)
					{
					/*	w = SEM.top(); SEM.pop();//����15
						TianSYNBL((TVAL_TYPE)type, vn, addr, w.pointer);
						addr += 2;//�����β�Ϊ+2*/
						
						read(w);
						return 1;
					}
					else
					{
						//system("cls"); 
						cout << "�β�����δ֪��" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					//system("cls"); 
					cout << "�β�Ӧ����:�������ͣ�" << endl; system("pause"); exit(0);
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
				SEM.push(w);//����2*/
				read(w);
				if (w.token == LA.SearchPt(":"))
				{
					read(w);
					TVAL_TYPE type;
					if ((type = (TVAL_TYPE)LeiXing()) != -1)
					{
				/*		w = SEM.top(); SEM.pop();//����5
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
						cout << "�β�����δ֪��" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
				//	system("cls"); 
					cout << "�β�Ӧ����:�������ͣ�" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				
				return 1;
			}
		}
	}



	//�ݹ��½��ӳ��򡪡�����˵��
	int SyntexAnalysis::ChangLiangShuoMing()
	{
		if (w.token == LA.SearchKt("const"))
		{
			read(w);
			if (w.token == 0)
			{
			/*	SEM.push(w);//����2*/
				read(w);
				if (w.token == LA.SearchPt("="))
				{
					read(w);
					if (w.token == 3)
					{
					/*	e = SEM.top(); SEM.pop();//����14
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
						cout << "����Ӧ��Ϊ���֣�" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					//system("cls"); 
					cout << "��������Ӧ��=�ţ�" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
			{
				//system("cls"); 
				cout << "���������Ϸ���" << endl; system("pause"); exit(0);
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
			/*var_num = 0;//����������*/
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
						}//����3*/

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
						cout << "��������δ֪��" << endl; system("pause"); exit(0);
						return -1;
					}
				}
				else
				{
					//system("cls"); 
					cout << "��������δ������" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				return -1;
		}
		else
		{
			//system("cls");
			cout << "��������ȱ��var��" << endl; system("pause"); exit(0);
			return -1;
		}
	}

		//�ݹ��½��ӳ��򡪡��������
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
					if (pos == LA.GetTokenLen())//���һ��end����procedure��Ӧ��end������(end,program, , )
					{
						SYN.push(w);//����0       //////////////////////////////////////////???
					//	Produce_FunBound();//����4       ///////////////////////
					}*/
					read(w);
					return 1;

				}
				else
				{
					//system("cls"); 
					cout << "�������ȱ��end��" << endl; system("pause"); exit(0);
					return -1;
				}
			}
			else
				//system("cls"); 
					cout << "��������е�������" << endl; system("pause"); exit(0);
				return -1;
		}
		else
		{
			//system("cls"); 
			cout << "�������ȱ��begin��" << endl; system("pause"); exit(0);
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

	//�ݹ��½��ӳ��򡪡���ʶ����
int SyntexAnalysis::BiaoZhiFuBiao()
	{
		if (w.token== 0)
		{
		/*	var_num++;
			SEM.push(w);//����2*/
			read(w);
			// cout<<"�ҽ�����"<<LA.SearchPt(",")<<"/"<<w.token;
			if (w.token == LA.SearchPt(","))
			{ //  cout<<"�ҽ�����";
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
			cout << "��ʶ�����Ʋ��Ϸ���" << endl; system("pause"); exit(0);
			return -1;
		}
	}

	//�ݹ��½��ӳ��򡪡�����
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

	//�ݹ��½��ӳ��򡪡����
	int SyntexAnalysis::YuJu()
	{ // cout<<"---------------------------------6"<<endl;
		if (FuZhiYuJu() > 0 || TiaoJianYuJu() > 0 || XunHuanYuJu() > 0 || DiaoYongYuJu() > 0)
			return 1;
		else
			return -1;
	}

	//�ݹ��½��ӳ��򡪡���ֵ���
	int SyntexAnalysis::FuZhiYuJu()
	{
		if (w.token == 0)
		{
		/*	SEM.push(w);*/
			read(w);
		//	cout<<w.token<<"���븴�����"<<LA.SearchKt(":=");
			if (w.token == LA.SearchPt(":="))
			{
			/*	SYN.push(w);*/
				read(w);
				if (SuanShuBiaoDaShi() > 0)
				{
			//		Produce_Asign();//����6                     ???
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

	//�ݹ��½��ӳ��򡪡��������
	int SyntexAnalysis::TiaoJianYuJu()
	{
		int thenpos, elsepos, thengoto, elsegoto;//��ַ������
		if (w.token == LA.SearchKt("if"))
		{
			read(w);
			if (TiaoJian() > 0)
			{
				if (w.token == LA.SearchKt("then"))
				{
				/*	SYN.push(w);//����0
			//////		thenpos = Produce_Then();//����8                ??????????????????*/
					read(w);
					if (YuJu() > 0 || FuHeYuJu() > 0)
					{    // cout<<"w jin lai le ";
						if (w.token == LA.SearchKt("else"))
						{
						/*	SYN.push(w);//����0
				//////			elsepos = Produce_Else();// ����8                ????
							thengoto = elsepos + 1;*/
							read(w);
							if (YuJu() > 0 || FuHeYuJu() > 0)
							{
							/*	elsegoto = Produce_IfEnd();//����10
								//��ַ����
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
						/*	thengoto = Produce_IfEnd();//����10
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
					cout << "�������ȱ��then��" << endl; system("pause"); exit(0);
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
	int SyntexAnalysis::TiaoJian()
	{
		if (SuanShuBiaoDaShi() > 0)
		{
			if (GuanXiFu() > 0)
			{
				if (SuanShuBiaoDaShi() > 0)
				{
				/*	Produce_BoolEXP();//����7*/
					
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
	int SyntexAnalysis::GuanXiFu()
	{
		//if (w.token >= LA.SearchPt(">") && w.token <= LA.SearchPt("!="))
		
		if (w.token == LA.SearchPt(">") || w.token == LA.SearchPt("!=")|| w.token == LA.SearchPt("==")|| w.token == LA.SearchPt(">")|| w.token == LA.SearchPt(">=")|| w.token == LA.SearchPt("<="))
		{
		/*	SYN.push(w);//����0*/
			read(w);
			return 1;
		}
		else
		{
			//system("cls"); 
			cout << "��ϵ������" << endl; system("pause"); exit(0);
			return -1;
		}

	}

	//�ݹ��½��ӳ��򡪡�ѭ�����
	int SyntexAnalysis::XunHuanYuJu()
	{
		int dopos, whendpos, dogoto, whendgoto;//������
		if (w.token == LA.SearchKt("while"))
		{
			/*SYN.push(w);//����0
			whendgoto = Produce_While();//����11*/
			read(w);
			if (TiaoJian() > 0)
			{
				if (w.token == LA.SearchKt("do"))
				{
				/*	SYN.push(w);//����0
					dopos = Produce_Do();//����12*/
					read(w);
					if (YuJu() > 0 || FuHeYuJu() > 0)
					{
						/*whendpos = Produce_WhEnd();//����13
						dogoto = whendpos + 1;
						//��ַ����
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
					cout << "ѭ�����ȱ��do��" << endl; system("pause"); exit(0);
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
					cout << "cuwu4��" << endl; system("pause"); exit(0);
					return -1;
					}
					
					}else{
					//system("cls"); 
					cout << "cuwu4��" << endl; system("pause"); exit(0);
					return -1;
					}
				}else{
					//system("cls"); 
					cout << "cuwu4��" << endl; system("pause"); exit(0);
					return -1;
					}
			}else{
					//system("cls"); 
					cout << "cuwu4��" << endl; system("pause"); exit(0);
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
				
		//	cout << "������ȱ�٣�" << endl; system("pause"); exit(0);
			return 1;			
			}
		}else{
			return -1;		
		}

	
	}
	//�ݹ��½��ӳ��򡪡��������ʽ
	int SyntexAnalysis::SuanShuBiaoDaShi()
	{
		
		if (E() > 0)
			return 1;
		else
		{
			//system("cls");
			cout << "�������ʽ����" << endl; system("pause"); exit(0);
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
			cout << "�������ʽӦ�ԣ�������" << endl; system("pause"); exit(0);
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
		/*	SYN.push(w);//����0*/
			read(w);
			if (T() > 0)
			{
			/*	Produce_EXP();//����7*/
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
		/*	SYN.push(w);//����0*/
			read(w);
			if (F() > 0)
			{
			/*	Produce_EXP();//����7*/
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
		/*	SEM.push(w);//����5*/
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

	*/

#endif