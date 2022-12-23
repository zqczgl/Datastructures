#include "iostream"
#include "queue"
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
template <class T>
class graphChain
{
public:
    graphChain(int initialCapacity =10);
    graphChain(const graphChain<T>&);
    ~graphChain(){
        while (firstNode!=NULL){
            chainNode<T>* nextNode=firstNode->next;
            delete firstNode;
            firstNode=nextNode;
        }
    };
    int indexOf(const T& theElement)const;//查找元素索引
    T* eraseElement(int theVertex);//删除
    void insertSort(const T &theElement);//按升序插入
    chainNode<T> * firstNode;
    int listSize;
};
template<class T>
graphChain<T>::graphChain(int initialCapacity) {
    firstNode=NULL;
    listSize=0;
}
template<class T>
int graphChain<T>::indexOf(const T &theElement) const {
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
void graphChain<T>::insertSort(const T &theElement) {
    chainNode<T>*currnetNode=firstNode;
    chainNode<T>*pNode=NULL;
    while (currnetNode!=NULL&&currnetNode->element<theElement){
        pNode=currnetNode;
        currnetNode=currnetNode->next;
    }
    if(pNode==NULL){
        firstNode=new chainNode<T>(theElement,currnetNode);
    }else
    pNode->next=new chainNode<T>(theElement,currnetNode);

}
template <class T>
T* graphChain<T>::eraseElement(int theVertex)
{
    chainNode<T> *current = firstNode,
            *trail = NULL;
    while (current != NULL && current->element != theVertex)
    {
        trail = current;
        current = current->next;
    }
    if (current == NULL)
        return NULL;
    T* theElement = &current->element;
    if (trail != NULL)
        trail->next = current->next;
    else
        firstNode = current->next;
    delete current;
    listSize--;
    return theElement;
}
class edge
{
public:
    edge(int theV1, int theV2)
    {v1 = theV1; v2 = theV2;}
    ~edge() {};
    int vertex1() const {return v1;}
    int vertex2() const {return v2;}
private:
    int v1,v2;
};
class linkedDigraph{
protected:
    int n;//顶点数
    int e;//边数
    graphChain<int> *aList;
public:
    linkedDigraph(int numberOfVertices=0){
        n=numberOfVertices;
        e=0;
        aList=new graphChain<int>[n+1];
    }
    ~linkedDigraph(){delete []aList;}
    bool existsEdge(int i,int j)const{
        if(i<1||j<1||i>n||j>n||aList[i].indexOf(j)==-1)
            return false;
        else
            return true;
    }
    int numberOfVerti0ces(){return n;}
    void insertEdge(edge *theEdge);
    void eraseEdge(int i,int j);
    void bfs(int v);//bfs遍历
    void bfsLength(int v);//bfs遍历长度
    void dfs(int reach[],int v);//dfs遍历
    int dfsLength(int reach[],int v);//dfs遍历长度
    void findPath(int theSource,int theDestination);//两点的最短路径长度
    void fdfs(int *reach, int v);//dfs遍历
    void connected();//有几个连同分支
    void minVert();//连同子图中最小点编号
};
void linkedDigraph::insertEdge(edge *theEdge) {
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if(aList[v1].indexOf(v2)==-1){
            aList[v1].insertSort(v2);
        }
        if(aList[v2].indexOf(v1)==-1){
            aList[v2].insertSort(v1);
        }
        e++;
}

void linkedDigraph::eraseEdge(int i, int j) {
    if(i>=1&&j>=1&&i<=n&&j<=n){
        int *v=aList[i].eraseElement(j);
        int *u=aList[j].eraseElement(i);
        if(v!=NULL&&u!=NULL)
            e--;
    }
}

void linkedDigraph::bfs(int v) {
    queue<int> q;
    int reach[n+1];
    for(int i=1;i<=n;i++)
        reach[i]=0;
    reach[v]=1;
    q.push(v);
    while (!q.empty()){
        int w=q.front();
        cout<<w<<" ";
        q.pop();
        for(chainNode<int> * u=aList[w].firstNode;u!=NULL;u=u->next){
            if(reach[u->element]==0)
            {q.push(u->element);
                reach[u->element]=1;}
        }
    }
    cout<<endl;
}

void linkedDigraph::bfsLength(int v) {
    int result=0;
    queue<int> q;
    int reach[n+1];
    for(int i=1;i<=n;i++)
        reach[i]=0;
    reach[v]=1;
    q.push(v);
    while (!q.empty()){
        int w=q.front();
        result++;
        q.pop();
        for(chainNode<int> * u=aList[w].firstNode;u!=NULL;u=u->next){
            if(reach[u->element]==0)
            {q.push(u->element);
                reach[u->element]=1;}
        }
    }
    cout<<result<<endl;
}

void linkedDigraph::dfs(int reach[],int v) {
    reach[v]=1;
    cout<<v<<" ";
    chainNode<int>* p=aList[v].firstNode;
    while (p!=NULL){
        if(reach[p->element]==0){
            dfs(reach,p->element);
        }
        p=p->next;
    }
}
void linkedDigraph::fdfs(int reach[],int v) {
    reach[v]=1;
    chainNode<int>* p=aList[v].firstNode;
    while (p!=NULL){
        if(reach[p->element]==0){
            fdfs(reach,p->element);
        }
        p=p->next;
    }
}
int linkedDigraph::dfsLength(int *reach, int v) {
    int result=1;
    reach[v]=1;
    chainNode<int>* p=aList[v].firstNode;
    while (p!=NULL){
        if(reach[p->element]==0){
            result+=dfsLength(reach,p->element);
        }
        p=p->next;
    }
    return result;
}

void linkedDigraph::findPath(int theSource, int theDestination) {
    int n=numberOfVerti0ces();
    queue<int> q;
    int path[n+1];
    int reach[n+1];
    for(int i=0;i<=n;i++){
    path[i]=0;
    reach[i]=0;
    }
    reach[theSource]=1;
    q.push(theSource);
    while (!q.empty()){
        int w=q.front();
        q.pop();
        chainNode<int>* p=aList[w].firstNode;
        while (p!=NULL){
            if(reach[p->element]==0){
                if(p->element==theDestination){
                    cout<<path[w]+1<<endl;
                    return ;
                }
                path[p->element] = path[w] + 1;
                q.push(p->element);
                reach[p->element] = 1;
            }
            p=p->next;
        }
    }
    cout<<-1<<endl;
}
void linkedDigraph::connected() {
    int n=numberOfVerti0ces();
    int reach[n+1];
    int flag=0;
    for(int i=1;i<=n;i++)
        reach[i]=0;
    for(int i=1;i<=n;i++){
        if(reach[i]==0){
            flag++;
            fdfs(reach,i);
        }
    }
    cout<<flag<<endl;
}

void linkedDigraph::minVert() {
    int n=numberOfVerti0ces();
    int reach[n+1];
    int flag=0;
    for(int i=1;i<=n;i++)
        reach[i]=0;
    for(int i=1;i<=n;i++){
        if(reach[i]==0){
           cout<<i<<" ";
            fdfs(reach,i);
        }
    }
    cout<<endl;
}
int main(){
    int n,s,t;
    int m;
    cin >> n >> m>>s>>t;
    int reach[n+1];
    linkedDigraph graph(n);
    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if (op == 0) {
            int v1, v2;
            cin >> v1 >> v2;
            edge *e=new edge(v1,v2);
            graph.insertEdge(e);
            delete e;
        }
        if (op == 1) {
            int v1, v2;
            cin >> v1 >> v2;
            graph.eraseEdge(v1, v2);
        }
    }
    graph.connected();
    graph.minVert();
    for(int i=1;i<=n;i++)
        reach[i]=0;
    cout<<graph.dfsLength(reach,s)<<endl;
    for(int i=1;i<=n;i++)
        reach[i]=0;
    graph.dfs(reach,s);
    cout<<endl;
    graph.bfsLength(t);
    graph.bfs(t);
    graph.findPath(s,t);
}

