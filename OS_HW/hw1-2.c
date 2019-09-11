#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include<malloc.h>




struct state {
    int num;
    char *name;
}NV;


void print_str(char *name1,typeof(NV) *pt)
{
    printf("%s = %d, name = %s\n",name1,pt->num,pt->name);
}

void change_str(int num2,char *name2,typeof(NV) *pt)
{
    pt->num = num2;
    pt->name = name2;

}

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

    //    printf("end:%s\n",end);
    //	printf("ptr:%s\n",ptr);

        char* ip = (char*)malloc((end-ptr)/sizeof(char));
        if(!ip)   exit(1);
    //    printf("%d\n",(end-ptr)/sizeof(char));
        memcpy(ip,ptr,(end-ptr)/sizeof(char));
        //printf("ip:%s\n",ip);
        int num = atoi(ip);
        printf("number = %d\n",num);
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
        printf("number = %d\n",num);
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

int main()
{

    typeof(NV) *pt1 = &NV;
    pt1->num = 10;
    pt1->name = "Nevada";

    print_str("Winco",&NV);
    change_str(200,"Costco",&NV);
    print_str("Costco",&NV);

    char buf[]="Start Program Meta-Data Code:\
S{begin}0; A{begin}0; P{run}11; M{allocate}2;\
O{monitor}7; I{hard drive}8; I{mouse}8; O{printer}20;\
P{run}6; O{printer}4; M{block}6;\
I{keyboard}17; M{block}4; O{printer}8; P{run}5; P{run}5;\
O{hard drive}6; P{run}18; A{finish}0; S{finish}0.\
End Program Meta-Data Code.";

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


    detect("P{run}",";",buf,&out,&s);
    stringFilter(buf,s+2);
    printf("s = %d, outvalue = %d\n",s,pt);

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
