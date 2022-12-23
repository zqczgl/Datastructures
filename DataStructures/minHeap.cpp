#include "iostream"
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
int main(){
    int n,m;
    minHeap<int> mh;
    cin>>n;
    int *element=new int[n+1];
    for(int i=1;i<=n;i++){
        cin>>element[i];
    }
    mh.initialize(element,n);
    cout<<mh.top()<<endl;
    cin>>m;
    for (int i = 0; i < m; i++) {
        int flag;
        cin>>flag;
        switch (flag) {
            case 1:
            { int num;
                cin>>num;
                mh.push(num);
                cout<<mh.top()<<endl;break;}
            case 2:
            {
                mh.pop();
                cout<<mh.top()<<endl;
                break;
            }
            case 3:{
                int l;
                cin>>l;
                int *ele=new int[l+1];
                for(int i=1;i<=l;i++){
                    cin>>ele[i];
                }
                mh.initialize(ele,l);
                for(int i=1;i<=l;i++){
                    cout<<mh.top()<<" ";
                    mh.pop();
                }
            }
        }
    }
}
