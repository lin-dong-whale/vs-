#include <stdio.h>
#include <limits.h>

// 合并两个已排好序的数组
void Merge(int a[], int left, int mid, int right)
{
    int len = right - left + 1;        //    数组的长度
    int* temp = new int[len];       // 分配个临时数组
    int k = 0;
    int i = left;                   // 前一数组的起始元素
    int j = mid + 1;                // 后一数组的起始元素
    while (i <= mid && j <= right)
    {
        //    选择较小的存入临时数组
        temp[k++] = a[i] <= a[j] ? a[i++] : a[j++];

    }
    while (i <= mid)
    {
        temp[k++] = a[i++];
    }
    while (j <= right)
    {
        temp[k++] = a[j++];
    }
    for (int k = 0; k < len; k++)
    {
        a[left++] = temp[k];
    }
}

// 递归实现的归并排序
void MergeSort(int a[], int left, int right)
{
    if (left == right)
        return;
    int mid = (left + right) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    Merge(a, left, mid, right);
}


int MergeSortTest() {
    int a[] = { 5,1,9,2,8,7,10,3,4,0,6 };
    int n = sizeof(a) / sizeof(int);
    MergeSort(a, 0, n - 1);
    printf("排序好的数组为：");
    for (int k = 0; k < n; ++k)
        printf("%d ", a[k]);
    printf("\n");
    return 0;
}