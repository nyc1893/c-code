
// Program Header Information ////////////////////////////////////////
/**
* @file main.c
*
* @brief program for SIM05
* 
* @details Simulation of a simle, one-program OS simulator
*
* @version 1.00
*          C.S. Student (10 Dec 2019)
*          Initial development of SIM05
*
* @note None
*/
// Program Description/Support /////////////////////////////////////
/*
 This assignment tests the knowledge of strings, reading from files,
 and data structures. This assignment allows to create a library
 of functions/classes for use in later projects. And this assignment
 is designed as a data structures problem.
*/
// Precompiler Directives //////////////////////////////////////////
//
/////  NONE
//
// Header Files ///////////////////////////////////////////////////
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<malloc.h>
#include <time.h>
#include <semaphore.h>
#include "pthread.h"
#include "unistd.h" 
 
 
static sem_t sig1;
static sem_t sig2;

//
// Global Constant Definitions ////////////////////////////////////
//

#define waittime 100
#define time_cyc 50
#define c_num 13
#define MAX_LINE 50
#define  option_num 9
#define ElementType1 long //store type
#define ElementType2 char //store type
#define ElementType3 long //store type
#define MAXSIZE 100 //max store size
#define ERROR -99 //ElementType for error notation
// unsigned int mem_call = 0 ; //to get an allocated initial address

int s1 = 0;//s1~s15 means the running deapth in terms of time for 
int s2 = 0;//each queue from q1~q15, will always be negative value
int s3 = 0;
int s4 = 0;		
int s5 = 0;

int s6 = 0;
int s7 = 0;	
int s8 = 0;
int s9 = 0;		
int s10 = 0;

int s11 = 0;
int s12 = 0;	
int s13 = 0;
int s14 = 0;		
int s15 = 0;


int pt1 = 1;//pt1~pt15 means the running in which level of the queue
int pt2 = 1;//for example pt1 = 1 means queue 1 is runing in the its 
int pt3 = 1;//index of 1.
int pt4 = 1;
int pt5 = 1;

int pt6 = 1;
int pt7 = 1;
int pt8 = 1;
int pt9 = 1;
int pt10 = 1;

int pt11 = 1;
int pt12 = 1;
int pt13 = 1;
int pt14 = 1;
int pt15 = 1;
int arr[15];	
int tit =0;

int vitual_flag = 0;//this is a flag for debug
int counter =0;     //this is a counter one function
unsigned int mem_call = 0 ; //to get an allocated initial address
int UsedPrinters=0;
int UsedHD=0;


//
// Class Definitions //////////////////////////////////////////////
//
struct conf
  {
   // struct that records Config information read from Config file
	   int p_num;
	   int scheducode;
	   int process;
	   int monitor;
	   int mouse;
	   int hardDrive;
	   int printer;
	   int keyboard;
	   int memory;
	   int sysmem;
	   int memsize;
	   int printerq;
	   int harddriveq;
//   bool logbothtrue;
//   char dataFile[15];
//   char outputFile[15];
  }Conf_Info;
      
	typedef struct __DATA
	{
		int 	ss1;//ss1~ss15 are how much levels for each queue
		int		ss2;
		int 	ss3;
		int		ss4;
		int 	ss5;
		
		int 	ss6;
		int		ss7;
		int 	ss8;
		int		ss9;
		int 	ss10;
		
		int 	ss11;
		int		ss12;
		int 	ss13;
		int		ss14;
		int 	ss15;

		long    add1;//add1~add15 are the address for each queue
		long 	add2;
		long    add3;
		long 	add4;	
		long    add5;
		
		long    add6;
		long 	add7;
		long    add8;
		long 	add9;	
		long    add10;
		
		long	add11;
		long 	add12;
		long    add13;
		long 	add14;	
		long    add15;
		
		int 	opt_num; //store the number of 
						 //now which process is running
		long    t1; //store start time for a I/O operation 
		long    t2; //store end time for a I/O operation 
		long    it1;//pass inital time in sec 
		long    it2;//pass inital time in usec 		
		char    *fmeta;
	}DATA;
    typedef struct {
        ElementType1 data[MAXSIZE];
        ElementType2 *name[MAXSIZE];
		ElementType3 data2[MAXSIZE];
        int front; // start of Q
        int rear; // end of Q
        int size; //number of element
    }Queue;
//
// Free Function Prototypes ///////////////////////////////////////
//
    Queue* CreateQueue();
    void DestroySequeue(Queue *q);
    int IsFullQ(Queue* q);
    void AddQ(Queue* q, ElementType1 item1,ElementType2 *item2,ElementType3 item3);
    int IsEmptyQ(Queue* q);
    ElementType1 DeleteQ(Queue* q);
    void PrintQueue(Queue* q);


    ElementType1 getQv(Queue* q,int offset);
    ElementType2 *getQs(Queue* q,int offset);
	ElementType3 getQv2(Queue* q,int offset);


	void SimulatorTimer(int waitTime);
	int cal_sjf(Queue* q,int s1,int ss);
	int min(int arr[],int size);
	int min2(int arr[]);
	void* printA(void* param);
	void* printB(void* param);

	char *MyStrCpy(char *dest,const char *scr);
    char *remove_space(char *str2, const char *str1);
	void readmeta(char *fileName,Queue *q1,Queue *q2,Queue *q3,Queue *q4,Queue *q5,Queue *q6,Queue *q7,Queue *q8,Queue *q9,Queue *q10,Queue *q11,Queue *q12,Queue *q13,Queue *q14,Queue *q15);


	int * checkmeta(char *fileName);
	int *getconf(char *fileName );
	int printConf(char *fname);	

	int delete_sub_str(const char *str, const char *sub_str, char *result_str);
	void SplitStrByStr( char* sources, char str, char arry[10][20], int* count);
	int allocateHardDrive();
	int allocatePrinter();
	unsigned int allocateMemory();
	void print_log(int opt,int opt_num,int it1,int it2);
	void print_log2(int opt,int opt_num,int it1,int it2,char *arr);
	void print_log3(int opt,int proc_num,int t1,int t2,char *arr);
	void disp_q(Queue* q,int s1,int ss);
	void process_q2(Queue* q,int c1,int ss,long t1,long t2,int proc_num);
	void process_q(Queue* q,int c1,int ss,long t1,long t2,int proc_num);

	void dis_arr(int arr[]);
	int count_num(int arr[]);
	int add_arr(int *arr,int num);
	int del_arr(int *arr);
	void swap_arr(int *arr);
	int get_arr(int arr[]);


	
	void* printC(void* param);
	void* printD(void* param);
		
	void p1(int t1,int t2,Queue *q1);
	void p2(int t1,int t2,Queue *q1);
	void p3(int t1,int t2,Queue *q1);
	void p4(int t1,int t2,Queue *q1);
	void p5(int t1,int t2,Queue *q1);
	void p6(int t1,int t2,Queue *q1);	
	void p7(int t1,int t2,Queue *q1);
	void p8(int t1,int t2,Queue *q1);
	void p9(int t1,int t2,Queue *q1);
	void p10(int t1,int t2,Queue *q1);
	void p11(int t1,int t2,Queue *q1);
	void p12(int t1,int t2,Queue *q1);
	void p13(int t1,int t2,Queue *q1);
	void p14(int t1,int t2,Queue *q1);
	void p15(int t1,int t2,Queue *q1);
	
	int SimulatorTest(char *fconf,char *fmeta);
	int cal_sum(Queue *q1,int num);	
	
	static void _split_whole_name(const char *whole_name, char *fname, char *ext);
	int checksuffix(char *fconf,char *suffix,int num);
	void splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);

    int main(int argc,char* argv[])
    {
        // char *cof = "config_3.conf";
        char *meta = "test_1a.mdf";
       
        if (argc < 2)
        {  
            printf("error!\n");
            printf("The right format should be: ./sim conffile\n");
            printf("A referrence command should be: ./sim config_1.conf\n");
            return -1;
        }
     
        // suffix check conf file
        if(!checksuffix(argv[1],".conf",6))
        {
            printf("Input conf file suffix error!\n");
            printf("It should be: .conf!\n");
            return 0;
        }
        // suffix check meta file
        if(!checksuffix(meta,".mdf",5))
        {
            printf("Input meta file suffix error!\n");
            printf("It should be: .mdf!\n");
            return 0;
        }

		// SimulatorTest(cof,meta);
        // SimulatorTest(argv[1],argv[2]); 
       SimulatorTest(argv[1],meta);
        return 0;
    }

/**
* @brief Function to delay
*
* @pre waitTime is a ms unit for simulation.
*
* @No return 
*
*/
	void SimulatorTimer(int waitTime)//this is a ms unit wait
	{

		usleep(1000*waitTime);
	}

/**
* @brief Function create a Queue  
*
* @return head of address of q
*
*/    
 Queue* CreateQueue() {
        Queue* q = (Queue*)malloc(sizeof(Queue));
        if (!q) {
            printf("Insufferent Space!\n");
            return NULL;
        }
        q->front = -1;
        q->rear = -1;
        q->size = 0;
        return q;
    }

/**
* @brief Function Destroy a Queue to release the memory
*/

    void DestroySequeue(Queue *q)
    {
        if (NULL != q)
        {
            free(q);
        }
    //    printf("Heap Space is free\n");
    }

/**
* @brief Function to check if a Queue is full.
*
* @return 0 means Queue is not full; return 1 means Queue is full.
*
*/
    int IsFullQ(Queue* q) {
        return (q->size == MAXSIZE);
    }
/**
* @brief Function add data into the Queue
*
* @pre item1 is a number, item2 is a string
*
*/
    void AddQ(Queue* q, ElementType1 item1,ElementType2 *item2,ElementType3 item3  ) {
        if (IsFullQ(q)) {
            printf("Queue is full!\n");
            return;
        }
        q->rear++;
        q->rear %= MAXSIZE;
        q->size++;
        q->data[q->rear] = item1;
		q->data2[q->rear] = item3;
        q->name[q->rear] = item2;
    }
/**
* @brief Function to check if a Queue is Empty.
*
* @return 0 means Queue is not Empty; return 1 means Queue is Empty.
*
*/
    int IsEmptyQ(Queue* q) {
        return (q->size == 0);
    }

/**
* @brief Function to remove one cell in a Queue.
*/
    ElementType1 DeleteQ(Queue* q) {
        if (IsEmptyQ(q)) {
//            printf("Empty Queue!\n");
            return ERROR;
        }
        q->front++;
        q->front %= MAXSIZE; //0 1 2 3 4 5
        q->size--;
        q->name[q->front];
        return q->data[q->front];
    }
/**
* @brief Function printout all the info. in a Queue.
*/
    void PrintQueue(Queue* q) {
        if (IsEmptyQ(q)) {
            printf("Empty Queue!\n");
            return;
        }
        printf("Print out Queue:\n");
        int index = q->front;
        int i;
        for (i = 0; i < q->size; i++) {
            index++;
            index %= MAXSIZE;
			printf("%ld\t  %s\t %d\n", q->data[index],q->name[index],q->data2[index]);
            // printf("%ld\t  %s\t 0x%08x\n", q->data[index],q->name[index],q->data2[index]);
        }
        printf("\n");
    }

/**
* @brief Function to get the info. from a Queue
*
* @pre Queue* q is the address for queue, offset is the Serial number of cell
*
* @return a value from a queue based on its offset
*
*/

    ElementType1 getQv(Queue* q,int offset) {
        if (IsEmptyQ(q)) {
//            printf("Empty Queue!\n");
            return -1;
        }
    //    printf("Print out Queue:\n");
        int index = q->front;
        int i;

        index = 0+offset;


        index %= MAXSIZE;
        return q->data[index];
    }


	ElementType3 getQv2(Queue* q,int offset) {
        if (IsEmptyQ(q)) {
//            printf("Empty Queue!\n");
            return -1;
        }
    //    printf("Print out Queue:\n");
        int index = q->front;
        int i;

        index = 0+offset;

        index %= MAXSIZE;
        return q->data2[index];
    }
/**
* @brief Function to get the info. from a Queue
*
* @pre Queue* q is the address for queue, offset is the Serial number of cell
*
* @return a string from a queue based on its offset
*
*/
    ElementType2 *getQs(Queue* q,int offset) {
        if (IsEmptyQ(q)) {
//            printf("Empty Queue!\n");
            return -1;
        }

        int index = q->front;
        int i;

        index = 0+offset;

        index %= MAXSIZE;

        return q->name[index];
    }
/**
* @brief Function to return the value of queue in terms of time in SJF scheduling
*/
int cal_sjf(Queue* q,int s1,int ss)
{
	int v1 = s1;
	int i =0;
	for(i =ss;i>0;i--)
	{
		v1 =v1 + getQv(q,i);
	}
	return v1;
}

/**
* @brief Function to get the min index based on flexible size of array
*/

int min(int arr[],int size)
{
	int result = 0;
	int ind = 0;
	int i = 0;

	// if(arr[0]==0 & arr[1]==0 & arr[2]==0& arr[3]==0 & arr[4]==0)  return -1;

	for (i =0;i< size;i++)
	{

		if(arr[i]>0)
		{
			result = arr[i];
			ind = i;
			break;
		}

//            printf("arr[%d] = %d\n",i,arr[i]);
	}

	for ( i =0;i< size;i++)
	{
		if(result>arr[i] & arr[i]>0)
		{
			result = arr[i];
			ind = i;
		}
	}
	return ind;
}

/**
* @brief Function to get the min index based on fixed size of array
*/

int min2(int arr[15])
{
	int result = 0;
	int ind = 0;
	int i = 0;

	if(arr[0]==0 & arr[1]==0 & arr[2]==0& arr[3]==0 & arr[4]==0&arr[5]==0 & arr[6]==0 & arr[7]==0& arr[8]==0 & arr[9]==0&arr[10]==0 & arr[11]==0 & arr[12]==0& arr[13]==0 & arr[14]==0)  return -1;

	for (i =0;i< 15;i++)
	{

		if(arr[i]>0)
		{
			result = arr[i];
			ind = i;
			break;
		}

//            printf("arr[%d] = %d\n",i,arr[i]);
	}

	for ( i =0;i< 15;i++)
	{
		if(result>arr[i] & arr[i]>0)
		{
			result = arr[i];
			ind = i;
		}
	}
	return ind;
}

/**
* @brief Function to read the info. from meta file
*
* The info. are splited by ";", and seperate the number and string stored into the queue
*
* @return the address for the queue
*
*/
    int *checkmeta(char *fileName)
    {
         int  digit;


        static int temp[7];
        char letter[50];

        int i = 0;
        int j = 0;
        int k =0;
        int err_line =0;
        int line_num=0;
         FILE * pFile;
        char mystring [100];
        char* res[999];    //store final result

        int p=0;    //pointer of res[]
        pFile = fopen (fileName , "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            while ( fgets (mystring , 100 , pFile) != NULL )    //read a line every time

            {
                int len = strlen(mystring);
                if(mystring[len-1]=='\n')
                    mystring[len-1] = '\0';

                char* tmp = (char*)malloc(100*sizeof(char));
                memcpy(tmp,mystring,len);//usage memcpy(dest, src, strlen(src));
                res[p++] = tmp;
                //puts (mystring);//put string every time
            }
            fclose (pFile);

        }
            int k2 =0 ;
			
         char *text1[] = {
			"S",
			"A",
            "P",
            "M",
            "O",
            "I"
         };			
			

         char *text2[] =
         {
            "Start Program Meta-Data Code:",
            "End Program Meta-Data Code."
         };

         char *text3[] =
         {
            "S{begin}",
            "A{begin}",
            "A{finish}",
            "S{finish}"
         };
		 
        // Queue* q = CreateQueue();
         for(i=0;i<p;i++)
         {
    // check the 1st line
            if(i==0)
            {
                 if(!strstr(res[i],text2[i]))
                 {
                    printf("In line %d,It should have those inforamtion:\n%s\n",i+1,text2[i]);
                    printf("please check the input Meta file\n");
                    return NULL;
                }
                else
                {
                    // AddQ(q, 0,text2[i],0);
                }

            }
            if(strstr(res[i],text3[3]))
            {
                // if(!strstr(res[i+1],text2[1]))
                // {
                    // printf("In line %d,It should have those inforamtion:\n%s\n",i+1+1,text2[1]);
                    // printf("please check the input Meta file\n");
                    // return NULL;
                // }
            line_num = i+1;
    //        printf("line_num is %d\n",line_num);
            }
            // printf("i=%d %s\n",i,res[i]);
         }
		 
		 // Queue* q = CreateQueue();
		 
		 
        int error_flag= 0;
        char* delim = ";";
        char* tmp;
        int  digit2;
        char buf1[255];
        char a[50][20];
        char c[50][20];
        int b[line_num];
        char *string = NULL;
         for(i=1;i<line_num;i++)
         {
                tmp = strtok(res[i], delim);
                while(tmp != NULL)
                {

                    MyStrCpy(a[j],tmp);
                    remove_space(c[j],a[j]);
                   // printf("before: %s\n",tmp);
                   // printf("after: %s\n",c[j]);
                    tmp = strtok(NULL, delim);
                    j++;
                }
                k=j;
               // printf("k = %d\n\n",k);

        }

        int num = 0;
        char str[30];

        for(j=0;j<k;j++)
        {
			// printf("C[%d] = %s \n",j,c[j]);
			if (strncmp(c[j],text1[0], 1) == 0)			//when it is S
			{
				if((strncmp(c[j],"S{begin}", 8) == 0)||(strncmp(c[j],"S{finish}", 9) == 0)){}
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be S{begin}or S{finish}.\n");
					return NULL;
				}
			}
			else if (strncmp(c[j],text1[1], 1) == 0)	//when it is A
			{
				if((strncmp(c[j],"A{begin}", 8) == 0)||(strncmp(c[j],"A{finish}", 9) == 0)){}
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be A{begin}or A{finish}.\n");
					return NULL;
				}
			}						
			else if (strncmp(c[j],text1[2], 1) == 0)	//when it is P
			{
				if(strncmp(c[j],"P{run}", strlen("P{run}")) == 0){}
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be P{run}.\n");
					return NULL;
				}
			}							
			else if (strncmp(c[j],text1[3], 1) == 0)//when it is M
			{
				if((strncmp(c[j],"M{allocate}", strlen("M{allocate}")) == 0)||(strncmp(c[j],"M{block}", strlen("M{block}")) == 0)){}	
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be M{allocate} or M{block}.\n");
					return NULL;
				}
			}
			else if (strncmp(c[j],text1[4], 1) == 0)	//when it is O
			{
				if((strncmp(c[j],"O{monitor}", strlen("O{monitor}")) == 0)||(strncmp(c[j],"O{printer}", strlen("O{printer}")) == 0)||(strncmp(c[j],"O{harddrive}",strlen("O{harddrive}")) == 0)){}	
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be O{monitor},O{printer} or O{hard drive}.\n");
					return NULL;
				}
			}							
			else if (strncmp(c[j],text1[5], 1) == 0)	//when it is I
			{
				if((strncmp(c[j],"I{harddrive}", strlen("I{harddrive}")) == 0)||(strncmp(c[j],"I{mouse}", strlen("I{mouse}")))||(strncmp(c[j],"I{keyboard}", strlen("I{keyboard}")) == 0)){}	
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be I{hard drive},I{mouse} or I{keyboard}.\n");
					return NULL;
				}
			}							

        }

    }
	
/**
* @brief Function to read meta file info. and stored into 15 queues
*/
	void readmeta(char *fileName,Queue *q1,Queue *q2,Queue *q3,Queue *q4,Queue *q5,Queue *q6,Queue *q7,Queue *q8,Queue *q9,Queue *q10,Queue *q11,Queue *q12,Queue *q13,Queue *q14,	Queue *q15)
    {
         int  digit;


        static int temp[7];
        char letter[50];

        int i = 0;
        int j = 0;
        int k =0;
        int err_line =0;
        int line_num=0;
         FILE * pFile;
        char mystring [100];
        char* res[999];    //store final result
		char name [5000];
        int p=0;    //pointer of res[]
        pFile = fopen (fileName , "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            while ( fgets (mystring , 100 , pFile) != NULL )    //read a line every time

            {
                int len = strlen(mystring);
                //if(mystring[len-1]=='\n')
                //    mystring[len-1] = '\0';
			    mystring[len] = '\0';

                char* tmp = (char*)malloc(500*sizeof(char));
                memcpy(tmp,mystring,len);//usage memcpy(dest, src, strlen(src));
                res[p++] = tmp;
				// free(tmp);
                // puts (mystring);//put string every time
            }
            fclose (pFile);
			
			
        }
		
			i = 1;
			// strcpy(name,res[i]);
			// printf("line = %d\n",i);
			// printf("it = %s\n",res[i]);
			// printf("\ncontent : %s\n",name);
			// printf("len of is %d\n",strlen(name));
			
			// printf("p = %d\n",p);
			for(i =1;i<p-1;i++)
			{
				// printf("line = %d\n",i);
				// printf("it = %s\n",res[i]);
				strcat(name,res[i]);
				
			}
			
	    char *sub_str1 = "S{begin}0;";
		char *sub_str2 = "S{finish}0";
	    // char *sub_str3 = "A{begin}0;";
		// char *sub_str4 = "A{finish}0";
		char *sub_str3 = ".";
		char *sub_str4 = ";";
		char *str = name;
		// char res[1000];
		// printf("name = %s\n",name);
	
		delete_sub_str(str, sub_str1, res);
		char *str2 = res;
		delete_sub_str(str2,sub_str2, res);
		char *str3 = res;
		delete_sub_str(str3,sub_str3, res);
		char *str4 = res;
		delete_sub_str(str4,sub_str4, res);				
		// char *str5 = res;
		// delete_sub_str(str5,sub_str5, res);		
	    // printf("res = %s\n", res);
		remove_space(name,res);
		// strcpy(name,res);
		
		int line =0;
		char* pStr  = name;
		char tmpChar = '}';
		
		char arry[100][20];
		char arry2[100][20];
		SplitStrByStr(pStr, tmpChar, arry, &line);
		// printf("line = %d\n", line);
		int darry[100];//cishu
		int darry2[100];//times
		int flag[100];
		// int  digit;
        char buf1[255];
		MyStrCpy(arry2[0],arry[0]);
		// arry2[0] = arry[0];
		for(i = 1; i < line; i++)
		{
			sscanf(arry[i],"%d %s" ,&digit,buf1);
			MyStrCpy(arry2[i],buf1);
			// arry2[i] = buf1;
			darry[i-1] = digit;
		}
		
	    char *text4[] =
        {
            "P",
            "M",
            "I",
            "O"
         };

        char *text5[] =
        {
            "harddrive",
            "mouse",
            "printer",
			"monitor",
            "keyboard"
         };	

		int prc_num =0;
		for(i = 0; i < line; i++)
		{
			
			if(!strncmp(arry2[i],"P",1))
			{
				// printf("Yeah\n");
				darry2[i] = (Conf_Info.process)*darry[i];
			}
			else if	(!strncmp(arry2[i],"M",1))
			{
				// printf("M\n");
				darry2[i] = Conf_Info.memory;
			}
			else if	((!strncmp(arry2[i],"I",1))|(!strncmp(arry2[i],"O",1)))
			{
				// printf("IO\n");
				if(strstr(arry2[i],text5[0]))
				{
					// printf("%s\n",text5[0]);
					darry2[i] = Conf_Info.hardDrive;
				}
				else if(strstr(arry2[i],text5[1]))
				{
					darry2[i] = Conf_Info.mouse;
					// printf("%s\n",text5[1]);
				}					
				else if(strstr(arry2[i],text5[2]))
				{
					darry2[i] = Conf_Info.printer;
					// printf("%s\n",text5[2]);
				}					
				else if(strstr(arry2[i],text5[3]))
				{
					darry2[i] = Conf_Info.monitor;
					// printf("%s\n",text5[3]);
				}				
				else if(strstr(arry2[i],text5[4]))
				{
					darry2[i] = Conf_Info.keyboard;
					// printf("%s\n",text5[4]);
				}
			}
			// printf("arry[%d] = %s  \t time = %d\n",i, arry2[i],darry[i]*darry2[i]);	
			if(!strncmp(arry2[i],"A{begin",strlen("A{begin")))
			{ ++prc_num;
			}
			flag[i] = prc_num;

		}
			for(i = 0; i < line; i++)
			{
			// printf("flag[%d] value = %d\n",i,flag[i]);
				if(flag[i]==1)	
				{
					AddQ(q1, darry[i]*darry2[i],arry2[i],0);
					AddQ(q4, darry[i]*darry2[i],arry2[i],0);
					AddQ(q7, darry[i]*darry2[i],arry2[i],0);
					AddQ(q10, darry[i]*darry2[i],arry2[i],0);
					AddQ(q13, darry[i]*darry2[i],arry2[i],0);
				}
				else if (flag[i]==2)
				{
					AddQ(q2, darry[i]*darry2[i],arry2[i],0);
					AddQ(q5, darry[i]*darry2[i],arry2[i],0);
					AddQ(q8, darry[i]*darry2[i],arry2[i],0);
					AddQ(q11, darry[i]*darry2[i],arry2[i],0);
					AddQ(q14, darry[i]*darry2[i],arry2[i],0);
				}
				else if (flag[i]==3)
				{
					AddQ(q3, darry[i]*darry2[i],arry2[i],0);
					AddQ(q6, darry[i]*darry2[i],arry2[i],0);
					AddQ(q9, darry[i]*darry2[i],arry2[i],0);
					AddQ(q12, darry[i]*darry2[i],arry2[i],0);
					AddQ(q15, darry[i]*darry2[i],arry2[i],0);
				}
			}
    }	

/**
* @brief pthread Function to control the pthread runing in SJF scheduling
*
* it will count down to 100 ms for next time reading and switch to pthread reading function
*/	
	void* printA(void* param)
	{
		// Queue *q6 = CreateQueue();
		int i =0;
		int j =0;
		int gap = 0;
		int size = 0;
		DATA* data = (DATA*)param;
		float time_use=0;

		//pointing to which command
		clock_t   total_t;
		struct timeval end;//struct timezone tz; //

		for(i = 0;i<5;i++)
		{

			sem_wait(&sig2);
		

			// printf("Now i = %d\n",i);
			if(i==0)
			{
				size =3;
				int arr1[size];
				arr1[0] = cal_sjf((data->add1),s1,data->ss1);
				arr1[1] = cal_sjf((data->add2),s2,data->ss2);
				arr1[2] = cal_sjf((data->add3),s3,data->ss3);
					
				// for(j =0;j<size;j++)
				// {
					// printf("arr1[%d] = %d\n",j,arr1[j]);
				// }
					
				if(min(arr1,size)==0)//q1 need to run next
				{
					s1 = s1 -100;
					data->opt_num = 1;
					process_q2(data->add1,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add1,1));						
					
				}
				
				else if(min(arr1,size)==1)//q2 need to run next
				{
					s2 = s2 -100;
					data->opt_num = 2;
					process_q2(data->add2,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add2,1));		
				}
						
				else if(min(arr1,size)==2)//q3 need to run next
				{
					s3-=100;
					data->opt_num = 3;
					process_q2(data->add3,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add3,1));						
				}		

					SimulatorTimer(waittime);		
			}

			if(i ==1)
			{
				size =6;
				int arr1[size];
				arr1[0] = cal_sjf((data->add1),s1,data->ss1);
				arr1[1] = cal_sjf((data->add2),s2,data->ss2);
				arr1[2] = cal_sjf((data->add3),s3,data->ss3);
				arr1[3] = cal_sjf((data->add4),s4,data->ss4);
				arr1[4] = cal_sjf((data->add5),s5,data->ss5);
				arr1[5] = cal_sjf((data->add6),s6,data->ss6);			
				
				// for(j =0;j<size;j++)
				// {
					// printf("arr1[%d] = %d\n",j,arr1[j]);
				// }
					
				if(min(arr1,size)==0)//q1 need to run next
				{
					s1 = s1 -100;
					data->opt_num = 1;
					process_q2(data->add1,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add1,1));						
					
				}
				
				else if(min(arr1,size)==1)//q2 need to run next
				{
					s2 = s2 -100;
					data->opt_num = 2;
					process_q2(data->add2,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add2,1));		
				}
						
				else if(min(arr1,size)==2)//q3 need to run next
				{
					s3-=100;
					data->opt_num = 3;
					process_q2(data->add3,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add3,1));						
				}		
				else if(min(arr1,size)==3)//q4 need to run next
				{
					s4-=100;
					data->opt_num = 4;
					process_q2(data->add4,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add4,1));						
				}
						
				else if(min(arr1,size)==4)//q5 need to run next
				{
					s5-=100;
					data->opt_num = 5;
					process_q2(data->add5,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add5,1));						
				}	
				else if(min(arr1,size)==5)//q6 need to run next
				{
					s6-=100;
					data->opt_num = 6;
					process_q2(data->add6,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add6,1));						
				}
					SimulatorTimer(waittime);					
			}
			if(i ==2)
			{
				size =9;
				int arr1[size];
				arr1[0] = cal_sjf((data->add1),s1,data->ss1);
				arr1[1] = cal_sjf((data->add2),s2,data->ss2);
				arr1[2] = cal_sjf((data->add3),s3,data->ss3);
				arr1[3] = cal_sjf((data->add4),s4,data->ss4);
				arr1[4] = cal_sjf((data->add5),s5,data->ss5);
				arr1[5] = cal_sjf((data->add6),s6,data->ss6);			
				arr1[6] = cal_sjf((data->add7),s7,data->ss7);
				arr1[7] = cal_sjf((data->add8),s8,data->ss8);
				arr1[8] = cal_sjf((data->add9),s9,data->ss9);	
				
				// for(j =0;j<size;j++)
				// {
					// printf("arr1[%d] = %d\n",j,arr1[j]);
				// }
					
				if(min(arr1,size)==0)//q1 need to run next
				{
					s1 = s1 -100;
					data->opt_num = 1;
					process_q2(data->add1,s2,2,data->it1,data->it2,data->opt_num);			
					
				}
				
				else if(min(arr1,size)==1)//q2 need to run next
				{
					s2 = s2 -100;
					data->opt_num = 2;
					process_q2(data->add2,s2,2,data->it1,data->it2,data->opt_num);	
				}
						
				else if(min(arr1,size)==2)//q3 need to run next
				{
					s3-=100;
					data->opt_num = 3;
					process_q2(data->add3,s2,2,data->it1,data->it2,data->opt_num);				
				}		
				else if(min(arr1,size)==3)//q4 need to run next
				{
					s4-=100;
					data->opt_num = 4;
					process_q2(data->add4,s2,2,data->it1,data->it2,data->opt_num);					
				}
						
				else if(min(arr1,size)==4)//q5 need to run next
				{
					s5-=100;
					data->opt_num = 5;
					process_q2(data->add5,s2,2,data->it1,data->it2,data->opt_num);					
				}	
				else if(min(arr1,size)==5)//q6 need to run next
				{
					s6-=100;
					data->opt_num = 6;
					process_q2(data->add6,s2,2,data->it1,data->it2,data->opt_num);
				}
				else if(min(arr1,size)==6)//q7 need to run next
				{
					s7-=100;
					data->opt_num = 7;
					process_q2(data->add7,s2,2,data->it1,data->it2,data->opt_num);					
				}
				else if(min(arr1,size)==7)//q8 need to run next
				{
					s8-=100;
					data->opt_num = 8;
					process_q2(data->add8,s2,2,data->it1,data->it2,data->opt_num);					
				}	
				else if(min(arr1,size)==8)//q9 need to run next
				{
					s9-=100;
					data->opt_num = 9;
					process_q2(data->add9,s2,2,data->it1,data->it2,data->opt_num);					
				}
						
					SimulatorTimer(waittime);					
			}		
			if(i ==3)
			{
				size =12;
				int arr1[size];
				arr1[0] = cal_sjf((data->add1),s1,data->ss1);
				arr1[1] = cal_sjf((data->add2),s2,data->ss2);
				arr1[2] = cal_sjf((data->add3),s3,data->ss3);
				arr1[3] = cal_sjf((data->add4),s4,data->ss4);
				arr1[4] = cal_sjf((data->add5),s5,data->ss5);
				arr1[5] = cal_sjf((data->add6),s6,data->ss6);			
				arr1[6] = cal_sjf((data->add7),s7,data->ss7);
				arr1[7] = cal_sjf((data->add8),s8,data->ss8);
				arr1[8] = cal_sjf((data->add9),s9,data->ss9);	
				arr1[9] = cal_sjf((data->add10),s10,data->ss10);
				arr1[10] = cal_sjf((data->add11),s11,data->ss11);
				arr1[11] = cal_sjf((data->add12),s12,data->ss12);			
				
				// for(j =0;j<size;j++)
				// {
					// printf("arr1[%d] = %d\n",j,arr1[j]);
				// }
				
				if(min(arr1,size)==0)//q1 need to run next
				{
					s1 = s1 -100;
					data->opt_num = 1;
					process_q2(data->add1,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add1,1));						
					
				}
				
				else if(min(arr1,size)==1)//q2 need to run next
				{
					s2 = s2 -100;
					data->opt_num = 2;
					process_q2(data->add2,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add2,1));		
				}
						
				else if(min(arr1,size)==2)//q3 need to run next
				{
					s3-=100;
					data->opt_num = 3;
					process_q2(data->add3,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add3,1));						
				}		
				else if(min(arr1,size)==3)//q4 need to run next
				{
					s4-=100;
					data->opt_num = 4;
					process_q2(data->add4,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add4,1));						
				}
						
				else if(min(arr1,size)==4)//q5 need to run next
				{
					s5-=100;
					data->opt_num = 5;
					process_q2(data->add5,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add5,1));						
				}	
				else if(min(arr1,size)==5)//q6 need to run next
				{
					s6-=100;
					data->opt_num = 6;
					process_q2(data->add6,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add6,1));						
				}
				else if(min(arr1,size)==6)//q7 need to run next
				{
					s7-=100;
					data->opt_num = 7;
					process_q2(data->add7,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add7,1));						
				}
				else if(min(arr1,size)==7)//q8 need to run next
				{
					s8-=100;
					data->opt_num = 8;
					process_q2(data->add8,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add8,1));						
				}	
				else if(min(arr1,size)==8)//q9 need to run next
				{
					s9-=100;
					data->opt_num = 9;
					process_q2(data->add9,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add9,1));						
				}
				
				else if(min(arr1,size)==9)//q10 need to run next
				{
					s10-=100;
					data->opt_num = 10;
					process_q2(data->add10,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add10,1));						
				}
				else if(min(arr1,size)==10)//q11 need to run next
				{
					s11-=100;
					data->opt_num = 11;
					process_q2(data->add11,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add11,1));						
				}	
				else if(min(arr1,size)==11)//q12 need to run next
				{
					s12-=100;
					data->opt_num = 12;
					process_q2(data->add12,s2,2,data->it1,data->it2,data->opt_num);
					// print_log(0, data->opt_num ,data->it1,data->it2);
					// print_log(1, data->opt_num ,data->it1,data->it2);
					// print_log2(0, data->opt_num ,data->it1,data->it2,getQs(data->add12,1));						
				}			
					SimulatorTimer(waittime);					
			}	
			
			if(i ==4)
			{
				size =15;
				int arr1[size];
				arr1[0] = cal_sjf((data->add1),s1,data->ss1);
				arr1[1] = cal_sjf((data->add2),s2,data->ss2);
				arr1[2] = cal_sjf((data->add3),s3,data->ss3);
				arr1[3] = cal_sjf((data->add4),s4,data->ss4);
				arr1[4] = cal_sjf((data->add5),s5,data->ss5);
				arr1[5] = cal_sjf((data->add6),s6,data->ss6);			
				arr1[6] = cal_sjf((data->add7),s7,data->ss7);
				arr1[7] = cal_sjf((data->add8),s8,data->ss8);
				arr1[8] = cal_sjf((data->add9),s9,data->ss9);	
				arr1[9] = cal_sjf((data->add10),s10,data->ss10);
				arr1[10] = cal_sjf((data->add11),s11,data->ss11);
				arr1[11] = cal_sjf((data->add12),s12,data->ss12);			
				arr1[12] = cal_sjf((data->add13),s13,data->ss13);
				arr1[13] = cal_sjf((data->add14),s14,data->ss14);
				arr1[14] = cal_sjf((data->add15),s15,data->ss15);				
				// for(j =0;j<size;j++)
				// {
					// printf("arr1[%d] = %d\n",j,arr1[j]);
				// }
					
				if(min(arr1,size)==0)//q1 need to run next
				{
					s1 = s1 -100;
					data->opt_num = 1;
					process_q2(data->add1,s2,2,data->it1,data->it2,data->opt_num);				
				}
				
				else if(min(arr1,size)==1)//q2 need to run next
				{
					s2 = s2 -100;
					data->opt_num = 2;
					process_q2(data->add2,s2,2,data->it1,data->it2,data->opt_num);	
				}
						
				else if(min(arr1,size)==2)//q3 need to run next
				{
					s3-=100;
					data->opt_num = 3;
					process_q2(data->add3,s2,2,data->it1,data->it2,data->opt_num);						
				}		
				else if(min(arr1,size)==3)//q4 need to run next
				{
					s4-=100;
					data->opt_num = 4;
					process_q2(data->add4,s2,2,data->it1,data->it2,data->opt_num);			
				}
						
				else if(min(arr1,size)==4)//q5 need to run next
				{
					s5-=100;
					data->opt_num = 5;
					process_q2(data->add5,s2,2,data->it1,data->it2,data->opt_num);						
				}	
				else if(min(arr1,size)==5)//q6 need to run next
				{
					s6-=100;
					data->opt_num = 6;
					process_q2(data->add6,s2,2,data->it1,data->it2,data->opt_num);						
				}
				else if(min(arr1,size)==6)//q7 need to run next
				{
					s7-=100;
					data->opt_num = 7;
					process_q2(data->add7,s2,2,data->it1,data->it2,data->opt_num);					
				}
				else if(min(arr1,size)==7)//q8 need to run next
				{
					s8-=100;
					data->opt_num = 8;
					process_q2(data->add8,s2,2,data->it1,data->it2,data->opt_num);					
				}	
				else if(min(arr1,size)==8)//q9 need to run next
				{
					s9-=100;
					data->opt_num = 9;
					process_q2(data->add9,s2,2,data->it1,data->it2,data->opt_num);						
				}
				
				else if(min(arr1,size)==9)//q10 need to run next
				{
					s10-=100;
					data->opt_num = 10;
					process_q2(data->add10,s2,2,data->it1,data->it2,data->opt_num);					
				}
				else if(min(arr1,size)==10)//q11 need to run next
				{
					s11-=100;
					data->opt_num = 11;
					process_q2(data->add11,s2,2,data->it1,data->it2,data->opt_num);					
				}	
				else if(min(arr1,size)==11)//q12 need to run next
				{
					s12-=100;
					data->opt_num = 12;
					process_q2(data->add12,s2,2,data->it1,data->it2,data->opt_num);						
				}			
				
				else if(min(arr1,size)==12)//q13 need to run next
				{
					s10-=100;
					data->opt_num = 13;
					process_q2(data->add13,s2,2,data->it1,data->it2,data->opt_num);					

				}
				else if(min(arr1,size)==13)//q14 need to run next
				{
					s11-=100;
					data->opt_num = 14;
					process_q2(data->add14,s2,2,data->it1,data->it2,data->opt_num);		
					
				}	
				else if(min(arr1,size)==14)//q15 need to run next
				{
					s12-=100;
					data->opt_num = 15;
					process_q2(data->add15,s2,2,data->it1,data->it2,data->opt_num);

				}						

					SimulatorTimer(waittime);					
			}					
			sem_post(&sig1); 

		}
		return (void*)"";
	}

/**
* @brief pthread Function for the pthread reading in SJF scheduling
*
* After each time reading data it will switch to pthread running function
*/	
	void* printB(void* param)
	{
		int i =0;
		DATA* data = (DATA*)param;
			Queue *q1 = CreateQueue();
			Queue *q2 = CreateQueue();
			Queue *q3 = CreateQueue();
			
			Queue *q4 = CreateQueue();		
			Queue *q5 = CreateQueue();
			Queue *q6 = CreateQueue();
			
			Queue *q7 = CreateQueue();
			Queue *q8 = CreateQueue();
			Queue *q9 = CreateQueue();		
			
			Queue *q10 = CreateQueue();
			Queue *q11 = CreateQueue();
			Queue *q12 = CreateQueue();
			
			Queue *q13 = CreateQueue();
			Queue *q14 = CreateQueue();		
			Queue *q15 = CreateQueue();
			
		
		readmeta(data->fmeta,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12,q13,q14,q15);
		for(i = 0;i<5;i++)
		{
			sem_wait(&sig1);
			
			float time_use=0;

			clock_t   total_t;
			struct timeval end;//struct timezone tz; //

			
			
			if( i ==0)
			{
				
				
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Simulator program starting\n",(total_t*0.1*10)/CLOCKS_PER_SEC);

				// printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1);
				// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
				
				data->add1 = q1;
				data->add2 = q2;
				data->add3 = q3;
				data->ss1 = 4;
				data->ss2 = 3;
				data->ss3 = 6;
			}
			
			if( i ==1)
			{
				// readmeta(data->fmeta,q4,q5,q6);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
				
				
				data->add4 = q4;
				data->add5 = q5;
				data->add6 = q6;
				
				data->ss4 = 4;
				data->ss5 = 3;
				data->ss6 = 6;			
				
			}

			if( i ==2)
			{
				// readmeta(data->fmeta,q7,q8,q9);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
				
				data->add7 = q7;
				data->add8 = q8;
				data->add9 = q9;
				
				data->ss7 = 4;
				data->ss8 = 3;
				data->ss9 = 6;
			}

			if( i ==3)
			{
				// readmeta(data->fmeta,q10,q11,q12);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);			
				data->add10 = q10;
				data->add11 = q11;
				data->add12 = q12;
				
				data->ss10 = 4;
				data->ss11 = 3;
				data->ss12 = 6;

			}

			if( i ==4)
			{
				// readmeta(data->fmeta,q13,q14,q15);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);			

				data->add13 = q13;
				data->add14 = q14;
				data->add15 = q15;
				
				data->ss13 = 4;
				data->ss14 = 3;
				data->ss15 = 6;		
			}		

			sem_post(&sig2); 
		}
		return (void*)"";
	}
   
   char *MyStrCpy(char *dest,const char *scr)
    {
        while (*scr!='\0')
        {
            *(dest++)=*(scr++);
        }
        *dest='\0';
        return dest;
    }
/**
* @brief Function remove_space out of a string
*
* @return a no space string
*
*/
    char *remove_space(char *str2, const char *str1)
    {
        while(*str1 != '\0'){
            if (*str1 == ' ')
            {
    //            count++;
            }else{
                *str2 = *str1;
                str2++;
            }
            str1++;
        }
        *str2 = '\0';
        return str2;
    }
	
/**
* @brief Function reads Config file
*
* @details Function reads Config file and record to Config table
*
* @pre char* fileName contains the name of Config file
*
* @pre struct* Config contains the Config table
*
* @post if the Config file doesn't exist, end the program
*
* @post all Config information recorded in Config table
*
* @return 0 means file reading error; return 1 means finish reading.
*
*/	
   int *getconf(char *fileName )
    {

        int  digit;
        char buf1[255];
        char buf2[255];
        char buf3[255];
        char buf4[255];
        char buf5[255];


        static int temp[c_num];
        char letter[50];
    //read conf file
        int i = 0;
        int j = 0;
        int k =0;

         FILE * pFile;
        char mystring [100];
        char* res[999];    //store final result

        int p=0;    //pointer of res[]
        pFile = fopen (fileName , "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            while ( fgets (mystring , 100 , pFile) != NULL )    //read a line every time

            {
                int len = strlen(mystring);
                if(mystring[len-1]=='\n')
                    mystring[len-1] = '\0';

                char* tmp = (char*)malloc(100*sizeof(char));
                memcpy(tmp,mystring,len);//usage memcpy(dest, src, strlen(src));
                res[p++] = tmp;
                //puts (mystring);//put string every time
            }
			
            fclose (pFile);

        }
		
		
            int k2 =0 ;

		char name[100];
			// printf("p = %d\n",p);
		 remove_space(name,res[1]);
		 // printf("%s\n",name);
		 
		if(strncmp(name,"Version/Phase:5.0",strlen("Version/Phase: 5.0")) == 0)	
		{
			 char *cof[c_num] = {"Processor Quantum Number","CPU Scheduling Code","Monitor display","Processor cycle",
					"Mouse cycle","Hard drive cycle","Keyboard cycle",
					"Memory cycle","Printer cycle","System memory","Memory block",
					"Printer quantity","Hard drive quantity"};
			 char *text[] =
			 {
				"Start Simulator Configuration File",
				"Version/Phase:",
				"File Path: Test_5a.mdf",
				"Processor Quantum Number {msec}:",
				"CPU Scheduling Code:",
				"Monitor display time {msec}:",
				"Processor cycle time {msec}:",
				"Mouse cycle time {msec}:",
				"Hard drive cycle time {msec}:",
				"Keyboard cycle time {msec}:",
				"Memory cycle time {msec}:",
				"Printer cycle time {msec}:",
				"System memory {kbytes}:",
				"Memory block size {kbytes}:",
				"Printer quantity:",
				"Hard drive quantity:",
				"Log:",
				"Log File Path:",
				"End Simulator Configuration File"
			 };
			 for(i=0;i<p;i++)
			 {
				 if(!strstr(res[i],text[i]))
				 {
					 printf("File input error in No.%d lines\n",i+1);
					 printf("It suppose to have these information:\n%s\n",text[i]);
					 return NULL;

				 }
				 else
				 {
					 for (j=0;j<c_num;j++)
					{
						 if(strstr(res[i],cof[j]))
						{	
							
							if(j ==1)
							{
								sscanf(res[i],"%s %s %s %s", buf1,buf2,buf3,buf4);
								// printf("%s\n", buf4);
								if(strcmp(buf4, "SJF") == 0)
								{
									// printf("This is SJF\n");
									digit = 0;
								}
								else if(strcmp(buf4, "FIFO") == 0)
								{
									// printf("This is FIFO\n");
									digit = 1;
								}
								else if(strcmp(buf4, "PS") == 0)
								{
									// printf("This is PS\n");
									digit = 2;
								}
								
								else if(strcmp(buf4, "RR") == 0)
								{
									// printf("This is RR\n");
									digit = 3;
								}								
								
								else 
								{
									printf("Input CPU Scheduling Code error!\n");
									return NULL;
								}
							}
							if(j==5)sscanf(res[i],"%s %s %s %s %s %d ", buf1,buf2,buf3,buf4,buf5,&digit );
							if(j==0|j==9|j ==12)sscanf(res[i],"%s %s %s %d ", buf1,buf2,buf3,&digit );
							if(j==11)sscanf(res[i],"%s %s  %d ", buf1,buf2,&digit );
							else sscanf(res[i],"%s %s %s %s %d ", buf1,buf2,buf3,buf4,&digit );
							temp[j] =digit;
						}
					}
				 }
			 }
			
			
		}

		// else if(strncmp(name,"Version/Phase:4.0",strlen("Version/Phase:4.0")) == 0)	
		// {}

		// else if(strncmp(name,"Version/Phase:3.0",strlen("Version/Phase:3.0")) == 0)
		// {}			
		
		// else if(strncmp(name,"Version/Phase:2.0",strlen("Version/Phase:2.0")) == 0)	
		// {}
		// else
		// {
			// printf("Please check the conf file version info. it should be Version/Phase:2.0 ,3.0 or 4.0!\n");
		// }
		 // for(int p2 = 0; p2<c_num;p2++)
		 // {
		 // printf("%d\t",temp[p2]);
		 // }
		  // printf("\n");
         return temp;

    }
/**
* @brief Function print out conf info. table
*
* @return 0 means file reading error; return 1 means finish reading.
*
*/	
    int printConf(char *fname)
    {
        int *p = getconf(fname);

        if (p==NULL)
        {
            printf("Please check your input Conf file!\n");
            return 0;
        }
		
        else
        {
            typeof(Conf_Info) *ptr1 = &Conf_Info;
			
			ptr1-> p_num = 		 *(p+0);
			ptr1-> scheducode =  *(p+1);
            ptr1-> process =     *(p+0+2);
            ptr1-> monitor =     *(p+1+2);
            ptr1-> mouse =       *(p+2+2);
            ptr1-> hardDrive =   *(p+3+2);
            ptr1-> printer =     *(p+4+2);
            ptr1-> keyboard =    *(p+5+2);
            ptr1-> memory =      *(p+6+2);
			
			ptr1-> sysmem =		*(p+7+2);
			ptr1-> memsize =	*(p+8+2);
			ptr1-> printerq =	*(p+9+2);
			ptr1-> harddriveq=	*(p+10+2);
			// printf("Now print\n");
			
			char *text[] =
			 {
				"p_num",
				"scheducode",
				"process",
				"monitor",
				"mouse",
				"hardDrive",
				"printer",
				"keyboard",
				"memory",
				"sysmem", 
				"memsize", 
				"printerq", 
				"harddriveq"
			 };
			
			
			
			// for (int i=0;i<13;i++)
			// {
				// printf("%s : %d\n",text[i],*(p+i));
			// }
			
			
            return 1;
        }
    }	
	
	
	int delete_sub_str(const char *str, const char *sub_str, char *result_str)
	{
		int count = 0;
		int str_len = strlen(str);
		int sub_str_len = strlen(sub_str);

		if (str == NULL)
		{
			result_str = NULL;
			return 0;
		}

		if (str_len < sub_str_len || sub_str == NULL)
		{
			while (*str != '\0')
			{
				*result_str = *str;
				str++;
				result_str++;
			}

			return 0;
		}

		while (*str != '\0')
		{
			while (*str != *sub_str && *str != '\0')
			{
				*result_str = *str;
				str++;
				result_str++;
			}

			if (strncmp(str, sub_str, sub_str_len) != 0)
			{
				*result_str = *str;
				str++;
				result_str++;
				continue;
			}
			else
			{
				count++;
				str += sub_str_len;
			}
		}

		*result_str = '\0';

		return count;
	}

	void SplitStrByStr( char* sources, char str, char arry[10][20], int* count)
	{

		int tmpCount = 0;
		char* sourcesCp1 = NULL;
		char* sourcesCp2 = NULL;
		sourcesCp1 = sources;
		sourcesCp2 = sources;

		do{
			//查找字符串s中首次出现字符c的位置
			sourcesCp1 = strchr(sourcesCp1, str);
			if (sourcesCp1 != NULL){
				if (sourcesCp1 - sourcesCp2 > 0){
					//返回找到字符的下一个位置 把之前的数据拷贝到数组中区
					strncpy(arry[tmpCount], sourcesCp2, sourcesCp1 - sourcesCp2);
					arry[tmpCount][sourcesCp1 - sourcesCp2] = '\0';
					tmpCount++;
					sourcesCp1++;
					sourcesCp2 = sourcesCp1;
				}
			}
			else
			{
				break;
			}
		} while (*sourcesCp1 != '\0');
		*count = tmpCount;

	}

	int allocateHardDrive()
	{
		UsedHD++;
		if (UsedHD >Conf_Info.harddriveq)
		{
			UsedHD=1;
			return UsedHD;
		}
		return UsedHD;
	}
/**
* @brief Function to implement a Printer counter. If it value = max, then reset
*
* @ return a Hard drive Number
*
*/	
	int allocatePrinter()
	{
		UsedPrinters++;
		if (UsedPrinters >Conf_Info.printerq)
		{
			UsedPrinters=1;
			return UsedPrinters;
		}
		return UsedPrinters;
	}
	unsigned int allocateMemory()
	{
		unsigned int address;
		address = mem_call*128;
		mem_call++;
		return address;
	}
	
/**
* @brief Function to simplify the console output information
*/	
	void print_log(int opt,int opt_num,int it1,int it2)//have no string output
	{		
		clock_t   total_t;
		float time_use=0;
		struct timeval start;
		struct timeval end;//struct timezone tz;

		gettimeofday(&end,NULL);
		time_use=(end.tv_sec - (it1))*1000000+(end.tv_usec - (it2));
		total_t = time_use;
		if(opt==0)
		{
			printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,opt_num);
		}
		else if (opt==1)
		{
			printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,opt_num);
		}
		else if (opt==2)
		{
			printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,opt_num);
		}
		else if (opt==3)
		{
			printf("%.3f - OS: process %d: completed\n",(total_t*0.1*10)/CLOCKS_PER_SEC,opt_num);
		}
	}
/**
* @brief Function to simplify the console output information, add a string part
*/		
	void print_log2(int opt,int opt_num,int it1,int it2,char *arr) //have string output
	{		
		clock_t   total_t;
		float time_use=0;
		struct timeval start;
		struct timeval end;//struct timezone tz;

		gettimeofday(&end,NULL);
		time_use=(end.tv_sec - (it1))*1000000+(end.tv_usec - (it2));
		total_t = time_use;
		if(opt==0)
		{
			printf("%.3f - Process %d: start %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,opt_num,arr);
		}
		else if (opt==1)
		{
			printf("%.3f - Process %d: end %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,opt_num,arr);
		}
	}
/**
* @brief Function to simplify the console output information, add a string part and will replace the string code
*
* to visible finial output in console
*/	
	void print_log3(int opt,int proc_num,int t1,int t2,char *arr) //have string output
	{		
		clock_t   total_t;
		float time_use=0;
		struct timeval start;
		struct timeval end;//struct timezone tz;

		gettimeofday(&end,NULL);
		time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
		total_t = time_use;
		if(opt==0)
		{
			// printf("%.3f - Process %d: start %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,opt_num,arr);
					if(!strncmp(arr,"A",strlen("M")))
					{
							printf("%.3f - OS: process %d completed in print log\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
							del_arr(arr);
				
					}
					else if(!strncmp(arr,"M",strlen("M")))
					{
						gettimeofday(&end,NULL);
						time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
						total_t = time_use;
						printf("%.3f - Process %d: allocating memory\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
		
						
					}
					
					else if(!strncmp(arr,"P",strlen("P")))
					{
						gettimeofday(&end,NULL);
						time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
						total_t = time_use;
						printf("%.3f - Process %d: start processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
					
					}
					
					else if(!strncmp(arr,"I",strlen("P")))
					{
						if(strstr(arr,"keyboard"))
						{
							gettimeofday(&end,NULL);
							time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
							total_t = time_use;
							printf("%.3f - Process %d: start keyboard input\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);

						}
					}	

					else if(!strncmp(arr,"O",strlen("P")))
					{
						if(strstr(arr,"keyboard"))
						{
							gettimeofday(&end,NULL);
							time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
							total_t = time_use;
							printf("%.3f - Process %d: start keyboard output\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);

						}
						else if(strstr(arr,"harddrive"))
						{
							gettimeofday(&end,NULL);
							time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
							total_t = time_use;
							printf("%.3f - Process %d: start hard drive output on HDD %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num,allocateHardDrive()-1);

						}
					}				

			
		}
		else if (opt==1)
		{

			if(!strncmp(arr,"M",strlen("M")))
			{
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;
				// printf("%.3f - Process %d: memory allocated at XXXXX\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
				printf("%.3f - Process %d: memory allocated at 0x%08x\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num,allocateMemory());
			}
			
			else if(!strncmp(arr,"P",strlen("P")))
			{
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;
				printf("%.3f - Process %d: end processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
			
			}
			
			else if(!strncmp(arr,"I",strlen("P")))
			{
				if(strstr(arr,"keyboard"))
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: end keyboard input\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);

				}
			}	

			else if(!strncmp(arr,"O",strlen("P")))
			{
				if(strstr(arr,"keyboard"))
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: end keyboard output\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);

				}
				else if(strstr(arr,"harddrive"))
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: end hard drive output\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);

				}
			}				
	

		}
	}
	
/**
* @brief Function show in info for the queue based on the death
*/		
	
	void disp_q(Queue* q,int s1,int ss)
	{
		int i =0;
		// printf("\tpt = %d\n",pt);
		printf("\ts1 = %d\n",s1);
		for(i = 0 ;i<ss;i++)
		{
			{	
				printf("\tIn process %d, time is %d, oper is %s\n",i,getQv(q,i),getQs(q,i));
			}
		}
	}
	
	
/**
* @brief Function for processing RR scheduling and get the output
*/		
	void process_q2(Queue* q,int c1,int ss,long t1,long t2,int proc_num)
	{
		int i =0;
		// printf("pt = %d\n",pt);
		// printf("s1 = %d\n",s1);
		clock_t   total_t;
		float time_use=0;
		struct timeval start;
		struct timeval end;//struct timezone tz;
		print_log(0, proc_num,t1,t2);
		print_log(1, proc_num,t1,t2);
		for(i = 1;i<ss;i++)
		{

			if(!strncmp(getQs(q,i),"A",strlen("M")))
			{

					printf("%.3f - OS: process %d completed\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
		
			}
			else if(!strncmp(getQs(q,i),"M",strlen("M")))
			{
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;
				printf("%.3f - Process %d: allocating memory\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
				
				// SimulatorTimer(c1+getQv(q,i));
				
				// gettimeofday(&end,NULL);
				// time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				// total_t = time_use;
				// printf("%.3f - Process %d: memory allocated at 0x%08x\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num,allocateMemory());					
				
			}
			
			else if(!strncmp(getQs(q,i),"P",strlen("P")))
			{
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;
				printf("%.3f - Process %d: start processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
				
				// SimulatorTimer(c1+getQv(q,i));
				
				// gettimeofday(&end,NULL);
				// time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				// total_t = time_use;
				// printf("%.3f - Process %d: end processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);							
			}
			
			else if(!strncmp(getQs(q,i),"I",strlen("P")))
			{
				if(strstr(getQs(q,i),"keyboard"))
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: start keyboard input\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
		
					// SimulatorTimer(c1+getQv(q,i));
					
					// gettimeofday(&end,NULL);
					// time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					// total_t = time_use;
					// printf("%.3f - Process %d: end keyboard input\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);	
				}
			}	

			else if(!strncmp(getQs(q,i),"O",strlen("P")))
			{
				if(strstr(getQs(q,i),"keyboard"))
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: start keyboard output\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
		
					// SimulatorTimer(c1+getQv(q,i));
					
					// gettimeofday(&end,NULL);
					// time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					// total_t = time_use;
					// printf("%.3f - Process %d: end keyboard output\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);	
				}
				else if(strstr(getQs(q,i),"harddrive"))
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: start hard drive output on HDD %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num,allocateHardDrive()-1);
		
					// SimulatorTimer(c1+getQv(q,i));
					
					// gettimeofday(&end,NULL);
					// time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					// total_t = time_use;
					// printf("%.3f - Process %d: end hard drive output\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);	
				}

			}	

		}
	
	}	
	
/**
* @brief Function for processing RR scheduling and get the output in another version
*/			
	void process_q(Queue* q,int c1,int ss,long t1,long t2,int proc_num)
	{
		int i =0;
		// printf("pt = %d\n",pt);
		// printf("s1 = %d\n",s1);
		clock_t   total_t;
		float time_use=0;
		struct timeval start;
		struct timeval end;//struct timezone tz;
		if(counter!=0)
		{
			print_log(0, proc_num,t1,t2);
			print_log(1, proc_num,t1,t2);
		}
		for(i = 1;i<ss;i++)
		{

			if(!strncmp(getQs(q,i),"A",strlen("M")))
			{

					printf("%.3f - OS: process %d completed\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
		
			}
			else if(!strncmp(getQs(q,i),"M",strlen("M")))
			{
				if(counter!=0)
				{
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;
				printf("%.3f - Process %d: allocating memory\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
				}
				SimulatorTimer(c1+getQv(q,i));
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;
				printf("%.3f - Process %d: memory allocated at 0x%08x\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num,allocateMemory());					
				
			}
			
			else if(!strncmp(getQs(q,i),"P",strlen("P")))
			{
				if(counter!=0)
				{
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;
				printf("%.3f - Process %d: start processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
				}
				SimulatorTimer(c1+getQv(q,i));
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;
				printf("%.3f - Process %d: end processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);							
			}
			
			else if(!strncmp(getQs(q,i),"I",strlen("P")))
			{
				if(strstr(getQs(q,i),"keyboard"))
				{
					if(counter!=0)
					{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: start keyboard input\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
					}
					SimulatorTimer(c1+getQv(q,i));
					
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: end keyboard input\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);	
				}
			}	

			else if(!strncmp(getQs(q,i),"O",strlen("P")))
			{
				if(strstr(getQs(q,i),"keyboard"))
				{
					if(counter!=0)
					{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: start keyboard output\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);
					}
					SimulatorTimer(c1+getQv(q,i));
					
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: end keyboard output\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);	
				}
				else if(strstr(getQs(q,i),"harddrive"))
				{
					if(counter!=0)
					{
						gettimeofday(&end,NULL);
						time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
						total_t = time_use;
						printf("%.3f - Process %d: start hard drive output on HDD %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num,allocateHardDrive()-1);
					}
					SimulatorTimer(c1+getQv(q,i));
					
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
					total_t = time_use;
					printf("%.3f - Process %d: end hard drive output\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num);	
				}

				
			}	

		}
		++counter;
	}
	

/**
* @brief Function to print the array info.
*
* I use an array to simulate a simple queue for RR scheduling
*
* its data type is like [1,2,3,0,0...0] it means there are 3 queue in RR scheduling
*
* when the time slice of process No.1 has been used up then it will swap to [2,3,1,0,0...0]
*
* so next is to run process No.2, zero means there is no other queue in the array
*/		
	void dis_arr(int arr[])
	{
		for(int i = 0; i<15;i++)
		{
			printf("arr[%d] = %d\n",i,arr[i]);
		}
	}
/**
* @brief Function to get how many processes in the queue
*/	
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
/**
* @brief Function to add one process in the array for example
*
* before adding is [2,3,0,...0] after adding it becomes [2,3,4,0,...0]
*
* it will only add in the right hand side
*/	
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
	
/**
* @brief Function to delete one process in the array for example
*
* before delete is [2,3,4,...0] after delete it becomes [3,4,0,...0]
*
* it will only delete in the left hand side
*/	
	int del_arr(int *arr)
	{
		int result =0;
		int tmp = 0;
		int num = count_num(arr);
	//    int tmp2 = 0;
		if(count_num(arr)==0)
		{
			result = -1;
	//        printf("You can not add \n");
		}
		else
		{

			for(int i = 1; i<count_num(arr);i++)
			{
				tmp = *(arr+i);
				 *(arr+i-1) = tmp;
			}
			*(arr+count_num(arr)-1) = 0;
		}
		
		if(count_num(arr)==num-1)result =1;
		// else result 
		return result;
	}
/**
* @brief Function to swap the array for example
*
* before swap is [2,3,4,...0] it becomes [3,4,2,...0]
*/	
	void swap_arr(int *arr)
	{
		int tmp = 0;
		tmp = *(arr+0);
		del_arr(arr);
		add_arr(arr,tmp);

	}
/**
* @brief Function to get the which process we need to run
*
* for example [2,3,4,...0] means we need to run process No.2
*/	
	int get_arr(int arr[])
	{
		return *arr;
	}
	
/**
* @brief Function from p15 ~ p1 to process the each queue in RR scheduling
*
* and get the correct output info.
*/		
	void p15(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s15 =s15 - Conf_Info.p_num;
		// printf("s15 is %d\n",s15);	

		if(s15+cal_sum(q1,pt15)>0)
		{
		
			print_log3(0, 15,t1,t2,getQs(q1,pt15));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 15,t1,t2,getQs(q1,pt15));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s15+ cal_sum(q1,pt15);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 15,t1,t2,getQs(q1,pt15));	
				SimulatorTimer(gap);
				print_log3(1, 15,t1,t2,getQs(q1,pt15));
				
				++pt15;
				
				if(strncmp(getQs(q1,pt15),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 15,t1,t2,getQs(q1,pt15));	
					SimulatorTimer(gap);
					print_log3(1, 15,t1,t2,getQs(q1,pt15));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,15,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 15,t1,t2);
				del_arr(arr);			
			}
		}		
	}	

	void p14(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s14 =s14 - Conf_Info.p_num;
		// printf("s14 is %d\n",s14);	

		if(s14+cal_sum(q1,pt14)>0)
		{
		
			print_log3(0, 14,t1,t2,getQs(q1,pt14));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 14,t1,t2,getQs(q1,pt14));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s14+ cal_sum(q1,pt14);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 14,t1,t2,getQs(q1,pt14));	
				SimulatorTimer(gap);
				print_log3(1, 14,t1,t2,getQs(q1,pt14));
				
				++pt14;
				
				if(strncmp(getQs(q1,pt14),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 14,t1,t2,getQs(q1,pt14));	
					SimulatorTimer(gap);
					print_log3(1, 14,t1,t2,getQs(q1,pt14));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,14,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 14,t1,t2);
				del_arr(arr);			
			}
		}		
	}	
	
	void p13(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s13 =s13 - Conf_Info.p_num;
		//printf("s13 is %d\n",s13);	

		if(s13+cal_sum(q1,pt13)>0)
		{
		
			print_log3(0, 13,t1,t2,getQs(q1,pt13));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 13,t1,t2,getQs(q1,pt13));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s13+ cal_sum(q1,pt13);
			//printf("gap = %d\n",gap);

			print_log3(0, 13,t1,t2,getQs(q1,pt13));	
			SimulatorTimer(gap);
			print_log3(1, 13,t1,t2,getQs(q1,pt13));
				
			++pt13;
			if(gap>0)
			{
				if(strncmp(getQs(q1,pt13),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 13,t1,t2,getQs(q1,pt13));	
					SimulatorTimer(gap);
					print_log3(1, 13,t1,t2,getQs(q1,pt13));	
					if(s13+cal_sum(q1,pt13)<0)
					{
						print_log(3,13,t1,t2);
						del_arr(arr);
					}
					else
					{
						swap_arr(arr);
					}
				}
				
			}
			else
			{
				print_log(3, 2,t1,t2);
				del_arr(arr);			
			}
		}		
	}		
	
	void p12(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s12 =s12 - Conf_Info.p_num;
		// printf("s12 is %d\n",s12);	

		if(s12+cal_sum(q1,pt12)>0)
		{
		
			print_log3(0, 12,t1,t2,getQs(q1,pt12));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 12,t1,t2,getQs(q1,pt12));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s12+ cal_sum(q1,pt12);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 12,t1,t2,getQs(q1,pt12));	
				SimulatorTimer(gap);
				print_log3(1, 12,t1,t2,getQs(q1,pt12));
				
				++pt12;
				
				if(strncmp(getQs(q1,pt12),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 12,t1,t2,getQs(q1,pt12));	
					SimulatorTimer(gap);
					print_log3(1, 12,t1,t2,getQs(q1,pt12));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,12,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 12,t1,t2);
				del_arr(arr);			
			}
		}		
	}	
	
	void p11(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s11 =s11 - Conf_Info.p_num;
		// printf("s11 is %d\n",s11);	

		if(s11+cal_sum(q1,pt11)>0)
		{
		
			print_log3(0, 11,t1,t2,getQs(q1,pt11));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 11,t1,t2,getQs(q1,pt11));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s11+ cal_sum(q1,pt11);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 11,t1,t2,getQs(q1,pt11));	
				SimulatorTimer(gap);
				print_log3(1, 11,t1,t2,getQs(q1,pt11));
				
				++pt11;
				
				if(strncmp(getQs(q1,pt11),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 11,t1,t2,getQs(q1,pt11));	
					SimulatorTimer(gap);
					print_log3(1, 11,t1,t2,getQs(q1,pt11));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,11,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 11,t1,t2);
				del_arr(arr);			
			}
		}		
	}	
	void p10(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s10 =s10 - Conf_Info.p_num;
		//printf("s10 is %d\n",s10);	

		if(s10+cal_sum(q1,pt10)>0)
		{
		
			print_log3(0, 10,t1,t2,getQs(q1,pt10));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 10,t1,t2,getQs(q1,pt10));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s10+ cal_sum(q1,pt10);
			//printf("gap = %d\n",gap);

			print_log3(0, 10,t1,t2,getQs(q1,pt10));	
			SimulatorTimer(gap);
			print_log3(1, 10,t1,t2,getQs(q1,pt10));
				
			++pt10;
			if(gap>0)
			{
				if(strncmp(getQs(q1,pt10),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 10,t1,t2,getQs(q1,pt10));	
					SimulatorTimer(gap);
					print_log3(1, 10,t1,t2,getQs(q1,pt10));	
					if(s10+cal_sum(q1,pt10)<0)
					{
						print_log(3,10,t1,t2);
						del_arr(arr);
					}
					else
					{
						swap_arr(arr);
					}
				}
				
			}
			else
			{
				print_log(3, 2,t1,t2);
				del_arr(arr);			
			}
		}		
	}	
	void p9(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s9 =s9 - Conf_Info.p_num;
		// printf("s9 is %d\n",s9);	

		if(s9+cal_sum(q1,pt9)>0)
		{
		
			print_log3(0, 9,t1,t2,getQs(q1,pt9));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 9,t1,t2,getQs(q1,pt9));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s9+ cal_sum(q1,pt9);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 9,t1,t2,getQs(q1,pt9));	
				SimulatorTimer(gap);
				print_log3(1, 9,t1,t2,getQs(q1,pt9));
				
				++pt9;
				
				if(strncmp(getQs(q1,pt9),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 9,t1,t2,getQs(q1,pt9));	
					SimulatorTimer(gap);
					print_log3(1, 9,t1,t2,getQs(q1,pt9));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,9,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 9,t1,t2);
				del_arr(arr);			
			}
		}		
	}		
	void p8(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s8 =s8 - Conf_Info.p_num;
		// printf("s8 is %d\n",s8);	

		if(s8+cal_sum(q1,pt8)>0)
		{
		
			print_log3(0, 8,t1,t2,getQs(q1,pt8));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 8,t1,t2,getQs(q1,pt8));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s8+ cal_sum(q1,pt8);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 8,t1,t2,getQs(q1,pt8));	
				SimulatorTimer(gap);
				print_log3(1, 8,t1,t2,getQs(q1,pt8));
				
				++pt8;
				
				if(strncmp(getQs(q1,pt8),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 8,t1,t2,getQs(q1,pt8));	
					SimulatorTimer(gap);
					print_log3(1, 8,t1,t2,getQs(q1,pt8));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,8,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 8,t1,t2);
				del_arr(arr);			
			}
		}		
	}		
	
	void p7(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s7 =s7 - Conf_Info.p_num;
		//printf("s7 is %d\n",s7);	

		if(s7+cal_sum(q1,pt7)>0)
		{
		
			print_log3(0, 7,t1,t2,getQs(q1,pt7));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 7,t1,t2,getQs(q1,pt7));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s7+ cal_sum(q1,pt7);
			//printf("gap = %d\n",gap);

			print_log3(0, 7,t1,t2,getQs(q1,pt7));	
			SimulatorTimer(gap);
			print_log3(1, 7,t1,t2,getQs(q1,pt7));
				
			++pt7;
			if(gap>0)
			{
				if(strncmp(getQs(q1,pt7),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 7,t1,t2,getQs(q1,pt7));	
					SimulatorTimer(gap);
					print_log3(1, 7,t1,t2,getQs(q1,pt7));	
					if(s7+cal_sum(q1,pt7)<0)
					{
						print_log(3,7,t1,t2);
						del_arr(arr);
					}
					else
					{
						swap_arr(arr);
					}
				}
				
			}
			else
			{
				print_log(3, 2,t1,t2);
				del_arr(arr);			
			}
		}		
	}	
	void p6(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s6 =s6 - Conf_Info.p_num;
		// printf("s6 is %d\n",s6);	

		if(s6+cal_sum(q1,pt6)>0)
		{
		
			print_log3(0, 6,t1,t2,getQs(q1,pt6));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 6,t1,t2,getQs(q1,pt6));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s6+ cal_sum(q1,pt6);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 6,t1,t2,getQs(q1,pt6));	
				SimulatorTimer(gap);
				print_log3(1, 6,t1,t2,getQs(q1,pt6));
				
				++pt6;
				
				if(strncmp(getQs(q1,pt6),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 6,t1,t2,getQs(q1,pt6));	
					SimulatorTimer(gap);
					print_log3(1, 6,t1,t2,getQs(q1,pt6));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,6,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 6,t1,t2);
				del_arr(arr);			
			}
		}		
	}

	void p5(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s5 =s5 - Conf_Info.p_num;
		// printf("s5 is %d\n",s5);	

		if(s5+cal_sum(q1,pt5)>0)
		{
		
			print_log3(0, 5,t1,t2,getQs(q1,pt5));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 5,t1,t2,getQs(q1,pt5));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s5+ cal_sum(q1,pt5);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 5,t1,t2,getQs(q1,pt5));	
				SimulatorTimer(gap);
				print_log3(1, 5,t1,t2,getQs(q1,pt5));
				
				++pt5;
				
				if(strncmp(getQs(q1,pt5),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 5,t1,t2,getQs(q1,pt5));	
					SimulatorTimer(gap);
					print_log3(1, 5,t1,t2,getQs(q1,pt5));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,5,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 5,t1,t2);
				del_arr(arr);			
			}
		}		
	}		
	
	void p4(int t1,int t2,Queue *q1)
		{
			int gap = 0;
			s4 =s4 - Conf_Info.p_num;
			//printf("s4 is %d\n",s4);	

			if(s4+cal_sum(q1,pt4)>0)
			{
			
				print_log3(0, 4,t1,t2,getQs(q1,pt4));	
				SimulatorTimer(Conf_Info.p_num);
				tit = tit + Conf_Info.p_num;
				
				print_log3(1, 4,t1,t2,getQs(q1,pt4));	
				swap_arr(arr);		
			}
			else 
			{
				gap = Conf_Info.p_num + s4+ cal_sum(q1,pt4);
				//printf("gap = %d\n",gap);

				print_log3(0, 4,t1,t2,getQs(q1,pt4));	
				SimulatorTimer(gap);
				print_log3(1, 4,t1,t2,getQs(q1,pt4));
					
				++pt4;
				if(gap>0)
				{
					if(strncmp(getQs(q1,pt4),"A",1)!= 0)
					{
						gap = Conf_Info.p_num -gap;
						// printf("gap = %d\n",gap);			
						print_log3(0, 4,t1,t2,getQs(q1,pt4));	
						SimulatorTimer(gap);
						print_log3(1, 4,t1,t2,getQs(q1,pt4));	
						if(s4+cal_sum(q1,pt4)<0)
						{
							print_log(3,4,t1,t2);
							del_arr(arr);
						}
						else
						{
							swap_arr(arr);
						}
					}
					
				}
				else
				{
					print_log(3, 2,t1,t2);
					del_arr(arr);			
				}
			}		
		}	
	void p3(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s3 =s3 - Conf_Info.p_num;
		// printf("s3 is %d\n",s3);	

		if(s3+cal_sum(q1,pt3)>0)
		{
		
			print_log3(0, 3,t1,t2,getQs(q1,pt3));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 3,t1,t2,getQs(q1,pt3));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s3+ cal_sum(q1,pt3);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 3,t1,t2,getQs(q1,pt3));	
				SimulatorTimer(gap);
				print_log3(1, 3,t1,t2,getQs(q1,pt3));
				
				++pt3;
				
				if(strncmp(getQs(q1,pt3),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 3,t1,t2,getQs(q1,pt3));	
					SimulatorTimer(gap);
					print_log3(1, 3,t1,t2,getQs(q1,pt3));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,3,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 3,t1,t2);
				del_arr(arr);			
			}
		}		
	}		
	void p2(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s2 =s2 - Conf_Info.p_num;
		// printf("s2 is %d\n",s2);	

		if(s2+cal_sum(q1,pt2)>0)
		{
		
			print_log3(0, 2,t1,t2,getQs(q1,pt2));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 2,t1,t2,getQs(q1,pt2));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s2+ cal_sum(q1,pt2);
			// printf("gap = %d\n",gap);
			if(gap>0)
			{
				print_log3(0, 2,t1,t2,getQs(q1,pt2));	
				SimulatorTimer(gap);
				print_log3(1, 2,t1,t2,getQs(q1,pt2));
				
				++pt2;
				
				if(strncmp(getQs(q1,pt2),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 2,t1,t2,getQs(q1,pt2));	
					SimulatorTimer(gap);
					print_log3(1, 2,t1,t2,getQs(q1,pt2));	
					swap_arr(arr);
				}
				else
				{
					print_log(3,2,t1,t2);
					del_arr(arr);
				}	
			}
			else
			{
				print_log(3, 2,t1,t2);
				del_arr(arr);			
			}
		}		
	}		
	void p1(int t1,int t2,Queue *q1)
	{
		int gap = 0;
		s1 =s1 - Conf_Info.p_num;
		//printf("s1 is %d\n",s1);	

		if(s1+cal_sum(q1,pt1)>0)
		{
		
			print_log3(0, 1,t1,t2,getQs(q1,pt1));	
			SimulatorTimer(Conf_Info.p_num);
			tit = tit + Conf_Info.p_num;
			
			print_log3(1, 1,t1,t2,getQs(q1,pt1));	
			swap_arr(arr);		
		}
		else 
		{
			gap = Conf_Info.p_num + s1+ cal_sum(q1,pt1);
			//printf("gap = %d\n",gap);

			print_log3(0, 1,t1,t2,getQs(q1,pt1));	
			SimulatorTimer(gap);
			print_log3(1, 1,t1,t2,getQs(q1,pt1));
				
			++pt1;
			if(gap>0)
			{
				if(strncmp(getQs(q1,pt1),"A",1)!= 0)
				{
					gap = Conf_Info.p_num -gap;
					// printf("gap = %d\n",gap);			
					print_log3(0, 1,t1,t2,getQs(q1,pt1));	
					SimulatorTimer(gap);
					print_log3(1, 1,t1,t2,getQs(q1,pt1));	
					if(s1+cal_sum(q1,pt1)<0)
					{
						print_log(3,1,t1,t2);
						del_arr(arr);
					}
					else
					{
						swap_arr(arr);
					}
				}
				
			}
			else
			{
				print_log(3, 2,t1,t2);
				del_arr(arr);			
			}
		}		
	}	
/**
* @brief pthread Function to process RR scheduling in 5 times reading in running part
*/	
	void* printC(void* param)
	{
		// Queue *q6 = CreateQueue();
		int i =0;
		int j =0;
		int gap = 0;
		int size = 0;
		DATA* data = (DATA*)param;
		float time_use=0;

		//pointing to which command
		clock_t   total_t;
		struct timeval end;//struct timezone tz; //

		for(i = 0;i<5;i++)
		{

			sem_wait(&sig2);
		

			// printf("Now i = %d\n",i);
			if(i==0)
			{
				// printf("The number of arr is %d\n",count_num(arr));
				// printf("Next to run is %d\n",get_arr(arr));
				while(tit<100)
				{
					if(get_arr(arr)==1)
					{
						if(cal_sjf((data->add1),s1,data->ss1)>=Conf_Info.p_num)
						{
							data->opt_num = 1;
							s1 = s1 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, 1,data->it1,data->it2,getQs(data->add1,pt1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, 1,data->it1,data->it2,getQs(data->add1,pt1));	
							swap_arr(arr);							
						}

					}
					
					else if(get_arr(arr)==2)
					{
						if(cal_sjf((data->add2),s2,data->ss2)>=Conf_Info.p_num)
						{
							data->opt_num = 2;
							s2 = s2 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add2,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add2,1));	
							swap_arr(arr);					
						}

					}
					
					else if(get_arr(arr)==3)
					{
						if(cal_sjf((data->add3),s3,data->ss3)>=Conf_Info.p_num)
						{
							data->opt_num = 3;
							s3 = s3 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add3,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add3,1));	
							swap_arr(arr);					
						}

					}				
				}
		
			}
			else if(i==1)
			{
				// printf("The number of arr is %d\n",count_num(arr));
				// printf("Next to run is %d\n",get_arr(arr));
				while(tit<200)
				{
					if(get_arr(arr)==1)
					{
						if(cal_sjf((data->add1),s1,data->ss1)>=Conf_Info.p_num)
						{
							data->opt_num = 1;
							s1 = s1 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add1,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add1,1));	
							swap_arr(arr);	
							
						}

					}
					
					else if(get_arr(arr)==2)
					{
						if(cal_sjf((data->add2),s2,data->ss2)>=Conf_Info.p_num)
						{
							data->opt_num = 2;
							s2 = s2 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add2,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add2,1));	
							swap_arr(arr);					
						}

					}
					
					else if(get_arr(arr)==3)
					{
						if(cal_sjf((data->add3),s3,data->ss3)>=Conf_Info.p_num)
						{
							data->opt_num = 3;
							s3 = s3 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add3,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add3,1));	
							swap_arr(arr);					
						}
					}	
					else if(get_arr(arr)==4)
					{
						if(cal_sjf((data->add4),s4,data->ss4)>=Conf_Info.p_num)
						{
							data->opt_num = 4;
							s4 = s4 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add4,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add4,1));	
							swap_arr(arr);					
						}

					}
					
					else if(get_arr(arr)==5)
					{
						if(cal_sjf((data->add5),s5,data->ss5)>=Conf_Info.p_num)
						{
							data->opt_num = 5;
							s5 = s5 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add5,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add5,1));	
							swap_arr(arr);					
						}
					}	

					else if(get_arr(arr)==6)
					{
						if(cal_sjf((data->add6),s6,data->ss6)>=Conf_Info.p_num)
						{
							data->opt_num = 6;
							s6 = s6 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add6,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add6,1));	
							swap_arr(arr);					
						}
					}
					
				}				
			
			}
			else if(i==2)
			{
				
				// printf("The number of arr is %d\n",count_num(arr));
				// printf("Next to run is %d\n",get_arr(arr));
				while(tit<300)
				{
					if(get_arr(arr)==1)
					{
						if(cal_sjf((data->add1),s1,data->ss1)>=Conf_Info.p_num)
						{
							data->opt_num = 1;
							s1 = s1 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add1,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add1,1));	
							swap_arr(arr);	
							
						}

					}
					
					else if(get_arr(arr)==2)
					{
						if(cal_sjf((data->add2),s2,data->ss2)>=Conf_Info.p_num)
						{
							data->opt_num = 2;
							s2 = s2 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add2,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add2,1));	
							swap_arr(arr);					
						}

					}
					
					else if(get_arr(arr)==3)
					{
						if(cal_sjf((data->add3),s3,data->ss3)>=Conf_Info.p_num)
						{
							data->opt_num = 3;
							s3 = s3 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add3,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add3,1));	
							swap_arr(arr);					
						}
					}	
					else if(get_arr(arr)==4)
					{
						if(cal_sjf((data->add4),s4,data->ss4)>=Conf_Info.p_num)
						{
							data->opt_num = 4;
							s4 = s4 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add4,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add4,1));	
							swap_arr(arr);					
						}

					}
					
					else if(get_arr(arr)==5)
					{
						if(cal_sjf((data->add5),s5,data->ss5)>=Conf_Info.p_num)
						{
							data->opt_num = 5;
							s5 = s5 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add5,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add5,1));	
							swap_arr(arr);					
						}
					}	

					else if(get_arr(arr)==6)
					{
						if(cal_sjf((data->add6),s6,data->ss6)>=Conf_Info.p_num)
						{
							data->opt_num = 6;
							s6 = s6 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add6,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add6,1));	
							swap_arr(arr);					
						}
					}
					else if(get_arr(arr)==7)
					{
						if(cal_sjf((data->add7),s7,data->ss7)>=Conf_Info.p_num)
						{
							data->opt_num = 7;
							s7 = s7 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add7,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add7,1));	
							swap_arr(arr);					
						}
					}

					else if(get_arr(arr)==8)
					{
						if(cal_sjf((data->add8),s8,data->ss8)>=Conf_Info.p_num)
						{
							data->opt_num = 8;
							s8 = s8 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add8,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add8,1));	
							swap_arr(arr);					
						}
					}

					else if(get_arr(arr)==9)
					{
						if(cal_sjf((data->add6),s6,data->ss6)>=Conf_Info.p_num)
						{
							data->opt_num = 9;
							s9 = s9 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add9,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add9,1));	
							swap_arr(arr);					
						}
					}				
				}				
							
			}
			
			else if(i==3)
			{
				
				// printf("The number of arr is %d\n",count_num(arr));
				// printf("Next to run is %d\n",get_arr(arr));
				while(tit<400)
				{
					if(get_arr(arr)==1)
					{
						if(cal_sjf((data->add1),s1,data->ss1)>=Conf_Info.p_num)
						{
							data->opt_num = 1;
							s1 = s1 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, 1,data->it1,data->it2,getQs(data->add1,pt1));	
							// print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add1,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, 1,data->it1,data->it2,getQs(data->add1,pt1));	
							// print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add1,1));	
							swap_arr(arr);	
							
						}

					}
					
					else if(get_arr(arr)==2)
					{
						if(cal_sjf((data->add2),s2,data->ss2)>=Conf_Info.p_num)
						{
							data->opt_num = 2;
							s2 = s2 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add2,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add2,1));	
							swap_arr(arr);					
						}

					}
					
					else if(get_arr(arr)==3)
					{
						if(cal_sjf((data->add3),s3,data->ss3)>=Conf_Info.p_num)
						{
							data->opt_num = 3;
							s3 = s3 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add3,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add3,1));	
							swap_arr(arr);					
						}
					}	
					else if(get_arr(arr)==4)
					{
						if(cal_sjf((data->add4),s4,data->ss4)>=Conf_Info.p_num)
						{
							data->opt_num = 4;
							s4 = s4 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add4,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add4,1));	
							swap_arr(arr);					
						}

					}
					
					else if(get_arr(arr)==5)
					{
						if(cal_sjf((data->add5),s5,data->ss5)>=Conf_Info.p_num)
						{
							data->opt_num = 5;
							s5 = s5 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add5,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add5,1));	
							swap_arr(arr);					
						}
					}	

					else if(get_arr(arr)==6)
					{
						if(cal_sjf((data->add6),s6,data->ss6)>=Conf_Info.p_num)
						{
							data->opt_num = 6;
							s6 = s6 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add6,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add6,1));	
							swap_arr(arr);					
						}
					}
					else if(get_arr(arr)==7)
					{
						if(cal_sjf((data->add7),s7,data->ss7)>=Conf_Info.p_num)
						{
							data->opt_num = 7;
							s7 = s7 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add7,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add7,1));	
							swap_arr(arr);					
						}
					}

					else if(get_arr(arr)==8)
					{
						if(cal_sjf((data->add8),s8,data->ss8)>=Conf_Info.p_num)
						{
							data->opt_num = 8;
							s8 = s8 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add8,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add8,1));	
							swap_arr(arr);					
						}
					}

					else if(get_arr(arr)==9)
					{
						if(cal_sjf((data->add6),s6,data->ss6)>=Conf_Info.p_num)
						{
							data->opt_num = 9;
							s9 = s9 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add9,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add9,1));	
							swap_arr(arr);					
						}
					}

					else if(get_arr(arr)==10)
					{
						if(cal_sjf((data->add10),s10,data->ss10)>=Conf_Info.p_num)
						{
							data->opt_num = 10;
							s10 = s10 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add10,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add10,1));	
							swap_arr(arr);					
						}
					}

					else if(get_arr(arr)==11)
					{
						if(cal_sjf((data->add11),s11,data->ss11)>=Conf_Info.p_num)
						{
							data->opt_num = 11;
							s11 = s11 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add11,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add11,1));	
							swap_arr(arr);					
						}
					}

					else if(get_arr(arr)==12)
					{
						if(cal_sjf((data->add12),s12,data->ss12)>=Conf_Info.p_num)
						{
							data->opt_num = 12;
							s12 = s12 - Conf_Info.p_num;
							tit = tit + Conf_Info.p_num;
							print_log3(0, data->opt_num,data->it1,data->it2,getQs(data->add12,1));	
							SimulatorTimer(Conf_Info.p_num);
							print_log3(1, data->opt_num,data->it1,data->it2,getQs(data->add12,1));	
							swap_arr(arr);					
						}
					}
					
				}
			}
			else if(i==4)
			{
				// printf("The number of arr is %d\n",count_num(arr));
				// dis_arr(arr);
				// printf("Next to run is %d\n",get_arr(arr));				
			}
			

			sem_post(&sig1); 

		}
		return (void*)"";
	}

/**
* @brief pthread Function to process RR scheduling in 5 times reading in reading part
*/	
	void* printD(void* param)
	{
		int i =0;
		DATA* data = (DATA*)param;
			Queue *q1 = CreateQueue();
			Queue *q2 = CreateQueue();
			Queue *q3 = CreateQueue();
			
			Queue *q4 = CreateQueue();		
			Queue *q5 = CreateQueue();
			Queue *q6 = CreateQueue();
			
			Queue *q7 = CreateQueue();
			Queue *q8 = CreateQueue();
			Queue *q9 = CreateQueue();		
			
			Queue *q10 = CreateQueue();
			Queue *q11 = CreateQueue();
			Queue *q12 = CreateQueue();
			
			Queue *q13 = CreateQueue();
			Queue *q14 = CreateQueue();		
			Queue *q15 = CreateQueue();
			
		
		readmeta(data->fmeta,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12,q13,q14,q15);
		for(i = 0;i<5;i++)
		{
			sem_wait(&sig1);
			
			float time_use=0;

			clock_t   total_t;
			struct timeval end;//struct timezone tz; //

			
			
			if( i ==0)
			{
			
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Simulator program starting\n",(total_t*0.1*10)/CLOCKS_PER_SEC);

				
				data->add1 = q1;
				data->add2 = q2;
				data->add3 = q3;
				data->ss1 = 4;
				data->ss2 = 3;
				data->ss3 = 6;
				add_arr(arr,1);
				add_arr(arr,2);
				add_arr(arr,3);
			}
			
			if( i ==1)
			{
				// readmeta(data->fmeta,q4,q5,q6);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
				
				
				data->add4 = q4;
				data->add5 = q5;
				data->add6 = q6;
				
				data->ss4 = 4;
				data->ss5 = 3;
				data->ss6 = 6;	
				
				add_arr(arr,4);
				add_arr(arr,5);
				add_arr(arr,6);			
			}

			if( i ==2)
			{
				// readmeta(data->fmeta,q7,q8,q9);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
				
				data->add7 = q7;
				data->add8 = q8;
				data->add9 = q9;
				
				data->ss7 = 4;
				data->ss8 = 3;
				data->ss9 = 6;
				
				add_arr(arr,7);
				add_arr(arr,8);
				add_arr(arr,9);				
				
			}

			if( i ==3)
			{
				// readmeta(data->fmeta,q10,q11,q12);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);			
				data->add10 = q10;
				data->add11 = q11;
				data->add12 = q12;
				
				data->ss10 = 4;
				data->ss11 = 3;
				data->ss12 = 6;
				
				add_arr(arr,10);
				add_arr(arr,11);
				add_arr(arr,12);	
			}

			if( i ==4)
			{
				// readmeta(data->fmeta,q13,q14,q15);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);			

				data->add13 = q13;
				data->add14 = q14;
				data->add15 = q15;
				
				data->ss13 = 4;
				data->ss14 = 3;
				data->ss15 = 6;	
				
				add_arr(arr,13);
				add_arr(arr,14);
				add_arr(arr,15);				
			}		

			sem_post(&sig2); 
		}
		return (void*)"";
	}


	int cal_sum(Queue *q1,int num)
	{
		int sum =0;
		for(int i=1;i<=num;i++)
			sum += getQv(q1,i);
		return sum;
	}
	
/**
* @brief Function the main part for simulation
*
* @pre char *fconf means input conf file,char *fmeta means input meta file
*
* @post it simulate the OS operation and get the start and end time for each process or thread
*
* it will frist check the configure file and meta file and get the schedule code for RR or SJF simulation
*
* @return 0 means there is some error in keywords of conf or meta files.
*
*/	
	int SimulatorTest(char *fconf,char *fmeta)
    {
		int i =0;

		if(printConf(fconf))
		{
			
		}
		else return 0;

		if(checkmeta(fmeta))
		{
			
		}
		else return 0;	
		clock_t   total_t;
		float time_use=0;
		struct timeval start;
		struct timeval end;//struct timezone tz;
		gettimeofday(&start,NULL); //gettimeofday(&start,&tz);
		

		pthread_t thread_A;
		pthread_t thread_B;

		
		sem_init(&sig1,0,1);
		sem_init(&sig2,0,0);

		DATA data = {0};
		gettimeofday(&end,NULL);

		data.it1 = start.tv_sec;
		data.it2 = start.tv_usec;
		data.fmeta = fmeta;
		
		if(Conf_Info.scheducode==3)
		{
			pthread_create(&thread_A,NULL,printC,&data);
			pthread_create(&thread_B,NULL,printD,&data);


			
			pthread_join(thread_A,NULL);
			pthread_join(thread_B,NULL);

			// printf("%d  %d\n", data.t1, data.t2); 

			sem_destroy(&sig1);
			sem_destroy(&sig2);
			// printf("finish pthread\n");

		
			while(get_arr(arr)!=0)
			{	

				if(get_arr(arr) == 1)
				{
					p1(data.it1,data.it2,data.add1);
				}			
				else if(get_arr(arr) == 2)
				{
					p2(data.it1,data.it2,data.add2);
				}
				else if(get_arr(arr) == 3)
				{
					p3(data.it1,data.it2,data.add3);
				}
				else if(get_arr(arr) == 4)
				{
					p4(data.it1,data.it2,data.add4);
				}			
				else if(get_arr(arr) == 5)
				{
					p5(data.it1,data.it2,data.add5);
				}
				else if(get_arr(arr) == 6)
				{
					p6(data.it1,data.it2,data.add6);
				}
				else if(get_arr(arr) == 7)
				{
					p7(data.it1,data.it2,data.add7);
				}			
				else if(get_arr(arr) == 8)
				{
					p8(data.it1,data.it2,data.add8);
				}
				else if(get_arr(arr) == 9)
				{
					p9(data.it1,data.it2,data.add9);
				}
				else if(get_arr(arr) == 10)
				{
					p10(data.it1,data.it2,data.add10);
				}	
				else if(get_arr(arr) == 11)
				{
					p11(data.it1,data.it2,data.add11);
				}
				else if(get_arr(arr) == 12)
				{
					p12(data.it1,data.it2,data.add12);
				}			
				else if(get_arr(arr) == 13)
				{
					p13(data.it1,data.it2,data.add13);
				}
				else if(get_arr(arr) == 14)
				{
					p14(data.it1,data.it2,data.add14);
				}
				else if(get_arr(arr) == 15)
				{
					p15(data.it1,data.it2,data.add15);
				}
			}
			// printf("Num of arr is %d\n",count_num(arr));
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data.it1))*1000000+(end.tv_usec - (data.it2));
			total_t = time_use;
			printf("%.3f - Simulator program ending\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
		}
		

			
		else if(Conf_Info.scheducode == 0 )
		{
			pthread_create(&thread_A,NULL,printA,&data);
			pthread_create(&thread_B,NULL,printB,&data);


			
			pthread_join(thread_A,NULL);
			pthread_join(thread_B,NULL);

			// printf("%d  %d\n", data.t1, data.t2); 

			sem_destroy(&sig1);
			sem_destroy(&sig2);
			// printf("finish pthread\n");

			
			int	size =15;
			int arr1[size];
			arr1[0] = cal_sjf((data.add1),s1,data.ss1);
			arr1[1] = cal_sjf((data.add2),s2,data.ss2);
			arr1[2] = cal_sjf((data.add3),s3,data.ss3);
			arr1[3] = cal_sjf((data.add4),s4,data.ss4);
			arr1[4] = cal_sjf((data.add5),s5,data.ss5);
			arr1[5] = cal_sjf((data.add6),s6,data.ss6);			
			arr1[6] = cal_sjf((data.add7),s7,data.ss7);
			arr1[7] = cal_sjf((data.add8),s8,data.ss8);
			arr1[8] = cal_sjf((data.add9),s9,data.ss9);	
			arr1[9] = cal_sjf((data.add10),s10,data.ss10);
			arr1[10] = cal_sjf((data.add11),s11,data.ss11);
			arr1[11] = cal_sjf((data.add12),s12,data.ss12);			
			arr1[12] = cal_sjf((data.add13),s13,data.ss13);
			arr1[13] = cal_sjf((data.add14),s14,data.ss14);
			arr1[14] = cal_sjf((data.add15),s15,data.ss15);		
			int j =0;

		
			while(min2(arr1)!=-1)
			{

				if(min2(arr1)==1)
				{
					process_q(data.add2,s2,data.ss2,data.it1,data.it2,2);
					arr1[1] = 0;
				}
				else if(min2(arr1)==2)
				{
					process_q(data.add3,s3,data.ss3,data.it1,data.it2,3);
					arr1[2] = 0;	
				}
				
				else if(min2(arr1)==3)
				{
					process_q(data.add4,s4,data.ss4,data.it1,data.it2,4);
					arr1[3] = 0;	
				}
				
				else if(min2(arr1)==4)
				{
					process_q(data.add5,s5,data.ss5,data.it1,data.it2,5);
					arr1[4] = 0;	
				}		
				else if(min2(arr1)==5)
				{
					process_q(data.add6,s6,data.ss6,data.it1,data.it2,6);
					arr1[5] = 0;	
				}
				
				else if(min2(arr1)==6)
				{
					process_q(data.add7,s7,data.ss7,data.it1,data.it2,7);
					arr1[6] = 0;	
				}
				
				else if(min2(arr1)==7)
				{
					process_q(data.add8,s8,data.ss8,data.it1,data.it2,8);
					arr1[7] = 0;	
				}				
				else if(min2(arr1)==8)
				{
					process_q(data.add9,s9,data.ss9,data.it1,data.it2,9);
					arr1[8] = 0;	
				}
				
				else if(min2(arr1)==9)
				{
					process_q(data.add10,s10,data.ss10,data.it1,data.it2,10);
					arr1[9] = 0;	
				}
				
				else if(min2(arr1)==10)
				{
					process_q(data.add11,s11,data.ss11,data.it1,data.it2,11);
					arr1[10] = 0;	
				}		
				else if(min2(arr1)==11)
				{
					process_q(data.add12,s12,data.ss12,data.it1,data.it2,12);
					arr1[11] = 0;	
				}
				
				else if(min2(arr1)==12)
				{
					process_q(data.add13,s13,data.ss13,data.it1,data.it2,13);
					arr1[12] = 0;	
				}
				
				else if(min2(arr1)==13)
				{
					process_q(data.add14,s14,data.ss14,data.it1,data.it2,14);
					arr1[13] = 0;	
				}	
				else if(min2(arr1)==14)
				{
					process_q(data.add15,s15,data.ss15,data.it1,data.it2,15);
					arr1[14] = 0;	
				}
				
				else if(min2(arr1)==0)
				{
					process_q(data.add1,s1,data.ss1,data.it1,data.it2,1);
					arr1[0] = 0;	
				}	
			}		
		
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data.it1))*1000000+(end.tv_usec - (data.it2));
			total_t = time_use;
			// printf("%.3f - Process %d: end %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num,getQs(q,i));
			printf("%.3f - Simulator program ending\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
		}
		else
		{
			printf("Sorry please check! Only support SJF and RR schedule.\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
			return 0;
		}

	}
 /**
* @brief Function to check 
*
* @pre char *fconf means input conf file,char *fmeta means input meta file
*
* @return 0 means there is some suffix error for conf or meta files.
*
*/
    int checksuffix(char *fconf,char *suffix,int num)
    {
       char drive[255];
       char dir[255];
       char fname[255];
       char ext[10];
        splitpath( fconf, drive, dir, fname, ext );
    //    printf( "  Ext: %s\n", ext );
        if(!strncmp(ext,suffix,num))   return 1;
        else return 0;

    }

/**
* @brief Function to split the file name and get the suffix 
*/

    void splitpath(const char *path, char *drive, char *dir, char *fname, char *ext)
    {
        char *p_whole_name;

        drive[0] = '\0';
        if (NULL == path)
        {
            dir[0] = '\0';
            fname[0] = '\0';
            ext[0] = '\0';
            return;
        }

        if ('/' == path[strlen(path)])
        {
            strcpy(dir, path);
            fname[0] = '\0';
            ext[0] = '\0';
            return;
        }

        p_whole_name = rindex(path, '/');
        if (NULL != p_whole_name)
        {
            p_whole_name++;
            _split_whole_name(p_whole_name, fname, ext);

            snprintf(dir, p_whole_name - path, "%s", path);
        }
        else
        {
            _split_whole_name(path, fname, ext);
            dir[0] = '\0';
        }
    }

    static void _split_whole_name(const char *whole_name, char *fname, char *ext)
    {
        char *p_ext;

        p_ext = rindex(whole_name, '.');
        if (NULL != p_ext)
        {
            strcpy(ext, p_ext);
            snprintf(fname, p_ext - whole_name + 1, "%s", whole_name);
        }
        else
        {
            ext[0] = '\0';
            strcpy(fname, whole_name);
        }
    }
