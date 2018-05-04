/*************************************************************************
	> File Name: thread_ex2.cpp --- thread类,detach()不阻塞主线程
	> Author: Frank Liu
	> Mail: frankliu624@gmail.com
	> Created Time: 2018年05月04日 星期五 15时42分43秒
 ************************************************************************/

#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

void thread01()
{
    for(int i=0; i < 5; ++i)
    {
        cout << "Thread 01 is working!" <<endl;
        sleep(1);
    }
}

void thread02()
{
    for(int i=0; i < 5; ++i)
    {
        cout << "Thread 02 is working!" <<endl;
        sleep(1);
    }
}

int main()
{
    thread task01(thread01);
    thread task02(thread02);
    task01.detach();
    task02.detach();
    for(int i=0; i < 5; ++i)
    {
        cout << "Main thread is working." <<endl;
        sleep(1);
    }

    return 0;
}
