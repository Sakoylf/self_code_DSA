#if defined( DSA_REDBLACK )
#define stature(p) ((p) ? (p)->height : 0) //红黑树节点的黑高度（NULL视作外部节点，对应于0）
#else
#define stature(p) ((p) ? (p)->height : -1) //其余BST中节点的高度（NUll视作空树，对应于-1）
#endif
#include "stack_vector.h"
#include "queue_list.h"
typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*; //节点位置
template <typename T> struct BinNode { //二叉树节点模板类
// 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
    T data; //数值
    BinNodePosi<T> parent, lc, rc; //父节点及左、右孩子
    int height; //高度（通用）
    int npl; //Null Path Length（左式堆，也可直接用height代替）
    RBColor color; //颜色（红黑树）
 // 构造函数
	BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }
    BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL,
	              int h = 0, int l = 1, RBColor c = RB_RED) :
	       data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }
 // 操作接口
	int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
    BinNodePosi<T> insertAsLC(T const&); //作为当前节点的左孩子插入新节点
    BinNodePosi<T> insertAsRC(T const&); //作为当前节点的右孩子插入新节点
    BinNodePosi<T> succ(); //取当前节点的直接后继
    template <typename VST> void travLevel(VST&); //子树层次遍历
    template <typename VST> void travPre(VST&); //子树先序遍历
    template <typename VST> void travIn(VST&); //子树中序遍历
    template <typename VST> void travPost(VST&); //子树后序遍历
 // 比较器、判等器（各列其一，其余自行补充）
	bool operator< (BinNode const& bn) { return data < bn.data; } //小于
    bool operator== (BinNode const& bn) { return data == bn.data; } //等于
	
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
            先序遍历
*********************************/


template < typename T, typename VST> //元素类型、操作器
void travPre_R(BinNodePosi<T> x, VST & visit) { //二叉树先序遍历算法（递归版）
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
        case 1: travPre_I1(this, visit); break; //迭代版#1
        case 2: travPre_I2(this, visit); break; //迭代版#2
        default: travPre_R(this, visit); break; //递归版
    }
}

/********************************
            中序遍历
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

template <typename T> template < typename VST> //元素类型、操作器
void BinNode<T>::travIn(VST & visit) { //二叉树中序遍历算法统一入口
    switch (rand() % 5) { //此处暂随机选择以做测试，共五种选择
        case 1: travIn_I1(this, visit); break; //迭代版#1
        case 2: travIn_I2(this, visit); break; //迭代版#2
        //case 3: travIn_I3(this, visit); break; //迭代版#3
        //case 4: travIn_I4(this, visit); break; //迭代版#4
        default: travIn_R(this, visit); break; //递归版
                      
    }
}


/********************************
            后序遍历
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
        S.pop();//删除空指针
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




template<typename T>template<typename VST> //元素类型、操作器
void BinNode<T>::travPost(VST & visit) { //二叉树后序遍历算法统一入口
    switch (rand() % 2) { //此处暂随机选择以做测试，共两种选择
       case 1: travPost_I(this, visit); break; //迭代版
       default: travPost_R(this, visit); break; //递归版
              
    }

}


/********************************
            层次遍历
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