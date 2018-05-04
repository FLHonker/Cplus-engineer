/*************************************************************************
	> File Name: pthread_test6.cpp  -- 信号量机制
	> Author: Frank Liu
	> Mail: frankliu624@gmail.com
	> Created Time: 2018年05月04日 星期五 14时53分57秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#define BOUNDARY 5
using namespace std;

int tasks = 10;
pthread_mutex_t tasks_mutex; //互斥锁
pthread_cond_t tasks_cond; //条件信号变量，处理两个线程间的条件关系，当task>5，hello2处理，反之hello1处理，直到task减为0

void* say_hello2(void* args)
{
	pthread_t pid = pthread_self(); //获取当前线程id
	cout << "[" << pid << "] hello in thread " << *((int*)args) << endl;
	bool is_signaled = false; //sign
	while(1)
	{
		pthread_mutex_lock( &tasks_mutex ); //加锁        
		if( tasks > BOUNDARY )        
		{
			cout << "[" << pid << "] take task: " << tasks << " in thread " << *((int*)args) << endl;
			--tasks; //modify        
		}
		else if( !is_signaled )
		{
			cout << "[" << pid << "] pthread_cond_signal in thread " << *((int*)args) << endl;
			pthread_cond_signal( &tasks_cond ); //signal:向hello1发送信号，表明已经>5            	
			is_signaled = true; //表明信号已发送，退出此线程        
		}        
		pthread_mutex_unlock( &tasks_mutex ); //解锁        
		if( tasks == 0 ) 
			break;    
	}
}

void* say_hello1(void* args)
{    
	pthread_t pid = pthread_self(); //获取当前线程id    
	cout << "[" << pid << "] hello in thread " << *((int*)args) << endl;
	while(1)
	{
		pthread_mutex_lock( &tasks_mutex ); //加锁
		if( tasks > BOUNDARY )
		{
			cout << "[" << pid << "] pthread_cond_signal in thread " << *((int*)args) << endl;
			pthread_cond_wait( &tasks_cond, &tasks_mutex ); //wait:等待信号量生效，接收到信号，向hello2发出信号，跳出wait,执行后续        
		}else{
			cout << "[" << pid << "] take task: " << tasks << " in thread " << *((int*)args) << endl;
			--tasks;
		}
		pthread_mutex_unlock( &tasks_mutex ); //解锁        
		if( tasks == 0 )            
			break;
	}		
}

int main()
{    
	pthread_attr_t attr; //线程属性结构体，创建线程时加入的参数    
	pthread_attr_init( &attr ); //初始化    
	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE ); //是设置你想要指定线程属性参数，这个参数表明这个线程是可以join连接的，join功能表示主程序可以等线程结束后再去做某事，实现了主程序和线程同步功能    
	pthread_cond_init( &tasks_cond, NULL ); //初始化条件信号量    
	pthread_mutex_init( &tasks_mutex, NULL ); //初始化互斥量    
	pthread_t tid1, tid2; //保存两个线程id    
	int index1 = 1, index2 = 2;   
	int ret = pthread_create( &tid1, &attr, say_hello1, (void*)&index1);    
	if( ret != 0 )
	{
		cout << "pthread_create error:error_code=" << ret << endl;    
	}  
	ret = pthread_create( &tid2, &attr, say_hello2, (void*)&index2);    
	if( ret != 0 )
	{
		cout << "pthread_create error:error_code=" << ret << endl;    
	}
	pthread_join( tid1, NULL ); //连接两个线程    
	pthread_join( tid2, NULL );    
	pthread_attr_destroy( &attr ); //释放内存    
	pthread_mutex_destroy( &tasks_mutex ); //注销锁    
	pthread_cond_destroy( &tasks_cond ); //正常退出
	
	return 0;
}

