#include "iostream"
using namespace std;
template <class T>
struct chainNode{
    T element;
    chainNode<T> *next;
    chainNode(){}
    chainNode(const T& element)
    {this->element=element;}
    chainNode(T element, chainNode<T> *next)  {this->element=element;this->next=next;}
};
template<class T>
class chain{
    public:
        chain(int initialCapacity =10);
        chain(const chain<T>&);
        ~chain();
        class iterator{
        public:
            iterator(chainNode<T>* theNode=NULL){node=theNode;}
            T& operator*()const {return node->element;}
            T* operator->() const{return &node->element;}
            iterator& operator++(){node=node->next;return *this;}
            iterator& operator++(int){
                iterator old=*this;
                node=node->next;
                return old;
            }
            bool operator!=(const iterator right)const
            {return node!=right.node;}
            bool operator==(const iterator right)const
            {return node==right.node;}

        protected:
            chainNode<T>* node;
        };
        bool empty()const{return listSize==0;}//检查链表是否为空
        int size() const {return listSize;}//返回链表大小
        int indexOf(const T& theElement)const;//查找元素索引
        void erase(int theIndex);//删除
        void insert(int theIndex,const T& theElement);//插入
        void reverse();//反转链表
        iterator begin(){return iterator(firstNode);}
        iterator end(){return iterator(NULL);}
        void output();//输出异或和
    protected:
        void checkIndex(int theIndex) const;
        chainNode<T> * firstNode;
        int listSize;
};
template<class T>
chain<T>::chain(int initialCapacity) {
    firstNode=NULL;
    listSize=0;
}
template<class T>
chain<T>::chain(const chain<T> &theList) {
    listSize = theList.listSize;
    if (listSize == 0) {
        firstNode = NULL;
        return;
    }
    chainNode<T> *sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    chainNode<T> *targetNode = firstNode;
    while (sourceNode != NULL) {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next=NULL;
}
template<class T>
chain<T>::~chain<T>() {
    while (firstNode!=NULL){
        chainNode<T>* nextNode=firstNode->next;
        delete firstNode;
        firstNode=nextNode;
    }
}
template<class T>
int chain<T>::indexOf(const T &theElement) const {
    chainNode<T>*currentNode=firstNode;
    int index=0;
    while (currentNode!=NULL&&currentNode->element!=theElement){
        currentNode=currentNode->next;
        index++;
    }
    if(currentNode==NULL)
        return -1;
    else
        return index;
}
template<class T>
void chain<T>::erase(int theIndex) {
    chainNode<T>* deleteNode;
    if(theIndex==0){
        deleteNode=firstNode;
        firstNode=firstNode->next;
    }
    else{
    chainNode<T> *currentNode=firstNode;
    for(int i=0;i<theIndex-1;i++){
        currentNode=currentNode->next;
    }
    deleteNode=currentNode->next;
    currentNode->next=currentNode->next->next;}
    delete deleteNode;
    listSize--;
}
template<class T>
void chain<T>::insert(int theIndex, const T &theElement) {
    if(theIndex==0){
        firstNode=new chainNode<T>(theElement,firstNode);
    }else{
        chainNode<T>*currentNode=firstNode;
        for(int i=0;i<theIndex-1;i++)
            currentNode=currentNode->next;
        currentNode->next=new chainNode<T>(theElement,currentNode->next);
    }
}
template<class T>
void chain<T>::reverse() {
    chainNode<T> *p=firstNode;
    firstNode=NULL;
    while (p!=NULL){
        chainNode<T> *temp=p->next;
        p->next=firstNode;
        firstNode=p;
        p=temp;
    }
}
template<class T>
void chain<T>::output() {
    iterator p;
    int j=0,sum=0;
    for(p=begin();p!=end();p++,j++)
        sum+=j^(*p);
    cout<<sum<<endl;
}
int main(){
    int n,q;//节点数，指令数；
    int idx,val;//位置和数值
    int element;
    cin>>n;
    cin>>q;
    chain<int> c;
    for(int i=0;i<n;i++){
        cin>>element;
        c.insert(i,element);
    }
    for(int i=0;i<q;i++){
        int flag;//标记
        cin>>flag;
        switch (flag) {
            case 1:
                cin>>idx>>val;
                c.insert(idx,val);
                break;
            case 2:
            {cin>>val;
                if(c.indexOf(val)==-1)
                    cout<<-1<<endl;
                else
                    c.erase(c.indexOf(val));
                break;}
            case 3:
                c.reverse();
                break;
            case 4:
                cin>>val;
                cout<<c.indexOf(val)<<endl;
                break;
            case 5:
                c.output();
        }
    }
}