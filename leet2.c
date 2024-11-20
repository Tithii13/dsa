#include <stdio.h>

int compareNumbers(int a,int b) {
    return a-b;
}

void bubbleSort(int arr[],int size) {
    int i,j,temp;
    for (i=0;i<size-1;i++) {
        for (j=i+1;j<size;j++) {
            if (compareNumbers(arr[i],arr[j])>0) {
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}

void findZeroSumTriplets(int arr[],int size) {
    bubbleSort(arr,size);
    
    for (int i=0;i<size-2;i++) {
        if (i>0&&arr[i]==arr[i-1]) {
            continue;
        }

        int l=i+1;
        int r=size-1;

        while (l<r) 
        {
            int currentSum=arr[i]+arr[l]+arr[r];
            if (currentSum==0) {
                printf("[%d, %d, %d]\n",arr[i],arr[l],arr[r]);
                
                while (l<r&&arr[l]==arr[l+1]) 
                {
                    l++;
                }
                while (l<r&&arr[r]==arr[r-1]) 
                {
                    r--;
                }

                l++;
                r--;
            } else if (currentSum < 0) {
                l++;
            } else {
                r--;
            }
        }
    }
}
int main() 
{
    int numbers[]={-1, 0, 1, 2, -1, -4};
    int size=sizeof(numbers)/sizeof(numbers[0]);

    printf("Triplets that sum to 0 are:\n");
    findZeroSumTriplets(numbers,size);

    return 0;
}
