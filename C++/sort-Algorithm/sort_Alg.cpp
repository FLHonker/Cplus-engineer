/***************************************************************************
*Copyright (c) 2017,Wuhan
*All rights reserved.
*
*filename: sort-Alg.cpp
*description: eight classic sort algorithm
*  直接插入(Straight Insertion Sort)、希尔排序(Shell`s Sort)、简单选择(Simple Selection Sort)、
*  堆排序(Heap Sort)、冒泡(Bubble Sort、快排(Quick Sort、归并(Merge Sort)、桶排序/基数排序(Radix Sort)
*
*@Version：V1.0
*@author：Frank Liu
*@time：20180416
*
*Change record 1: // Change history record, including modification date, version number, modification person and modification contents
*change-time      version          change-author         change-content

* 20180416         V1.0              Frank                  create
*******************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

/**************************************************************
 *
 * 插入排序——直接插入排序(Straight Insertion Sort)
 * 时间复杂度：O(n) = 2^n
 *
***************************************************************/
void InsertSort(int arr[], int n)
{
	int i, j, temp;
	
	for (i = 1; i<n; ++i)
	{
		temp = arr[i];    //设置哨兵，标记数组边界
		for(j = i-1; j>=0 && temp < arr[j]; --j)
		{
			arr[j+1] = arr[j];   //向后移动元素一格
		}
		arr[j+1] = temp;   //插入到正确位置
	}
}

/**************************************************************
 *
 * 插入排序——希尔排序(Shell's Sort) or 缩小增量排序
 * 时间复杂度：不确定
 * 不稳定的排序。
 *
***************************************************************/
void ShellInsertSort(int arr[], int n, int dk)
{
	for(int i=dk; i<n; ++i)
	{
		if(arr[i] < arr[i-dk])  //若第i个元素大于i-1元素，直接插入;小于的话，移动有序表后插入.
		{
			int temp = arr[i];   //设置哨兵
			//arr[i] = arr[i-dk];   //首先后移一个元素
			//直接插入排序
			int j=i-dk;
			for(; j>=0 && temp < arr[j]; j-=dk)
			{
				arr[j+dk] = arr[j];
			}
			arr[j+dk] = temp;
		}
	}
}
//缩小增量迭代
void ShellSort(int arr[], int n)
{
	for(int dk = n/2; dk >= 1; dk/=2)
		ShellInsertSort(arr, n, dk);
}


/**************************************************************
 *
 * 选择排序——简单选择排序(Simple Selection Sort) 
 * 时间复杂度：O(n)=2^n
 *
***************************************************************/
void sSelectionSort(int arr[], int n)
{
    unsigned int index;
    for(unsigned int i=0; i<n; ++i)
    {
        index = i;
        for(unsigned int j=i+1; j<n; ++j)
        {
            if(arr[j]<arr[index])
                index = j;
        }
        swap (arr[i], arr[index]);
    }
}

/**************************************************************
 *
 * 选择排序——简单选择排序的改进——二元选择排序
 * 每趟选出两个最小和最大元素，只需要[n/2]趟。
 *
 **************************************************************/
 void Select2Sort(int arr[], int n)
 {
    for(unsigned int i=0; i <= n/2; ++i)
    {
        unsigned int min = i, max = n-1-i;
        for(unsigned int j=i+1; j<n-1-i; ++j)
        {
            if(arr[j]<arr[min])
                min = j;
            if(arr[j]>arr[max])
                max = j;
        }
        swap(arr[i], arr[min]);
        swap(arr[n-1-i], arr[max]);
    }
 }

/**************************************************************
 *
 * 选择排序——堆排序（Heap Sort）
 * 时间复杂度：O(n) = nlogn
 *
 **************************************************************/
/** 1.
 * 已知H[s…m]除了H[s] 外均满足堆的定义 
 * 调整H[s],使其成为大顶堆.即将对第s个结点为根的子树筛选,  
 * 
 * @param H是待调整的堆数组 
 * @param s是待调整的数组元素的位置 
 * @param n是数组的长度 
 * 
 */  
void HeapAdjust(int H[],int s, int n)  
{  
    int temp  = H[s];  
    int child = 2*s+1; //左孩子结点的位置。 
    while (child < n) {  
        if(child+1 < n && H[child] < H[child+1]) { //如果左子结点小于右子结点，child指向右子结点
            ++child ;  
        }  
        if(H[s] < H[child]) {  // 如果较大的子结点大于父结点  
            H[s] = H[child];   // 那么把较大的子结点往上移动，替换它的父结点  
            s = child;         // 重新设置s ,即待调整的下一个结点的位置  
            child = 2*s+1;  
        }  else {            // 如果当前待调整结点大于它的左右孩子，则不需要调整，直接退出  
             break;  
        }  
        H[s] = temp;         // 当前待调整的结点放到比其大的孩子结点位置上  
    }  
}
  
  
/** 2.
 * 初始堆进行调整 
 * 将H[0..n-1]建成堆 
 * 调整完之后第一个元素是序列的最小的元素 
 */  
void BuildingHeap(int H[], int n)  
{   
    //最后一个有孩子的节点的位置 i=  (n -1) / 2  
    for (int i = (n -1) / 2 ; i >= 0; --i)  
        HeapAdjust(H,i,n);  
}  

/** 
 * 堆排序算法 
 */  
void HeapSort(int H[], int n)  
{  
    //初始堆  
    BuildingHeap(H, n);  
    //从最后一个元素开始对序列进行调整  
    for (int i = n - 1; i > 0; --i)  
    {  
        //交换堆顶元素H[0]和堆中最后一个元素  
        //int temp = H[i]; H[i] = H[0]; H[0] = temp;  
    	swap(H[i], H[0]);
        //每次交换堆顶元素和堆中最后一个元素之后，都要对堆进行调整  
        HeapAdjust(H,0,i);  
  }  
}

/**************************************************************
 *
 * 交换排序——冒泡排序（Bubble Sort）
 * 时间复杂度：O(n) = 2^n 
 * 稳定排序
 **************************************************************/
void BubbleSort(int arr[], int n)
{
    for(int i=0; i < n - 1; ++i)   //一共跑n-1趟
    {
        for(int j=0; j < n-1-i; ++j)   //将大数冒泡到最后面
        {
            if(arr[j+1] < arr[j])
                swap(arr[j], arr[j+1]);
        }
    }
}

/**************************************************************
 *
 * 交换排序——快速排序（Quick Sort）
 * 递归实现
 * 时间复杂度：O(n) = nlogn 
 * 不稳定排序
 **************************************************************/

 // 将表一分为二
template <typename T>
int partation(T arr[], int low, int high)
{
    T privotkey = arr[low];   //基准元素
    while(low < high)    //从表的两端交替向中间扫描
    {
        while(low < high && arr[high] >= privotkey) 
           --high;
        swap(arr[low], arr[high]);
        while(low < high && arr[low] <= privotkey)
           ++low;
        swap(arr[low], arr[high]);
    }
    return low;
}

// 递归快排
void QuickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int privotkey = partation(arr, low, high);  //划分表
        QuickSort(arr, low, privotkey -1);   //递归对低子表排序
        QuickSort(arr, privotkey +1, high);   //递归对高子表排序
    }
}

/**
 * 快速排序的改进：high-low > k时进行递归子排序使之基本有序，
 * 小于k时再进行插入排序。其中，k 为指定值，k = 8 时性能最佳。
 */
void qSort_improve(int arr[], int low, int high, int k)
{
    if(high - low > k)   //长度大于k 时递归
    {
        int privotkey = partation(arr, low, high);   //调用partation的算法不变
        qSort_improve(arr, low, privotkey -1, k);
        qSort_improve(arr, privotkey +1, high, k);
    }
}
void QuickSort_improve(int arr[], int n, int k)
{
    qSort_improve(arr, 0, n, k);

    //再用插入排序对基本有序序列排序
    for(int i =0; i < n; ++i)
    {
        int temp = arr[i];
        int j = i - 1;
        for( ;j >= 0 && temp < arr[j]; --j)
        {
            swap(arr[j], arr[j+1]);
        }
        arr[j+1] = temp;
    }
}

/**************************************************************
 *
 * 归并排序（Merge Sort）
 * 时间复杂度：O(n) = 
 * 稳定排序
 **************************************************************/


/**
 * 输出数组元素
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
	int b[] = {5,3,95,0,12,4,5,7,66,20,3,3,45};
	ShellSort(b, 13);
	printArray(b, 13);
   	int c[]={4,54,6,0,2,2,35,41,20,1,7};
    sSelectionSort(c, 11);
	printArray(c, 11);
    int d[]={4,54,6,0,2,2,35,41,20,1,7};
    Select2Sort(d, 11);
    printArray(d, 11);
	int e[]={4,54,6,0,2,2,35,41,20,1,7};
	HeapSort(e, 11);
	printArray(e, 11);
    int f[]={95,5,4,6,23,0,27,12,3,54,5};
    BubbleSort(f, 11);
    printArray(f, 11);
    int g[]={58,6,2,54,51,0,2,32,5,1,5,7};
    QuickSort(g, 0, 11);
    printArray(g, 12);
    int h[] = {21,4,5,0,21,7,84,56,32,1,11,47};
    QuickSort_improve(h, 12, 4);
    printArray(h, 12);

	return 0;
}

