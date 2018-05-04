/*************************************************************************
	> File Name: pthread_test1.cpp -- 创建和终止线程
	> Author: Frank Liu 
	> Mail: frankliu624@gmail.com
	> Created Time: 2018年05月04日 星期五 09时45分49秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#define NUM_THREADS 8

using namespace std;

//线程运行函数，函数返回的是函数指针，便于后面作为参数
void* say_hello(void* args)
{
    cout << "Hello pthread!" <<endl;
}

int main()
{
    pthread_t tids[NUM_THREADS];
    for(int i=0; i < NUM_THREADS; ++i)
    {
        //参数：线程id、线程参数、调用的函数、传入函数的参数
        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        if(ret != 0)
        {
            cout << "pthread_create error: error_code=" << ret <<endl;
            exit(-1);
        }
    }
    //等待线程退出后，进程才结束：
    pthread_exit(NULL);

    return 0;
}
