#pragma once
#include "list.hpp"

template<typename T>
class Queue :public List<T>
{
public:
	void enqueue(T const& e) this->insertAsLast(e);//����
	T dequeue() return this->remove(this->last());//����
	T& front() return this->first()->data;
};