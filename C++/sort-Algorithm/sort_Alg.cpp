/***************************************************************************
*Copyright (c) 2017,Wuhan
*All rights reserved.
*
*filename: sort-Alg.cpp
*description: eight classic sort algorithm
*			  ֱ�Ӳ���(Straight Insertion Sort)��ϣ������(Shell`s Sort)����ѡ��(Simple Selection Sort)��
*			  ������(Heap Sort)��ð��(Bubble Sort������(Quick Sort���鲢(Merge Sort)��Ͱ����/��������(Radix Sort)
*
*@Version��V1.0
*@author��Frank Liu
*@time��20180416
*
*Change record 1: // Change history record, including modification date, version number, modification person and modification contents
*change-time      version          change-author         change-content

* 20180416         V1.0              Frank                  create
*******************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

/**************************************************************
 *
 * �������򡪡�ֱ�Ӳ�������(Straight Insertion Sort)
 * ʱ�临�Ӷȣ�O(n) = 2^n
 *
***************************************************************/
void InsertSort(int arr[], int n)
{
	int i, j, temp;
	
	for (i = 1; i<n; ++i)
	{
		temp = arr[i];    //�����ڱ����������߽�
		for(j = i-1; j>=0 && temp<arr[j]; --j)
		{
			arr[j+1] = arr[j];   //����ƶ�Ԫ��һ��
		}
		arr[j+1] = temp;   //���뵽��ȷλ��
	}
}


/**
 * �������Ԫ��
*/
void printArray(int arr[], int n)
{
	for(int i=0; i<n; ++i)
		cout << arr[i] << " ";
	cout<<endl;
}

int main()
{
	int a[] = {7,4,5,2,0,6,5,42,32,1,1,23};
	InsertSort(a, 12);
	printArray(a, 12);
	
	return 0;
}
