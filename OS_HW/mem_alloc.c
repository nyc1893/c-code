#include<stdio.h>


unsigned int mem_call = 4294967294;

void dis_mem()
{
	char s[20];
	sprintf(s, "0x%08x", mem_call*128); //产生"123"
	printf("%s\n",s);
	// printf("Now is %04o\n",mem_call*128);
	++mem_call;
	// printf("Now is %d\n",mem_call);

}

int main()

{
	// char s[20];
	dis_mem();
	dis_mem();
	dis_mem();

	
	// sprintf(s, "%d", 123); //产生"123"
    // printf("Now is %s\n",s);

}
