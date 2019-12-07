
/*
 to  compile:
 gcc -pthread main.c
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
 
static sem_t s1;
static sem_t s2;
static sem_t s3;
static sem_t s4;
static sem_t s5;

#define num 2
#define waittime 98

typedef struct __DATA
{
	long    t1; //store start time for a I/O operation 
	long    t2; //store end time for a I/O operation 
	long    it1;//pass inital time in sec 
	long    it2;//pass inital time in usec 		
	// char    *word2;
}DATA;


void SimulatorTimer(int waitTime)//this is a ms unit wait
{

	usleep(1000*waitTime);
}

void* printA(void* param)
{
	sem_wait(&s5);
	DATA* data = (DATA*)param;
	float time_use=0;

	clock_t   total_t;
	struct timeval end;//struct timezone tz; //
  
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - start reading \n",(total_t*0.1*10)/CLOCKS_PER_SEC);
	data->t1 = total_t;
	SimulatorTimer(waittime);
	printf("read A\n");
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - end reading \n",(total_t*0.1*10)/CLOCKS_PER_SEC);            
	data->t2 = total_t;
	sem_post(&s1); 
	return (void*)"";
}


void* printB(void* param)
{
	sem_wait(&s1);
	DATA* data = (DATA*)param;
	float time_use=0;

	clock_t   total_t;
	struct timeval end;//struct timezone tz; //
  
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
	data->t1 = total_t;
	SimulatorTimer(waittime);
	printf("read A\n");
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - end reading \n",(total_t*0.1*10)/CLOCKS_PER_SEC);            
	data->t2 = total_t;
	sem_post(&s2); 
	return (void*)"";
}

void* printC(void* param)
{
	sem_wait(&s2);
	DATA* data = (DATA*)param;
	float time_use=0;

	clock_t   total_t;
	struct timeval end;//struct timezone tz; //
  
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
	data->t1 = total_t;
	SimulatorTimer(waittime);
	printf("read A\n");
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - end reading \n",(total_t*0.1*10)/CLOCKS_PER_SEC);            
	data->t2 = total_t;
	sem_post(&s3); 
	return (void*)"";
}

void* printD(void* param)
{
	sem_wait(&s3);
	DATA* data = (DATA*)param;
	float time_use=0;

	clock_t   total_t;
	struct timeval end;//struct timezone tz; //
  
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
	data->t1 = total_t;
	SimulatorTimer(waittime);
	printf("read A\n");
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - end reading \n",(total_t*0.1*10)/CLOCKS_PER_SEC);            
	data->t2 = total_t;
	sem_post(&s4); 
	return (void*)"";
}

void* printE(void* param)
{
	sem_wait(&s4);
	DATA* data = (DATA*)param;
	float time_use=0;

	clock_t   total_t;
	struct timeval end;//struct timezone tz; //
  
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - start reading\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
	data->t1 = total_t;
	SimulatorTimer(waittime);
	printf("read A\n");
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
	total_t = time_use;
	printf("%.3f - end reading \n",(total_t*0.1*10)/CLOCKS_PER_SEC);            
	data->t2 = total_t;
	sem_post(&s5); 
	return (void*)"";
}


/*
void *printA(void *arg)
{
    int i = 0;
    for(i = 1;i < num;i++)
    {
        sem_wait(&s5);     //close A
		SimulatorTimer(waittime);
        printf("read A\n",i);
        sem_post(&s1);   //open B

    }
    return NULL;
}

void  *printB(void *arg)
{
    int i = 0;
    for(i = 1;i < num;i++)
    {
        sem_wait(&s1);	//close B
		SimulatorTimer(waittime);
        printf("read B\n");
        sem_post(&s2); //open C

    }
    return NULL;
}



void *printC(void *arg)
{
    int i = 0;
    for(i = 1;i < num;i++)
    {
        sem_wait(&s2);//close C
		SimulatorTimer(waittime);
        printf("read C\n");
        sem_post(&s3); //open A

    }
    return NULL;
}

void *printD(void *arg)
{
    int i = 0;
    for(i = 1;i < num;i++)
    {
        sem_wait(&s3);//close C
		SimulatorTimer(waittime);
        printf("read D\n");
        sem_post(&s4); //open A

    }
    return NULL;
}

void *printE(void *arg)
{
    int i = 0;
    for(i = 1;i < num;i++)
    {
        sem_wait(&s4);//close C
		SimulatorTimer(waittime);
        printf("read E\n");
        sem_post(&s5); //open A

    }
    return NULL;
}
*/
int main()
{
	
	
	float time_use=0;
	struct timeval start;
	struct timeval end;//struct timezone tz;
	gettimeofday(&start,NULL); //gettimeofday(&start,&tz);
	
	
    pthread_t thread_A;
    pthread_t thread_B;
    pthread_t thread_C;
	pthread_t thread_D;
	pthread_t thread_E;
	
    sem_init(&s1,0,0);
    sem_init(&s2,0,0);
    sem_init(&s3,0,0);
    sem_init(&s4,0,0);	
    sem_init(&s5,0,1);
	
	DATA data = {0};
	gettimeofday(&end,NULL);
	// gettimeofday(&end,NULL);
	data.it1 = start.tv_sec;
	data.it2 = start.tv_usec;
	
    pthread_create(&thread_A,NULL,printA,&data);
    pthread_create(&thread_B,NULL,printB,&data);
    pthread_create(&thread_C,NULL,printC,&data);
    pthread_create(&thread_D,NULL,printD,&data);
    pthread_create(&thread_E,NULL,printE,&data);

	
    pthread_join(thread_A,NULL);
    pthread_join(thread_B,NULL);
    pthread_join(thread_C,NULL);
    pthread_join(thread_D,NULL);
    pthread_join(thread_E,NULL);
	// printf("%d  %d\n", data.t1, data.t2); 
	
    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    sem_destroy(&s4);
    sem_destroy(&s5);	
	
    printf("\n");
    
    return 0;

}
