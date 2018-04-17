# C++基础与算法学习
## 1. 八大排序算法
* <font size=4> 直接插入排序 </font>
* <font size=4> 希尔排序 </font>
* <font size=4> 选择排序 </font>
* <font size=4> 堆排序 </font>
* <font size=4> 冒泡排序 </font>
* <font size=4> 快速排序 </font>
* <font size=4> 基数排序 </font>

## 2. 单例模式实现

## 3. 拷贝构造函数
<em>**为什么复制构造函数的参数需要加const和引用?**</em>
3.1 首先跑一个小程序，看下调用关系。
```
#include <iostream>
using namespace std;
class CExample
{
public:
    CExample(int x) :m_nTest(x) //带参数构造函数
    {
        cout<< "constructor with argument."<<endl;
    }
    CExample(const CExample & ex) //拷贝构造函数
    {
        m_nTest = ex.m_nTest;
        cout << "copy constructor."<<endl;
    }
    CExample& operator = (const CExample &ex)//赋值函数(赋值运算符重载)
    {
        cout << "assignment operator." << endl;
        m_nTest = ex.m_nTest;
        return *this;
    }
    void myTestFunc(CExample ex)
    {
    }
private:
    int m_nTest;
};

int main()
{
    CExample aaa(2);
    CExample bbb(3);
    bbb = aaa;
    CExample ccc = aaa;
    bbb.myTestFunc(aaa);
    system("pause");
    return 0;
}
```
【输出结果】

![内存对齐][1]
[1]: https://github.com/FLHonker/Cplus-engineer/blob/master/images/copy-constructor.png?raw=true
【分析结果】
> 第一个输出： constructor with argument.     //CExample aaa(2);

这里创建了变量aaa，在创建的同时还带有参数2，那就调用带参数的构造函数

> 第二个输出：constructor with argument.     //CExample bbb(3);

分析同第一个

> 第三个输出：assignment operator.             //bbb = aaa;

bbb之前已经创建了，所以这个不会调用构造函数，而只是将aaa赋值给bbb，所以调用赋值函数。

> 第四个输出：copy constructor.    //CExample ccc = aaa;

这个和上一个的区别就在于：bbb之前已经创建过了，而这里的ccc是在这条语句才创建的，所以这里是在创建ccc的同时将aaa赋值给ccc，所以这句调用的肯定是构造函数，又因为需要将aaa赋值给ccc，所以调用的是拷贝构造函数。

> 第五个输出：copy constructor.     //  bbb.myTestFunc(aaa);

这里是调用了一个自己写的myTestFunc函数，其中这个函数中的参数没有采用引用，那就是值传递的方式。就是编译器先创建一个类型为CExample名称为ex的对象，然后将aaa的值传递给ex（值传递方式的特性），将相当于要执行一条CExample ex = aaa的语句。经第四个输出的分析可知，这需要调用拷贝构造函数。所以输出copy constrctor。

3.2 为什么要用引用？
【错误答案】个人第一反应：为了减少一次内存拷贝。
【正确答案】由上节的第五个输出分析可知，在执行bbb.myTestFunc(aaa);时，其实会调用拷贝构造函数。如果我们的拷贝构造函数的参数不是引用，那么在bbb.myTestFunc(aaa);时，调用CExample ex = aaa;，又因为ex之前没有被创建，所以又需要调用拷贝构造函数，故而又执行CExample ex = aaa;，就这样永远的递归调用下去了。
**所以， 拷贝构造函数是须要带引用类型的参数的，而且这也是编译器强制性要求的。C++的标准不允许复制构造函数传值参数，只能将构造函数修改为A（const A& other），也就是把传值参数改为常量引用。（注意：传指针也是不可以的，只能改为引用）。**
3.3 为什么要用const？
【正确答案】如果在函数中不会改变引用类型参数的值，加不加const的效果是一样的。而且不加const，编译器也不会报错。但是为了整个程序的安全，还是加上const，防止对引用类型参数值的意外修改。

## 4. 深拷贝与浅拷贝
当用一个已初始化过了的自定义类类型对象去初始化另一个新构造的对象的时候，拷贝构造函数就会被自动调用。也就是说，当类的对象需要拷贝时，拷贝构造函数将会被调用。以下情况都会调用拷贝构造函数：
（1）一个对象以值传递的方式传入函数体;
（2）一个对象以值传递的方式从函数返回;
（3）一个对象需要通过另外一个对象进行初始化。

    如果在类中没有显式地声明一个拷贝构造函数，那么，编译器将会自动生成一个默认的拷贝构造函数，该构造函数完成对象之间的位拷贝，位拷贝又称浅拷贝。
    自定义拷贝构造函数是一种良好的编程风格，它可以阻止编译器形成默认的拷贝构造函数，提高源码效率。

* 浅拷贝和深拷贝
　　在某些状况下，类内成员变量需要动态开辟堆内存，如果实行位拷贝，也就是把对象里的值完全复制给另一个对象，如A=B。这时，如果B中有一个成员变量指针已经申请了内存，那A中的那个成员变量也指向同一块内存。这就出现了问题：当B把内存释放了（如：析构），这时A内的指针就是野指针了，出现运行错误。
<em>深拷贝和浅拷贝可以简单理解为：如果一个类拥有资源，当这个类的对象发生复制过程的时候，资源重新分配，这个过程就是**深拷贝**，反之，没有重新分配资源，就是**浅拷贝**。</em>

**example1:**
```c++
Array(const Array &arr){ /// 拷贝构造函数
      m_iCount = arr.m_iCount;
      m_pArr = new int[m_iCount];   //深拷贝
      for(int i=0;i<m_iCount;i++) m_pArr[i]=arr.m_pArr[i];
        cout<<"Array &"<<endl;
}
```
**example2**
```
Array(const Array &arr){ /// 拷贝构造函数
      m_iCount = arr.m_iCount;   //浅拷贝
}
```
## 5. 运算符重载 >>  <<  ==  []  


## 6. 内存对齐
* 内存对齐的作用：
>(1)平台原因：不是所有的硬件平台都能访问任意内存地址上的任意数据的；某些硬件平台只能在某些地址取得特定类型的数据，否则会抛出硬件异常。
>(2)性能原因：经过内存对齐后，减少了CPU访问内存的总线周期数，速度大大提升。
* 内存对齐规则：
>(1)第一个数据成员放在offset为0的位置，之后的每个数据成员的内存对齐按照#pradma pack(n)指定的值和成员自身长度值中较小的那个进行。【偏移量为其自身大小的整数倍。size%offset==0】
>(2)各数据成员对齐后，类（结构体或联合）也进行对齐，偏移量为最大字段长度的整数倍。
* 关于#pragma pack(n)
> 作为一个预编译命令来设置内存对齐的粒度。n的缺省值是按照编译器自身设置，一般为8，合法数值分别是1,2,4,8,16；若n为其他值是无效的。
<img src="https://github.com/FLHonker/Cplus-engineer/blob/master/images/%E5%86%85%E5%AD%98%E5%AF%B9%E9%BD%90ex.jpg?raw=true" width = "480" height = "500" alt="内存对齐example" align=center />
    
## 7. C++的TCP通信（多线程）
> 简述：TCP通信服务端和客户端代码是不同的。首先，服务端有一个ServerSocket，初始化以后（包括设置IP和端口，绑定监听等过程），这些都设置好以后，就可以使用accept（）方法等待客户端连接了，这个方法是阻塞的。一旦连接成功，就会返回一个新的Socket，使用这个Socket就可以接收数据和发送数据了。客户端自始始终都只有一个Socket，这个Socket初始化以后，使用connect()方法和服务器进行连接，连接成功后，这个Socket就可以进行通信了。
### Windows下API简介
在windows下进行TCP通信，使用Ws2_32.dll动态链接库。
1 . WSAStartup函数：该函数用于初始化Ws2_32.dll动态链接库，在使用socket之前，一定要初始化该链接库。 
初始化：

WSADATA wsaData;
WSAStartup(MAKEWORD(2, 2), &wsaData)//第一个参数表示winsock的版本，本例使用的是winsock2.2版本。

2 . socket函数，创建一个socket

//af:一个地址家族，通常为AF_INET
//type:套接字类型，SOCK_STREAM表示创建面向流连接的套接字。为SOCK_DGRAM，表示创建面向无连接的数据包套接字。为SOCK_RAW，表示创建原始套接字
//protocol:套接字所用协议，不指定可以设置为0
//返回值就是一个socket
SOCKET socket(int af,int type,int protocol);

3 . bind函数：该函数用于将套接字绑定到指定的端口和地址。 
第一个参数为socket，第二个参数是一个结构指针，它包含了端口和IP地址信息，第三个参数表示缓冲区长度。需要说明的是，第二个参数在API中表示为：const struct sockaddr FAR*,这个语法结构我还没见过，网上说这是远指针，win16时期的产物，算是长见识了。

 SOCKADDR_IN addrSrv;
 addrSrv.sin_family = AF_INET;
 addrSrv.sin_port = htons(8888); //1024以上的端口号
 addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//IP地址
 bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));

4 . listen函数：将socket设置为监听模式，服务端的socket特有。必须将服务端的socket设置为监听模式才能和服务端简历连接。 
里面有两个参数，第一个参数为socket，第二个参数为等待连接最大队列的长度。
```
listen(sockSrv,10)
```
5 . accept函数：服务端socket接收客户端的连接请求，连接成功，则返回一个socket，该socket可以在服务端发送和接收数据。第一个参数为socket，第二个参数为包含客户端端口IP信息的sockaddr_in结构指针，第三个参数为接收参数addr的长度。

int len = sizeof(SOCKADDR);
accept(sockSrv, (SOCKADDR *) &addrClient, &len);

6 . closesocket函数：关闭socket，里面的唯一的一个参数就是要关闭的socket。 
7 . connect函数：客户端socket发送连接请求的函数，第一个参数是客户端的socket，第二个参数是一个结构体指针，里面包括连接主机的地址和ip，第三个参数为缓冲区的长度。

connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv));
1
8 . htons函数：将一个16位无符号短整型数据由主机排列方式转化为网络排列方式，htonl函数的作用恰好相反。 
9 . recv函数：接收数据，第一个参数为socket，第二个参数为接收数据缓冲区，第三个参数为缓冲区的长度，第四个参数为函数的调用方式。

char buff[1024];
recv(sockClient, buff, sizeof(buff), 0);

10 . send函数：发送数据，里面的参数基本和recv（）一样。

![服务端代码cpp][3]
![客户端代码cpp][4]
![服务端的class实现][5]
[3]:https://github.com/FLHonker/Cplus-engineer/blob/master/C++/tcp-com/tcp-communication-server.cpp
[4]:https://github.com/FLHonker/Cplus-engineer/blob/master/C++/tcp-com/tcp-communication-client.cpp
[5]:https://github.com/FLHonker/Cplus-engineer/blob/master/C++/tcp-com/tcp-server-class.cpp

## 8. 
  