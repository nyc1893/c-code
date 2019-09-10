#include <stdio.h>
#include <string.h>

#include <stdlib.h>
struct
{
	int num;
	char *name;

} NV;

void print_str(char *name1,typeof(NV) *pt)
{
    printf("%s = %d, name = %s\n",name1,pt->num,pt->name);
}

void change_str(int num2,char *name2,typeof(NV) *pt)
{
    pt->num = num2;
    pt->name = name2;

}

int main()
{

    int a = 1;
    int b = 2;

	typeof(NV) CA;
	NV = {10, "Nevada"};
    CA = {300, "California"};
    printf("HH\n");
	printf("a = %d, b = %d\n", a,b);

	typeof(NV) *pt1 = &NV;
	typeof(CA) *pt2 = &CA;

	printf("NV = %d, name = %s\n",NV.num,NV.name);

    NV.num = 20;
    NV.name = "cc";
    printf("NV = %d, name = %s\n",pt1->num,pt1->name);
    print_str("Winco",&NV);
    change_str(200,"Costco",&NV);
    print_str("Costco",&NV);

    char buf[]="HTTP/1.1 200 OK\
Content-Type: text/html\
Server: DynDNS-CheckIP/1.0\
Connection: close\
Cache-Control: no-cache\
Pragma: no-cache\
Content-Length: 105\
\
<html><head><title>Current IP Check</title></head><body>Current IP Address: 1234</body></html>\
Current IP Address: 2234<";
    char *ptr = NULL;
	char *end = NULL;
	//char ip[32] = {0};
	ptr = strstr(buf,"Current IP Address:");
	ptr = ptr + 20;
	end = strstr(ptr,"<");
	//printf("end:%s\n",end);
	//printf("ptr:%s\n",ptr);

	char* ip = (char*)malloc((end-ptr)/sizeof(char));
    if(!ip)   exit(1);
    printf("%d\n",(end-ptr)/sizeof(char));
    memcpy(ip,ptr,(end-ptr)/sizeof(char));
    printf("ip:%s\n",ip);
    int num = atoi(ip);
    printf("ip = %d\n",num);
    free(ip);
    ip = NULL;

    ptr = strstr(end,"Current IP Address:");
	ptr = ptr + 20;
	end = strstr(ptr,"<");
	//printf("end:%s\n",end);
	//printf("ptr:%s\n",ptr);


    if(!ip)   ip = (char*)malloc((end-ptr)/sizeof(char));
    memcpy(ip,ptr,(end-ptr)/sizeof(char));
    printf("ip:%s\n",ip);
    num = atoi(ip);
    printf("ip = %d\n",num);
    free(ip);
    ip = NULL;
    return 0;
}
