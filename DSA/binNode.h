#if defined( DSA_REDBLACK )
#define stature(p) ((p) ? (p)->height : 0) //������ڵ�ĺڸ߶ȣ�NULL�����ⲿ�ڵ㣬��Ӧ��0��
#else
#define stature(p) ((p) ? (p)->height : -1) //����BST�нڵ�ĸ߶ȣ�NUll������������Ӧ��-1��
#endif
#include "stack_vector.h"
#include "queue_list.h"
typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*; //�ڵ�λ��
template <typename T> struct BinNode { //�������ڵ�ģ����
// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
    T data; //��ֵ
    BinNodePosi<T> parent, lc, rc; //���ڵ㼰���Һ���
    int height; //�߶ȣ�ͨ�ã�
    int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
    RBColor color; //��ɫ���������
 // ���캯��
	BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }
    BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL,
	              int h = 0, int l = 1, RBColor c = RB_RED) :
	       data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }
 // �����ӿ�
	int size(); //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
    BinNodePosi<T> insertAsLC(T const&); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
    BinNodePosi<T> insertAsRC(T const&); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
    BinNodePosi<T> succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
    template <typename VST> void travLevel(VST&); //������α���
    template <typename VST> void travPre(VST&); //�����������
    template <typename VST> void travIn(VST&); //�����������
    template <typename VST> void travPost(VST&); //�����������
 // �Ƚ������е�����������һ���������в��䣩
	bool operator< (BinNode const& bn) { return data < bn.data; } //С��
    bool operator== (BinNode const& bn) { return data == bn.data; } //����
	
};

template <typename T> BinNodePosi<T> BinNode<T>::insertAsLC(T const& e)
{
    return lc = new BinNode(e, this);
}

template <typename T> BinNodePosi<T> BinNode<T>::insertAsRC(T const& e)
{
    return rc = new BinNode(e, this);
}

template <typename T> int BinNode<T>::size()
{
    int s = 1;
    if (lc) s += lc->size();
    if (rc) s += rc->size();
    return s;

}

/********************************
            �������
*********************************/


template < typename T, typename VST> //Ԫ�����͡�������
void travPre_R(BinNodePosi<T> x, VST & visit) { //��������������㷨���ݹ�棩
    if (!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template<typename T,typename VST>
void traPre_I1(BinNodePosi<T> x, VST& visit)
{
    Stack<BinNodePosi<T>> S;
    if(x) S.push(x);
    while (!S.empty())
    {
        x = S.pop();
        visit(x->data);
        if (x->rc) S.push(x->rc);
        if (x->lc) S.push(x->lc);
    }
}


template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi<T> x, VST& visit, Stack<BinNodePosi<T>>& S)
{
    while (x)
    {
        visti(x->data);
        S.push(x->rc);
        x = x->lc;
    }
}

template<typename T, typename VST>
void trvaPre_I2(BinNodePosi<T> x, VST& visit)
{
    Stack<BinNodePosi<T>> S;
    while (true)
    {
        visitAlongLeftBranch(x, visit, S);
        if (S.empty()) break;
        x = S.pop();
}




template <typename T>template<typename VST>
void BinNode<T>::travPre(VST& visit)
{
    switch (rand() % 3)
    {
        case 1: travPre_I1(this, visit); break; //������#1
        case 2: travPre_I2(this, visit); break; //������#2
        default: travPre_R(this, visit); break; //�ݹ��
    }
}

/********************************
            �������
*********************************/
template<typename T, typename VST>
void travIn_I1(BinNodePosi<T> x, VST& visit)
{
    if (!x) return;
    travIn_I1(x->lc, visit);
    visit(x->data);
    travIn_I1(x->rc, visit);
    
}

template<typename T>
static void goAlongLeftBranch(BinNodePosi<T> x, Stack<BinNodePosi<T>> &S)
{
    while (x->lc) S.push(s->lc);
}
template<typename T, typename VST>
void travIn_I2(BinNodePosi<T> x, VST& visit)
{
    Stack<BinNodePosi<T>> S;
    while (true)
    {
        goAlongLeftBranch(x, S);
        if (S.empty()) break;
        x = S.pop();
        visit(x->data);
        x = x->rc;
    }

}

template <typename T> template < typename VST> //Ԫ�����͡�������
void BinNode<T>::travIn(VST & visit) { //��������������㷨ͳһ���
    switch (rand() % 5) { //�˴������ѡ���������ԣ�������ѡ��
        case 1: travIn_I1(this, visit); break; //������#1
        case 2: travIn_I2(this, visit); break; //������#2
        //case 3: travIn_I3(this, visit); break; //������#3
        //case 4: travIn_I4(this, visit); break; //������#4
        default: travIn_R(this, visit); break; //�ݹ��
                      
    }
}


/********************************
            �������
*********************************/
template<typename T, typename VST>
void travPost_I1(BinNodePosi<T> x, VST& visit)
{
    if (!x) return;
    travIn_I1(x->lc, visit);
    travIn_I1(x->rc, visit);
    visit(x->data);
}



template<typename T,typename VST>
static void gotoLeftmostLeaf(Stack<BinNodePosi<T>>& S)
{
    while (BinNodePosi<T> x = S.top())
    {
        if (x->lc) {
            if (x->rc)
            {
                S.push(x->rc);
            }
            S.push(x->lc);
        }
        else
            S.push(x->rc);
        S.pop();//ɾ����ָ��
    }
}

template<typename T, typename VST>
void travPost_I(BinNodePosi<T> x, VST& visit)
{
    Stack<BinNodePosi<T>> S;
    if (x)S.push(x);
    while (!S.empty())
    {
        if (S.top() != x->parent)
        {
            gotoLeftmostLeaf(S)
        }
        x = S.pop();
        visit(x->data);
    }
}




template<typename T>template<typename VST> //Ԫ�����͡�������
void BinNode<T>::travPost(VST & visit) { //��������������㷨ͳһ���
    switch (rand() % 2) { //�˴������ѡ���������ԣ�������ѡ��
       case 1: travPost_I(this, visit); break; //������
       default: travPost_R(this, visit); break; //�ݹ��
              
    }

}


/********************************
            ��α���
*********************************/
template<typename T> template<typename VST>
void BinNode<T>::travLevel(VST& visit)
{
    Queue<BinNodePosi<T>> Q;
    Q.enqueue(this);
    while (!Q.empty())
    {
        BinNodePosi<T> x = Q.dequeue();
        visit(x->data);
        if (x->lc) Q.enqueue(x->lc);
        if (x->rc) Q.enqueue(x->rc);

    }
}