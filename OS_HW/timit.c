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
