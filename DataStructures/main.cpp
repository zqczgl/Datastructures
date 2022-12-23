#include "booster.h"
void check() {
    int flag = 0;
    stringstream ss;
    for (int i = 1; i <= 100; i++) {
        cout << "正在测试数据集: " << i << "\n";
        string opstd = "C:\\Users\\86151\\Desktop\\Data\\output\\";
        string myin = "C:\\Users\\86151\\Desktop\\Data\\myoutput\\";
        opstd += to_string(i) + ".out";
        myin += to_string(i) + ".out";
        ifstream finstd(opstd);
        int ans; finstd >> ans;
        finstd.close();
        ifstream finmy(myin);
        int me; finmy >> me;
        finmy.close();
        cout<<"myout       out"<<endl;
        cout<<me<<"            "<<ans<<endl;
        if (me != ans) {
            cout << "Wrong Answer\n";
            ss << i << "WA！\n";
            flag = 1;
        }
        else {
            cout << "Accept\n";
        }
    }
    if (!flag) {
        cout << "All Accept!\n";
    }
    else cout << "Some Wrong\n";
    cout << ss.str();
}
int main(){
    clock_t startTime,endTime;
    startTime = clock();//计时开始
    for (int i = 1; i <= 100; ++i) {
        string input = "C:\\Users\\86151\\Desktop\\Data\\input\\input";
        string myout = "C:\\Users\\86151\\Desktop\\Data\\myoutput\\";
        input += to_string(i) + ".in";
        myout += to_string(i) + ".out";
        fin=ifstream(input);
        graph g=graph();
        g.topsort();
        g.branch_bound();
        // g.backtracking(2,0);
        ofstream fout(myout);
        fout<<g.bestRes;
    }
    endTime = clock();//计时结束
    cout << "运行总时间为: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    check();
}

