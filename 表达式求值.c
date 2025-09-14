#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static int i=0;//创建静态变量否则不好在Getnum函数里传数据
typedef struct{
	int *base;
	int *top;
	int size;
}OPND;//数字栈
typedef struct{
	char *base;
	char *top;
	int size;
}OPTR;//符号栈
void InitOPND(OPND *d){
	d->size=100;
	d->base =(int *)malloc(d->size*sizeof(int));
	d->top=d->base;
}
void InitOPTR(OPTR *r){
	r->size=100;
	r->base=(char *)malloc(r->size*sizeof(char));
	r->top=r->base ;
}
void PushOPND(OPND *d,int m){
	*d->top++=m;
}
void PushOPTR(OPTR *r,char ch){
	*r->top++=ch;
}
void PopOPND(OPND *d,int *a){
	if(d->top!=d->base)
	*a=*--d->top;
}
void PopOPTR(OPTR *r,char *c){
	if(r->top!=r->base )
	*c=*--r->top;
}
int GetTopND(OPND d){
	return *(d.top-1) ;
}
char GetTopTR(OPTR r){
	return *(r.top-1);
}
	
//int convertch(char a)
//	{ char ch[]={'+','-','*','/','^','(',')','='};
//		int n=0; 
//	while(ch[n]!='\0'&&ch[n]!=a)  
//		{ n++; } 
//	if(ch[n]==a){ return i; } 
//		else{ return -1; } 
//}
char compare(char a,char b){//查表比运算顺序
	int m,n;
	char ch[]={'+','-','*','/','^','(',')','='};
	char COMPARE[8][8]={ 
	{'>','>','<','<','<','<','>','>'}, 
	{'>','>','<','<','<','<','>','>'},
	{'>','>','>','>','<','<','>','>'}, 
	{'>','>','>','>','<','<','>','>'}, 
	{'>','>','>','>','<','>','>','>'}, 
	{'<','<','<','<','<','<','=','?'}, 
	{'>','>','>','>','>','?','>','>'}, 
	{'<','<','<','<','<','<','?','='}, 
	};
	for(m=0;m<8;m++){
		if(a==ch[m]) break;
	}
	for(n=0;n<8;n++){
		if(b==ch[n]) break;
	}
	return COMPARE[m][n]; }
int operate (int a,char c,int b){//对于正常的运算
	int res=0;
	switch(c){
		case '+':res=a+b;break;
		case'-':res=a-b;break;
		case'*':res=a*b;break;
		case'/':res=a/b;break;
	}
	return res;
}
int Getnum(char ch[], int j)//把数字转化回来
{
	int num=ch[j]-48;
	j++;
	while(ch[j]>='0'&&ch[j]<='9')
		num=num*10+ch[j++]-48; 
	i=j;
	return num;
}
int In(char c){//判断是否是运算符
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='\n'||c=='=')
	return 1;
	else return 0;
}
int main(){
	OPND d;
	OPTR r;
	InitOPND(&d);
	InitOPTR(&r);
	PushOPTR(&r,'=');
	char ch[100],theta,x;
	int a,b,num;
	gets(ch);
	while(ch[i]!='='||GetTopTR(r)!='='){
		if(!In(ch[i]))//判断数字
		{
			num=Getnum(ch,i);
			PushOPND(&d,num);
		}
		else{
			switch(compare(GetTopTR(r),ch[i])){
				case '<':
					PushOPTR(&r,ch[i]);
					i++;
					break;
				case'=':
					PopOPTR(&r,&x);//把栈顶弹出同时跳过当前的符号
					i++;
					break;
				case'>':
					PopOPND(&d,&a);
					PopOPND(&d,&b);
					PopOPTR(&r,&theta);
					PushOPND(&d,operate(b,theta,a));
					break;
			}
		}
	}
	printf("%d\n",GetTopND(d));
	return 0;
}