/*************************************************************************
	> File Name: arrow_opt_ovload.cpp
	> Author: Frank Liu
	> Mail: frankliu624@gmail.com
	> Created Time: 2018年04月26日 星期四 16时37分58秒
 ************************************************************************/

#include<iostream>
using namespace std;

class A 
{
public:
    void action()
    {
        cout << "Action in class A!" <<endl;
    }
};

class B 
{
    A a;
public:
    A* operator->()   //oveerloading ->
    {
        return &a;
    }

    void action()
    {
        cout << "Action in class B!" <<endl;
    }
};

class C
{
    B b;
public:
    B operator->()
    {
        return b;
    }

    void action()
    {
        cout << "Action in class C!" <<endl;
    }
};

int main()
{
    //情况1:对象指针引用成员函数
    C *pc = new C;
    pc->action();
    //情况2:递归寻找带有成员action()的类对象指针
    C c;
    c->action();

    return 0;
}
