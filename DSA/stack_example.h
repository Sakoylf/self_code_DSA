#pragma once
#include<iostream>
#include<algorithm>
#include "stack_vector.h"
using namespace std;

/***************************************************
				栈与队列
***************************************************/
void convert(Stack<char>& S, __int64 n, int base)
{
	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while (0 < n)
	{
		S.push(digit[n % base]);
		n /= base;
	}

}

bool paren(const char exp[], int lo, int hi)   //exp里面只有括号
{
	Stack<char> S;
	for (int i = lo; i < hi; i++)
	{
		switch (exp[i]) {
		case '(': case'[':case'{': S.push(exp[i]); break;
		case')': if (S.empty() || S.pop() != '(') return false; break;
		case']':if (S.empty() || S.pop() != '[') return false; break;
		case'}':if (S.empty() || S.pop() != '{') return false; break;
		default:break;//非括号字符一律忽略
		}
	}
	return S.empty();
}

//void append(char* rpn, double opnd) { //将操作数接至RPN末尾
//    char buf[64];
//    if ((int)opnd < opnd) sprintf(buf, "%6.2f \0", opnd); //浮点格式，或
//    else                       sprintf(buf, "%d \0", (int)opnd); //整数格式
//    strcat(rpn, buf); //RPN加长
//}
//void append(char* rpn, char optr) { //将运算符接至RPN末尾
//    int n = strlen(rpn); //RPN当前长度（以'\0'结尾，长度n + 1）
//    sprintf(rpn + n, "%c \0", optr); //接入指定的运算符
//
//}
//
//double calcu(char op, double b) { //执行一元运算
//    switch (op) {
//       case '!': return (double) facI((int)b); //目前仅有阶乘，可照此方式添加
//       default: exit(-1);
//	}
//}
//
//void readNumber(char* & p, Stack<float> &stk)
//{
//	stk.push((float)(*p - '0'));
//	while (isdigit(*(++p)))
//	{
//		stk.push(stk.pop() * 10 + (*p - '0'));
//	}
//	if ('.' != *p) return;
//	float fraction = 1;
//	while (isdigit(*(++p)))
//	{
//		stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
//	}
//}
//
 //#define N_OPTR 9 //运算符总数
 //typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //运算符集合
 ////加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

 //const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
 //   /*              |-------------------- 当 前 运 算 符 --------------------| */
 //   /*              +      -      *      /      ^      !      (      )      \0 */
 //   /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
 //   /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
 //   /* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
 //   /* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
 //   /* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
 //   /* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
 //   /* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
 //   /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
 //   /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
 //};
 // 
//Operator optr2rank(char op) { //由运算符转译出编号
//    switch (op) {
//       case '+': return ADD; //加
//       case '-': return SUB; //减
//       case '*': return MUL; //乘
//       case '/': return DIV; //除
//       case '^': return POW; //乘方
//       case '!': return FAC; //阶乘
//       case '(': return L_P; //左括号
//       case ')': return R_P; //右括号
//       case '\0': return EOE; //起始符与终止符
//       default: exit(-1); //未知运算符
//					  
//	}
//	
//}
// char orderBetween(char op1, char op2) //比较两个运算符之间的优先级
// { return pri[optr2rank(op1)][optr2rank(op2)]; }
//
//
//float evaluate(char* S, char*& RPN)
//{
//	Stack<float> opnd; Stack<char> optr;
//	optr.push('\0');
//	while (!optr.empty())
//	{
//		if (isdigit(*S))
//		{
//			readNumber(S, opnd);
//			append(RPN, opnd.top());
//		}
//		else
//			switch (orderBetween(optr.top(), *S))
//			{
//			case '<':
//				optr.push(*S); S++; break;
//			case '=':
//				optr.pop(); S++; break;
//			case '>':
//				char op = optr.pop();
//				append(RPN, op)
//				if ('!' == op) opnd.push(calcu(op, opnd.pop()));
//				else
//				{
//					float p0pnd2 = opnd.pop(), p0pnd1 = opnd.pop();
//					opnd.push(calcu(p0pnd1, op, opnd2));
//				}
//				break;
//			}
//	}
//	return opnd.pop();
//}