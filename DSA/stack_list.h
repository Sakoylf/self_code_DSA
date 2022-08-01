#pragma once

#include "list.hpp"






//#include "Vector/Vector.h" //以向量为基类，派生出栈模板类
template <typename T> class Stack : public List<T> { //将向量的首/末端作为栈底/顶
public: //原有接口一概沿用
	void push(T const& e) { this->insertAsLast(e); } //入栈：等效于将新元素作为向量的末元素插入
	T pop() { return this->remove(this->last()); } //出栈：等效于删除向量的末元素
	T& top() { return this->last()->data; } //取顶：直接返回向量的末元素
};