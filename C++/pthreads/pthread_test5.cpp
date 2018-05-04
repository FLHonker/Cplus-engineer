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

int sum = 0; //定义全局变量，让所有线程同时写，这样就需要锁机制
pthread_mutex_t sum_mutex; //互斥锁

//线程运行函数，函数返回的是函数指针，便于后面作为参数
void* say_hello(void* args)
{
    int tid = *((int*)args);  //对传入的参数强制类型转换
    cout << "Hello pthread! thread_ID: " << tid <<endl;
    pthread_mutex_lock( &sum_mutex ); //先加锁，再修改sum的值，锁被占用就阻塞，直到拿到锁再修改sum
    cout << "before sum is " << sum;
    sum += tid; 
    cout << ", after sum is " << sum << endl; 	
    pthread_mutex_unlock( &sum_mutex ); //释放锁，供其他线程使用
    pthread_exit(0);
}

int main()
{
    pthread_t tids[NUM_THREADS];
    pthread_attr_t attr;  //线程属性结构体，创建线程时加入的参数
    void *status;
    //初始化并设置为可连接的(joinable)
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init( &sum_mutex, NULL ); //对锁进行初始化
    for(int i=0; i < NUM_THREADS; ++i)
    {
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
    cout << "finally sum is " << sum << endl;
    pthread_mutex_destroy( &sum_mutex ); //注销锁
    //等待线程退出后，进程才结束：
    pthread_exit(NULL);

    return 0;
}
