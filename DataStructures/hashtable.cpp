#include<iostream>
using namespace std;
template<class K,class E>
class hashTable{
    pair<K,E> **table;
    int dSize;
    int divisor;
public:
    hashTable(int theDivisor);
    int search(const K& theKey) const;
    int find(const K& theKey);
    void insert(const pair<K,E>&thePair);
    void erase(const K& theKey);
};
template<class K,class E>
hashTable<K,E>::hashTable(int theDivisor) {
    divisor=theDivisor;
    dSize=0;
    table=new pair<K,E>*[divisor];
    for(int i=0;i<divisor;i++)
        table[i]=NULL;
}
template<class K,class E>
int hashTable<K, E>::search(const K &theKey) const {
    int i=(int) theKey%divisor;
    int j=i;
    do{
        if(table[j]==NULL||table[j]->first==theKey)
            return j;
        j=(j+1)%divisor;
    } while (j!=i);
    return j;
}
template<class K,class E>
int hashTable<K,E>::find(const K &theKey) {
    int b= search(theKey);
    if(table[b]!=NULL&&table[b]->first==theKey)
        return b;
    return -1;
}
template<class K,class E>
void hashTable<K,E>::insert(const pair<K, E> &thePair) {
    int b= search(thePair.first);
    if(table[b]==NULL){
        table[b]=new pair<K,E>(thePair);
        cout<<b<<endl;
        dSize++;
    }else{
        if(table[b]->first==thePair.first){
            cout<<"Existed"<<endl;
        }
    }
}
template<class K, class E>
void hashTable<K, E>::erase(const K & theKey){
    int b = search(theKey);
    if (table[b] == NULL || table[b]->first != theKey)
        cout << "Not Found" << endl;
    else
    {
        delete table[b];
        table[b] = NULL;
        int count = 0;
        int i = b, m = b, signal;
        do
        {
            i = (i + 1) % divisor;
            if (table[i] == NULL)
                break;
            signal = table[i]->first % divisor;
            if ((signal <= m && m < i) || (signal <= m &&i < signal  ) || (i < signal && m < i))
            {
                table[m] = table[i];
                table[i] = NULL;
                m = i;
                count++;
            }
        } while ( i != b);
        cout << count << endl;
    }
}
int main(){
    int d,m;
    cin>>d>>m;
    hashTable<int,int> hashTable(d);
    for(int i=0;i<m;i++){
        int flag,x;
        pair<int,int> p;
        cin>>flag>>x;
        p.first=x,p.second=x;
        switch (flag) {
            case 0: hashTable.insert(p);break;
            case 1:cout<<hashTable.find(p.first)<<endl;break;
            case 2:hashTable.erase(p.first);
        }
    }
}