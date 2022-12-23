#include "iostream"
#include "algorithm"
using namespace std;
    int main(){
    int n;
    cin>>n;
    int num[n];
    int count=0;
        for (int i = 0; i < n; ++i) {
            cin>>num[i];
        }
        sort(num,num,num+n);
        for (int i = 1; i <n ; ++i) {
            if(num[i]-num[i-1]==1){
                count++;
            }
            cout<<count;
        }
}


