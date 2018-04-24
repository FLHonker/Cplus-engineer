# C++基础与算法学习

## 1. 八大排序算法
_参考：
[1. CSDN八大经典排序算法](https://blog.csdn.net/youzhouliu/article/details/52311443)
[2. CSDN稳定与不稳定排序方法](https://blog.csdn.net/stand1210/article/details/52403569)_

#### 1.0 排序算法分类
![排序算法分类](./images/C-img/sort-alg.jpg)

-----

#### 1.1 直接插入排序

<font color="#0000cc" face="宋体" >**基本思想:**</font>

将一个记录插入到已排序好的有序表中，从而得到一个新，记录数增1的有序表。即：先将序列的第1个记录看成是一个有序的子序列，然后从第2个记录逐个进行插入，直至整个序列有序为止。
_要点：设立哨兵，作为临时存储和判断数组边界之用。_
如果碰见一个和插入元素相等的，那么插入元素把想插入的元素放在相等元素的后面。所以，相等元素的前后顺序没有改变，从原无序序列出去的顺序就是排好序后的顺序，所以插入排序是稳定的。

```c++
void InsertSort(int arr[], int n)
{
	int i, j, temp;
	for (i = 1; i<n; ++i)
	{
		temp = arr[i];    //设置哨兵，标记数组边界
		for(j = i-1; j>=0 && temp<arr[j]; --j)
		{
			arr[j+1] = arr[j];   //向后移动元素一格
		}
		arr[j+1] = temp;   //插入到正确位置
	}
}

```
<font color="#ff3300" face="宋体">* 其他插入排序：二分插入排序，2-路插入排序</font>

---

#### 1.2 希尔排序

希尔排序是1959 年由D.L.Shell 提出来的，相对直接排序有较大的改进。希尔排序又叫缩小增量排序

<font color="#0000cc" face="宋体" >**基本思想:**</font>

先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录“基本有序”时，再对全体记录进行依次直接插入排序。

<font color="#0000cc" face="宋体" >**操作方法:**</font>

 1. 选择一个增量序列t1，t2，…，tk，其中ti>tj，tk=1；
 2. 按增量序列个数k，对序列进行k趟排序；
 3. 每趟排序，根据对应的增量ti，将待排序列分割成若干长度为m 的子序列，分别对各子表进行直接插入排序。仅增量因子为1 时，整个序列作为一个表来处理，表长度即为整个序列的长度。
> 我们简单处理增量序列：增量序列d = {n/2 ,n/4, n/8 .....1} n为要排序数的个数, 即：先将要排序的一组记录按某个增量d（n/2,n为要排序数的个数）分成若干组子序列，每组中记录的下标相差d.对每组中全部元素进行直接插入排序，然后再用一个较小的增量（d/2）对它进行分组，在每组中再进行直接插入排序。继续不断缩小增量直至为1，最后使用直接插入排序完成排序。

```c++
void ShellInsertSort(int arr[], int n, int dk)
{
	for(int i=dk; i<n; ++i)
	{
		if(arr[i] < arr[i-dk])  //若第i个元素大于i-1元素，直接插入;小于的话，移动有序表后插入.
		{
			int temp = arr[i];   //设置哨兵
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
```

希尔排序时效分析很难，关键码的比较次数与记录移动次数依赖于增量因子序列d的选取，特定情况下可以准确估算出关键码的比较次数和记录的移动次数。目前还没有人给出选取最好的增量因子序列的方法。增量因子序列可以有各种取法，有取奇数的，也有取质数的，但需要注意：增量因子中除1 外没有公因子，且最后一个增量因子必须为1。希尔排序方法是一个不稳定的排序方法。

---
#### 1.3 simple选择排序
<font color="#0000cc" face="宋体" >**基本思想:**</font>

在要排序的一组数中，选出最小（或者最大）的一个数与第1个位置的数交换；然后在剩下的数当中再找最小（或者最大）的与第2个位置的数交换，依次类推，直到第n-1个元素（倒数第二个数）和第n个元素（最后一个数）比较为止。
<font color="#0000cc" face="宋体" >**操作方法:**</font>

第一趟，从n 个记录中找出关键码最小的记录与第一个记录交换；
第二趟，从第二个记录开始的n-1 个记录中再选出关键码最小的记录与第二个记录交换；
以此类推.....
第i 趟，则从第i 个记录开始的n-i+1 个记录中选出关键码最小的记录与第i 个记录交换，
直到整个序列按关键码有序。

```c++
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
```
**simple选择排序的改进——二元选择排序**
简单选择排序，每趟循环只能确定一个元素排序后的定位。我们可以考虑改进为每趟循环确定两个元素（当前趟最大和最小记录）的位置,从而减少排序所需的循环次数。改进后对n个数据进行排序，最多只需进行[n/2]趟循环即可。具体实现如下：

```c++
void Select2Sort(int arr[], int n)
 {
    for(unsigned int i=0; i < n/2; ++i)
    {
        unsigned int min = i, max = n-1-i;
        for(unsigned int j=i+1; j<n-1-i; ++j)
        {
            if(arr[j]<arr[min])
                min = j;
            else if(arr[j]>arr[max])
                max = j;
        }
        swap(arr[i], arr[min]);
        swap(arr[n-1-i], arr[max]);
    }
 }
 ```
---
#### 1.4 堆排序

堆排序是一种树形选择排序，是对直接选择排序的有效改进。若以一维数组存储一个堆，则堆对应一棵完全二叉树，且所有非叶结点的值均不大于(或不小于)其子女的值，根结点（堆顶元素）的值是最小(或最大)的。
初始时把要排序的n个数的序列看作是一棵顺序存储的二叉树（一维数组存储二叉树），调整它们的存储序，使之成为一个堆，将堆顶元素输出，得到n 个元素中最小(或最大)的元素，这时堆的根节点的数最小（或者最大）。然后对前面(n-1)个元素重新调整使之成为堆，输出堆顶元素，得到n 个元素中次小(或次大)的元素。依此类推，直到只有两个节点的堆，并对它们作交换，最后得到有n个节点的有序序列。称这个过程为堆排序。

因此，实现堆排序需解决两个问题：
1. 如何将n 个待排序的数建成堆；
2. 输出堆顶元素后，怎样调整剩余n-1 个元素，使其成为一个新堆。

```c++
/**************************************************************
 *
 * 选择排序——堆排序（Heap Sort）
 * 时间复杂度：O(n) = nlogn
 *
 **************************************************************/
/**
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
    while (child < n) 
    {  
        if(child+1 < n && H[child] < H[child+1])  //如果左子结点小于右子结点，child指向右子结点 
            ++child;
        if(H[s]<H[child]) 
        {   // 如果较大的子结点大于父结点  
            H[s] = H[child]; // 那么把较大的子结点往上移动，替换它的父结点  
            s = child;       // 重新设置s ,即待调整的下一个结点的位置  
            child = 2*s+1;  
        }  else {            // 如果当前待调整结点大于它的左右孩子，则不需要调整，直接退出  
             break;  
        }  
        H[s] = temp;         // 当前待调整的结点放到比其大的孩子结点位置上  
    }  
}  

/*
 * 初始堆进行调整 
 * 将H[0..n-1]建成堆 
 * 调整完之后第一个元素是序列的最小的元素 
 */  
void BuildingHeap(int H[], int n)  
{   
    //最后一个有孩子的节点的位置 i= (n -1) / 2  
    for (int i = (n -1) / 2 ; i >= 0; --i)  
        HeapAdjust(H,i,n);  
}  
/* 
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
```
---
#### 1.5 冒泡排序 

这个不用多说，和选择排序很像，区别是每次找出相对大的数立即交换位置，直到冒泡到最后面，交换次数较多。

```c++
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
```

---
#### 1.6 快速排序

<font color="#0000cc" face="宋体" >**基本思想:**</font>

1）选择一个基准元素,通常选择第一个元素或者最后一个元素;

2）通过一趟排序讲待排序的记录分割成独立的两部分，其中一部分记录的元素值均比基准元素值小,另一部分记录的 元素值比基准值大;

3）此时基准元素在其排好序后的正确位置;

4）然后分别对这两部分记录用同样的方法继续进行排序，直到整个序列有序。

<font color="#0000cc" face="宋体" >**分析:**</font>

快速排序是通常被认为在同数量级（O(nlog<sub>2</sub>n)）的排序方法中平均性能最好的。但若初始序列按关键码有序或基本有序时，快排序反而蜕化为冒泡排序。为改进之，通常以“三者取中法”来选取基准记录，即将排序区间的两个端点与中点三个记录关键码居中的调整为支点记录。快速排序是一个不稳定的排序方法。

```c++
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

```

<font color="#0000cc" face="宋体" >**快速排序的改进:**</font>

在本改进算法中,只对长度大于k的子序列递归调用快速排序,让原序列基本有序，然后再对整个基本有序序列用插入排序算法排序。实践证明，改进后的算法时间复杂度有所降低，且当k取值为 8 左右时,改进算法的性能最佳。

```c++
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

```
---
#### 1.7 归并排序

<font color="#0000cc" face="宋体" >**基本思想:**</font>

归并（Merge）排序法是将两个（或两个以上）有序表合并成一个新的有序表，即把待排序序列分为若干个子序列，每个子序列是有序的,然后再把有序子序列合并为整体有序序列。

<font color="#0000cc" face="宋体" >**合并方法:**</font>

设r[i…n]由两个有序子表r[i…m]和r[m+1…n]组成，两个子表长度分别为m-i+1、n-m。

1. j=m+1；k=i；i=i; //置两个子表的起始下标及辅助数组的起始下标
2. 若i>m 或j>n，转⑷ //其中一个子表已合并完，比较选取结束
3. //选取r[i]和r[j]较小的存入辅助数组rf
   如果r[i]<r[j]，rf[k]=r[i]； i++； k++； 转⑵
   否则，rf[k]=r[j]； j++； k++； 转⑵
4. //将尚未处理完的子表中元素存入rf
   如果i<=m，将r[i…m]存入rf[k…n] //前一子表非空
   如果j<=n ,  将r[j…n] 存入rf[k…n] //后一子表非空
5. 合并结束。

```c++
/**************************************************************
 *
 * 归并排序（Merge Sort）
 * 时间复杂度：O(n) = nlogn
 * 稳定排序
 **************************************************************/
//二路归并算法
//将r[i…m]和r[m +1 …n]归并到辅助数组rf[i…n] 
template <typename T>
void Merge(T *r, T *rf, int i, int m, int n)
{
	int j, k;
	for (j = m+1, k=i; i <= m && j <= n; ++k)
	{
		if(r[i] < r[j]) rf[k] = r[i++];
		else rf[k] = r[j++];
	}
	while(i <= m)  rf[k++] = r[i++];
	while(j <= n)  rf[k++] = r[j++];
}

// 1. 归并排序的迭代算法
template <typename T>
void MergeSort_iteration(T *r, T *rf, int n)
{
	int len = 1;
	T *q = r;
	while(len < n)
	{
		int s = len;
		len = len << 1;   //x2
		//对等长的两个子表合并
		int i = 0;
		for( ; len + i < n; i += len)    
			Merge(q, rf, i, i +s -1, i +len -1); 
		//对不等长的两个子表合并  
		if(i + s < n)
			Merge(q, rf, i, i +s -1, n -1);
		swap(q, rf);   //交换q,rf，以保证下一趟归并时仍然从q归并到rf。
	}
}

// 2. 归并排序的递归算法
template <typename T>
void MSort_recursive(T *r, T *rf, int start, int end)
{
	T *rf2 = new T[end - start +1];   //important!!!
	if(start == end)
		rf[start] = r[start];
	else {
		int m =(start + end)/2;    //平分*r 表
		MSort_recursive(r, rf2, start, m);   //递归地将r[s…m]归并为有序的rf2[s…m]
		MSort_recursive(r, rf2, m +1, end);  //递归地将r[m+1…e]归并为有序的rf2[m+1…e]
		Merge(rf2, rf, start, m, end);        //将rf2[s…m]和rf2[m+1…e]归并到p1[s…e]
	}
}

template <typename T>
void MergeSort_recursive(T *r, T *rf, int n)
{
	MSort_recursive(r, rf, 0, n -1);   
}

``
---
#### 1.8 基数排序

---
> **八大排序算法性能比较表**
> 
>![八大排序算法比较表](./images/C-img/sort-compare.jpg)
<i>当n较大，则应采用时间复杂度为O(nlog<sub>2</sub>n)的排序方法：快速排序、堆排序或归并排序序。
   快速排序：是目前基于比较的内部排序中被认为是最好的方法，当待排序的关键字是随机分布时，快速排序的平均时间最短。</i>

---
#### 1.9 稳定排序与不稳定排序方法分析
首先，排序算法的稳定性大家应该都知道，通俗地讲就是能保证排序前2个相等的数其在序列的前后位置顺序和排序后它们两个的前后位置顺序相同。在简单形式化一下，如果Ai = Aj，Ai原来在位置前，排序后Ai还是要在Aj位置前。

其次，说一下稳定性的好处。排序算法如果是稳定的，那么从一个键上排序，然后再从另一个键上排序，第一个键排序的结果可以为第二个键排序所用。基数排序就是这样，先按低位排序，逐次按高位排序，低位相同的元素其顺序再高位也相同时是不会改变的。另外，如果排序算法稳定，对基于比较的排序算法而言，元素交换的次数可能会少一些（个人感觉，没有证实）。

回到主题，现在分析一下常见的排序算法的稳定性，每个都给出简单的理由。

(1)冒泡排序

冒泡排序就是把小的元素往前调或者把大的元素往后调。比较是相邻的两个元素比较，交换也发生在这两个元素之间。所以，如果两个元素相等，我想你是不会再无聊地把他们俩交换一下的；如果两个相等的元素没有相邻，那么即使通过前面的两两交换把两个相邻起来，这时候也不会交换，所以相同元素的前后顺序并没有改变，所以冒泡排序是一种稳定排序算法。

(2)选择排序

选择排序是给每个位置选择当前元素最小的，比如给第一个位置选择最小的，在剩余元素里面给第二个元素选择第二小的，依次类推，直到第n - 1个元素，第n个元素不用选择了，因为只剩下它一个最大的元素了。那么，在一趟选择，如果当前元素比一个元素小，而该小的元素又出现在一个和当前元素相等的元素后面，那么交换后稳定性就被破坏了。比较拗口，举个例子，序列5 8 5 2 9，我们知道第一遍选择第1个元素5会和2交换，那么原序列中2个5的相对前后顺序就被破坏了，所以选择排序不是一个稳定的排序算法。

(3)插入排序 
插入排序是在一个已经有序的小序列的基础上，一次插入一个元素。当然，刚开始这个有序的小序列只有1个元素，就是第一个元素。比较是从有序序列的末尾开始，也就是想要插入的元素和已经有序的最大者开始比起，如果比它大则直接插入在其后面，否则一直往前找直到找到它该插入的位置。如果碰见一个和插入元素相等的，那么插入元素把想插入的元素放在相等元素的后面。所以，相等元素的前后顺序没有改变，从原无序序列出去的顺序就是排好序后的顺序，所以插入排序是稳定的。

(4)快速排序 
快速排序有两个方向，左边的i下标一直往右走，当a[i] <= a[center_index]，其中center_index是中枢元素的数组下标，一般取为数组第0个元素。而右边的j下标一直往左走，当a[j] > a[center_index]。如果i和j都走不动了，i <= j，交换a[i]和a[j],重复上面的过程，直到i > j。 交换a[j]和a[center_index]，完成一趟快速排序。在中枢元素和a[j]交换的时候，很有可能把前面的元素的稳定性打乱，比如序列为5 3 3 4 3 8 9 10 11，现在中枢元素5和3（第5个元素，下标从1开始计）交换就会把元素3的稳定性打乱，所以快速排序是一个不稳定的排序算法，不稳定发生在中枢元素和a[j] 交换的时刻。

(5)归并排序 
归并排序是把序列递归地分成短序列，递归出口是短序列只有1个元素（认为直接有序）或者2个序列（1次比较和交换），然后把各个有序的段序列合并成一个有序的长序列，不断合并直到原序列全部排好序。可以发现，在1个或2个元素时，1个元素不会交换，2个元素如果大小相等也没有人故意交换，这不会破坏稳定性。那么，在短的有序序列合并的过程中，稳定是是否受到破坏？没有，合并过程中我们可以保证如果两个当前元素相等时，我们把处在前面的序列的元素保存在结果序列的前面，这样就保证了稳定性。所以，归并排序也是稳定的排序算法。

(6)基数排序 
基数排序是按照低位先排序，然后收集；再按照高位排序，然后再收集；依次类推，直到最高位。有时候有些属性是有优先级顺序的，先按低优先级排序，再按高优先级排序，最后的次序就是高优先级高的在前，高优先级相同的低优先级高的在前。基数排序基于分别排序，分别收集，所以其是稳定的排序算法。

(7)希尔排序(shell) 
希尔排序是按照不同步长对元素进行插入排序，当刚开始元素很无序的时候，步长最大，所以插入排序的元素个数很少，速度很快；当元素基本有序了，步长很小， 插入排序对于有序的序列效率很高。所以，希尔排序的时间复杂度会比O(n^2)好一些。由于多次插入排序，我们知道一次插入排序是稳定的，不会改变相同元素的相对顺序，但在不同的插入排序过程中，相同的元素可能在各自的插入排序中移动，最后其稳定性就会被打乱，所以shell排序是不稳定的。

(8)堆排序 
我们知道堆的结构是节点i的孩子为2 * i和2 * i + 1节点，大顶堆要求父节点大于等于其2个子节点，小顶堆要求父节点小于等于其2个子节点。在一个长为n 的序列，堆排序的过程是从第n / 2开始和其子节点共3个值选择最大（大顶堆）或者最小（小顶堆），这3个元素之间的选择当然不会破坏稳定性。但当为n / 2 - 1， n / 2 - 2， ... 1这些个父节点选择元素时，就会破坏稳定性。有可能第n / 2个父节点交换把后面一个元素交换过去了，而第n / 2 - 1个父节点把后面一个相同的元素没 有交换，那么这2个相同的元素之间的稳定性就被破坏了。所以，堆排序不是稳定的排序算法。

综上，得出结论: 选择排序、快速排序、希尔排序、堆排序不是稳定的排序算法，而冒泡排序、插入排序、归并排序和基数排序是稳定的排序算法，不稳定的排序算法有：快、希、选、堆。（记忆：找到工作就可以“快些选一堆”美女来玩了（并不能））！


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
[1]: ./images/C-img/copy-constructor.png
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
>**所以， 拷贝构造函数是须要带引用类型的参数的，而且这也是编译器强制性要求的。C++的标准不允许复制构造函数传值参数，只能将构造函数修改为A（const A& other），也就是把传值参数改为常量引用。（注意：传指针也是不可以的，只能改为引用）。**

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
<div align=center>
<img src="./images/C-img/内存对齐ex.jpg" width = "480" height = "500" alt="内存对齐example" align=center />
</div>    
    
## 7. C++的TCP通信（多线程）
> 简述：TCP通信服务端和客户端代码是不同的。首先，服务端有一个ServerSocket，初始化以后（包括设置IP和端口，绑定监听等过程），这些都设置好以后，就可以使用accept（）方法等待客户端连接了，这个方法是阻塞的。一旦连接成功，就会返回一个新的Socket，使用这个Socket就可以接收数据和发送数据了。客户端自始始终都只有一个Socket，这个Socket初始化以后，使用connect()方法和服务器进行连接，连接成功后，这个Socket就可以进行通信了。

**服务端tcp过程**
<div align=center>
![server](./images/C-img/tcpserver.png)
</div>
**客户端tcp过程**
<div align=center>
![client](./images/C-img/tcpclient.png)
</div>

### Windows下API简介
在windows下进行TCP通信，使用Ws2_32.dll动态链接库。

（1）WSAStartup函数：该函数用于初始化Ws2_32.dll动态链接库，在使用socket之前，一定要初始化该链接库。 
初始化：

WSADATA wsaData;
WSAStartup(MAKEWORD(2, 2), &wsaData)//第一个参数表示winsock的版本，本例使用的是winsock2.2版本。

（2）socket函数，创建一个socket

//af:一个地址家族，通常为AF_INET
//type:套接字类型，SOCK_STREAM表示创建面向流连接的套接字。为SOCK_DGRAM，表示创建面向无连接的数据包套接字。为SOCK_RAW，表示创建原始套接字
//protocol:套接字所用协议，不指定可以设置为0
//返回值就是一个socket
SOCKET socket(int af,int type,int protocol);

（3）bind函数：该函数用于将套接字绑定到指定的端口和地址。 
第一个参数为socket，第二个参数是一个结构指针，它包含了端口和IP地址信息，第三个参数表示缓冲区长度。需要说明的是，第二个参数在API中表示为：const struct sockaddr FAR*,这个语法结构我还没见过，网上说这是远指针，win16时期的产物，算是长见识了。
```
 SOCKADDR_IN addrSrv;
 addrSrv.sin_family = AF_INET;
 addrSrv.sin_port = htons(8888); //1024以上的端口号
 addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//IP地址
 bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
```
(4) listen函数：将socket设置为监听模式，服务端的socket特有。必须将服务端的socket设置为监听模式才能和服务端简历连接。 
里面有两个参数，第一个参数为socket，第二个参数为等待连接最大队列的长度。
```
listen(sockSrv,10)
```
(5) accept函数：服务端socket接收客户端的连接请求，连接成功，则返回一个socket，该socket可以在服务端发送和接收数据。第一个参数为socket，第二个参数为包含客户端端口IP信息的sockaddr_in结构指针，第三个参数为接收参数addr的长度。
```
int len = sizeof(SOCKADDR);
accept(sockSrv, (SOCKADDR *) &addrClient, &len);
```
(6) closesocket函数：关闭socket，里面的唯一的一个参数就是要关闭的socket。 
(7) connect函数：客户端socket发送连接请求的函数，第一个参数是客户端的socket，第二个参数是一个结构体指针，里面包括连接主机的地址和ip，第三个参数为缓冲区的长度。
```
connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv));
```
(8) htons函数：将一个16位无符号短整型数据由主机排列方式转化为网络排列方式，htonl函数的作用恰好相反。 
(9) recv函数：接收数据，第一个参数为socket，第二个参数为接收数据缓冲区，第三个参数为缓冲区的长度，第四个参数为函数的调用方式。
```
char buff[1024];
recv(sockClient, buff, sizeof(buff), 0);
```
(10) send函数：发送数据，里面的参数基本和recv()一样。

[服务端代码cpp](./C++/tcp-com/tcp-communication-server.cpp)

[客户端代码cpp](./C++/tcp-com/tcp-communication-client.cpp)		

[服务端的class实现](./C++/tcp-com/tcp-server-class.cpp)

## 8. C++内存管理（内存模型）

## 9. 字符串朴素匹配算法和KMP

### 10. C++中虚继承的作用及底层实现原理
