#ifndef UNTITLED_ARRAYLIST_H
#define UNTITLED_ARRAYLIST_H
#include<iostream>
#include<string>
using namespace std;
template<class T>
void changeLength1D(T*& a,int olgLength,int newLength);
class student{
public:
    string name;
    long long tele;
    long long classnum;
    long long dorm;
};

class list{
public:
    list(int initialCapacity=10);
    ~list(){delete[]stu;}
    void insert(string n, long long t, long long c, long long d);
    void erase(string n);
    int search(string n);
    void manul(string name, int s, long long New);
    long long output(long long cl);
private:
    int arrayLength;
    int listSize;
    student *stu;
};
template<class T>
void changeLength1D(T*& a,int oldLength,int newLength){
    T* temp=new T[newLength];
    int number=min(oldLength,newLength);
    copy(a,a+number,temp);
    delete []a;
    a=temp;
}
list::list(int initialCapacity){
    arrayLength=initialCapacity;
    stu=new student[arrayLength];
    listSize=0;
}
void list::insert(string n, long long t, long long c, long long d){
    if(listSize=arrayLength){
        changeLength1D(stu,arrayLength,arrayLength*2);
        arrayLength=arrayLength*2;
    }
    stu[listSize].classnum = c;
    stu[listSize].dorm = d;
    stu[listSize].name = n;
    stu[listSize].tele = t;
    listSize++;
}
void list::erase(string n){
    int i;
    for(i=0;i<listSize;i++){
        if(stu[i].name==n)
            break;
    }
    copy(stu+i+1,stu+listSize,stu+i);
    listSize--;
}
int list::search(string n){
    for(int i=0;i<listSize;i++)
        if(stu[i].name==n)return 1;
    return 0;
}
void list::manul(string n, int s, long long New) {
    int i;
    for (i = 0; i < listSize; i++) {
        if (stu[i].name == n) {
            if (s == 1) stu[i].tele = New;
            else if (s == 2) stu[i].classnum = New;
            else if (s == 3) stu[i].dorm = New;
        }
    }
}
long long list::output(long long cl){
    int sum=0;
    for(int i=0;i<listSize;i++){
        if(stu[i].classnum==cl){
            sum=sum^stu[i].dorm;
        }
    }
    return sum;
}
#endif //UNTITLED_ARRAYLIST_H
