#include <string.h>
#include <stdio.h>
#define ElementType int
#define N 20 //ElementType的特殊值，标志错误
#define ERROR -99 //ElementType的特殊值，标志错误


int getv2(char s1[]) ///////////// problem
 {

    char s2[20];

    strncpy(s2, s1, strlen(s1)-strlen(";"));

    int n = atoi(s2);
//    printf("%d\n",n);
    return n;
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

//输出数组
void PrintArryData(char arry[30][20], int cnt){
	for (int i = 0; i < cnt; i++){
		printf("%s\n", arry[i]);
	}
}

void find(Queue* q,char buf[], char aim[])
{

    char *delim = "}";
    char *p = NULL;

    int f =0;
    char str[50];
    int num1 =0;
     strtok(buf, delim);

    while((p = strtok(NULL, delim)))
    {
//         printf("%s\n",p);

        if(f)
        {
            sscanf(p,"%d %s",&num1, str);
            AddQ(q, num1);
        }

     char  *ptr = strstr(p,aim);
        if(ptr!=NULL) f =1;
        else f = 0;
    }
}



void main(){
	int line = 0;
	char arry[30][20];
    int a[] = {10,30,20,15,25,10,30,50,15};

	char* pStr = "Start Program Meta-Data Code:\
S{begin}0; A{begin}0; P{run}11; M{allocate}2;\
O{monitor}7; I{hard drive}8; I{mouse}8; O{printer}20;\
P{run}6; O{printer}4; M{block}6;\
I{keyboard}17; M{block}4; O{printer}8; P{run}5; P{run}5;\
O{hard drive}6; P{run}18; A{finish}0; S{finish}0.\
End Program Meta-Data Code.";
	char tmpChar = '}';

	SplitStrByStr(pStr, tmpChar, arry, &line);
//	PrintArryData(arry, line);
    int i =0;
    int j =0;
  #define  option_num 9
      char *option[option_num] = {"P{run","M{allocate","O{monitor","I{hard","I{mouse","O{printer","M{block","O{hard","I{key"};
        for(i = 0; i < option_num; i++) {
//        printf("option[%d] = %s\n", i+1, option[i]);
    }
//    ok(arry[30][20] ,"P{");
    int b[option_num];
    int k =0;

    printf("Configuration File Data\n");
//PrintArryData(arry, line);
    printf("Meta-Data Metrics\n");


 for(i = 0; i < 20; i++)
 {
    for( j = 0; j < option_num; j++)
    if(strstr(arry[i],option[j]))
    {

        k = getv2(arry[i+1]);
//        printf("In line %d th, j = %d, value is =%d\n",i,j,k);

         switch(j)
        {
           case 0:
            printf("P{run}%d - %d ms\n",k,k*a[j]);
              break;
           case 1:
            printf("M{allocate}%d - %d ms\n",k,k*a[j]);
              break;
           case 2:
            printf("O{monitor}%d - %d ms\n",k,k*a[j]);
              break;
           case 3:
            printf("I{hard drive}%d - %d ms\n",k,k*a[j]);
              break;
           case 4:
            printf("I{mouse}%d - %d ms\n",k,k*a[j]);
              break;
           case 5:
            printf("O{printer}%d - %d ms\n",k,k*a[j]);
              break;
           case 6:
            printf("M{block}%d - %d ms\n",k,k*a[j]);
              break;
           case 7:
            printf("O{hard drive}%d - %d ms\n",k,k*a[j]);
              break;
           default:
            printf("I{keyboard}%d - %d ms\n",k,k*a[j]);
              break;
        }

    }
 }
FILE *fpWrite=fopen("1.txt","w");
	if(fpWrite==NULL)
	{
		return 0;
	}
	for(int i=0;i<10;i++)
		fprintf(fpWrite,"%d ",i);
	fclose(fpWrite);
	system("pause");
}
