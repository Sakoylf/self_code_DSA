#pragma once
#include<iostream>
#include<algorithm>
#include "stack_vector.h"
using namespace std;

/***************************************************
				ջ�����
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

bool paren(const char exp[], int lo, int hi)   //exp����ֻ������
{
	Stack<char> S;
	for (int i = lo; i < hi; i++)
	{
		switch (exp[i]) {
		case '(': case'[':case'{': S.push(exp[i]); break;
		case')': if (S.empty() || S.pop() != '(') return false; break;
		case']':if (S.empty() || S.pop() != '[') return false; break;
		case'}':if (S.empty() || S.pop() != '{') return false; break;
		default:break;//�������ַ�һ�ɺ���
		}
	}
	return S.empty();
}

//void append(char* rpn, double opnd) { //������������RPNĩβ
//    char buf[64];
//    if ((int)opnd < opnd) sprintf(buf, "%6.2f \0", opnd); //�����ʽ����
//    else                       sprintf(buf, "%d \0", (int)opnd); //������ʽ
//    strcat(rpn, buf); //RPN�ӳ�
//}
//void append(char* rpn, char optr) { //�����������RPNĩβ
//    int n = strlen(rpn); //RPN��ǰ���ȣ���'\0'��β������n + 1��
//    sprintf(rpn + n, "%c \0", optr); //����ָ���������
//
//}
//
//double calcu(char op, double b) { //ִ��һԪ����
//    switch (op) {
//       case '!': return (double) facI((int)b); //Ŀǰ���н׳ˣ����մ˷�ʽ���
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
 //#define N_OPTR 9 //���������
 //typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //���������
 ////�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

 //const char pri[N_OPTR][N_OPTR] = { //��������ȵȼ� [ջ��] [��ǰ]
 //   /*              |-------------------- �� ǰ �� �� �� --------------------| */
 //   /*              +      -      *      /      ^      !      (      )      \0 */
 //   /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
 //   /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
 //   /* ջ  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
 //   /* ��  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
 //   /* ��  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
 //   /* ��  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
 //   /* ��  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
 //   /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
 //   /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
 //};
 // 
//Operator optr2rank(char op) { //�������ת������
//    switch (op) {
//       case '+': return ADD; //��
//       case '-': return SUB; //��
//       case '*': return MUL; //��
//       case '/': return DIV; //��
//       case '^': return POW; //�˷�
//       case '!': return FAC; //�׳�
//       case '(': return L_P; //������
//       case ')': return R_P; //������
//       case '\0': return EOE; //��ʼ������ֹ��
//       default: exit(-1); //δ֪�����
//					  
//	}
//	
//}
// char orderBetween(char op1, char op2) //�Ƚ����������֮������ȼ�
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