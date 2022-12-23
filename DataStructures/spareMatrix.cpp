#include<iostream>
#include <vector>
using namespace std;
template<class T>
struct matrixTerm{
    matrixTerm(){}
    matrixTerm(int row,int col,T value){this->value=value;this->col=col;
        this->row=row;}
    int row,col;
    T value;
};
template<class T>
class spareMatrix
{
    friend istream& operator>>(istream& in,spareMatrix<T>& x){
        int numberOfTerms;
        in>>x.rows>>x.cols>>numberOfTerms;
        x.terms.resize(numberOfTerms);
        matrixTerm<T> mTerm;
        for(int i=0;i<numberOfTerms;i++){
            in>>mTerm.row>>mTerm.col>>mTerm.value;
            x.terms[i]=mTerm;
        }
        return in;
    }
    public:
        void output();
        void set();
        void Set(int theRow,int theColumn,T theValue);
        void transpose();
        void add(spareMatrix<T> &b);
        void multi(spareMatrix<T> &b);
        T get(int theRow,int theColumn);
    private:
        int rows,cols;
        vector<matrixTerm<T>> terms;
};
template<class T>
void spareMatrix<T>::output() {
    cout<<rows<<" "<<cols<<endl;
    typename vector<matrixTerm<T>>::iterator p=terms.begin();
    for(int i=1;i<=rows;i++){
        for(int j=1;j<=cols;j++){
            if(p!=terms.end()&&i==(*p).row&&j==(*p).col){
                cout<<(*p).value<<" ";
                p++;
            }
            else
                cout<<0<<" ";
        }
        cout<<endl;
    }
}
template<class T>
void spareMatrix<T>::set(){
    terms.clear();//清空数据
    cin>>rows>>cols;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            T temp;
            cin>>temp;
            if(temp!=0){
                matrixTerm<T> mTerm;
                mTerm.row=i+1; mTerm.col=j+1;mTerm.value=temp;
                terms.push_back(mTerm);
            }
        }
    }
}
template<class T>
void spareMatrix<T>::transpose() {
    {
        spareMatrix<T> b;
        b.cols = rows;
        b.rows = cols;
        b.terms.resize(terms.size());
        int* colSize = new int[cols + 1];
        int* rowNext = new int[cols + 1];
        for (int i = 1; i <= cols; i++)
            colSize[i] = 0;
        for (typename vector<matrixTerm<T>>::iterator i=terms.begin();i!=terms.end();
        i++)
            colSize[(*i).col]++;
        rowNext[1] = 0;
        for (int i = 2; i <= cols; i++)
            rowNext[i] = rowNext[i - 1] + colSize[i - 1];
        matrixTerm<T> mTerm;
        for(typename vector<matrixTerm<T>>::iterator i=terms.begin();i!=terms.end();
            i++ )
        {
            int j=rowNext[(*i).col]++;
            mTerm.row=(*i).col;
            mTerm.col=(*i).row;
            mTerm.value=(*i).value;
            b.terms[j]=mTerm;
        }
        *this = b;
    }
}
template<class T>
void spareMatrix<T>::Set(int theRow,int theColumn,T theValue){
    if(get(theRow,theColumn)!=0){
        for (typename vector<matrixTerm<T>>::iterator i=terms.begin();i!=terms.end();
             i++){
            if((*i).row==theRow&&(*i).col==theColumn)
                (*i).value=theValue;
        }
    }else{
        terms.resize(terms.size()+1);
        typename vector<matrixTerm<T>>::iterator i=terms.begin();
        for (;i!=terms.end();i++){
            if(theRow*cols+theColumn<(*i).row*cols+(*i).col){
                break;
            }
        }
        matrixTerm<T> mterm;
        mterm.row=theRow; mterm.col=theColumn;mterm.value=theValue;
        terms.insert(i,mterm);
    }
}
template<class T>
void spareMatrix<T>:: add(spareMatrix<T> &b){
    spareMatrix<T> c;
    if(b.cols!=cols||b.rows!=rows){
        *this=b;
        cout<<-1<<endl;
        return;
    }
    c.rows=rows;
    c.cols=cols;
    c.terms.clear();
    typename vector<matrixTerm<T>>::iterator it=terms.begin();
    typename vector<matrixTerm<T>>::iterator ib=b.terms.begin();
    typename vector<matrixTerm<T>>::iterator itEnd=terms.end();
    typename vector<matrixTerm<T>>::iterator ibEnd=b.terms.end();
    while(it!=itEnd && ib!=ibEnd){
        int tIndex=(*it).row*cols+(*it).col;
        int bIndex=(*ib).row*cols+(*ib).col;
        if(tIndex<bIndex){
            c.terms.push_back(*it);
            it++;
        }
        else{
            if(tIndex==bIndex){
                if((*it).value+(*ib).value!=0){
                    matrixTerm<T> mTerm;
                    mTerm.row=(*it).row;
                    mTerm.col=(*it).col;
                    mTerm.value=(*it).value+(*ib).value;
                    c.terms.push_back(mTerm);
                }
                it++;ib++;
            }
            else{
                c.terms.push_back(*ib);
                ib++;
            }
        }
    }
    for(;it!=itEnd;it++)
        c.terms.push_back(*it);
    for(;ib!=ibEnd;ib++)
        c.terms.push_back(*ib);
    *this=c;
}
template<class T>
void spareMatrix<T>::multi(spareMatrix<T> &b){
    if(cols!=b.rows){//不符合乘法条件直接输出
        *this=b;
        cout<<-1<<endl;
        return;
    }
    spareMatrix<T> c;//存相乘后的矩阵
    c.rows = rows;
    c.cols=b.cols;
    int* rowSize = new int[b.rows + 1];//b矩阵的每一行非零元素数
    int *rowNext=new int[b.rows+1];//b矩阵每一行第一个非零元素索引
    T *temp=new T[b.cols+1];//临时储存数组
    for (int i = 1; i <= b.rows; i++)
        rowSize[i] = 0;
    for (typename vector<matrixTerm<T>>::iterator i=b.terms.begin();i!=b.terms.end();
         i++)
        rowSize[(*i).row]++;
    rowNext[1]=0;
    for(int i=2;i<=b.rows;i++)
        rowNext[i]=rowNext[i-1]+rowSize[i-1];
    typename vector<matrixTerm<T>>::iterator p=terms.begin();
    for(int i=1;p!=terms.end()&&i<=rows;i++){//逐行来构造结果矩阵
        for(int i=1;i<=b.cols;i++)
            temp[i]=0;
        while(p!=terms.end()&&(*p).row==i){
        int col=(*p).col;
        if(rowSize[col]!=0){
            for(int i=rowNext[col];i<rowNext[col]+rowSize[col];i++){
                temp[b.terms[i].col]+=(*p).value*b.terms[i].value;
            }
        }
        p++;
        }
        for(int j=1;j<=b.cols;j++){
            if(temp[j]!=0){//只存非零的元素
            matrixTerm<T> mTerm;
            mTerm.row=i;
            mTerm.col=j;
            mTerm.value=temp[j];
            c.terms.push_back(mTerm);}
        }
    }
    *this=c;
}
template<class T>
T spareMatrix<T>::get(int theRow,int theColumn){
    for (typename vector<matrixTerm<T>>::iterator i=terms.begin();i!=terms.end();
         i++){
        if((*i).row==theRow&&(*i).col==theColumn)
            return (*i).value;
        return 0;
    }
}
int main() {
    /*int n;
    cin >> n;
    spareMatrix<int> a;
    for (int i = 0; i < n; i++) {
        int flag;
        cin >> flag;
        switch (flag) {
            case 1:
                a.set();
                break;
            case 2:
            {spareMatrix<int> b;
                cin >> b;a.multi(b);
                break;}
            case 3:{
                spareMatrix<int> b;
                cin >> b;a.add(b);
                break;
            }
            case 4:
                a.output();
                break;
            case 5:
                a.transpose();
        }
    }*/
    spareMatrix<int> a;
    a.set();
    a.output();
    a.Set(4,3,6);
    a.output();
}