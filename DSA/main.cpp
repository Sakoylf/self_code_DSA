#include<iostream>
using namespace std;
#include <cstring>
#include"stack_vector.h"
#include"vector.hpp"
#include"stack_example.h"


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
	  //输出p指向的字符串！
	
	
	//B = new int[10];
	
	system("pause");

	return 0;
}