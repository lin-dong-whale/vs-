#include <stdio.h>
#include <limits.h>

// �ϲ��������ź��������
void Merge(int a[], int left, int mid, int right)
{
    int len = right - left + 1;        //    ����ĳ���
    int* temp = new int[len];       // �������ʱ����
    int k = 0;
    int i = left;                   // ǰһ�������ʼԪ��
    int j = mid + 1;                // ��һ�������ʼԪ��
    while (i <= mid && j <= right)
    {
        //    ѡ���С�Ĵ�����ʱ����
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

// �ݹ�ʵ�ֵĹ鲢����
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
    printf("����õ�����Ϊ��");
    for (int k = 0; k < n; ++k)
        printf("%d ", a[k]);
    printf("\n");
    return 0;
}