
/*
 to  compile:
 gcc -pthread main.c
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
 
static sem_t sig1;
static sem_t sig2;
// static sem_t s3;
// static sem_t s4;
// static sem_t s5;

#define num 2
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
	
	long    add6;//for output
	
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

// disp_q((data.add1),s1,data.ss1,data.pt1));

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
	
	
	

int main()
{
    if (freopen ("output.txt", "w", stdout) == NULL)
        fprintf(stderr, "error redirecting stdout\n");
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
	// PrintQueue(data.add1);
	// PrintQueue(data.add6);
    fclose(stdout);
	
   // FILE *stream;
    // if ((stream = freopen("output.txt", "w", stdout)) == NULL)
        // exit(-1);
    // printf("this is stdout output\n");
    // stream = freopen("/dev/tty","w",stdout);
    // /*stdout是向程序的末尾的控制台重定向*/
    // printf("And now back to the console once again\n");


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
		AddQ((data->add6), 0,"start processing action2",0);
		// printf("Now i = %d\n",i);
		if(i==0)
		{
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;			
			printf("%.3f - Process %d: start processing action %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,1,getQs((data->add1),(data-> pt1)));
			
			AddQ((data->add6), 0,"start processing action3",0);
			
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
		
		Queue *q6 = CreateQueue();//for output
		
		data->add6 = q6;
		
		AddQ(q6, 0,"Simulator program starting",0);
		if( i ==0)
		{
			gettimeofday(&end,NULL);
			time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
			total_t = time_use;
			printf("%.3f - Simulator program starting\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
			AddQ(q6, 1,"Simulator program starting",0);
			
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
