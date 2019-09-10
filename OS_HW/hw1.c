#include <stdio.h>
#include <string.h>
struct
{
	int num;
	char *name; 
	
} NV;


int main()
{
    // Question 1
    int a = 1;
    int b = 2;
    
	typeof(NV) CA;
    
    printf("HH\n");
	printf("a = %d, b = %d", a,b);
    
	typeof(NV) *pt1 = &NV;
	typeof(CA) *pt2 = &CA;
	
	pt1->num = 10;
	pt1->name = "Nevada";
	
	pt2 ->num = 300;
	pt2->name = "California";
	
	printf("NV = %d, name = %c",pt1->num,pt1->name);
	
	
	
	
	
    return 0;
}
