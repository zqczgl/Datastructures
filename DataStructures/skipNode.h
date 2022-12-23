#ifndef UNTITLED_SKIPNODE_H
#define UNTITLED_SKIPNODE_H
#include <cmath>
#include <sstream>
#include "iostream"
using namespace std;
template <class K,class E>
struct skipNode{
    pair<K,E> element;
    skipNode<K,E> **next;
    skipNode(const pair<K,E>& thePair,int size):element(thePair){
        next=new skipNode<K,E>*[size];
    }
};
template <class K,class E>
class skipList{
public:
    float cutOff;//层数
    int levels;//目前最大非空链表
    int dSize;//数量
    int maxLevel;//最大链表层数
    K tailKey;//最大关键字
    skipNode<K,E>* headNode;//头节点
    skipNode<K,E>* tailNode;//尾节点
    skipNode<K,E>** last;//每层的最后一个节点
    public:
    skipList(K largeKey,int maxPairs,float prob);//构造函数
    pair<const K,E>* find(const K& theKey) const;
    int level() const;
    skipNode<K, E> *search(const K &theKey) const;
    void insert(const pair<const K, E> &thePair);
    void erase(const K &theKey);
    int eraseFirst();
    int eraseLast();
    void output();
    void find(const K &theKey);
    void output2();
};
template<class K,class E>
skipList<K,E>::skipList(K largeKey, int maxPairs, float prob) {
    cutOff=prob*RAND_MAX;
    maxLevel=(int)ceil(logf((float)maxPairs)/logf(1/prob))-1;
    levels=0;
    dSize=0;
    tailKey=largeKey;
    pair<K,E> tailPair;
    tailPair.first=tailKey;
    headNode=new skipNode<K,E>(tailPair,maxLevel+1);
    tailNode=new skipNode<K,E>(tailPair,0);
    last=new skipNode<K,E>*[maxLevel+1];
    for (int i = 0; i <=maxLevel ; ++i) {
        headNode->next[i]=tailNode;
    }
}
template<class K,class E>
pair<const K, E> *skipList<K, E>::find(const K &theKey) const {
    if (theKey>=tailKey)
        return NULL;
    skipNode<K,E>* beforeNode=headNode;
    for (int i = levels; i >=0 ; --i) {
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
    }
    if (beforeNode->next[0]->element.first==theKey)
        return &beforeNode->next[0]->element;
    return NULL;
}
template<class K,class E>
int skipList<K,E>::level()const{
    int lev=0;
    while (rand()<=cutOff)
        lev++;
    return (lev<=maxLevel)?lev:maxLevel;
}
template<class K,class E>
skipNode<K,E>* skipList<K,E>::search(const K& theKey) const{
    skipNode<K,E>* beforeNode=headNode;
    for (int i = levels; i >=0 ; --i) {
        while (beforeNode->next[i]->element.first<theKey)
            beforeNode=beforeNode->next[i];
        last[i]=beforeNode;
    }
    return  beforeNode->next[0];
}
template<class K,class E>
void skipList<K,E>::find(const K& theKey){
    skipNode<K,E>* theNode= search(theKey);
    if (theNode->element.first!=theKey){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;
}
template<class K,class E>
void skipList<K,E>::insert(const pair<const K,E>& thePair){
    if (thePair.first>=tailKey){
        ostringstream s;
        s<<"Key = "<<thePair.first<<"Must be <"<<tailKey;
        return;
    }
    skipNode<K,E>* theNode= search(thePair.first);
    if (theNode->element.first==thePair.first){
        theNode->element.second=thePair.second;
        return;
    }
    int theLevel=level();
    if (theLevel>levels){
        theLevel=++levels;
        last[theLevel]=headNode;
    }
    skipNode<K,E>* newNode=new skipNode<K,E>(thePair,theLevel+1);
    for (int i = 0; i <= theLevel; ++i) {
        newNode->next[i]=last[i]->next[i];
        last[i]->next[i]=newNode;
    }
    dSize++; return;
}
template<class K,class E>
void skipList<K,E>::erase(const K& theKey){
    if (theKey>=tailKey)
        return;
    skipNode<K,E>* theNode= search(theKey);
    if (theNode->element.first!=theKey){
        return;
    }
    for (int i = 0; i <=levels&&last[i]->next[i]==theNode ; ++i) {
        last[i]->next[i]=theNode->next[i];
    }
    while (levels>0&&headNode->next[levels]==tailNode)
        levels--;
    delete theNode;
    dSize--;
}
template<class K,class E>
int skipList<K,E>::eraseFirst(){
    skipNode<K,E>* theNode=headNode->next[0];
    for (int i = 0; i <=levels&&headNode->next[i]==theNode ; ++i) {
        headNode->next[i]=theNode->next[i];
    }
    while (levels>0&&headNode->next[levels]==tailNode)
        levels--;
    int result=theNode->element.first;
    delete theNode;
    dSize--;
    return result;
}
template<class K,class E>
int skipList<K,E>::eraseLast(){
    skipNode<K,E>* theNode=headNode;
    while (theNode->next[0]!=tailNode)
        theNode=theNode->next[0];
    K key=theNode->element.first;
    erase(key);
    return key;
}
template<class K,class E>
void skipList<K,E>::output() {
    int sum=0;
    skipNode<K,E>* theNode=headNode;
    while (theNode->next[0]!=tailNode){
        theNode=theNode->next[0];
        sum=sum^theNode->element.first;
    }
    cout<<sum<<endl;
}
#endif //UNTITLED_SKIPNODE_H
