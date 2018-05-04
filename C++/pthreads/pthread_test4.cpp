/*************************************************************************
	> File Name: pthread_test4.cpp  -- 线程的连接和分离
	> Author: Frank Liu 
	> Mail: frankliu624@gmail.com
	> Created Time: 2018年05月04日 星期五 14时13分13秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#define NUM_THREADS 8

using namespace std;

//线程运行函数，函数返回的是函数指针，便于后面作为参数
void* say_hello(void* args)
{
    int tid = *((int*)args);  //对传入的参数强制类型转换
    sleep(1);
    cout << "Sleeping inthread..." <<endl;
    cout << "Hello pthread! thread_ID: " << tid << "...exiting." <<endl;
    pthread_exit(NULL);
}

int main()
{
    pthread_t tids[NUM_THREADS];
    pthread_attr_t attr;
    void *status;
    //初始化并设置为可连接的(joinable)
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for(int i=0; i < NUM_THREADS; ++i)
    {
        cout << "main():创建线程," << i <<endl;
        //参数：线程id、线程参数、调用的函数、传入函数的参数
        int ret = pthread_create(&tids[i], NULL, say_hello, (void*)&i);
        if(ret != 0)
        {
            cout << "pthread_create error: error_code=" << ret <<endl;
            exit(-1);
        }
    }
    
    pthread_attr_destroy(&attr);  //删除属性，并等待其他线程
    for(int i=0; i < NUM_THREADS; ++i)
    {
    	int ret = pthread_join(tids[i], &status);
    	if(ret)
        {
            cout << "Error:unable to join," << ret <<endl;
            exit(-1);
        }
        cout << "Main: completed thread id :" << i;
        cout << ", exiting with status:" << status << endl; 
    }
    cout << "Main: program exiting." << endl; 
    //等待线程退出后，进程才结束：
    pthread_exit(NULL);

    return 0;
}
