#include<stdio.h>
#include<stdlib.h>

#define MAX 100

struct heap
{
int data[MAX];
int size;
};

void initheap(struct heap* h)
{
    h->size=0;
}

void swap(int* a,int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void heapify(struct heap* h,int index)
{
    int largest=index;
    int left=2*index+1;
    int right=2*index+2;
    if(left<h->size&&h->data[left]>h->data[largest])
    {
    largest=left;
    }
    if(right<h->size&&h->data[right]>h->data[largest])
    {
        largest=right;
    }

    if(largest!= index)
    {
       swap(&h->data[index],&h->data[largest]);
        heapify(h,largest);
    }
}

void insertkey(struct heap* h,int value)
{
    if(h->size>=MAX)
    {
        printf("full\n");
    }
    h->data[h->size]=value;
    h->size++;

    int i=h->size-1;
    while(i>0&&h->data[(i-1)/2]<h->data[i])
    {
        swap(&h->data[i],&h->data[(i-1)/2]);
        i=(i-1)/2;
    }
printf("Inserted: %d",value);
}

void inckey(struct heap* h ,int index,int data)
{
    if(data<h->data[index])
    { 
        printf("new key is smaller\n");
        return;
    }
    h->data[index]=data;

    while(index>0&&h->data[(index-1)/2]>h->data[index])
    {
        swap(&h->data[index],&h->data[(index-1)/2]);
        index=(index-1)/2;
    }
}

void decreasekey(struct heap* h,int index,int data)
{
    if(data>h->data[index])
    {
        printf("new key is greater\n");
        return;
    }
    h->data[index]=data;
    heapify(h,index);
}

void heapsort(struct heap* h)
{
     int orgsize=h->size;
    for(int i=(h->size/2)-1;i>=0;i--)
    {
        swap(&h->data[0],&h->data[i]);
        h->size--;
        heapify(h,0);
    }
    h->size=orgsize;
}

int main()
{
    struct heap* h;
    initheap(&h);

       insertkey(&h, 10);
    insertkey(&h, 20);
    insertkey(&h, 35);
    insertkey(&h, 30);
    insertkey(&h, 15);

    printf("Heap before sorting: ");
    print(&h);

    heapsort(&h);
    printf("Heap after sorting: ");
    print(&h);

    return 0;
}