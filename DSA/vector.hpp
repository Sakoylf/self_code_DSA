#pragma once
#include<iostream>
#include<stdlib.h>
using namespace std;
using Rank = int; //秩
//typedef int Rank;
#include"fib.h"
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

template <typename T> class Vector { //向量模板类
protected:

    Rank _size; Rank _capacity;  T* _elem; //规模、容量、数据区
    void copyFrom(T const* A, Rank lo, Rank hi); //复制数组区间A[lo, hi)
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时压缩
    bool bubble(Rank lo, Rank hi); //扫描交换
    void bubbleSort(Rank lo, Rank hi); //起泡排序算法
    Rank maxItem(Rank lo, Rank hi); //选取最大元素
    void selectionSort(Rank lo, Rank hi); //选择排序算法
    void merge(Rank lo, Rank mi, Rank hi); //归并算法
    void mergeSort(Rank lo, Rank hi); //归并排序算法
    void heapSort(Rank lo, Rank hi); //堆排序（稍后结合完全堆讲解）
    Rank partition(Rank lo, Rank hi); //轴点构造算法
    void quickSort(Rank lo, Rank hi); //快速排序算法
    void shellSort(Rank lo, Rank hi); //希尔排序算法
public:
 // 构造函数
    //Vector(int c = DEFAULT_CAPACITY) { _elem = new T[_capacity = c]; _size = 0; }
    Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
    {
        _elem = new T[_capacity = c]; 
        for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //数组整体复制
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //区间
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //向量整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间
 // 析构函数
    ~Vector() { 
        delete []_elem;
        system("pause");
    } //释放内部空间
 // 只读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    int disordered() const;//判断是否有序，返回逆序数
    Rank find(T const& e) const { return find(e, 0, _size); } //无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi) const; //无序向量区间查找
    Rank search(T const& e) const //有序向量整体查找
    { return (0 >= _size) ? -1 : search(e, 0, _size); }
    Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找
 // 可写访问接口
	T& operator[] (Rank r) const ; //重载下标操作符，可以类似于数组形式引用各元素
    Vector<T> &operator= (Vector<T> const& V); //重载赋值操作符，以便直接克隆向量
    T remove(Rank r); //删除秩为r的元素
    int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)之内的元素
    Rank insert(Rank r, T const& e); //插入元素
    Rank insert(T const& e) {  return insert(_size, e); } //默认作为末元素插入
    void sort(Rank lo, Rank hi); //对[lo, hi)排序
    void sort() { sort(0, _size); } //整体排序
    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
    void unsort() { unsort(0, _size); } //整体置乱
    Rank deduplicate(); //无序去重
    Rank uniquify(); //有序去重
 // 遍历
    void traverse(void (*visit) (T&)); //遍历（使用函数指针，只读或局部性修改）
    template <typename VST> void traverse(VST& visit); //遍历（使用函数对象，可全局性修改）

}; //Vector


template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) //复制数组区间A[lo, hi)
{
	_elem = new T[2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}

template<typename T>
void Vector<T>::expand() //空间不足时扩容
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
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const   //const 只保证不动类的数据
{
	while ((lo < hi--) && (_elem[hi] != e));  //实际上是从hi-1开始检索，因为前边有hi--
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
void Vector<T>::traverse(void (*visit) (T&))//函数指针
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
Rank Vector<T>::uniquify() //有序去重
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
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)   //版本A  三个分支 左一右二，不稳定
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
//static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)  //版本B 两个分支 左右都只比较一次，整体性能更稳定
//{
//	while (1 < hi - lo)
//	{
//		Rank mi = (lo + hi) >> 1;
//		(e < A[mi]) ? hi = mi : lo = mi;
//	}
//	return (A[lo] == e) : lo : -1;
//}


//template<typename T>
//static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)   //版本C，最优版本，满足返回值为不大于e的最后一个值的位置,不变性A[lo]<=e<A[hi]
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
