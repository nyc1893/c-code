#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<malloc.h>

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


////输出链表模块
//void cal(S *head)
//{
// int i;
// int s1 = 0;
// int s2 = 0;
// S *p=head->next;
// while(p)//当p不为空的时候执行
// {
//     if(p->name == "cc")
//        s1 += p ->num;
//     if(p->name == "aa")
//        s2 += p ->num;
//     p=p->next;//指针后移
// }
// printf("%d %d \n",s1,s2);
//
//}



void detect(char *lf,char *rt,char *buf,int *out,int *s)
{


    char *ptr = NULL;
	char *end = NULL;
	//char ip[32] = {0};
//	printf("lf:%s\n",lf);
//	printf("rt:%s\n",rt);
//	printf("buf:%s\n",buf);

	ptr = strstr(buf,lf);
    if(!ptr)
    {
        printf("Input wrong, there is no match with %s\n",lf);
        return 0;
    }
    else
    {
        ptr = ptr + strlen(lf);
    //	printf("sizeof(lf)/sizeof(char):%d\n",strlen(lf));
        end = strstr(ptr,rt);

//        printf("end:%s\n",end);
//    	printf("ptr:%s\n",ptr);

        char* ip = (char*)malloc((end-ptr)/sizeof(char));
        if(!ip)   exit(1);
    //    printf("%d\n",(end-ptr)/sizeof(char));
        memcpy(ip,ptr,(end-ptr)/sizeof(char));
        //printf("ip:%s\n",ip);
        int num = atoi(ip);
//        printf("number = %d\n",num);
        free(ip);
        ip = NULL;
    //    printf("buf len:%d\n",strlen(buf));
    //    printf("end len:%d\n",strlen(end));
         *out=num;
         *s = (strlen(buf)-strlen(end));
    }
}


int detectc(char *lf,char *buf)
{
    char *ptr = NULL;

	ptr = strstr(buf,lf);
	if(!ptr)
    {
        printf("Input wrong, there is no match with %s\n",lf);
        return 0;
    }
    else
    {
        ptr = ptr + strlen(lf);

        char* ip = (char*)malloc(4);
        if(!ip)   exit(1);

        memcpy(ip,ptr,4);

        int num = atoi(ip);
//        printf("number = %d\n",num);
        free(ip);
        ip = NULL;

        return (strlen(buf)-strlen(ptr));
    }
}




void stringFilter(char *str,int num)
{
    int j =0;
    if(str ==NULL)
    {
        printf("Error");
    }
    else
    {

            for (int i = num-1; str[i] != '\0'; i++)
            {
                str[j] = str[i];
                j++;
            }

    }

    str[j] = '\0';
}


char *getfileall(char *fname)
{
	FILE *fp;
	char *str;
	char txt[1000];
	int filesize;
	if ((fp=fopen(fname,"rt"))==NULL){
		printf("打开文件%s错误\n",fname);
		return NULL;
	}

	fseek(fp,0,SEEK_END);

	filesize = ftell(fp);
	str=(char *)malloc(filesize);
	str[0]=" ";

	rewind(fp);
	while((fgets(txt,1000,fp))!=NULL){
		strcat(str,txt);
	}
	fclose(fp);
	return str;
}

int main()
{

    char *p;
	char *fname="test_1a.txt";
	p=getfileall(fname);
	if (p!=NULL)
        printf("Load file done!\n");
//    printf("%s", p);

    char buf[1000];
    strcpy(buf, p);
    printf("len = %d\n",strlen(buf));
    printf("buf = %s\n",buf);



//   char  buf[]="Start Program Meta-Data Code:\
//S{begin}0; A{begin}0; P{run}11; M{allocate}2;\
//O{monitor}7; I{hard drive}8; I{mouse}8; O{printer}20;\
//P{run}6; O{printer}4; M{block}6;\
//I{keyboard}17; M{block}4; O{printer}8; P{run}5; P{run}5;\
//O{hard drive}6; P{run}18; A{finish}0; S{finish}0.\
//End Program Meta-Data Code.";

    char conf[] = " Start Simulator Configuration File\
Version/Phase: 1.0\
File Path: Test_1a.mdf\
Monitor display time {msec}: 20\
Processor cycle time {msec}: 10\
Mouse cycle time {msec}: 25\
Hard drive cycle time {msec}: 15\
Keyboard cycle time {msec}: 50\
Memory cycle time {msec}: 30\
Printer cycle time {msec}: 10\
Log: Log to Both\
Log File Path: logfile_1.lgf\
End Simulator Configuration File";

    int *s =NULL;
    int *out =NULL;


    detect("P(run)",";",buf,&out,&s);
    stringFilter(buf,s+2);
    printf("s = %d, outvalue = %d\n",s,out);



//    s = detect("M{allocate}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("O{monitor}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("I{hard drive}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("I{mouse}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("O{printer}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("P{run}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("O{printer}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("P{run}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("P{run}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("O{hard drive}",";",buf);
//    stringFilter(buf,s+2);
//
//    s = detect("P{run}c",";",buf);
//    stringFilter(buf,s+2);
//
//
//
//    s = detectc("Monitor display time {msec}: ",conf);
//    stringFilter(conf,s);
//
//    s = detectc("Processor cycle time {msec}: ",conf);
//    stringFilter(conf,s);
//
//    s = detectc("Mouse cycle time {msec}: ",conf);
//    stringFilter(conf,s);
//
//    s = detectc("Hard drive cycle time {msec}: ",conf);
//    stringFilter(conf,s);
//
//    s = detectc("Keyboard cycle time {msec}: ",conf);
//    stringFilter(conf,s);
//
//    s = detectc("Memory cycle time {msec}: ",conf);
//    stringFilter(conf,s);
//
//    s = detectc("Printer cycle time {msec}: ",conf);
//    stringFilter(conf,s);
//
//
//   s = detectc("123: ",conf);



    return 0;

}
