/*
面试：链表问题集锦
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

//1. O(1)时间删除链表节点，从无头单链表中删除节点
void deleteRandomNode(Node *cur)
{
    assert(cur != NULL);
    assert(cur->next != NULL);
    Node *pNext = cur->next;
    // next节点数据覆盖掉cur节点的数据
    cur->data = pNext->data;
    // 删除next节点
    cur->next = pNext->next;
    free(pNext);    //free
}

//2.1. 单链表的转置,循环方法
Node* reverseByLoop(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    Node *pre = NULL, *next = NULL;
    while(head != NULL)
    {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    return pre;
}

//2.2. 单链表的转置,递归方法
Node* reverseByRecursion(Node *head)
{
    //第一个条件是判断异常，第二个条件是结束判断
    if(head == NULL || head->next == NULL)
        return head;
    
    Node *newHead = reverseByRecursion(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;    //返回新链表的头指针
}

//3. 求链表倒数第k个节点
Node* theKthNode(Node *head,int k)
{
    if(k < 0) return NULL;    //异常判断

    Node *p1 = head, *p2 = head;
    // p2先超前p1，k个Node
    int i = 0;
    for (; i < k && p2 != NULL; ++i)
    {
        p2 = p2->next;
    }
    if(i < k)   return NULL;  //考虑k大于链表长度的case
    
    // p1和p2一起前移，直到p2到达链表尾部
    while(p2 != NULL)
    {
        p1 = p1->next;
        p2 = p2->next;    
    }
    return p1;
}

//4. 求链表的中间节点
Node* theMiddleNode(Node *head)
{
    if(head == NULL)
        return NULL;
    Node *slow,*fast;
    slow = fast = head;
    //如果要求在链表长度为偶数的情况下，返回中间两个节点的第一个，可以用下面的循环条件
    //while(fast && fast->next != NULL && fast->next->next != NULL)  
    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;    //快指针移动两个Node
        slow = slow->next;          //慢指针移动一个Node
    }
    return slow;
}

//5. 判断单链表是否存在环,参数circleNode是环内节点，后面的题目会用到
bool hasCircle(Node *head,Node *circleNode)
{
    Node *slow,*fast;
    slow = fast = head;
    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
        {
            circleNode = fast;
            return true;
        }
    }
    return false;
}

//6. 找到环的入口点
Node* findLoopPort(Node *head)
{
    //如果head为空，或者为单结点，则不存在环
    if(head == NULL || head->next == NULL) return NULL;
    Node *slow,*fast;
    slow = fast = head;
    //先判断是否存在环
    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
            break;
    }
    if(fast != slow) return NULL;    //不存在环
    fast = head;                //快指针从头开始走，步长变为1
    while(fast != slow)            //两者相遇即为入口点
    {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

//7. 判断两个链表是否相交
bool isIntersect(Node *h1,Node *h2)
{
    if(h1 == NULL || h2 == NULL) return false;    //异常判断
    while(h1->next != NULL)
    {
        h1 = h1->next;
    }
    while(h2->next != NULL)
    {
        h2 = h2->next;
    }
    if(h1 == h2) return true;        //尾节点是否相同
    else return false;
}

//8. 判断两个带环链表是否相交
bool isIntersectWithLoop(Node *h1,Node *h2)
{
    Node *circleNode1,*circleNode2;
    if(!hasCircle(h1,circleNode1))    //判断链表带不带环，并保存环内节点
        return false;                //不带环，异常退出
    if(!hasCircle(h2,circleNode2))
        return false;
    Node *temp = circleNode2->next;
    while(temp != circleNode2)
    {
        if(temp == circleNode1)
            return true;
        temp = temp->next;
    }
    return false;
}

//9. 求两链表相交的第一个公共节点
Node* findIntersectNode(Node *h1,Node *h2)
{
    int len1 = listLength(h1);          //求链表长度
    int len2 = listLength(h2);
    //对齐两个链表
    if(len1 > len2)
    {
        for(int i=0;i<len1-len2;i++)
            h1=h1->next;
    }
    else 
    {
        for(int i=0;i<len2-len1;i++)
            h2=h2->next;
    }
    while(h1 != NULL)
    {
        if(h1 == h2)
            return h1;
        h1 = h1->next;
        h2 = h2->next;    
    }
    return NULL;
}
