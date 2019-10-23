#include <time.h>
#include <stdio.h>


int main()
{
   clock_t start_t, end_t, total_t;
   int i;

   start_t = clock();
   printf("start timeit\n");
   int j = 0;


//   printf("a loop，start_t = %ld\n", start_t);
   for(i=0; i< 30000; i++)
   {
	for(j=0; j< 10000; j++)
	{
	}
   }
   end_t = clock();
//   printf("loop end，end_t = %ld\n", end_t);
//   printf("CLOCKS_PER_SEC =  %d\n", CLOCKS_PER_SEC);
   total_t = end_t - start_t;
   printf("total_t = %ld\n", total_t);
   printf("CPU Running time:%.3f seconds\n", (total_t*0.1*10)/CLOCKS_PER_SEC);   // (total_t*0.1*10)  使得整数类型转为小数类型
   printf("Finish timeit...\n");


   return 0;
}



/*
Another way
*/
#include<stdio.h>

#include<sys/time.h>
#include <time.h>
#include<unistd.h>




void wait(int num)

{

	usleep(1000*num);

}

int main()

{
	
	
	float time_use=0;
	struct timeval start;
	struct timeval end;//struct timezone tz; //后面有说明
	gettimeofday(&start,NULL); //gettimeofday(&start,&tz);结果一样
	// printf("start.tv_sec:%d\n",start.tv_sec);
	// printf("start.tv_usec:%d\n",start.tv_usec);

	wait(10);
	gettimeofday(&end,NULL);
	// printf("end.tv_sec:%d\n",end.tv_sec);
	// printf("end.tv_usec:%d\n",end.tv_usec);
	time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
	printf("time_use is %.0f ms\n",time_use/1000);
       

}
