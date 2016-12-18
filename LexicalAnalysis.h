#ifndef _LEXICALANALYSIS_H_
#define _LEXICALANALYSIS_H_
#define iTAndKT 20
#define cT 21
#define sT 22
#define CT 23
#define PT 24
#include "Main.h"
class LexicalAnalysis{
private:
struct Token Token_T[300];
struct Token ptCache[150];
struct Token ktCache[150];
int Tokenlen;      //Token的长度
int pt_Tokenlen;		//pt_Tokenlen的长度
int kt_Tokenlen;		//kt_Tokenlen的长度
int flag;		//输入程序的序号
int id_kt;
int id_pt;
string it[100];			//it表的内容
string ct[100];			//ct表的内容
int CT_Table[100];
int  id_it;
int id_ct;
int id_CT;
bool IsEof;

int TxtToSring(char* a);
bool JudgeKt(string Word);
bool JudgePt(string str);
int kt_cache(string State);
int pt_cache(string State);
void GetToken(int Token_id,string State);
char GetNextChar(char *a);
void GetBackChar();
bool IsNumber(char c);
bool IsLetter(char a);
void DFA(char *Pro);
public:
int SearchKt(string Word);
int SearchPt(string str);
int Scanning();
void print_Token();
LexicalAnalysis(){
 Tokenlen = 0;      //Token的长度
 pt_Tokenlen=0;		//pt_Tokenlen的长度
 kt_Tokenlen=0;		//kt_Tokenlen的长度
 flag=3;		//输入程序的序号
 id_kt=4;
 id_pt=24;
  id_it=0;
 id_ct=0;
 id_CT=0;
 IsEof=1;
}
};



int LexicalAnalysis::TxtToSring(char* a){
	FILE *fp;
 if((fp=fopen(".//pro.txt","rt"))==NULL){
       printf("\nCannot open file strike any key exit!");
	   getch();
	   exit(1);
       return 0;
 }
	   fseek(fp, SEEK_SET,0);
	   fread(a,1,800,fp);
		fclose(fp);
		return 1;
 }

//判断字符在kt表的位置
int LexicalAnalysis::SearchKt(string Word){
	for(int i=0;i<20;i++){
		if(strcmp(kt[i],Word.c_str())==0){	 
			return id_kt+i;		 
		}
	}
	return -1;
}

//判断字符在pt表d的位置
int LexicalAnalysis::SearchPt(string str){
for(int i=0;i<19;i++){
	if(strcmp(pt[i],str.c_str())==0){
		return id_pt+i;		  
		}
	}
	return -1;
}

//判断字符是否在kt表
bool LexicalAnalysis::JudgeKt(string Word){
	for(int i=0;i<20;i++){
		if(strcmp(kt[i],Word.c_str())==0){	 
		  return 1;		 
		}
	}
	return 0;
}
//判断字符是否在pt表
bool LexicalAnalysis::JudgePt(string str){
for(int i=0;i<19;i++){
	if(strcmp(pt[i],str.c_str())==0){
		  return 1;		  
		}
	}
	return 0;
}
//建立当前阶段已有的kt的缓存数据
int LexicalAnalysis::kt_cache(string State){
	for(int i=0;i<kt_Tokenlen;i++){
		if(strcmp(State.c_str(),ktCache[i].state.c_str())==0){
			return ktCache[i].token;		
		}
	}
	return 0;
}
//建立当前阶段已有的pt的缓存数据
int LexicalAnalysis::pt_cache(string State){
	for(int i=0;i<pt_Tokenlen;i++){
		if(strcmp(ptCache[i].state.c_str(),State.c_str())==0){	  
		  return  ptCache[i].token;
		}	
	}
	return 0;
}

void LexicalAnalysis::GetToken(int Token_id,string State){
	if(Token_id==4){
		if(kt_cache(State)!=0){	
		Token_T[Tokenlen].token=kt_cache(State);
		Token_T[Tokenlen].state=State;
		Token_T[Tokenlen].pointer=-1;/**/
		Tokenlen++;
		}else{	
			Token_T[Tokenlen].token=id_kt; 
			Token_T[Tokenlen].state=State;
			Token_T[Tokenlen].pointer=-1;/**/
			ktCache[kt_Tokenlen].token =id_kt;
			ktCache[kt_Tokenlen].state =State;
			ktCache[kt_Tokenlen].pointer=-1;/**/
			id_kt++;
			Tokenlen++;
			kt_Tokenlen++;
			}
	}else if(Token_id==5){
		if(pt_cache(State)!=0){
		Token_T[Tokenlen].token=pt_cache(State);
		Token_T[Tokenlen].state=State;
		Token_T[Tokenlen].pointer=-1;/**/
		Tokenlen++;
		}else if(pt_cache(State)==0){
				Token_T[Tokenlen].token=id_pt;  
				Token_T[Tokenlen].state=State;  
				Token_T[Tokenlen].pointer=-1;/**/
				ptCache[pt_Tokenlen].token =id_pt;
				ptCache[pt_Tokenlen].state =State;
				ptCache[pt_Tokenlen].pointer=-1;/**/
				id_pt++;
				Tokenlen++;
				pt_Tokenlen++;
				}	
	}else if(Token_id==0){
		Token_T[Tokenlen].token=0;
		Token_T[Tokenlen].state=State;
		Token_T[Tokenlen].pointer=id_it;
		it[id_it].assign(State);
		id_it++;
		Tokenlen++;
	}else if(Token_id==1){
		Token_T[Tokenlen].token=1;
		Token_T[Tokenlen].state=State;
		Token_T[Tokenlen].pointer=id_ct;
		it[id_ct].assign(State);
		id_ct++;
		Tokenlen++;
	}else if(Token_id==2){
		Token_T[Tokenlen].token=2;
		Token_T[Tokenlen].state=State;
		Token_T[Tokenlen].pointer=id_ct;
		it[id_ct].assign(State);
		id_ct++;
		Tokenlen++;
	}else if(Token_id==3){
		Token_T[Tokenlen].token=3;
		Token_T[Tokenlen].state=State;	
		Token_T[Tokenlen].pointer=id_CT;
		it[id_CT].assign(State);
		id_CT++;
		Tokenlen++;
	}

}


//获得下一个字符
char LexicalAnalysis::GetNextChar(char *a){
	
	char ch;
	ch=a[flag];
	if(ch=='\0'){
	
	 return ch;
	}
	else{
	
		flag++;
	return ch;
	}
}
//退倒上一个字符
void LexicalAnalysis::GetBackChar(){
      flag--;
}

//判断该字符是否为数字
bool LexicalAnalysis::IsNumber(char c){
	if(c>=48&&c<=58){
	   return 1;
	}else
	{
	return 0;
	}
}
//判断该字符是否为英文字母
bool LexicalAnalysis::IsLetter(char a){
	if(isalpha(a)==1||isalpha(a)==2){
	return 1;
	}
	else
		return 0;
}

//词法分析的自动机
void LexicalAnalysis::DFA(char *Pro){
		
	bool IsSave;
	char c;
	int Token_id=0;	
	string  CurrentToken="";
	string  TokenStr="";
	int CurrentState=1;
	while(CurrentState!=0){
		c=GetNextChar(Pro);
		if(c=='\0')
		{
			IsEof=0;
			return;
		}
		IsSave=true;
	    switch(CurrentState){
		case 1:
			if(IsNumber(c)){
				CurrentState=3;
			}else if(IsLetter(c)){
				CurrentState=2;
			}else if(c==' '||c=='\t'||c=='\n'){
				IsSave=false;
			}else if(c=='\''){
                CurrentState=9;
			}else if(c=='\"'){
                CurrentState=11;
			}else if(c=='>'){
                CurrentState=4;
			}else if(c=='<'){
                CurrentState=5;
			}else if(c=='='){
                CurrentState=6;
			}else if(c==':'){
                CurrentState=50;
			}else{
                CurrentState=18;
			}
			break;
        case 2:
            if(!IsLetter(c)&&!IsNumber(c)){
			
                CurrentState=20;
                GetBackChar();
                IsSave=false;			
            }
			break;

		case 50:
			 if(c=='='){			
                CurrentState=6;		
            }

			break;
	 	case iTAndKT:
			
			if(JudgeKt(TokenStr)){
				Token_id=4;
				
			}
			else{
				
			  Token_id=0;
			}
			CurrentState=0;
			 GetBackChar();
             IsSave=false;
			break;
			 
        case 3:
            if(c=='.'){
                 CurrentState=8;
            }
            else if(!IsNumber(c)&&c!='.'){
                CurrentState=23;
                GetBackChar();
                IsSave=false;
            }
			break;
        case 8:
            if(IsNumber(c)){
                CurrentState=7;
				
            }
			break;
        case 7:
            if(!IsNumber(c)){
                CurrentState=23;
                GetBackChar();
                IsSave=false;
            }
			break;
		case CT:
			
			Token_id=3;
			CurrentState=0;
		    GetBackChar();
            IsSave=false;
			break;			 
        case 9:
            if(IsLetter(c)){
                CurrentState=10;			
            }
			break;
        case 10:
            if(c=='\''){
                CurrentState=16;				
            }
			break;
        case 16:           
                CurrentState=cT;
                GetBackChar();
                IsSave=false;
				break;
		case cT:
			
			Token_id=1;
			CurrentState=0;
		    GetBackChar();
            IsSave=false;
			break;
        case 11:
            if(IsLetter(c)){
                CurrentState=12;			
            }
			break;
        case 12:
            if(c=='\"'){
                CurrentState=17;
            }else if(IsLetter(c)){
                CurrentState=12;
            }
			break;
        case 17:          
			CurrentState=sT;
            GetBackChar();
            IsSave=false;
			break;
		case sT:
			Token_id=2;
			CurrentState=0;
		    GetBackChar();
            IsSave=false;
			break;
         case 4:
            if(c=='='){
                CurrentState=13;
            }else{
			   CurrentState=PT;
               GetBackChar();
               IsSave=false;
            }
			break;
         case 13:
            
               CurrentState=PT;
               GetBackChar();
               IsSave=false;
               break;

		 case PT:
			 if(JudgePt(TokenStr)){
				Token_id=5;			
				}
			 CurrentState=0;
			 GetBackChar();
             IsSave=false;
			 break;

         case 5:
             if(c=='='){
                CurrentState=14;
             }else {
              CurrentState=PT;
              GetBackChar();
              IsSave=false;
             }
			 break;
         case 14:
               CurrentState=PT;
               GetBackChar();
               IsSave=false;
               break;
         case 6:
             if(c=='='){
                CurrentState=15;
             }
             else{
              CurrentState=PT;
              GetBackChar();
              IsSave=false;
             }
			 break;
         case 15:
              CurrentState=PT;
              GetBackChar();
              IsSave=false;
              break;
         case 18:
			 CurrentState=PT;
             GetBackChar();
             IsSave=false;
             break;


        default:
            cout<<"error"<<endl;
            break;
	    }
        if(IsSave){
			TokenStr.push_back(c);
        }	
		if(CurrentState==0){
			CurrentToken=TokenStr;
			GetToken(Token_id,CurrentToken);
		       }	
	}
}

int LexicalAnalysis::Scanning(){
	char Pro[800]={0};
	TxtToSring(Pro);
	while(IsEof){
    DFA(Pro);	
	}
   return 1;
}

void LexicalAnalysis::print_Token(){
	int a=Tokenlen;
 int i=0;
 while(a){
	 cout<<"("<<Token_T[i].token<<","<<Token_T[i].pointer<<")"<<"     ->        "<<Token_T[i].state<<endl;
	 a--;
	 i++;
 }
}








#endif