#include <stack>
#include <cstring>
#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
struct Node {   //节点
    struct Node *parent;//父指针
    struct Node *FirstChild;//第一个儿子指针
    struct Node *brother;//兄弟指针
    bool is_file;//是文件还是目录
    string fileName;
};
class CatalogTree{
public:
    CatalogTree();
    ~CatalogTree(){ deletef("/");}
    string getiPath();
    void cd();
    void cd(string str);
    void cdParent();
    void dir();
    void mkdir(string str);
    void mkfile(string str);
    void deletef(string str);
    void save(string str);
    void load(string str);
private:
    Node *root;//根节点
    Node* currentPosition;//当前位置
    void recSave(Node* position, int Depth , FILE *file);
};
CatalogTree::CatalogTree(){
    root=new Node;
    root->parent=NULL;
    root->FirstChild=NULL;
    root->brother=NULL;
    root->is_file=false;
    root->fileName="/";
    currentPosition=root;
}
void CatalogTree::mkdir(string str){
    Node* temp;
    for (temp = currentPosition->FirstChild; temp != NULL; temp = temp->brother) {
        if (temp->fileName==str) {
            return;
        }
    }
    temp = new Node;
    temp->parent = currentPosition;
    temp->FirstChild = NULL;
    temp->is_file = false;
    temp->fileName=str;
    temp->brother = currentPosition->FirstChild;//永远将新文件作为第一个文件
    currentPosition->FirstChild = temp;
}

void CatalogTree::mkfile(string str) {
    Node* temp;
    for (temp = currentPosition->FirstChild; temp != NULL; temp = temp->brother) {
        if (temp->fileName==str) {
            return;
        }
    }
    temp = new Node;
    temp->parent = currentPosition;
    temp->FirstChild = NULL;
    temp->is_file = true;
    temp->fileName=str;
    temp->brother = currentPosition->FirstChild;//永远将新文件作为第一个文件
    currentPosition->FirstChild = temp;
}

void CatalogTree::cdParent() {
    if(currentPosition->parent!=NULL)
        currentPosition=currentPosition->parent;
}

string CatalogTree::getiPath() {
    string result="";
    Node* temp=currentPosition;
    stack<string> stack;
    while (temp!=NULL){
        stack.push(temp->fileName);
        temp=temp->parent;
    }
    while (!stack.empty()){
        bool flag=true;
        result+=stack.top();
        if(stack.top()=="/") flag= false;
        stack.pop();
        if(flag&&!stack.empty())
            result+="/";
    }
    return result;
}
void CatalogTree::cd() {
    Node* temp=currentPosition;
    stack<string> stack;
    while (temp!=NULL){
        stack.push(temp->fileName);
        temp=temp->parent;
    }
    while (!stack.empty()){
        bool flag=true;
        cout<<stack.top();
        if(stack.top()=="/") flag= false;
        stack.pop();
        if(flag&&!stack.empty())
            cout<<"/";
    }
    cout<<endl;
}
void CatalogTree::dir() {
    if(currentPosition->FirstChild==NULL){
        return;
    }
    Node *temp;
    vector<string> files;
    vector<string> dirs;
    for (temp = currentPosition->FirstChild; temp != NULL; temp = temp->brother) {
        if(temp->is_file) files.push_back(temp->fileName);
        else dirs.push_back(temp->fileName);
    }
    sort(files.begin(),files.end());
    sort(dirs.begin(),dirs.end());
    for (int i = 0; i < files.size(); ++i) {
        cout<<files[i]<<"*\n";
    }
    for (int i = 0; i < dirs.size(); ++i) {
        cout<<dirs[i]<<endl;
    }
}
void CatalogTree::deletef(string str) {
    Node* temp,*pre=NULL;
    for (temp = currentPosition->FirstChild; temp != NULL; temp = temp->brother) {
        if (str == temp->fileName) {
            if(temp->is_file){//如果是文件
                if(pre==NULL){
                    temp->parent->FirstChild = temp->brother;
                }else{
                    pre->brother=temp->brother;
                }
                delete temp;
            }else{//如果是目录
                if (temp->FirstChild == NULL) {//目录没有文件，直接删除
                    if (temp == root) return;
                    if (temp->parent->FirstChild == temp) {
                        temp->parent->FirstChild = temp->brother;
                    }
                    else{
                        pre->brother=temp->brother;
                    }
                    delete temp;
                }else {//目录里面有文件要把文件也删除
                    Node* position=currentPosition;
                    while (temp->FirstChild!=NULL){
                        currentPosition=temp->FirstChild;
                        deletef(temp->FirstChild->fileName);
                    }
                    currentPosition=position;
                }
            }
            break;
        }
        pre=temp;
    }
}
void CatalogTree::cd(string str) {
    Node* temp;
    if (str[0] == '/') {//如果第一个字符为'/',证明是绝对路径
        Node* t = root;
        bool flag;
        string p;
        int left=1,right=1;
        while (right<str.size())
        {
            while (right<str.size()&&str[right]!='/')right++;
            p=str.substr(left,right-left);
            flag = false;
            for (temp = t->FirstChild; temp != NULL; temp = temp->brother) {
                if (temp->fileName == p&&temp->is_file == false) {
                    t = temp;//不断修改t的值
                    flag = true;
                    break;
                }
            }
            if (flag == false ) {
                return;
            }
            left=right=right+1;
        }
        currentPosition = t;
    }else{//相对路径
        Node* t = currentPosition;
        bool flag;
        string p;
        int left=0,right=1;
        if(str.size()==1){//特殊情况str就一个字符
            flag = false;
            for (temp = t->FirstChild; temp != NULL; temp = temp->brother) {
                if (temp->fileName == str&&temp->is_file == false) {
                    t = temp;
                    flag = true;
                    break;
                }
            }
            if (flag == false ) {
                return;
            }
            currentPosition = t;
            return;
        }
        while (right<str.size())
        {
            while (right<str.size()&&str[right]!='/')right++;
            p=str.substr(left,right-left);
            flag = false;
            for (temp = t->FirstChild; temp != NULL; temp = temp->brother) {
                if (temp->fileName == p&&temp->is_file == false) {
                    t = temp;
                    flag = true;
                    break;
                }
            }
            if (flag == false ) {
                return;
            }
            left=right=right+1;
        }
        currentPosition = t;
    }
}
void  CatalogTree::recSave(Node* position, int Depth , FILE *file)//从文件打印出目录结构
{
    Node* temp;
    if (position != NULL) {
        for (int i = 0; i < Depth; i++) {
            fprintf(file , "\t");
        }
        if (position->is_file == true) {
            fprintf(file, "%s .f\n", position->fileName.c_str());
        }
        else {
            fprintf(file, "%s .d\n", position->fileName.c_str());
        }

        if (position->is_file == false)
            for (temp = position->FirstChild; temp != NULL; temp = temp->brother)
                recSave(temp, Depth + 1, file);
    }
}
void CatalogTree::save(string str) {
    string filename="C:\\Users\\86151\\Desktop\\data\\input\\"+str;
    FILE* file = fopen(filename.c_str(), "w");
    fprintf(file, "%s\n", getiPath().c_str());//第一行记录当前的位置
    recSave(this->root, 0, file);//将目录结构存入文件
    fclose(file);
}
void  recLoad(CatalogTree *tree , char *preDir, int preDepth, FILE *file)//将文件中内容载入
{
    char buf[120];
    char type[3];
    char subBuf[100];
    memset(buf, 0, sizeof(buf));
    memset(type, 0, sizeof(type));
    memset(subBuf, 0, sizeof(subBuf));
    int i;
    int t_n = 0;
    fgets(buf, sizeof(buf), file);//读取一行数据fgets读到换行符会停止
    if (strlen(buf) == 0) return;//如果读到文件末尾，结束
    strncpy(type, buf + strlen(buf) - 3, 2);//获取改行数据是文件还是目录
    for (i = 0; buf[i] == '\t'; i++) {//判断文件是哪一级的
        t_n++;
    }
    if (i == 0) recLoad(tree, "/", 0, file);//根目录
    else
    {

        strncpy(subBuf, buf + t_n, strlen(buf) - 4 - t_n);//文件名字
        if (t_n > preDepth) {//比上一行多说明是上一行的子文件
            tree->cd(preDir);
        }
        else if (t_n < preDepth) {//回到本行的父亲节点
            for (int j = t_n; j < preDepth; j++) {
                tree->cdParent();
            }
        }
        if (strcmp(type, ".d") == 0) {//目录
            tree->mkdir(subBuf);
        }
        else {//文件
            tree->mkfile(subBuf);
        }
        recLoad(tree, subBuf, t_n, file);//读下一行
    }
}
void CatalogTree::load(string str) {//搜索当前位置的路径，使用递归
    string filename="C:\\Users\\86151\\Desktop\\data\\input\\"+str;
    FILE *file = fopen(filename.c_str(), "r");
    char buf[120];
    fgets(buf, sizeof(buf), file);
    buf[strlen(buf)-1]=0;
    recLoad(this, "/", 0, file);
    cd(buf);
    fclose(file);
}
