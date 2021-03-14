

#include <iostream>
using namespace std;

class Node {
public:
    int p;//用于存贮二进制某位的值
    Node* next;//用于找到下一位二进制的节点
    Node(){
        p = -1;//无参构造默认值为-1；
        this->next = NULL;//后继指针设为空
    }
    Node(int num) {
        p = num;//有参构造，将参数转为p值
        this->next = NULL;
    }
};

class NumOp {
public:
    Node* h;//头结点，用于保存inte或frac链表
    Node* firstone = NULL;//右边第一个1的位置
    int flag;//1表示正数，0表示负数
    int k;//小数保留位数
    NumOp(int flag,int k):flag(flag),k(k) {//构造函数
        h = new Node;
    }
    ~NumOp()  {//释放内存
        delete h;
        delete firstone;
    }
    void DtoB(int inte) {//整数部分的原码转换(存在链表h中)      
        do {//建立二进制链表
            Node* node;
            if (inte % 2) {
                node = new Node(1);//整数位为1
                if (!firstone)//目前还没有出现1
                {
                    firstone = node;//保存1的位置
                }
            }
            else {
                node = new Node(0);//整数位为0
            }
            node->next = h->next;
            h->next = node;//将原节点插入到头结点之后（倒序插入）
        } while (inte /= 2);//当商为0结束
    }
    void DtoB(double frac) {//小数部分的原码转换(存在链表h中)      
        Node* last = h;//链表尾结点
        int i = 0;
        while (frac *= 2) {//建立二进制链表,循环k次自动停止
            if (i++ >= k) break;//k次后结束循环
            Node* node;
            if (frac >= 1) {
                node = new Node(1);//整数位为1
                firstone = node;//记录最右边第一个1的位置
                frac--;
            }
            else {
                node = new Node(0);//整数位为0
            }
            last->next = node;
            last = node;//将原节点插入到尾结点之后（正序插入）
        };
    }
    void Out1() {//负数输出（输出头结点到firstone节点数据的取反值，和剩余节点的原值（右边第一个1和之后的0））
        Node* pre = h, * pr = h->next;//遍历链表，输出二进制结果
        while (pr != firstone) {//节点还没遍历到最右的1
            pre = pr;
            pr = pr->next;//循环前进
            if (pre) {
                cout << !(pre->p);//输出相反值
            }
            delete pre;//释放节点
        } 
        while (pr) {//输出之后所有节点数据
            pre = pr;
            pr = pr->next;
            if (pre) {
                cout << pre->p;//输出原值
            }
            delete pre;//释放节点
        }
    }
    void Out2() {//正数输出
        Node* pre = h,*pr = h->next;//遍历链表，输出二进制结果
        while (pr) {  //输出所有节点数据
            pre = pr;
            pr = pr->next;  //循环前进        
            if (pre) {
                cout << pre->p;//输出原值
            }
            delete pre;//释放节点
        }
    }
    void Change(int inte,double frac) {
        DtoB(inte);        
        if (flag) {//正数or +0
            cout << 0;//表示正数
            Out2();//使用正数的输出函数
            cout << ".";         //输出小数点
            DtoB(frac);//小数部分的转化，
            Out2();//使用正数的输出函数
        }
        else if(frac == 0){//负数且小数为0
            cout << 1;//表示负数
            Out1();//只处理整数，使用取反加一的输出函数
        }
        else {//正常负数
            cout << 1;//表示负数
            firstone = NULL;//整数不需要加一，将firstone定位到末尾（NULL）
            Out1();//使用负数的输出函数
            cout << ".";
            DtoB(frac);//处理负数
            Out1();//使用负数的输出函数
        }
    }
};

int main()
{
    unsigned int inte;
    double frac;//保存数字的整数部分和小数部分
    int k;//小数的保留位数
    int flag;//保存正负数，1为正，0为负
    cout << "the sample of input: 0(negative) 12(must be a inte) 0.8(no more than 1) 9(int)" << endl;
    cout << "positive:1/negative:0" << endl;
    cin >> flag;
    cout << "Please input the integer" << endl;
    cin >> inte;
    cout << "Please input the fraction" << endl;
    cin >> frac;
    cout << "Please input the num of fraction" << endl;
    cin >> k;
    
    NumOp* numop = new NumOp(flag, k);
    numop->Change(inte, frac);//调用转换函数
}

