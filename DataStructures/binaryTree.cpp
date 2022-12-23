#include "iostream"
#include "queue"
using namespace std;
template<class T>
struct binaryTreeNode{
    T element;
    binaryTreeNode<T>* leftChild;
    binaryTreeNode<T>* rightChild;
    binaryTreeNode(){leftChild=rightChild=NULL;}
    binaryTreeNode(const T&theElement){
        element=theElement;
        leftChild=rightChild=NULL;
    }
    binaryTreeNode(const T&theElement,binaryTreeNode<T>* theLeftChild,binaryTreeNode<T>* theRightChild){
        element(theElement);
        leftChild=theLeftChild;
        rightChild=theLeftChild;
    }
};
template<class E>
class linkedBinaryTree{
  public:
    linkedBinaryTree(){root=NULL;}
    void preOrder(void(*theVisit)(binaryTreeNode<E>*))
    {visit=theVisit;preOrder(root);}
    void inOrder(void(*theVisit)(binaryTreeNode<E>*))
    {visit=theVisit;inOrder(root);}
    void postOrder(void(*theVisit)(binaryTreeNode<E>*))
    {visit=theVisit;postOrder(root);}
    void levelOrder(void(*theVisit)(binaryTreeNode<E>*));
    void levelOrderOutput() { levelOrder(output); cout << endl;}
    void makeTree(binaryTreeNode<E>*theRoot);
    int height()const{return height(root);}
    int treeSize()const{return treeSize(root);}
private:
    binaryTreeNode<E> *root;
    static void (*visit)(binaryTreeNode<E>*);
    static void preOrder(binaryTreeNode<E>*t);
    static void inOrder(binaryTreeNode<E>*t);
    static void postOrder(binaryTreeNode<E>*t);
    static void output(binaryTreeNode<E>*t){cout<<t->element<<" ";}
    static int height(binaryTreeNode<E>*t);
    static int treeSize(binaryTreeNode<E>*t);
};
template<class T>
void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T>*);
template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E>*t) {
    if(t!=NULL){
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}
template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E>*t) {
    if(t!=NULL){
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}
template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E>*t) {
    if(t!=NULL){
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}
template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E>*))
{
    queue<binaryTreeNode<E>*> q;
    binaryTreeNode<E>* t = root;
    while (t != NULL)
    {
        theVisit(t);
        if (t->leftChild != NULL)
            q.push(t->leftChild);
        if (t->rightChild != NULL)
            q.push(t->rightChild);


        if (q.empty()) {
            return;
        }
        else {
            t = q.front();
            q.pop();
        }
    }
}
template<class E>
void linkedBinaryTree<E>::makeTree(binaryTreeNode<E>*theRoot)
{
    root = theRoot;
}
template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>*t)  {
    if(t==NULL)
        return 0;
    int h1=height(t->leftChild);
    int h2= height(t->rightChild);
    if(h1>h2)
        return ++h1;
    else
        return ++h2;
}
template<class E>
int linkedBinaryTree<E>::treeSize(binaryTreeNode<E>*t){
    int count=0;
    if(t==NULL)
        return 0;
    count=treeSize(t->leftChild)+treeSize(t->rightChild)+1;
    return count;
}
int main() {
    int n;
    cin >> n;
    binaryTreeNode<int> treeNode[n];
    for (int i = 0; i <n; i++) {
        int l, r;
        cin >> l >> r;
        treeNode[i].element=i+1;
        if (l != -1)
            treeNode[i].leftChild = &treeNode[l-1];
        if(r!=-1)
            treeNode[i].rightChild=&treeNode[r-1];
    }
    linkedBinaryTree<int> t;
    t.makeTree(treeNode);
    t.levelOrderOutput();
    for(int i=0;i<n;i++){
        t.makeTree(&treeNode[i]);
        cout<<t.treeSize()<<" ";
    }
    cout<<endl;
    for(int i=0;i<n;i++){
        t.makeTree(&treeNode[i]);
        cout<<t.height()<<" ";
    }
}