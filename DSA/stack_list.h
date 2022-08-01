#pragma once

#include "list.hpp"






//#include "Vector/Vector.h" //������Ϊ���࣬������ջģ����
template <typename T> class Stack : public List<T> { //����������/ĩ����Ϊջ��/��
public: //ԭ�нӿ�һ������
	void push(T const& e) { this->insertAsLast(e); } //��ջ����Ч�ڽ���Ԫ����Ϊ������ĩԪ�ز���
	T pop() { return this->remove(this->last()); } //��ջ����Ч��ɾ��������ĩԪ��
	T& top() { return this->last()->data; } //ȡ����ֱ�ӷ���������ĩԪ��
};