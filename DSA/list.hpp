#pragma once
#include"listnode.h"
#include<iostream>
template <typename T> class List { //�б�ģ����
 private:
    int _size; ListNodePosi<T> header, trailer; //��ģ��ͷ�ڱ���β�ڱ�
 protected:
    void init(); //�б���ʱ�ĳ�ʼ��
    int clear(); //������нڵ�
    void copyNodes(ListNodePosi<T>, int); //�����б�����λ��p���n��
    ListNodePosi<T> merge(ListNodePosi<T>, int, List<T> &, ListNodePosi<T>, int); //�鲢
    void mergeSort(ListNodePosi<T> &, int); //�Դ�p��ʼ������n���ڵ�鲢����
    void selectionSort(ListNodePosi<T>, int); //�Դ�p��ʼ������n���ڵ�ѡ������
    void insertionSort(ListNodePosi<T>, int); //�Դ�p��ʼ������n���ڵ��������
    void radixSort(ListNodePosi<T>, int); //�Դ�p��ʼ������n���ڵ��������

 public:
 // ���캯��
    List() { init(); } //Ĭ��
    List(List<T> const& L); //���帴���б�L
    List(List<T> const& L, Rank r, int n); //�����б�L���Ե�r�����n��
    List(ListNodePosi<T> p, int n); //�����б�����λ��p���n��
 // ��������
    ~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
 // ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return _size <= 0; } //�п�
    T& operator[] (Rank r) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
    ListNodePosi<T> first() const { return header->succ; } //�׽ڵ�λ��
    ListNodePosi<T> last() const { return trailer->pred; } //ĩ�ڵ�λ��
    bool valid(ListNodePosi<T> p) //�ж�λ��p�Ƿ����Ϸ�
	    { return p && (trailer != p) && (header != p); } //��ͷ��β�ڵ��ͬ��NULL
    ListNodePosi<T> find(T const& e) const //�����б����
	    { return find(e, _size, trailer); }
    ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const; //�����������
    ListNodePosi<T> search(T const& e) const //�����б����
	    { return search(e, _size, trailer); }
    ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const; //�����������
    ListNodePosi<T> selectMax(ListNodePosi<T> p, int n); //��p����n-1�������ѡ�������
    ListNodePosi<T> selectMax() { return selectMax(header->succ, _size); } //���������
 // ��д���ʽӿ�
	ListNodePosi<T> insertAsFirst(T const& e); //��e�����׽ڵ����
    ListNodePosi<T> insertAsLast(T const& e); //��e����ĩ�ڵ����
    ListNodePosi<T> insertBefore(ListNodePosi<T> p, T const e);
    ListNodePosi<T> insertAfter(ListNodePosi<T> p, T const e);
    ListNodePosi<T> insert(ListNodePosi<T> p, T const& e); //��e����p�ĺ�̲���
    ListNodePosi<T> insert(T const& e, ListNodePosi<T> p); //��e����p��ǰ������
    T remove(ListNodePosi<T> p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
    void merge(List<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); } //ȫ�б�鲢
    void sort(ListNodePosi<T> p, int n); //�б���������
    void sort() { sort(first(), _size); } //�б���������
    int deduplicate(); //����ȥ��
    int uniquify(); //����ȥ��
    void reverse(); //ǰ���ã�ϰ�⣩
// ����
	void traverse(void (*) (T&)); //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
    template < typename VST> //������
	void traverse(VST&); //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�

}; //List


template<typename T>
void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}

template<typename T>
T& List<T>::operator[](Rank r)const
{
	ListNodePosi<T> p = first();
	while (0 < r--) p = p->succ;
	return p->data;
}

template<typename T>
ListNodePosi<T> List<T>::find(T const& e, int n, ListNodePosi<T> p) const
{
	while (0 < n--)
	{
		if (e == (p = p->pred)->data) return p;
	}
	return NULL;
}

template<typename T>
ListNodePosi<T> List<T>::insertBefore(ListNodePosi<T> p, T const e)
{
	_size++;
	return p->insertAsPred(e);
}


template<typename T>
ListNodePosi<T> List<T>::insertAfter(ListNodePosi<T> p, T const e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
void List<T>::copyNodes(ListNodePosi<T> p, int n) //�����б�����λ��p���n��
{
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
ListNodePosi<T> List<T>::insertAsLast(T const& e)
{
	return insertBefore(trailer, e);
}

template<typename T>
T List<T>::remove(ListNodePosi<T> p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template<typename T>
List<T>::~List()
{
	clear(); delete header; delete trailer;
}

template<typename T>
int List<T>::clear()
{
	int oldsize = _size;
	while (0 < _size)
	{
		remove(header->succ);
	}
	return oldsize;

}

template<typename T>
int List<T>::deduplicate() //����ȥ��
{
	if (_size < 2) return 0;
	int oldsize = _size;
	ListNodePosi<T> p = first();
	Rank r = 1;
	while (trailer != (p = p->succ))   //�ӵڶ�����ʼ��ǰѰ��
	{
		ListNodePosi q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
	return oldsize - _size;
}

template<typename T>
int List<T>::uniquify() //����ȥ��
{
	if (_size < 2) return 0;
	int oldsize = _size;
	ListNodePosi<T>  p = first;
	ListNodePosi<T> q;
	while (trailer != (q = p->succ))
	{
		if (p->data != q->data) p = q;
		else remove(q);
	}
	return oldsize - _size;
}

template<typename T>
ListNodePosi<T> List<T>::search(T const& e, int n, ListNodePosi<T> p) const //�����������
{
	while (0 <= n--)
	{
		if (((p = p->pred)->data) <= e) break;
	}
	return p;
}

template<typename T>
void List<T>::sort(ListNodePosi<T> p, int n) //�б���������
{
	ListNodePosi<T>  head = p->pred;
	ListNodePosi<T>  tail = p;
	for (int i = 0; i < n; i++)
	{
		tail = tail->succ;
	}
	while (0 < n)
	{
		insertBefore(tail, remove(selectMax(head->succ, n)));
		tail = tail->pred;
		n--;
	}
}


template<typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n) //��p����n-1�������ѡ�������
{
	ListNodePosi<T> max = p;
	for (ListNodePosi<T> cur = p; 0 < n; n--)
	{
		if (!lt((cur = cur->succ)->data, max->data)) max = cur;   //not less than  ��>= max
	}
	return max;
}


template<typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n) //�Դ�p��ʼ������n���ڵ��������
{
	for (int r = 0; r < n; r++)
	{
		insertAfter(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}