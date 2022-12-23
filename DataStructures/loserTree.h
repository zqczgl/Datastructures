//
// Created by 86151 on 2022/4/5.
//
#ifndef UNTITLED_LOSERTREE_H
#define UNTITLED_LOSERTREE_H
#include <iostream>
#include "math.h"
#include "string"
#include <cstdio>
#include <fstream>
using namespace std;
template <class T>
class loserTree
{
public:
    loserTree(T* thePlayer=NULL, int theNumberOfPlayers=0);//构造函数
    ~loserTree(){delete[] tree;delete[] advance;}//析构函数
    int winner() const {return tree[0];};//返回赢者
    void rePlay(int thePlayer,T newvalue);//重赛
    void play(int,int,int);//进行一场比赛
    int winner(int x,int y){return player[x]<=player[y]?x:y;};//返回某场比赛赢者
    int loser(int x,int y){return player[x]<=player[y]?y:x;};//返回某场比赛输者
private:
    int numberOfPlayers;//人数
    int* tree;//保留输者，tree[0]为最后赢家
    int* advance;//保留赢者
    T* player;//选手
    int lowExt;
    int offset;
};
template<class T>
loserTree<T>::loserTree(T *thePlayer, int theNumberOfPlayers) {
    int n=theNumberOfPlayers;
    player=thePlayer;
    numberOfPlayers=n;
    tree=new int[n+1];
    advance=new int[n+1];
    int s=pow(2, floor(log(n-1)/ log(2)));
    lowExt=2*(n-s); offset=2*s-1;
    for (int i=2; i<=lowExt; i+=2)
        play((i+offset)/2,i-1,i);
    int temp;
    if(n%2==1){//如果有奇数个结点，处理下面晋级的一个和这个单独的结点
        play(n/2,advance[n-1],lowExt+1);
        temp=lowExt+3;
    }
    else temp=lowExt+2;//偶数个结点，直接处理次下层
    for (int i=temp; i<=n; i+=2)//经过这个循环，所有的外部结点都处理完毕
        play((i-lowExt+n-1)/2,i-1,i);
    tree[0]=advance[1];//tree[0]是最终的赢者，也就是决赛的晋级者
}
template <class T>
void loserTree<T>::play(int p, int leftChild, int rightChild)
{
    tree[p]=loser(leftChild,rightChild);
    advance[p]=winner(leftChild,rightChild);
    while(p % 2 == 1 && p > 1){
        tree[p/2]=loser(advance[p-1],advance[p]);
        advance[p/2]=winner(advance[p-1],advance[p]);
        p /= 2;
    }
}
template <class T>
void loserTree<T>::rePlay(int thePlayer, T newvalue)
{
    int n=numberOfPlayers;
    player[thePlayer]=newvalue;
    int matchNode,leftChild,rightChild;
    if(thePlayer<=lowExt){
        matchNode=(offset+thePlayer)/2;
        leftChild=2*matchNode-offset;
        rightChild=leftChild+1;
    }
    else {
        matchNode=(thePlayer-lowExt+n-1)/2;//thePlayer-lowExt+n-1将其换算成二叉树中的索引，/2是求其父节点
        if(2*matchNode==n-1){
            leftChild=advance[2*matchNode];
            rightChild=leftChild+1;
        }
        else{
            leftChild=2*matchNode-n+1+lowExt;
            rightChild=leftChild+1;
        }
    }
    if(thePlayer==tree[0]){
        for (; matchNode>=1; matchNode/=2){
            int oldLoserNode=tree[matchNode];
            tree[matchNode]=loser(oldLoserNode,thePlayer);
            advance[matchNode]=winner(oldLoserNode,thePlayer);
            thePlayer=advance[matchNode];
        }
    }
    else {
        tree[matchNode]=loser(leftChild,rightChild);
        advance[matchNode]=winner(leftChild,rightChild);
        if(matchNode==n-1 && n%2==1){//这种情况下有一场可能还没打的比赛，不能直接用advance
            matchNode/=2;
            tree[matchNode]=loser(advance[n-1],lowExt+1);
            advance[matchNode]=winner(advance[n-1],lowExt+1);
        }
        matchNode/=2;
        for (; matchNode>=1; matchNode/=2){
            tree[matchNode]=loser(advance[matchNode*2],advance[matchNode*2+1]);
            advance[matchNode]=winner(advance[matchNode*2],advance[matchNode*2+1]);
        }
    }
    tree[0]=advance[1];
}
struct merge{
    int id,key;
    bool operator<=(merge &p){
        return (id!=p.id) ? (id<p.id) : (key<p.key);
    }
};
string getFilepath(int layer,int index){
    return "C:\\Users\\86151\\Desktop\\output\\Seg" + to_string(layer) + "+" + to_string(index) + ".txt";
}
int visitDisk=0,cacheSize=200;
int toSegString(int size){
    int filenum=0;
    merge* m=new merge[size+1];
    int incache=0,outcahe=0;
    for (int i = 1; i <= size; ++i) {
        incache++;
        if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;};
        cin >> m[i].key;
        m[i].id = 1;
    }
    if(incache>0) visitDisk++;
    ofstream fout1(getFilepath(0,1), ios::app);
    int flag=1;
    loserTree<merge> ltree(m, size);
    int num=0;
    incache=0;
    while (m[ltree.winner()].key!=INT_MIN) {
        if(!(cin >> num)) num=INT_MIN;
        else {incache++;if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}}
        merge winner ;
        winner.id=m[ltree.winner()].id;
        winner.key=m[ltree.winner()].key;
        if(ltree.winner()>size){
            size=size+1;
            size=size-1;
        }
        merge newplay;
        newplay.key = num;
        if (num >= winner.key) newplay.id = winner.id;
        else newplay.id =(num==INT_MIN) ? INT_MAX :winner.id+1;
        filenum = winner.id > filenum ? winner.id : filenum;
        ltree.rePlay(ltree.winner(), newplay);
        if(winner.id>flag){
            flag=winner.id;
            fout1=ofstream (getFilepath(0,winner.id), ios::app);
        }
        fout1<<winner.key <<" ";
        outcahe++;
        if(outcahe%cacheSize==0&&outcahe!=0){visitDisk++;outcahe=0;}
    }
    if(incache!=0) visitDisk++;
    if(outcahe!=0) visitDisk++;
    fout1.close();
    return filenum;
}
void outSort(int filenum,int k){
    int incache=0,outcache=0;
    int layer=0;
    if (filenum == 1) {
        ofstream out("C:\\Users\\86151\\Desktop\\output\\output.txt");
        ifstream fin(getFilepath(0,1));
        int tempnumber;
        while (fin >> tempnumber) {
            out << tempnumber << ' ';
            incache++;outcache++;
            if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}
            if(outcache%cacheSize==0&&outcache!=0){visitDisk++;outcache=0;}
        }
        if(incache!=0) {visitDisk++; incache=0;}
        if(outcache!=0) {visitDisk++; outcache=0;}
    }
    while (filenum > 1) {
        int index=1,outindex=1;
        layer++;
        int count = filenum;
        while (count > 0) {
            if (count == 1) {
                ifstream fin = ifstream(getFilepath(layer - 1, index));
                int temp;
                ofstream fout(getFilepath(layer, outindex), ios::app);
                while (fin >> temp) {
                    fout << temp << ' ';
                    incache++;outcache++;
                    if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}
                    if(outcache%cacheSize==0&&outcache!=0){visitDisk++;outcache=0;}
                }
                if(incache!=0) {visitDisk++; incache=0;}
                if(outcache!=0) {visitDisk++; outcache=0;}
                fout.close();
                count--;
            } else {
                int segFilenum = count > k ? k : count;
                pair<int, int> element[segFilenum + 1];
                int temp=index;
                ifstream fins[segFilenum+1];
                for (int i = 1; i <= segFilenum; ++i) {
                    fins[i]=ifstream(getFilepath(layer-1,index));
                    fins[i] >> element[i].first;
                    incache++;
                    if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}
                    element[i].second = index;
                    index++;
                }
                if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}
                loserTree<pair<int, int>> loserTree(element, segFilenum);
                ofstream fout(getFilepath(layer,outindex), ios::app);
                while (element[loserTree.winner()].first != INT_MAX) {
                    pair<int, int> winner = element[loserTree.winner()];
                    pair<int, int> newplay;
                    if (!(fins[winner.second-temp+1] >> newplay.first)) newplay.first = INT_MAX;
                    else {incache++;if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}}
                    newplay.second = winner.second;
                    loserTree.rePlay(loserTree.winner(), newplay);
                    fout << winner.first << ' ';
                    outcache++;
                    if(outcache%cacheSize==0&&outcache!=0){visitDisk++;outcache=0;}
                }
                if(incache!=0) {visitDisk++; incache=0;}
                if(outcache!=0) {visitDisk++; outcache=0;}
                count -= segFilenum;
                outindex++;
                fout.close();
                for (int i = 1; i <= segFilenum; ++i) {
                    fins[i].close();
                }
            }
        }
        filenum= ceil((float)filenum/k);
    }
}
int main() {
    freopen("C:\\Users\\86151\\Desktop\\input\\data5\\data5.in", "r", stdin);
    int n, size =1000, k = 8;
    cin >> n;
    int filenum=toSegString(size);
    outSort(filenum,k);
    cout<<visitDisk;
}
#endif //UNTITLED_LOSERTREE_H
