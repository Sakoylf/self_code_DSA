#pragma once

class Fib {
public:
	Fib(int n)
	{
		f = 1;
		g = 0;
		while (g < n) next();
	}
	int get()
	{
		return g;
	}
	int next()
	{
		g += f;
		f = g - f;
		return g;
	}
	int prev()
	{
		f = g - f;
		g -= f;
		return g;
	}
private:
	int f, g;
};