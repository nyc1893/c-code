

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//创建结构体及其成员
typedef struct Node
{
 int num;//编号
 char *name;//姓名

 struct Node *next;//指针域
}S;//结构体定义为S



//创建链表模块
S *create(int n,char word[])
{
    S *head,*p,*q;//定义指针
    int i;
    head=(S*)malloc(sizeof(S));//头节点开辟空间

    head->next=NULL;//置空头节点的指针域
    q=head;//q指针记录头节点的地址
    p=head->next;//p指针记录头节点的指针域的地

    p=(S *)malloc(sizeof(S));//p指针开辟空间
    //输入各成员
    p->num=n;
    p->name = word;


    p->next=NULL;//置空p节点的指针域
    q->next=p;//p，q节点连接
    q=p;//q指针后移
    return head;//返回链表的起始地址
}



void insert(S *head,int n, char word[])
{
    int num;//flag实现判断指针是否到达最后一个节点

    S *p,*r; //定义指针便于插入操作



     r=(S *)malloc(sizeof(S));//为r开辟空间
    if(r==NULL)                             //空间不足处理
    {
        printf("No Enough Memory\n");
        exit(0);
    }

     r->num=n;
     r->name=word;
     r->next=NULL;

    if(head==NULL) head = p;
     else
    {
         S *q=head;
        while(q->next!=NULL) q=q->next;
        q->next = r;
    }


}




//输出链表模块
void print(S *head)
{
 int i;
 S *p=head->next;
 while(p)//当p不为空的时候执行
 {
     printf("%d %s \n",p->num,p->name);
     p=p->next;//指针后移
 }
}


//输出链表模块
void cal(S *head)
{
 int i;
 int s1 = 0;
 int s2 = 0;
 S *p=head->next;
 while(p)//当p不为空的时候执行
 {
     if(p->name == "cc")
        s1 += p ->num;
     if(p->name == "aa")
        s2 += p ->num;
     p=p->next;//指针后移
 }
 printf("%d %d \n",s1,s2);

}


//主函数
int main()
{
    S *head;


    printf("start of Main fuction:\n");


    head=create(1,"cc");
    insert(head,2,"cc");
    insert(head,3,"aa");
    insert(head,4,"aa");
    print(head);
    cal(head);
    return 0;

}


