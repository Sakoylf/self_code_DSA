#pragma once
#include<iostream>
#include<stdlib.h>
using namespace std;
using Rank = int; //��
//typedef int Rank;
#include"fib.h"
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template <typename T> class Vector { //����ģ����
protected:

    Rank _size; Rank _capacity;  T* _elem; //��ģ��������������
    void copyFrom(T const* A, Rank lo, Rank hi); //������������A[lo, hi)
    void expand(); //�ռ䲻��ʱ����
    void shrink(); //װ�����ӹ�Сʱѹ��
    bool bubble(Rank lo, Rank hi); //ɨ�轻��
    void bubbleSort(Rank lo, Rank hi); //���������㷨
    Rank maxItem(Rank lo, Rank hi); //ѡȡ���Ԫ��
    void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
    void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
    void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
    void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩
    Rank partition(Rank lo, Rank hi); //��㹹���㷨
    void quickSort(Rank lo, Rank hi); //���������㷨
    void shellSort(Rank lo, Rank hi); //ϣ�������㷨
public:
 // ���캯��
    //Vector(int c = DEFAULT_CAPACITY) { _elem = new T[_capacity = c]; _size = 0; }
    Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
    {
        _elem = new T[_capacity = c]; 
        for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����
 // ��������
    ~Vector() { 
        delete []_elem;
        system("pause");
    } //�ͷ��ڲ��ռ�
 // ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return !_size; } //�п�
    int disordered() const;//�ж��Ƿ����򣬷���������
    Rank find(T const& e) const { return find(e, 0, _size); } //���������������
    Rank find(T const& e, Rank lo, Rank hi) const; //���������������
    Rank search(T const& e) const //���������������
    { return (0 >= _size) ? -1 : search(e, 0, _size); }
    Rank search(T const& e, Rank lo, Rank hi) const; //���������������
 // ��д���ʽӿ�
	T& operator[] (Rank r) const ; //�����±������������������������ʽ���ø�Ԫ��
    Vector<T> &operator= (Vector<T> const& V); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
    T remove(Rank r); //ɾ����Ϊr��Ԫ��
    int remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
    Rank insert(Rank r, T const& e); //����Ԫ��
    Rank insert(T const& e) {  return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
    void sort(Rank lo, Rank hi); //��[lo, hi)����
    void sort() { sort(0, _size); } //��������
    void unsort(Rank lo, Rank hi); //��[lo, hi)����
    void unsort() { unsort(0, _size); } //��������
    Rank deduplicate(); //����ȥ��
    Rank uniquify(); //����ȥ��
 // ����
    void traverse(void (*visit) (T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    template <typename VST> void traverse(VST& visit); //������ʹ�ú������󣬿�ȫ�����޸ģ�

}; //Vector


template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) //������������A[lo, hi)
{
	_elem = new T[2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}

template<typename T>
void Vector<T>::expand() //�ռ䲻��ʱ����
{
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldelem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];

	delete[] oldelem;
}

template<typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 2 > _capacity) return;
	T* oldelem = _elem;
	_elem = new T[_capacity >> 1];
	for (int i = 0; i < _size; i++) _elem[i] = oldelem[i];
	delete[] oldelem;
}

template<typename T>
T& Vector<T>::operator[] (Rank r) const
{
	cout << "sda" << endl;
	return _elem[r];
}

template<typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
	expand();
	for (int i = _size; i > r; i--)
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e;
	_size++;
	return r;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo; shrink();
	return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const   //const ֻ��֤�����������
{
	while ((lo < hi--) && (_elem[hi] != e));  //ʵ�����Ǵ�hi-1��ʼ��������Ϊǰ����hi--
	return hi;
}

template<typename T>
Vector<T>& Vector<T>::operator= (Vector<T> const& V)
{
	if (_elem) delete[] _elem;
	copyFrom(V._elem, 0, V.size());
	return *this;
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;
	for (Rank i = hi - lo; i > 0; i--)
	{
		swap(V[i - 1], V[rand() % i]);
	}
}

template<typename T>
Rank Vector<T>::deduplicate()
{
	Rank oldsize = _size;
	Rank i = 1;
	while (i < _size)
	{
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	}
	return oldsize - _size;
}

template<typename T>
void Vector<T>::traverse(void (*visit) (T&))//����ָ��
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}


template<typename T> template<typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template<typename T>
int Vector<T>::disordered()const
{
	int n = 0;
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i - 1] > _elem[i])n++;
	}
	return n;
}

template<typename T>
Rank Vector<T>::uniquify() //����ȥ��
{
	Rank i = 0, j = 0;
	while (++j < _size)
	{
		if (_elem[i] != _elem[j])
		{
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i; shrink();
	return j - i;
}

template<typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi);

template<typename T>
static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi);

template<typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi)const
{
	return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}


template<typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)   //�汾A  ������֧ ��һ�Ҷ������ȶ�
{
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		if (e < A[mi])
		{
			hi = mi;
		}
		else if (A[mi] < e)
		{
			lo = mi + 1;
		}
		else return mi;
	}
	return -1;
}

//template<typename T>
//static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)  //�汾B ������֧ ���Ҷ�ֻ�Ƚ�һ�Σ��������ܸ��ȶ�
//{
//	while (1 < hi - lo)
//	{
//		Rank mi = (lo + hi) >> 1;
//		(e < A[mi]) ? hi = mi : lo = mi;
//	}
//	return (A[lo] == e) : lo : -1;
//}


//template<typename T>
//static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)   //�汾C�����Ű汾�����㷵��ֵΪ������e�����һ��ֵ��λ��,������A[lo]<=e<A[hi]
//{
//	while (lo < hi)
//	{
//		Rank mi = (hi + lo) >> 1;
//		(e < A[mi]) ? hi = mi : lo = mi + 1;
//	}
//	return --lo;
//}


template<typename T>
static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi)
{
	Fib fib(hi - lo);
	while (lo < hi)
	{
		while (hi - lo < fib.get()) fib.prev();
		Rank mi = lo + fib.get() - 1;
		if (e < A[mi]) hi = mi;
		else if (A[mi] < e) lo = mi + 1;
		else return mi;
	}
	return -1;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand() % 5)
	{
	case 1:bubbleSort(lo, hi); break;
	case 2:selectionSort(lo, hi); break;
	case 3:mergeSort(lo, hi); break;
	case 4:heapSort(lo, hi); break;
	default:quickSort(lo, hi); break;
	}
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
	Rank last = lo;
	while (++lo < hi)
	{
		if (_elem[lo - 1] > _elem[lo])
		{
			swap(_elem[lo - 1], _elem[lo]);
			last = lo;
		}
	}
	return last;


	/*bool sorted = true;
	while (++lo < hi)
	{
		if (_elem[lo - 1] > _elem[lo])
		{
			swap(_elem[lo - 1], _elem[lo]);
			sorted = false;
		}
	}
	return sorted;*/

}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (lo < (hi = bubble(lo, hi)));
	//while(!bubble(lo,hi--));
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return;
	Rank mi = (lo + hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo;
	Rank lb = mi - lo;
	T* B = new T[lb];
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	T* C = _elem + mi;
	Rank lc = hi - mi;
	for (Rank i = 0, j = 0, k = 0; (j < lb || k < lc);)
	{
		if ((j < lb) && (lc <= k || (B[j] <= C[k]))) A[i++] = B[j++];
		if ((k < lc) && (lb <= j || (C[k] < B[j]))) A[i++] = C[k++];
	}
	delete[] B;
}
