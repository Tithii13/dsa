#include<stdio.h>
#include<stdlib.h>

#define MAX 100
struct heap
{
int data[MAX];
int size;
};

void swap(int* a,int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void heapify(struct heap* h,int i)
{
int small=i;
int left=2*i+1;
int right=2*i+2;
if(left<h->size&&h->data[left]<h->data[small])
{
    small=left;
}
if(right<h->size&&h->data[right]<h->data[small])
{
    small=right;
}
if(small!=i)
{
    swap(&h->data[i],&h->data[small]);
    heapify(h,small);
}
}

void build(struct heap* h,int arr[],int n)
{
    h->size=n;
    for(int i=0;i<n;i++)
    {
        h->data[i]=h->data[i];
    }
    for(int i=(h->size/2)-1;i>=0;i--)
    {
heapify(h,i);
    }
}

int exmin(struct heap* h)
{
    if(h->size==0)
    {
        return -1;
    }
    int min=h->data[0];
    h->data[0]=h->data[h->size-1];
    h->size--;
    heapify(h,0);

    return min;
}

void heapsort(int arr[],int n)
{
    struct heap h;
    build(&h,arr,n);

    for(int i=0;i<n;i++)
    {
        arr[i]=exmin(&h);
    }
}

int kth(int arr[],int k,int n)
{
    if(k<=0||k>n)
    {
        return -1;
    }
    struct heap heap;
    build(&heap,arr,n);
    int kthh=-1;
    for(int i=0;i<k;i++)
    {
 kthh=exmin(&heap);
    }
    return kthh;
}

void printheap(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}