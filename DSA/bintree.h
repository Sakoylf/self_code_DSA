#pragma once
#include "binNode.h" //����������ڵ���
 template <typename T> class BinTree { //������ģ����
 protected:
    int _size; BinNodePosi<T> _root; //��ģ�����ڵ�
    virtual int updateHeight(BinNodePosi<T> x); //���½ڵ�x�ĸ߶�
    void updateHeightAbove(BinNodePosi<T> x); //���½ڵ�x�������ȵĸ߶�
public:
    BinTree() : _size(0), _root(NULL) { } //���캯��
    ~BinTree() { if (0 < _size) remove(_root); } //��������
    int size() const { return _size; } //��ģ
    bool empty() const { return !_root; } //�п�
    BinNodePosi<T> root() const { return _root; } //����
    BinNodePosi<T> insert(T const&); //������ڵ�
    BinNodePosi<T> insert(T const&, BinNodePosi<T>); //��������
    BinNodePosi<T> insert(BinNodePosi<T>, T const&); //�����Һ���
    BinNodePosi<T> attach(BinTree<T> *&, BinNodePosi<T>); //����������
    BinNodePosi<T> attach(BinNodePosi<T>, BinTree<T> *&); //����������
    int remove(BinNodePosi<T>); //����ɾ��
    BinTree<T>* secede(BinNodePosi<T>); //��������
    template < typename VST> //������
    void travLevel(VST & visit) { if (_root) _root->travLevel(visit); } //��α���
    template < typename VST> //������
    void travPre(VST & visit) { if (_root) _root->travPre(visit); } //�������
    template < typename VST> //������
    void travIn(VST & visit) { if (_root) _root->travIn(visit); } //�������
    template < typename VST> //������
    void travPost(VST & visit) { if (_root) _root->travPost(visit); } //�������
    bool operator< (BinTree<T> const& t) //�Ƚ������������в��䣩
	    { return _root && t._root && lt(_root, t._root); }
    bool operator== (BinTree<T> const& t) //�е���
	    { return _root && t._root && (_root == t._root); }

}; //BinTree

 template<typename T>
 int BinTree<T>::updateHeight(BinNodePosi<T> x)
 {
     return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

 template<typename T>
 void BinTree<T>::updateHeightAbove(BinNodePosi<T> x)
 {
     while (x)
     {
         updateHeight(x);
         x = x->parent;
     }
 }

 template<typename T>
 BinNodePosi<T> BinTree<T>::insert(BinNodePosi<T> x, T const& e)
 {
     _size++;
     x->insertAsRC(e);
     updateHeightAbove(x);
     return x->rc;
 }

 template<typename T>
 BinNodePosi<T> BinTree<T>::insert( T const& e, BinNodePosi<T> x)
 {
     _size++;
     x->insertAsLC(e);
     updateHeightAbove(x);
     return x->lc;
 }

 template < typename VST> //������
 void travPre(VST& visit) { if (_root) _root->travPre(visit); } //�������