#include<iostream>
using namespace std;
#include <cstring>
#include"stack.h"
#include"vector.hpp"

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
		switch(exp[i]) {
		case '(': case'[':case'{': S.push(exp[i]); break;
		case')': if (S.empty() || S.pop() != '(') return false; break;
		case']':if (S.empty() || S.pop() != '[') return false; break;
		case'}':if (S.empty() || S.pop() != '{') return false; break;
		default:break;//�������ַ�һ�ɺ���
		}
	}
	return S.empty();
}



/***************************************************
				
***************************************************/
int main()
{
	


	__int64 n = 20;
	int base = 2;;
	Stack<char> s;
	convert(s, n, base);
	while (s.size() != 0)
	{
		cout << s.pop() ;
	}
	cout << endl;
	  //���pָ����ַ�����
	
	
	//B = new int[10];
	
	system("pause");

	return 0;
}