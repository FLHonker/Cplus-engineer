/*************************************************************************
	> File Name: singleton.cpp
	> Author: Frank Liu
	> Mail: frankliu624@gmail.com
	> Created Time: 2018年04月25日 星期三 13时30分48秒
 ************************************************************************/

#include<iostream>
using namespace std;

/**
 * 教科书里的单例模式
 */
class Singleton
{
protected:
    Singleton(){}
private:
    static Singleton* p;
public:
    static Singleton* getInstance();
};
Singleton* Singleton::p = NULL;
Singleton* Singleton::getInstance()
{
    if(p == NULL)
        p = new Singleton();
    return p;
}

/**
 * 加锁的经典懒汉实现
 */
class Singleton
{
protected:
    Singleton()
    {
        pthread_mutex_init(&mutex);
    }
private:
    static pthread_mutex_t mutex;
    static Singleton* p;
public:
    static Singleton* getInstance();
};
pthread_mutex_t Singleton::mutex;
Singleton* Singleton::p = NULL;
Singleton* Singleton::getInstance()
{
    if(p == NULL)
    {
        pthread_mutex_lock(&mutex);
        if(p == NULL)
           p = new Singleton();
        pthread_mutex_unlock(&mutex);
    }
    return p;
}

/**
 * 内部静态变量的懒汉实现
 */
class Singleton
{
protected:
    Singleton()
    {
        pthread_mutex_init(&mutex);
    }
private:
    static pthread_mutex_t mutex;
public:
    static Singleton* getInstance();
};
pthread_mutex_t Singleton::mutex;
Singleton* Singleton::getInstance()
{
    pthread_mutex_lock(&mutex);
    static Singleton obj;
    pthread_mutex_unlock(&mutex);

    return obj;
}

/**
 * 天生线程安全的饿汉实现
 */
class Singleton
{
protected:
    Singleton(){}
private:
    static Singleton* p;
public:
    static Singleton* getInstance();
};
Singleton* Singleton::p = new Singleton();
Singleton* Singleton::getInstance()
{
    return p;
}
