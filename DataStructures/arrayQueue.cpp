#include "iostream"
using namespace std;
template<class T>
class arrayQueue{
    public:
        arrayQueue(int initialCapacity=10);
        ~arrayQueue(){delete []queue;};
        T&front();
        T&back();
        void pop();
        void push(const T&theElement);
    private:
    int arrayLength;
    int queFront;
    int queBack;
    T *queue;
};
template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity){
    arrayLength=initialCapacity;
    queue=new T[arrayLength];
    queFront=queBack=0;
}
template<class T>
T& arrayQueue<T>::front(){
    return queue[(queFront+1)%arrayLength];
}
template<class T>
T& arrayQueue<T>::back(){
    return queue[queBack];
}
template<class T>
void arrayQueue<T>::push(const T&theElement){
    if((queBack+1)%arrayLength==queFront){
        T* newQueue=new T[2*arrayLength];
        int start=(queFront+1)%arrayLength;
        if(start<2)
            copy(queue+start,queue+start+arrayLength-1,newQueue);
        else{
            copy(queue+start,queue+arrayLength,newQueue);
            copy(queue,queue+queBack+1,newQueue+arrayLength-start);
        }
        queFront=2*arrayLength-1;
        queBack=arrayLength-2;
        arrayLength*=2;
        delete[]queue;
        queue=newQueue;
    }
    queBack=(queBack+1)%arrayLength;
    queue[queBack]=theElement;
}
template<class T>
void arrayQueue<T>::pop(){
    queFront=(queFront+1)%arrayLength;
    queue[queFront].~T();
}
int main(){
    int n;
    cin>>n;
    arrayQueue<int> que(n);
    for(int i=1;i<=n;i++){
        que.push(i);
    }
    for (int i = 1; i <= n-1; i++) {
        que.pop();
        que.push(que.front());
        que.pop();
    }
    cout<<que.front();
}

