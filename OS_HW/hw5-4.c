
/*
 to  compile:
 gcc -pthread main.c
 
 finish readmeta to Queue
 to do for 15 queue sjf
 and RR
*/

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
// static sem_t s3;
// static sem_t s4;
// static sem_t s5;


#define waittime 96
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

int s1 = 0;
int s2 = 0;	
int s3 = 0;
int s4 = 0;		
int s5 = 0;
int vitual_flag = 0;
int counter =0;

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

	int 	ss1;
	int		ss2;
	int 	ss3;
	int		ss4;
	int 	ss5;
	
	int		pt1;
	int 	pt2;
	int		pt3;
	int		pt4;
	int 	pt5;
	
	long    add1;
	long 	add2;
	long    add3;
	long 	add4;	
	long    add5;

	int 	opt_num;
	long    t1; //store start time for a I/O operation 
	long    t2; //store end time for a I/O operation 
	long    it1;//pass inital time in sec 
	long    it2;//pass inital time in usec 		
	// char    *word2;
}DATA;
    typedef struct {
        ElementType1 data[MAXSIZE];
        ElementType2 *name[MAXSIZE];
		ElementType3 data2[MAXSIZE];
        int front; // start of Q
        int rear; // end of Q
        int size; //number of element
    }Queue;

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

	void disp_q(Queue* q,int s1,int ss,int pt);
	void process_q(Queue* q,int s1,int ss,int pt,long t1,long t2,int proc_num);
	char *MyStrCpy(char *dest,const char *scr);
    char *remove_space(char *str2, const char *str1);
	
	void readmeta(char *fileName,Queue *q1,Queue *q2,Queue *q3);
	int * checkmeta(char *fileName);
	int *getconf(char *fileName );
	int printConf(char *fname);	

	int delete_sub_str(const char *str, const char *sub_str, char *result_str);
	void SplitStrByStr( char* sources, char str, char arry[10][20], int* count);
	
	int SimulatorTest(char *fconf,char *fmeta)
    {

		Queue *q1 = CreateQueue();
		Queue *q2 = CreateQueue();
		Queue *q3 = CreateQueue();
		if(printConf(fconf))
		{
		}
		else return 0;

		if(checkmeta(fmeta))
		readmeta(fmeta,q1,q2,q3);
		
	}
	
int main()
{
	char *fconf = "config_1.conf";
	char *fmeta = "test_1a.mdf";
	SimulatorTest(fconf,fmeta);
	
	/*
	clock_t   total_t;
	float time_use=0;
	struct timeval start;
	struct timeval end;//struct timezone tz;
	gettimeofday(&start,NULL); //gettimeofday(&start,&tz);
	

    pthread_t thread_A;
    pthread_t thread_B;
    // pthread_t thread_C;
	// pthread_t thread_D;
	// pthread_t thread_E;
	
    sem_init(&sig1,0,1);
    sem_init(&sig2,0,0);
    // sem_init(&s3,0,0);
    // sem_init(&s4,0,0);	
    // sem_init(&s5,0,1);
	
	DATA data = {0};
	gettimeofday(&end,NULL);
	// gettimeofday(&end,NULL);
	data.it1 = start.tv_sec;
	data.it2 = start.tv_usec;

	
    pthread_create(&thread_A,NULL,printA,&data);
    pthread_create(&thread_B,NULL,printB,&data);
    // pthread_create(&thread_C,NULL,printC,&data);
    // pthread_create(&thread_D,NULL,printD,&data);
    // pthread_create(&thread_E,NULL,printE,&data);

	
    pthread_join(thread_A,NULL);
    pthread_join(thread_B,NULL);
    // pthread_join(thread_C,NULL);
    // pthread_join(thread_D,NULL);
    // pthread_join(thread_E,NULL);
	// printf("%d  %d\n", data.t1, data.t2); 

    sem_destroy(&sig1);
    sem_destroy(&sig2);

	
    // printf("\n");
    // printf("finish pthread\n");
	
	int arr[5];
	arr[0] = cal_sjf((data.add1),s1,data.ss1);
	arr[1] = cal_sjf((data.add2),s2,data.ss2);
	arr[2] = cal_sjf((data.add3),s3,data.ss3);
	arr[3] = cal_sjf((data.add4),s4,data.ss4);
	arr[4] = cal_sjf((data.add5),s5,data.ss5);
	if(vitual_flag)
	{
		printf("\t1st value = %d\n", cal_sjf((data.add1),s1,data.ss1));
		printf("\t2nd value = %d\n", cal_sjf((data.add2),s2,data.ss2));
		printf("\t3rd value = %d\n", cal_sjf((data.add3),s3,data.ss3));
		printf("\t4th value = %d\n", cal_sjf((data.add4),s4,data.ss4));
		printf("\t5th value = %d\n", cal_sjf((data.add5),s5,data.ss5));
	}
	while(min2(arr)!=-1)
	{
		if (min2(arr)==0)
		{
			process_q((data.add1),s1,data.ss1,data.pt1,data.it1,data.it2,1);
			s1 = s1 - arr[0];
			arr[0] = cal_sjf((data.add1),s1,data.ss1);
			arr[1] = cal_sjf((data.add2),s2,data.ss2);
			arr[2] = cal_sjf((data.add3),s3,data.ss3);
			arr[3] = cal_sjf((data.add4),s4,data.ss4);
			arr[4] = cal_sjf((data.add5),s5,data.ss5);
			
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data.it1))*1000000+(end.tv_usec - (data.it2));
			total_t = time_use;
			printf("%.3f - OS: process %d completed\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1);		
		}
		else if(min2(arr)==1)
		{
			process_q((data.add2),s2,data.ss2,data.pt2,data.it1,data.it2,2);
			
			s2 = s2 - arr[1];
			arr[0] = cal_sjf((data.add1),s1,data.ss1);
			arr[1] = cal_sjf((data.add2),s2,data.ss2);
			arr[2] = cal_sjf((data.add3),s3,data.ss3);
			arr[3] = cal_sjf((data.add4),s4,data.ss4);
			arr[4] = cal_sjf((data.add5),s5,data.ss5);			
			
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data.it1))*1000000+(end.tv_usec - (data.it2));
			total_t = time_use;
			printf("%.3f - OS: process %d completed\n",(total_t*0.1*10)/CLOCKS_PER_SEC,2);				
		}

		else if(min2(arr)==2)
		{
			process_q((data.add3),s3,data.ss3,data.pt3,data.it1,data.it2,3);
			s3 = s3 - arr[2];
			arr[0] = cal_sjf((data.add1),s1,data.ss1);
			arr[1] = cal_sjf((data.add2),s2,data.ss2);
			arr[2] = cal_sjf((data.add3),s3,data.ss3);
			arr[3] = cal_sjf((data.add4),s4,data.ss4);
			arr[4] = cal_sjf((data.add5),s5,data.ss5);			
			
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data.it1))*1000000+(end.tv_usec - (data.it2));
			total_t = time_use;
			printf("%.3f - OS: process %d completed\n",(total_t*0.1*10)/CLOCKS_PER_SEC,3);				
		}
		else if(min2(arr)==3)
		{
			process_q((data.add4),s4,data.ss4,data.pt4,data.it1,data.it2,4);
			s4 = s4 - arr[3];
			arr[0] = cal_sjf((data.add1),s1,data.ss1);
			arr[1] = cal_sjf((data.add2),s2,data.ss2);
			arr[2] = cal_sjf((data.add3),s3,data.ss3);
			arr[3] = cal_sjf((data.add4),s4,data.ss4);
			arr[4] = cal_sjf((data.add5),s5,data.ss5);			
			
			
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data.it1))*1000000+(end.tv_usec - (data.it2));
			total_t = time_use;
			printf("%.3f - OS: process %d completed\n",(total_t*0.1*10)/CLOCKS_PER_SEC,4);				
		}
		else if(min2(arr)==4)
		{
			process_q((data.add5),s5,data.ss5,data.pt5,data.it1,data.it2,5);
		
			s5 = s5 - arr[4];
			arr[0] = cal_sjf((data.add1),s1,data.ss1);
			arr[1] = cal_sjf((data.add2),s2,data.ss2);
			arr[2] = cal_sjf((data.add3),s3,data.ss3);
			arr[3] = cal_sjf((data.add4),s4,data.ss4);
			arr[4] = cal_sjf((data.add5),s5,data.ss5);			
			
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data.it1))*1000000+(end.tv_usec - (data.it2));
			total_t = time_use;
			printf("%.3f - OS: process %d completed\n",(total_t*0.1*10)/CLOCKS_PER_SEC,5);				
		}
	}
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data.it1))*1000000+(end.tv_usec - (data.it2));
	total_t = time_use;	
	printf("%.3f - Simulator program ending\n");
*/
    return 0;

}




void SimulatorTimer(int waitTime)//this is a ms unit wait
{

	usleep(1000*waitTime);
}





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

int min2(int arr[])
{
	int result = 0;
	int ind = 0;
	int i = 0;

	if(arr[0]==0 & arr[1]==0 & arr[2]==0& arr[3]==0 & arr[4]==0)  return -1;

	for (i =0;i< 5;i++)
	{

		if(arr[i]>0)
		{
			result = arr[i];
			ind = i;
			break;
		}

//            printf("arr[%d] = %d\n",i,arr[i]);
	}

	for ( i =0;i< 5;i++)
	{
		if(result>arr[i] & arr[i]>0)
		{
			result = arr[i];
			ind = i;
		}
	}
	return ind;
}

	void disp_q(Queue* q,int s1,int ss,int pt)
	{
		int i =0;
		printf("\tpt = %d\n",pt);
		printf("\ts1 = %d\n",s1);
		for(i = pt ;i<ss;i++)
		{
			{	
				printf("\tIn process %d, time is %d, oper is %s\n",i,getQv(q,i),getQs(q,i));
			}
		}
	}
	
	void process_q(Queue* q,int s1,int ss,int pt,long t1,long t2,int proc_num)
	{
		int i =0;
		// printf("pt = %d\n",pt);
		// printf("s1 = %d\n",s1);
		clock_t   total_t;
		float time_use=0;
		struct timeval start;
		struct timeval end;//struct timezone tz;
		
		for(i = pt ;i<ss;i++)
		{
			{	
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;
				if(counter!=0)
				{
					printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num,getQs(q,i));
				}
				SimulatorTimer(s1+getQv(q,i));
				s1 = s1 - getQv(q,i);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (t1))*1000000+(end.tv_usec - (t2));
				total_t = time_use;			
				printf("%.3f - Process %d: end processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc_num,getQs(q,i));
			}
		}
		++counter;
	}
	

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
	

void readmeta(char *fileName,Queue *q1,Queue *q2,Queue *q3)
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
			
			printf("p = %d\n",p);
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
	    printf("res = %s\n", res);
		remove_space(name,res);
		// strcpy(name,res);
		
		int line =0;
		char* pStr  = name;
		char tmpChar = '}';
		
		char arry[100][20];
		char arry2[100][20];
		SplitStrByStr(pStr, tmpChar, arry, &line);
		printf("line = %d\n", line);
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




		// Queue *q1 = CreateQueue();
		// Queue *q2 = CreateQueue();
		// Queue *q3 = CreateQueue();
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
			printf("arry[%d] = %s  \t time = %d\n",i, arry2[i],darry[i]*darry2[i]);	
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
				}
				else if (flag[i]==2)
				{
					AddQ(q2, darry[i]*darry2[i],arry2[i],0);
				}
				else if (flag[i]==3)
				{
					AddQ(q3, darry[i]*darry2[i],arry2[i],0);
				}
			}
    }	
	
void* printA(void* param)
{
	// Queue *q6 = CreateQueue();
	int i =0;
	int gap = 0;
	
	DATA* data = (DATA*)param;
	float time_use=0;

	//pointing to which command
	clock_t   total_t;
	struct timeval end;//struct timezone tz; //
	data-> pt1=0;
	data-> pt2=0;
	data-> pt3=0;
	data-> pt4=0;
	data-> pt5=0;
	
	for(i = 0;i<5;i++)
	{

		sem_wait(&sig2);

		// printf("Now i = %d\n",i);
		if(i==0)
		{
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;			
			printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1,getQs((data->add1),(data-> pt1)));
			
			s1 = getQv((data->add1),0);
			data->opt_num = 1;
			// printf("1st value = %d\n", cal_sjf((data->add1),s1,data->ss1));
			s1 = s1 -100;
			if(s1>0)
			{
				SimulatorTimer(waittime);	
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;				
				printf("%.3f - Process %d: end processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1,getQs((data->add1),data-> pt1));				
				
				
			}
			else
			{
				SimulatorTimer(s1+waittime);
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;				
				printf("%.3f - Process %d: end processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1,getQs((data->add1),data-> pt1));
				
				++(data->pt1);
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;				
				
				printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1,getQs((data->add1),data-> pt1));
				SimulatorTimer(100-(s1+waittime));
				
			}
			if(vitual_flag)
			{
				printf("\t1st value = %d\n", cal_sjf((data->add1),s1,data->ss1));
			// s1 = getQv((data->add1),(data-> pt1));
			// printf("\t1st value = %d\n", cal_sjf((data->add1),s1,(data->ss1)-1));
			// printf("2nd value = %d\n", cal_sjf((data->add2),s2,data->ss2));
			// printf("3rd value = %d\n", cal_sjf((data->add3),s3,data->ss3));
			// printf("4th value = %d\n", cal_sjf((data->add4),s4,data->ss4));
			// printf("5th value = %d\n", cal_sjf((data->add5),s5,data->ss5));
			}
		}


		if(i==1)
		{	

			s2 = getQv((data->add2),0);
			if(cal_sjf((data->add1),s1,data->ss1)<cal_sjf((data->add2),s2,data->ss2))
			{
				s1 = s1 -100;
				data->opt_num = 1;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);	
				
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add1),data-> pt1));
				SimulatorTimer(waittime);	
			}
			else
			{
				s2 = s2 -100;
				data->opt_num = 2;

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);	
				
				if(s2>0)
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));					
					SimulatorTimer(waittime);	
				}
				else
				{
					SimulatorTimer(s2+waittime);
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					printf("%.3f - Process %d: end processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));
					
					++(data-> pt2);
					
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					
					printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));
					SimulatorTimer(100-(s2+waittime));
				
				}
				
				
			}
			
			if(vitual_flag)
			{		
			// s4 = getQv((data->add4),0);
			// s5 = getQv((data->add5),0);
			printf("\t1st value = %d\n", cal_sjf((data->add1),s1,data->ss1));
			printf("\t2nd value = %d\n", cal_sjf((data->add2),s2,data->ss2));
			// printf("3rd value = %d\n", cal_sjf((data->add3),s3,data->ss3));
			// printf("4th value = %d\n", cal_sjf((data->add4),s4,data->ss4));
			// printf("5th value = %d\n", cal_sjf((data->add5),s5,data->ss5));
			}
		}		

		if(i==2)
		{	
	
			// printf("%.3f - start running process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1);
			s3 = getQv((data->add3),0);
			int arr3[3];
			arr3[0] = cal_sjf((data->add1),s1,data->ss1);
			arr3[1] = cal_sjf((data->add2),s1,data->ss2);
			arr3[2] = cal_sjf((data->add3),s1,data->ss3);
			
			// SimulatorTimer(waittime);	
			// printf("smallest index = %d\n",min(arr3,3));
			if(min(arr3,3)==0)
			{

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);			
				
				s1 = s1 -100;
				data->opt_num = 1;
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add1),data-> pt1));
				SimulatorTimer(waittime);
			}
			else if(min(arr3,3)==1)
			{
				s2 = s2 -100;
				data->opt_num = 2;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);	
				
				if(s2>0)
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));					
					SimulatorTimer(waittime);	
				}
				else
				{
					SimulatorTimer(s2+waittime);
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					printf("%.3f - Process %d: end processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));
					
					++(data-> pt2);
					
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					
					printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));
					SimulatorTimer(100-(s2+waittime));
				
				}
			}
			else if(min(arr3,3) ==2)
			{
				s3 = s3 -100;
				data->opt_num = 3;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
				
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add3),data-> pt3));
				SimulatorTimer(waittime);
			}

			
			// s5 = getQv((data->add5),0);
			if(vitual_flag)
			{
			printf("\t1st value = %d\n", cal_sjf((data->add1),s1,data->ss1));
			printf("\t2nd value = %d\n", cal_sjf((data->add2),s2,data->ss2));
			printf("\t3rd value = %d\n", cal_sjf((data->add3),s3,data->ss3));
			// printf("4th value = %d\n", cal_sjf((data->add4),s4,data->ss4));
			// printf("5th value = %d\n", cal_sjf((data->add5),s5,data->ss5));
			}
		}
		if(i==3)
		{	
			s4 = getQv((data->add4),0);
			// printf("%.3f - start running process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1);
			int arr4[4];
			arr4[0] = cal_sjf((data->add1),s1,data->ss1);
			arr4[1] = cal_sjf((data->add2),s1,data->ss2);
			arr4[2] = cal_sjf((data->add3),s1,data->ss3);
			arr4[3] = cal_sjf((data->add4),s1,data->ss4);
			
			// SimulatorTimer(waittime);	
			if(min(arr4,4)==0)
			{
				SimulatorTimer(waittime);
				s1 = s1 -100;
				data->opt_num = 1;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
				
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add1),data-> pt1));				
			}
			else if(min(arr4,4)==1)
			{
				s2 = s2 -100;
				data->opt_num = 2;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				
				if(s2>0)
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));					
					SimulatorTimer(waittime);	
				}
				else
				{
					SimulatorTimer(s2+waittime);
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					printf("%.3f - Process %d: end processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));
					++(data-> pt2);
					
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					
					printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));
					SimulatorTimer(100-(s2+waittime));
				
				}		
			}
			
			else if(min(arr4,4) ==2)
			{
				s3 = s3 -100;
				data->opt_num = 3;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add3),data-> pt3));
				SimulatorTimer(waittime);	
				// printf("%.3f - start running process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
			}
			else if(min(arr4,4) ==3)
			{
				s4 = s4 -100;
				data->opt_num = 4;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);	
			
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add4),data-> pt4));
				// printf("%.3f - start running process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
				SimulatorTimer(waittime);					
			}			
			
			if(vitual_flag)
			{			
			printf("\t1st value = %d\n", cal_sjf((data->add1),s1,data->ss1));
			printf("\t2nd value = %d\n", cal_sjf((data->add2),s2,data->ss2));
			printf("\t3rd value = %d\n", cal_sjf((data->add3),s3,data->ss3));
			printf("\t4th value = %d\n", cal_sjf((data->add4),s4,data->ss4));
			// printf("5th value = %d\n", cal_sjf((data->add5),s5,data->ss5));
			}
		}

		if(i==4)
		{	
			s5 = getQv((data->add5),0);
			// printf("%.3f - start running process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1);
			int arr5[5];
			arr5[0] = cal_sjf((data->add1),s1,data->ss1);
			arr5[1] = cal_sjf((data->add2),s1,data->ss2);
			arr5[2] = cal_sjf((data->add3),s1,data->ss3);
			arr5[3] = cal_sjf((data->add4),s1,data->ss4);
			arr5[4] = cal_sjf((data->add5),s1,data->ss5);
			
			// SimulatorTimer(waittime);	
			if(min(arr5,5)==0)
			{
				s1 = s1 -100;
				data->opt_num = 1;
			
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
				
				
				printf("%.3f - start running process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);	
				SimulatorTimer(waittime);					
			}
			else if(min(arr5,5)==1)
			{
				s2 = s2 -100;
				data->opt_num = 2;
			
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
				
				if(s2>0)
				{
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));					
					SimulatorTimer(waittime);	
				}
				else
				{
					SimulatorTimer(s2+waittime);
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					printf("%.3f - Process %d: end processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));
					++(data-> pt2);
					
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
					total_t = time_use;				
					
					printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num,getQs((data->add2),data-> pt2));
					SimulatorTimer(100-(s2+waittime));
				
				}				
			}
			else if(min(arr5,5) ==2)
			{
				s3 = s3 -100;
				data->opt_num = 3;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
				
				printf("%.3f - start running process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
				SimulatorTimer(waittime);	
			}
			else if(min(arr5,5) ==3)
			{
				s4 = s4 -100;
				data->opt_num = 4;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
				
				printf("%.3f - start running process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);	
				SimulatorTimer(waittime);					
			}			
			else if(min(arr5,5) ==4)
			{
				s5 = s5 -100;
				data->opt_num = 5;
				
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);

				gettimeofday(&end,NULL);
				time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
				total_t = time_use;
				printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
								
				printf("%.3f - start running process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);					
				SimulatorTimer(waittime);	
			}					
			
			if(vitual_flag)
			{
			printf("\t1st value = %d\n", cal_sjf((data->add1),s1,data->ss1));
			printf("\t2nd value = %d\n", cal_sjf((data->add2),s2,data->ss2));
			printf("\t3rd value = %d\n", cal_sjf((data->add3),s3,data->ss3));
			printf("\t4th value = %d\n", cal_sjf((data->add4),s4,data->ss4));
			printf("\t5th value = %d\n", cal_sjf((data->add5),s5,data->ss5));
			}
		}
		
		// printf("%.3f - start running \n",(total_t*0.1*10)/CLOCKS_PER_SEC);
		// data->t1 = total_t;
		// SimulatorTimer(waittime);
		// printf("running \n");
		// gettimeofday(&end,NULL);
		// time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
		// total_t = time_use;
		// if(i<4)
		// {
			// printf("%.3f - end running by interupput\n",(total_t*0.1*10)/CLOCKS_PER_SEC);     
		// }		
		// data->t2 = total_t;
		
		
		
		
		sem_post(&sig1); 

	}
	return (void*)"";
}


void* printB(void* param)
{
	int i =0;
	
	
	
	for(i = 0;i<5;i++)
	{
		sem_wait(&sig1);
		DATA* data = (DATA*)param;
		float time_use=0;

		clock_t   total_t;
		struct timeval end;//struct timezone tz; //
		Queue *q1 = CreateQueue();
		Queue *q2 = CreateQueue();
		Queue *q3 = CreateQueue();
		Queue *q4 = CreateQueue();		
		Queue *q5 = CreateQueue();
		
		if( i ==0)
		{
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;
			printf("%.3f - Simulator program starting\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
			
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;
			printf("%.3f - OS: preparing process 1\n",(total_t*0.1*10)/CLOCKS_PER_SEC);

			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;
			
			printf("%.3f - OS: starting process 1\n",(total_t*0.1*10)/CLOCKS_PER_SEC);	
			
			// printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1);
			// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
			AddQ(q1, 70,"A",0);
			++(data->ss1);
			AddQ(q1, 200,"B",0);
			++(data->ss1);
			AddQ(q1, 366,"C",0);
			++(data->ss1);
			data->add1 = q1;

		}
		
		if( i ==1)
		{
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;
			printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
			// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
			

			
			AddQ(q2, 320,"A",0);
			++(data->ss2);
			AddQ(q2, 120,"B",0);
			++(data->ss2);
			data->add2 = q2;

		}
		
		if( i ==2)
		{
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;
			printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
			// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
			
			AddQ(q3, 200,"A",0);
			++(data->ss3);
			AddQ(q3, 140,"B",0);
			++(data->ss3);
			AddQ(q3, 332,"C",0);
			++(data->ss3);
			data->add3 = q3;
 
		}

		if( i ==3)
		{
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;
			printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
			// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);			
			AddQ(q4, 200,"A",0);
			++(data->ss4);
			AddQ(q4, 100,"B",0);
			++(data->ss4);
			AddQ(q4, 266,"C",0);
			++(data->ss4);
			data->add4 = q4;

		}

		if( i ==4)
		{
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;
			printf("%.3f - Process %d: interrupt processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->opt_num);
			// printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);			
			AddQ(q5, 200,"A",0);
			++(data->ss5);
			AddQ(q5, 100,"B",0);
			++(data->ss5);
			AddQ(q5, 260,"C",0);
			++(data->ss5);
			data->add5 = q5;
			
		}		
		/*
       if(i<6)
		{
			data->t1 = total_t;
			// SimulatorTimer(waittime);
			// printf("read data\n");
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;
			// printf("%.3f - end reading \n",(total_t*0.1*10)/CLOCKS_PER_SEC);            
			data->t2 = total_t;
			sem_post(&sig2); 
		}
		else if(i>=6){}
		*/
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
		 printf("%s\n",name);
		 
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
									printf("This is SJF\n");
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
									printf("This is RR\n");
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
			printf("Now print\n");
			
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
			
			
			
			for (int i=0;i<13;i++)
			{
				printf("%s : %d\n",text[i],*(p+i));
			}
			
			
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

void SplitStrByStr( char* sources, char str, char arry[10][20], int* count){

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



