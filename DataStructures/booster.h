
#ifndef UNTITLED_BOOSTER_H
#define UNTITLED_BOOSTER_H
#include "bits/stdc++.h"
using namespace std;
ifstream fin;
struct btnode {//用于分支定界的子集树
    btnode* parent;//指向父节点
    int press;//
    int level;//子集树层级
    bool have_bt;//是否放放大器
    int bstnum;//优先级 从根到节点x的路径上的bst个数
    btnode() {
        parent = NULL;
        press = 0; level = 0; have_bt = false;
        bstnum = 0;

    }
    btnode(int pres, int lev, btnode* par = NULL, int bstn = 0) {
        parent = par;
        press = pres; level = lev;
        bstnum = bstn;
        have_bt = false;
    }
};
class Edge {
public:
    int to;// 终点编号
    int cost;// 长度
    Edge(int to, int cost) : to(to), cost(cost) {}
    ~Edge() {}
};
class Node {
public:
    vector<Edge> edges;//记录所有出边
    int press;
    bool booster;
    int max_to_cost;//以该点为起点的最长边
    int toponum;//按拓扑序是第几
    Node() {
        press = 0;
        booster = false;
        edges.clear();
        max_to_cost = 0;
        toponum = 0;
    }
    ~Node() {}
};

struct cmp
{
    bool operator () (const btnode* p1, const btnode* p2) {
        return p1->bstnum > p2->bstnum;
    }
};

class graph {
private:
    int Pmin, Pmax;
    vector<Node> nodes;// 点
    vector<int> in_deg;//各点的入度
    vector<int> topo;//拓扑序列
    vector<bool> place_bst;//是否要放在这
    priority_queue<btnode*, vector<btnode*>, cmp> pq;//最小堆
public:
    int n, m;//顶点数 边
    graph() {
        fin >> n >> m >> Pmax;
        Pmin = 0;
        bestRes = INT_MAX;
        in_deg.resize(n + 1, 0);
        topo.resize(n + 1, 0);
        place_bst.resize(n + 1, false);
        //初始化顶点
        for (int i = 0; i <= n; i++)
            nodes.emplace_back(Node());
        //读入边
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            fin >> u >> v >> w;
            nodes[u].edges.emplace_back(v, w);
            //修改入度
            in_deg[v]++;
            nodes[u].max_to_cost = max(nodes[u].max_to_cost, w);
        }
        nodes[1].press = Pmax;
        place_bst[1] = true;
    }
    ~graph() {}
    int bestRes;//最优解 数目
    void topsort();//拓扑排序
    void backtracking(int level, int cnt);//回溯解决
    void branch_bound();//分支定界解决

};
void graph::topsort()
{//确定一个拓扑序列 以便后续
    int cnt = 1;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        nodes[u].toponum = cnt;
        topo[cnt] = u;//排序
        cnt++;
        for (auto e : nodes[u].edges) {
            if (--in_deg[e.to] == 0)
                q.push(e.to);
        }
    }
}
// 回溯  剪枝
void graph::backtracking(int level, int cnt)
{
    int u = topo[level];//当前点
    if (level >= n) {//到了最底层
        if(bestRes>cnt) {
            bestRes = cnt;
            for (int i = 1; i <= n; i++) {
                place_bst[i] = false;
                place_bst[i] = nodes[i].booster;
            }
        }
        return;
    }
    int j;
    int flag = 0;
    int temp_pre = INT32_MAX;
    for (int k = 1; k < level; k++) {
        for (auto& x : nodes[topo[k]].edges) {
            if (x.to == u)
                temp_pre = min(temp_pre, nodes[topo[k]].press - x.cost);
        }
    }
    for (j = 0; j < 2; j++)//对于每个点都有放放大器和不放放大器两种可能
    {
        if (j == 0) {//决策为不放，但是发现此点必须放。
            for (auto& v : nodes[u].edges) {//对于所有出边进行判断
                int next_pr = temp_pre - v.cost;
                if (next_pr < Pmin) {
                    flag = 1;
                    break;
                }
            }
        }
        if (j == 1 || flag == 1) {//放
            cnt++;
            nodes[u].press = Pmax;
            nodes[u].booster = true;
            //剪枝
            if (cnt >= bestRes)
                return;
            else {
                backtracking(level + 1, cnt);
            }
        }else if (j == 0) {//不放
            nodes[u].press = temp_pre;
            nodes[u].booster = false;
            backtracking(level + 1, cnt);
        }
    }
}
//分支定界
void graph::branch_bound()
{//分支定界通过活节点扩张来生成子集树
    btnode* enode = new btnode(Pmax, 1);//活结点
    int level = 1;
    while (level <= n - 1)
    {//进行活结点的拓展
        int vert = topo[level+1];//该层扩展的节点
        int temp_press = INT32_MAX;
        int flag = 0;
        //求扩展结点的压力
        for (int k = 1; k <= level ; k++) {
            for (auto& e : nodes[topo[k]].edges) {
                if (e.to == vert) {
                    btnode* p = enode;
                    for (int j = level; j > k; j--)
                        p = p->parent;
                    temp_press = min(temp_press, p->press - e.cost);
                }
            }
        }
        //必须放
        if (temp_press - nodes[vert].max_to_cost < Pmin) {
            flag = 1;
        }
        if (flag == 0) {//两种 放或者放

            btnode* t = new btnode(temp_press, level + 1, enode, enode->bstnum);
            pq.push(t);
            btnode* tt = new btnode(Pmax, level + 1, enode, enode->bstnum + 1);
            tt->have_bt = true;
            pq.push(tt);
        }
        else {
            btnode* tt = new btnode(Pmax, level + 1, enode, enode->bstnum + 1);
            tt->have_bt = true;
            pq.push(tt);
        }
        enode = pq.top(); pq.pop();
        level = enode->level;
    }
    bestRes = enode->bstnum;
    btnode* p = enode;
    while (p) {
        place_bst[topo[p->level]] = p->have_bt;
        p = p->parent;
    }
}
#endif //UNTITLED_BOOSTER_H
