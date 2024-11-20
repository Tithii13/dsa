
#include<stdio.h>
int main()
{
int n,i,k;
int temp,j;
int a[10];
printf("Enter the number of elements in the array: ");
scanf("%d",&n);
printf("Enter the elements: \n");
for(i=0;i<n;i++)
{
    scanf("%d",&a[i]);
}
printf("ARRAY ELEMENTS: \n");
k=0;
while(k<n)
{
    if(a[k]==0)
    {
        temp=a[k];
        for(j=k;j<n-1;j++)
        {
            a[j]=a[j+1];
        }
        a[j]=temp;
     // k=0;
       }
      // else
    {

        k=k+1;
    }
    
}
for(i=0;i<n;i++)
{
    printf("%d  ",a[i]);
}
return 0;
}
