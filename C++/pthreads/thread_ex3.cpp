/*************************************************************************
	> File Name: thread_ex3.cpp --- 多数据竞争
	> Author: Frank Liu
	> Mail: frankliu624@gmail.com
	> Created Time: 2018年05月04日 星期五 15时51分40秒
 ************************************************************************/

#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

int num = 100;  //全局变量

void thread01()
{
    while(num > 0)
    {
    	cout << num <<endl;
    	--num;
    	sleep(1);
    }
}

void thread02()
{
    while(num > 0)
    {
    	cout << num <<endl;
    	--num;
    	sleep(1);
    }
}

int main()
{
    thread task01(thread01);
    thread task02(thread02);
    task01.join();
    task02.join();

    return 0;
}
