#pragma once
#include "list.hpp"

template<typename T>
class Queue :public List<T>
{
public:
	void enqueue(T const& e) this->insertAsLast(e);//入列
	T dequeue() return this->remove(this->last());//出列
	T& front() return this->first()->data;
};