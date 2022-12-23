#include "iostream"
#include "iomanip"
using namespace std;
template<class T>
class arrayStack {
public:
    arrayStack(int initialCapacity=10);
    ~arrayStack(){delete[] stack;}
    bool empty()const {return stackTop==-1;};
    int size()const{return stackTop+1;}
    T&top(){return stack[stackTop];}
    void pop(){stack[stackTop--].~T();}
    void push(const T& theElement);
private:
    int stackTop;
    int arrayLength;
    T *stack;
};
template<class T>
void changeLength1D(T*& a,int oldLength,int newLength){
    T* temp=new T[newLength];
    int number=min(oldLength,newLength);
    copy(a,a+number,temp);
    delete []a;
    a=temp;
}
template<class T>
arrayStack<T>::arrayStack(int initialCapacity){
    arrayLength=initialCapacity;
    stack=new T[arrayLength];
    stackTop=-1;
}
template<class T>
void arrayStack<T>::push(const T &theElement) {
    if(stackTop==arrayLength-1){
        changeLength1D(stack,arrayLength,2*arrayLength);
        arrayLength=arrayLength*2;
    }
    stack[++stackTop]=theElement;
}
void  calculate(arrayStack<double>& number,arrayStack<char>&signal ){
    double num1,num2;
    num1=number.top();number.pop();
    num2=number.top();number.pop();
    switch (signal.top()) {
        case '+':
            number.push(num1+num2);
            break;
        case '-':
            number.push(num2-num1);
            break;
        case '*':
            number.push(num1*num2);
            break;
        case '/':
            number.push(num2/num1);
    }
    signal.pop();
}
void operate(string str){
    int length=str.size();
    arrayStack<char> signal(length);
    arrayStack<double> number(length);
    for(int i=0;i<length;i++){
        switch(str[i]){
            case '+':{
                if(signal.empty()||signal.top()=='(')
                    signal.push(str[i]);
                else{
                    while (!signal.empty()&&signal.top()!='(')
                        calculate(number,signal);
                    signal.push(str[i]);
                }
                break;
            }
            case '-':{
                if(signal.empty()||signal.top()=='(')
                    signal.push(str[i]);
                else{
                    while (!signal.empty()&&signal.top()!='(')
                        calculate(number,signal);
                    signal.push(str[i]);
                }
                break;
            }
            case '*':{
                if(signal.empty()||signal.top()=='('||signal.top()=='+'||signal.top()=='-')
                    signal.push(str[i]);
                else{
                    calculate(number,signal);
                    signal.push(str[i]);
                }
                break;
            }
            case '/':
            {if(signal.empty()||signal.top()=='('||signal.top()=='+'||signal.top()=='-')
                    signal.push(str[i]);
                else{
                    calculate(number,signal);
                    signal.push(str[i]);
                }
                break;
        }
            case '(':
                signal.push(str[i]);
                break;
            case ')':{
                while (signal.top() != '(') {
                    calculate(number, signal);
                }
                signal.pop();
                break;
            }
            default:
                double x=str[i]-48;
                number.push(x);
        }
    }
    while (!signal.empty())
        calculate(number, signal);
    cout<<setiosflags(ios_base::fixed)<<setprecision(2)<<number.top()<<endl;
}
int main(){
    int n;
    cin>>n;
    string str;
    for(int i=0;i<n;i++){
        cin>>str;
        operate(str);
    }
}
