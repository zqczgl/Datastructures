#include "iostream"
#include "queue"
using namespace std;
template<class T>
void changeLength1D(T*& a,int oldLength,int newLength){
    T* temp=new T[newLength];
    int number=min(oldLength,newLength);
    copy(a,a+number,temp);
    delete []a;
    a=temp;
}
template<class T>
class minHeap{
public:
    minHeap(int initLength=10){heapSize=0;arrayLength=initLength;heap=new T[arrayLength];}
    ~minHeap(){delete[]heap;}
    void push(const T&theElement);
    void pop();
    void initialize(T *theHeap,int theSize);
    T& top(){return heap[1];}
private:
    T*heap;
    int heapSize;
    int arrayLength;
};
template<class T>
void minHeap<T>::push(const T&theElement){
    if(heapSize==arrayLength-1){
        changeLength1D(heap,arrayLength,2*arrayLength);
        arrayLength*=2;
    }
    int currentNode=++heapSize;
    while(currentNode!=1&&heap[currentNode/2]>theElement){
        heap[currentNode]=heap[currentNode/2];
        currentNode/=2;
    }
    heap[currentNode]=theElement;
}
template<class T>
void minHeap<T>::pop() {
    heap[1].~T();
    T lastElement=heap[heapSize--];
    int currentNode=1,child=2;
    while (child<=heapSize){
        if(child<heapSize&&heap[child]>heap[child+1])
            child++;
        if(lastElement<=heap[child])
            break;
        heap[currentNode]=heap[child];
        currentNode=child;
        child*=2;
    }
    heap[currentNode]=lastElement;
}
template<class T>
void minHeap<T>::initialize(T *theHeap, int theSize) {
    delete []heap;
    heap=theHeap;
    heapSize=theSize;
    arrayLength=theSize+1;
    for(int root=heapSize/2;root>=1;root--){
        T rootElement=heap[root];
        int child=2*root;
        while (child<=heapSize){
            if(child<heapSize&&heap[child]>heap[child+1])
                child++;
            if(rootElement<=heap[child])
                break;
            heap[child/2]=heap[child];
            child*=2;
        }
        heap[child/2]=rootElement;
    }
}
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
        element=theElement;
        leftChild=theLeftChild;
        rightChild=theRightChild;
    }
};
template<class E>
class linkedBinaryTree{
public:
    linkedBinaryTree(){root=NULL;}
    void makeTree(const E& element,linkedBinaryTree<E>&left,linkedBinaryTree<E>&right);
    int huffLength(int *b);
private:
    binaryTreeNode<E> *root;
    static void (*visit)(binaryTreeNode<E>*);
};
template<class T>
void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T>*);
template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,linkedBinaryTree<E>&left,linkedBinaryTree<E>&right)
{
    root=new binaryTreeNode<E>(element,left.root,right.root);
}
template<class T>
struct huffmanNode{
    linkedBinaryTree<T> *tree;
    T weight;
    operator T() const{return weight;}
};
template<class T>
linkedBinaryTree<int>* huffmanTree(T weight[],int n){
  huffmanNode<T>*hNode=new huffmanNode<T>[n+1];
    linkedBinaryTree<int>emptyTree;
    for(int i=1;i<=n;i++){
        hNode[i].weight=weight[i];
        hNode[i].tree=new linkedBinaryTree<int>;
        hNode[i].tree->makeTree(i,emptyTree,emptyTree);
    }
    minHeap<huffmanNode<T>> heap(1);
    heap.initialize(hNode,n);
    huffmanNode<T> w,x,y;
    linkedBinaryTree<int>*z;
    for(int i=1;i<n;i++){
        x=heap.top();heap.pop();
        y=heap.top();heap.pop();
        z=new linkedBinaryTree<int>;
        z->makeTree(0,*x.tree,*y.tree);
        w.weight=x.weight+y.weight;
        w.tree=z;
        heap.push(w);
        delete x.tree;
        delete y.tree;
    }
    return heap.top().tree;
}
template<class T>
int linkedBinaryTree<T>::huffLength(int *b)
{
    int result = 0;
    queue<binaryTreeNode<T>*> q;
    binaryTreeNode<T> *currentNode;
    q.push(root);
    root->element = 0;
    int temp;
    while (!q.empty())
    {
        currentNode = q.front();
        q.pop();
        if (currentNode->leftChild != NULL)
        {
            q.push(currentNode->leftChild);
            temp=currentNode->leftChild->element;
            currentNode->leftChild->element = currentNode->element + 1;
            if(temp!=0){
                result+=b[temp]*currentNode->leftChild->element;
            }
        }
        if (currentNode->rightChild != NULL)
        {
            q.push(currentNode->rightChild);
            temp=currentNode->rightChild->element;
            currentNode->rightChild->element = currentNode->element + 1;
            if(temp!=0){
                result+=b[temp]*currentNode->leftChild->element;
            }
        }
    }
    return result;
}
int main(){
    string str;
    int index = 1,n= 0;
    cin >> str;
    int *arr = new int[26];
    for (int i = 0; i < 26; i++)
        arr[i] = 0;
    for (int j = 0; j < str.size(); j++)
    {
        arr[(int)str[j] - 97]++;
        if (arr[(int)str[j] - 97] == 1) n++;
    }
    int *b = new int[n+1];
    for (int k = 0;k < 26; k++)
    {
        if (arr[k] != 0)
        {
            b[index]=arr[k];
            index++;
        }
    }
 linkedBinaryTree<int>*tree= huffmanTree(b,n);
 cout<<tree->huffLength(b);
}