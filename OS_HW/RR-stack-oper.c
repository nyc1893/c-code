#include<stdio.h>
#include<malloc.h>
#include<string.h>

void display(int arr[])
{
    for(int i = 0; i<15;i++)
    {
        printf("arr[%d] = %d\n",i,arr[i]);
    }
}

int count_num(int arr[])
{
    int result =0;
    if(arr[14]!=0) result = 15;
    for(int i = 0; i<15;i++)
    {

        if(!arr[i] )
        {
            result = i;
            break;
        }

//        printf("arr[%d] = %d\n",i,arr[i]);
    }
//    printf("The number of arr is %d\n",count_num(arr));
    return result;
}

int add_arr(int *arr,int num)
{
    int result =0;
    if(count_num(arr)==15)
    {
        result = -1;
//        printf("You can not add \n");
    }
    else
    {
        result =0;
        *(arr+count_num(arr)) = num;
    }
    return result;
}

int del_arr(int *arr)
{
    int result =0;
    int tmp = 0;
//    int tmp2 = 0;
    if(count_num(arr)==0)
    {
        result = -1;
//        printf("You can not add \n");
    }
    else
    {
        result =0;
        for(int i = 1; i<count_num(arr);i++)
        {
            tmp = *(arr+i);
             *(arr+i-1) = tmp;
        }
        *(arr+count_num(arr)-1) = 0;
    }
    return result;
}

void swap_arr(int *arr)
{
    int tmp = 0;
    tmp = *(arr+0);
    del_arr(arr);
    add_arr(arr,tmp);

}



//int arr[15] = {1,2,3,4,5,6,7,8,9,1,1,2,3,4,5};
int arr[15] = {1,2,3};
void main(){

//

    display(arr);
    printf("The number of arr is %d\n",count_num(arr));

//    add_arr(&arr,8);
//    if(add_arr(&arr,8)<0)    printf("OMG\n");
    swap_arr(arr);
    display(arr);
    printf("The number of arr is %d\n",count_num(arr));

//    del_arr(&arr);
//    display(arr);
//    printf("The number of arr is %d\n",count_num(arr));
//    del_arr(&arr);
//    del_arr(&arr);
//    del_arr(&arr);
//    display(arr);
//    printf("The number of arr is %d\n",count_num(arr));
//    if(del_arr(&arr)<0)    printf("OMG\n");

}
