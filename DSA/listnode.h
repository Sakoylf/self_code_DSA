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
		:data(e), pred(p), succ(s) {} //默认构造器

	ListNodePosi<T> insertAsPred(T const& e); //紧靠当前节点之前插入新节点
    ListNodePosi<T> insertAsSucc(T const& e); //紧随当前节点之后插入新节点

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