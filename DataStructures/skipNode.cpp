#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <algorithm>
#include <queue>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
using namespace std;
struct Variable//变量结构体
{
    Variable(){
        visitDiskTime=0;
        n=0; m=0;
        numberOfDisk=0;
    }
    string path;//磁盘的位置，可以根据自己的电脑修改
    string fileName="Disk.txt";//磁盘文件名称
    string file;//最终完整路径
    int visitDiskTime,n,m,numberOfDisk;
    char ch1,ch;
};
struct SequentialStringPlayer//用于构建顺串
{
    int id,key;
    bool operator<=(SequentialStringPlayer &p){
        return (id!=p.id) ? (id<p.id) : (key<p.key);
    }
};
template <class T>
class loserTree
{
public:
    virtual ~loserTree(){}
    virtual void initialize(T* thePlayer,int number)=0;
    virtual int getTheWinner() const =0;
    virtual void rePlay(int thePLayer,T newvalue)=0;
};
template <class T>
class MinimumLoserTree : public loserTree<T>
{
public:
    MinimumLoserTree(T* thePlayer=nullptr,int theNumberOfPlayers=0){
        tree=nullptr; advance=nullptr;
        initialize(thePlayer,theNumberOfPlayers);
    }
    ~MinimumLoserTree(){delete[] tree;delete[] advance;}
    void initialize(T* thePlayer,int theNumberOfPlayers);//初始化
    int getTheWinner() const {return tree[0];};//输出当前的赢者
    void rePlay(int thePlayer,T newvalue);//重构
private:
    int numberOfPlayers;
    int* tree;//记录内部结点，tree[0]是最终的赢者下标，不使用二叉树结点，因为父子关系都是通过计算得出
    int* advance;//记录比赛晋级的成员
    T* player;//参与比赛的元素
    int lowExt;//最底层外部结点的个数,2*(n-s)
    int offset;//2*s-1
    void play(int,int,int);
    int winner(int x,int y){return player[x]<=player[y]?x:y;};//返回更小的元素下标
    int loser(int x,int y){return player[x]<=player[y]?y:x;};//返回更大的元素下标
};
template <class T>
void MinimumLoserTree<T>::initialize(T* thePlayer,int theNumberOfPlayers)
{
    int n=theNumberOfPlayers;
    if(n<2) {
        cout<<"Error! the number must >= 2"<<endl;
        return;
    }
    player=thePlayer;
    numberOfPlayers=n;
    delete[] tree; delete[] advance;
    tree=new int[n+1];
    advance=new int[n+1];

    int s; for (s=1; 2*s<=n-1; s+=s);//s=2^log(n-1)-1（常数优化速度更快），s是最底层最左端的内部结点

    lowExt=2*(n-s); offset=2*s-1;

    for (int i=2; i<=lowExt; i+=2)//最下面一层开始比赛
        play((i+offset)/2,i-1,i);//父结点计算公式第一条

    int temp=0;
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
void MinimumLoserTree<T>::play(int p, int leftChild, int rightChild)
{
    //tree结点存储相对较大的值，也就是这场比赛的输者
    tree[p]=loser(leftChild,rightChild);
    //advance结点存储相对较小的值，也就是这场比赛的晋级者
    advance[p]=winner(leftChild,rightChild);

    while(p % 2 == 1 && p > 1){
        tree[p/2]=loser(advance[p-1],advance[p]);
        advance[p/2]=winner(advance[p-1],advance[p]);
        p /= 2;//向上搜索
    }
}
template <class T>
void MinimumLoserTree<T>::rePlay(int thePlayer,T newvalue)
{
    int n=numberOfPlayers;
    if(thePlayer <= 0 || thePlayer > n){
        cout<<"Error! the number must >0 & <=n"<<endl;
        return;
    }

    player[thePlayer]=newvalue;

    int matchNode,//将要比赛的场次
    leftChild,//比赛结点的左儿子
    rightChild;//比赛结点的右儿子

    if(thePlayer<=lowExt){//如果要比赛的结点在最下层
        matchNode=(offset+thePlayer)/2;
        leftChild=2*matchNode-offset;
        rightChild=leftChild+1;
    }
    else {//要比赛的结点在次下层
        matchNode=(thePlayer-lowExt+n-1)/2;
        if(2*matchNode==n-1){//特殊情况，其中一方是晋级后的人
            leftChild=advance[2*matchNode];
            rightChild=thePlayer;
        }
        else{
            leftChild=2*matchNode-n+1+lowExt;//这个操作是因为上面matchNode计算中/2取整了
            rightChild=leftChild+1;
        }
    }
    //到目前位置，我们已经确定了要比赛的场次以及比赛的选手

    //下面进行比赛重构，也就是和赢者树最大的不同，分两种情况
    if(thePlayer==tree[0]){//当你要重构的点是上一场比赛的赢家的话，过程比赢者树要简化
        for (; matchNode>=1; matchNode/=2){
            int oldLoserNode=tree[matchNode];//上一场比赛的输者
            tree[matchNode]=loser(oldLoserNode,thePlayer);
            advance[matchNode]=winner(oldLoserNode,thePlayer);
            thePlayer=advance[matchNode];
        }
    }
    else {//其他情况重构和赢者树相同
        tree[matchNode]=loser(leftChild,rightChild);
        advance[matchNode]=winner(leftChild,rightChild);
        if(matchNode==n-1 && n%2==1){//特殊情况，比赛结点是最后一层的最后一场比赛
            //特殊在matchNode/2后，左儿子是晋级的选手，右儿子是一场都没有比过赛的选手
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
    tree[0]=advance[1];//最终胜者
}
void init(Variable &va)
{
    cout<<"请输入您想要的模拟磁盘位置，接下来的操作都是在当前路径下进行，输入样例：/Users/longzhengtian/Desktop/text/"<<endl;
    cout<<"请输入："; cin>>va.path; va.file=va.path+va.fileName;
    cout<<"请输入您想要在磁盘中初始化数字的个数，这些数字将用于模拟外排序过程："; cin>>va.n;
    cout<<"请输入缓冲区大小（此处为缓冲区能存储数字的个数）："; cin>>va.m;
    cout<<"请问您是否想要将原始数据，顺串，最终数据显示在控制台中('y' or 'n')："; cin>>va.ch1; cout<<endl;

    ofstream fout1(va.file);
    if(!fout1.is_open()){
        cout<<"无法打开指定磁盘文件，无法初始化磁盘"<<endl;
        exit(0);
    }
    if(va.ch1=='y') cout<<"原始磁盘文件有："<<endl;
    for (int i=1; i<=va.n; i++){
        int x=rand()%1000+1;
        fout1<<x<<' ';//random是C++11标准
        if(va.ch1=='y') cout<<x<<' ';
    }
    if(va.ch1=='y') cout<<endl<<endl;
    fout1.close();
}
void SequentialStringConstruction(Variable &va,SequentialStringPlayer* ssplayer)
{
    ifstream fin1(va.file);
    for (int i=1; i<=va.m; i++){//将数据读入缓冲区，进行顺串构造
        fin1>>ssplayer[i].key;
        ssplayer[i].id=1;
        va.visitDiskTime++;//访存次数+1
    }
    MinimumLoserTree<SequentialStringPlayer> sstree(ssplayer,va.m);
    int num=0;
    for (int i=1; i<=va.n; i++){//依次从磁盘中取出元素，放入顺串生成树

        if(!(fin1>>num)) num=INT_MIN;
        else va.visitDiskTime++;

        SequentialStringPlayer tempwinner=ssplayer[sstree.getTheWinner()];
        SequentialStringPlayer tempnum; tempnum.key=num;

        if(num >= tempwinner.key) tempnum.id=tempwinner.id;
        else tempnum.id=num=(num==INT_MIN) ? INT_MAX :tempwinner.id+1;

        sstree.rePlay(sstree.getTheWinner(),tempnum);

        string smallfile=va.path+"smallfile"+to_string(tempwinner.id)+".txt";
        va.numberOfDisk=max(va.numberOfDisk,tempwinner.id);
        ofstream fout2(smallfile, ios::app);
        fout2<<tempwinner.key<<' ';

        fout2.close();
        va.visitDiskTime++;
    }
    fin1.close();
    cout<<"顺串分配完毕，生成"<<va.numberOfDisk<<"个顺串，顺串文件见您当前路径下出现的新文件"<<endl;
    if(va.ch1=='y'){
        cout<<"我们将这些数据在这里显示如下："<<endl;
        for (int i=1; i<=va.numberOfDisk; i++)
        {
            string smallfile=va.path+"smallfile"+to_string(i)+".txt";
            ifstream finx(smallfile);
            int tempx=0;
            cout<<"smallfile"<<i<<".txt: ";
            while(finx>>tempx)
                cout<<tempx<<' ';
            cout<<endl;
            finx.close();
        }
    }
}
void GenerateTheFinalResult(Variable &va)
{
    cout<<endl<<"请问是否将最终排序结果放入原文件，如果否，则程序将新建一个Disk2.txt文件并放入此文件中（输入'y'或'n'代表'是'与'否')："; cin>>va.ch;
    string newFile;
    if(va.ch=='y') newFile=va.file;
    else newFile=va.path+"Disk2.txt";

    ofstream fout3(newFile);

    if(va.numberOfDisk==1){//只生成了一个顺串文件，直接将其加入目标文件
        string smallfile=va.path+"smallfile"+to_string(1)+".txt";
        ifstream fin4(smallfile);
        int tempnumber;
        while(fin4>>tempnumber){
            fout3<<tempnumber<<' ';
            va.visitDiskTime+=2;
        }
        fout3.close();
        fin4.close();
        cout<<"由于只生成了1个顺串，直接将此结果放入目标文件中，磁盘访存次数为"<<va.visitDiskTime<<"次，原因是每个数据都读写4次"<<endl;
        if(va.ch1=='y'){
            cout<<"最终外排序结果如下："<<endl;
            ifstream finy(newFile);
            int tempy;
            while(finy>>tempy)
                cout<<tempy<<' ';
            cout<<endl;
            finy.close();
        }
        exit(0);
    }

    int dplayer[va.numberOfDisk+10];//初始化队列
    int pointer[va.numberOfDisk+10];//各个小磁盘文件的指针
    for (int i=1; i<=va.numberOfDisk; i++){
        string smallfile=va.path+"smallfile"+to_string(i)+".txt";
        ifstream fin2(smallfile);
        fin2>>dplayer[i];
        pointer[i]=fin2.tellg();
        fin2.close();
    }
    MinimumLoserTree<int> dtree(dplayer,va.numberOfDisk);
    int cnt=0;
    while(cnt<va.n){
        cnt++;
        int temp=dtree.getTheWinner();
        int tempwinner=dplayer[temp];
        fout3<<tempwinner<<' ';
        va.visitDiskTime++;
        string smallfile=va.path+"smallfile"+to_string(temp)+".txt";
        ifstream fin3(smallfile);
        fin3.clear(); fin3.seekg(pointer[temp]+1);
        int tempnum;
        if(pointer[temp]+1==0) tempnum=INT_MAX;
        else {
            fin3>>tempnum;
            pointer[temp]=fin3.tellg();
            if(pointer[temp]+1==0) tempnum=INT_MAX;
        }
        va.visitDiskTime++;
        dtree.rePlay(temp,tempnum);
        fin3.close();
    }
    fout3.close();
    cout<<endl;
    cout<<"将这些文件进行"<<va.numberOfDisk<<"路归并，已经结果存入到目标文件中。磁盘访存次数为"<<va.visitDiskTime<<"次，原因是每个数据都读写4次"<<endl;
    if(va.ch1=='y'){
        cout<<"最终外排序结果如下："<<endl;
        ifstream finy(newFile);
        int tempy;
        while(finy>>tempy)
            cout<<tempy<<' ';
        cout<<endl;
        finy.close();
    }
}
int main()
{
    srand(time(nullptr));
    Variable va;
    init(va);//初始化，生成随机磁盘文件
    SequentialStringPlayer ssplayer[va.n+10];
    SequentialStringConstruction(va,ssplayer);//构造顺串
    GenerateTheFinalResult(va);//生成最终结果
    return 0;
}
