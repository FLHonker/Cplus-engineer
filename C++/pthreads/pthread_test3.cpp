/*************************************************************************
	> File Name: pthread_test3.cpp -- 向线程传入自定义参数（结构体）
	> Author: Frank Liu 
	> Mail: frankliu624@gmail.com
	> Created Time: 2018年05月04日 星期五 13时41分13秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#define NUM_THREADS 8

using namespace std;

typedef struct thread_data
{
	int thread_id;
	char *message;
}thread_data;

//线程运行函数，函数返回的是函数指针，便于后面作为参数
void* printMsg(void* args)
{
    thread_data *my_data = (thread_data*)args;;  //对传入的参数强制类型转换
    cout << "thread_ID: " << my_data->thread_id << ", Message:" << my_data->message <<endl;
    pthread_exit(NULL);
}

int main()
{
    pthread_t tids[NUM_THREADS];
    thread_data mydatas[NUM_THREADS];
    for(int i=0; i < NUM_THREADS; ++i)
    {
        cout << "main():创建线程," << i <<endl;
        mydatas[i].thread_id = i;
        mydatas[i].message = "Hello,pthread!";
        //参数：线程id、线程参数、调用的函数、传入函数的参数
        int ret = pthread_create(&tids[i], NULL, printMsg, (void*)&mydatas[i]);
        sleep(1);   //sleep 1s
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
