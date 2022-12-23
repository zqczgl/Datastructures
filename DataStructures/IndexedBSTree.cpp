#include <iostream>
using namespace std;

template <class T>
struct binarySearchNode{
    T element;
    binarySearchNode<T>* leftChild;
    binarySearchNode<T>* rightChild;
    int leftSize;
    binarySearchNode(const T& theElement){
        element = theElement;
        leftChild = NULL;
        rightChild = NULL;
        leftSize = 0;
    }
    binarySearchNode(const T& theElement, binarySearchNode<T>* theLeft, binarySearchNode<T>* theRight, int LeftTreeSize){
        element = theElement;
        leftChild = theLeft;
        rightChild = theRight;
        leftSize = LeftTreeSize;
    }
};
template <class T>
class bianrySearchTree{
public:
    bianrySearchTree(){
        root = NULL;
        treeSize = 0;
    }
    int insert(const T& theElement);
    int erase(const T& theElement);
    int eraseByIndex(int a);
    int find(const T& theElement);
    int Search(int a);

private:
    binarySearchNode<T>* root;
    int treeSize;
};

template <class T>
int bianrySearchTree<T>::insert(const T& theElement){
    binarySearchNode<T>* p = root;
    binarySearchNode<T>* pp = NULL;
    int sum = 0;
    while (p != NULL){
        pp = p;
        if (p->element < theElement){
            sum = sum^p->element;
            p = p->rightChild;
        }
        else if (p->element > theElement){
            sum = sum^p->element;
            p = p->leftChild;
        }
        else if (p->element == theElement) {
            return 0;
        }
    }
    binarySearchNode<T>* newNode = new binarySearchNode<T>(theElement);
    if (root != NULL){
        if (theElement > pp->element)
            pp->rightChild = newNode;
        else
            pp->leftChild = newNode;
    }
    else
        root = newNode;
    treeSize++;
    p = root;
    while (p->element != theElement)
    {
        if (p->element < theElement)
        {
            p = p->rightChild;
        }
        else
        {
            p->leftSize++;
            p = p->leftChild;
        }
    }
    return sum;
}

template <class T>
int bianrySearchTree<T>::erase(const T& theElement)
{
    binarySearchNode<T>* p = root;
    binarySearchNode<T>* pp = NULL;
    int sum = 0;
    while (p != NULL && p->element != theElement)
    {
        sum ^= p->element;
        pp = p;
        if (p->element < theElement)
        {
            p = p->rightChild;
        }
        else
        {
            p = p->leftChild;
        }
    }
    if (p == NULL)
    {
        return 0;
    }
    sum ^= p->element;
    p = root;
    while (p != NULL && p->element != theElement)
    {
        if (p->element < theElement)
        {
            p = p->rightChild;
        }
        else if (p->element > theElement)
        {
            p->leftSize--;
            p = p->leftChild;
        }
    }

    if (p->leftChild != NULL && p->rightChild != NULL)
    {
        binarySearchNode<T>* ps = p->rightChild;
        binarySearchNode<T>* s = p;
        while (ps->leftChild != NULL)
        {
            ps->leftSize--;
            s = ps;
            ps = ps->leftChild;
        }

        binarySearchNode<T>* newNode = new binarySearchNode<T>(ps->element, p->leftChild, p->rightChild, p->leftSize);
        if (pp == NULL)
            root = newNode;
        else if (p == pp->leftChild)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;

        if (s == p)
            pp = newNode;
        else
            pp = s;

        delete p;
        p = ps;
    }

    binarySearchNode<T>* c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;
    if (p == root)
        root = c;
    else
    {
        if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    treeSize--;
    delete p;
    return sum;
}

template <class T>
int bianrySearchTree<T>::eraseByIndex(int a)
{
    binarySearchNode<T>* p = root;
    binarySearchNode<T>* pp = NULL;
    int sum = 0;
    while (p != NULL && p->leftSize != a)
    {
        sum ^= p->element;
        pp = p;
        if (p->leftSize > a)
        {
            p = p->leftChild;
        }
        else if (p->leftSize < a)
        {
            a = a - p->leftSize - 1;
            p = p->rightChild;
        }
    }
    if (p == NULL)
        return 0;
    sum ^= p->element;
    int theElement = p->element;
    p = root;
    while (p != NULL && p->element != theElement)
    {
        if (p->element < theElement)
        {
            p = p->rightChild;
        }
        else if (p->element > theElement)
        {
            p->leftSize--;
            p = p->leftChild;
        }
    }

    if (p->leftChild != NULL && p->rightChild != NULL)
    {
        binarySearchNode<T>* ps = p->rightChild;
        binarySearchNode<T>* s = p;
        while (ps->leftChild != NULL)
        {
            ps->leftSize--;
            s = ps;
            ps = ps->leftChild;
        }

        binarySearchNode<T>* newNode = new binarySearchNode<T>(ps->element, p->leftChild, p->rightChild, p->leftSize);
        if (pp == NULL)
            root = newNode;
        else if (p == pp->leftChild)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;

        if (s == p)
            pp = newNode;
        else
            pp = s;

        delete p;
        p = ps;
    }

    binarySearchNode<T>* c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;

    if (p == root)
        root = c;
    else
    {
        if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    treeSize--;
    delete p;
    return sum;
}

template <class T>
int bianrySearchTree<T>::find(const T& theElement)
{
    binarySearchNode<T>* p = root;
    int sum = 0;
    while (p != NULL )
    {
        sum =sum^p->element;
        if (p->element > theElement)
        {
            p = p->leftChild;
        }
        else
        {
            if(p->element<theElement)
                p=p->rightChild;
            else
                return sum;
        }
    }
        return 0;
}

template <class T>
int bianrySearchTree<T>::Search(int a)
{
    binarySearchNode<T>* p = root;
    int sum = 0;
    while (p != NULL && p->leftSize != a)
    {
        sum ^= p->element;
        if (p->leftSize > a)
        {
            p = p->leftChild;
        }
        else if (p->leftSize < a)
        {
            a = a - p->leftSize - 1;
            p = p->rightChild;
        }
    }
    if (p == NULL)
        return 0;
    else
    {
        sum ^= p->element;
        return sum;
    }
}

int main(){
    bianrySearchTree<int> x;
    int m, a, b;
    cin >> m;
    for(int i=0;i<m;i++){
        cin >> a >> b;
        if (a == 0){
            cout << x.insert(b) << endl;
        }
        if (a == 1){
            cout << x.find(b) << endl;
        }
        if (a == 2){
            cout << x.erase(b) << endl;
        }
        if (a == 3){
            b = b - 1;
            cout << x.Search(b) << endl;
        }
        if (a == 4){
            b = b - 1;
            cout << x.eraseByIndex(b) << endl;
        }
    }
}

