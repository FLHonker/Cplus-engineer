/*************************************************************************
	> File Name: KMP.cpp
	> Author: Frank Liu 
	> Mail: frankiu624@gmail.com
	> Created Time: 2018年05月02日 星期三 10时23分17秒
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

vector<int> getNext(string T)
{
    vector<int> next(T.size(),0);
    next[0] = -1;
    //next[1] = 0;
    int j = 0, k = -1;
    for(int j = 2; j < T.size(); ++j)
    {
        while(k > 0 && T[j -1] != T[k])
            k = next[k];
        if(T[j -1] == T[k])
            k++;
        next[j] = k;
    }
    /* 或者这样写：
    while(j < T.size())
    {
        if(k == -1 || T[j] == T[k])
        {//串后缀与前缀没有相等的子串或者此时j下标下的字符与k下的字符相等。 
            k++; j++;
            next[j] = k;
        }else
            k = next[k];  //缩小子串的范围继续比较 
    } */
    return next;
}

int KMP(string S, string T)
{
    vector<int> next = getNext(T);  //计算得到next数组
    int i = 0, j = 0;
    while(S[i] != '\0' && T[j] != '\0')
    {
        if(S[i] == T[j])
        {
            i++; j++;
        } else{
            j = next[j];   
        }
        if(j == -1)
        {
            i++; j++;
        }
    }
    if(T[j] == '\0')
        return i -j;
    else
        return -1;
}

int main()
{
    string S = "asdwewfdfsasdeCSDasdAwewewqWE";
    string T = "asde";
    cout << KMP(S, T) <<endl;
    return 0;
}
