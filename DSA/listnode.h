#pragma once
using Rank = int;
#include<iostream>

template<typename T> struct ListNode;

template<typename T> using ListNodePosi =  ListNode<T>*;

template<typename T>
struct ListNode
{
	T data;
	ListNodePosi<T> pred;
	ListNodePosi<T> succ;
	ListNode() {}
	ListNode(T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL)
		:data(e), pred(p), succ(s) {} //Ĭ�Ϲ�����

	ListNodePosi<T> insertAsPred(T const& e); //������ǰ�ڵ�֮ǰ�����½ڵ�
    ListNodePosi<T> insertAsSucc(T const& e); //���浱ǰ�ڵ�֮������½ڵ�

};

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(T const& e)
{
	ListNodePosi<T> x = new ListNode<T>(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi<T> x = new ListNode<T>(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}