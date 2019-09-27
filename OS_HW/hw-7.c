// Program Header Information ////////////////////////////////////////
/**
* @file Sim01.c
*
* @brief program for SIM01
*
* @details Simulation of a simle, one-program OS simulator
*
* @version 2.00
*          C.S. Student (4 Sep 2019)
*          Initial development of SIM01
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



struct conf
  {
   // struct that records Config information read from Config file
   int process;
   int monitor;
   int mouse;
   int hardDrive;
   int printer;
   int keyboard;
   int memory;
//   bool logbothtrue;
//   char dataFile[15];
//   char outputFile[15];
  }Conf_Info;
//
// Global Constant Definitions ////////////////////////////////////
//
#define c_num 7
#define MAX_LINE 50
#define  option_num 9
//
// Class Definitions //////////////////////////////////////////////
//

//
// Free Function Prototypes ///////////////////////////////////////
//
int getv2(char s1[]);
void SplitStrByStr( char *sources, char str, char arry[10][20], int* count);
int *getconf(char *fileName );
char *getfileall(char *fname);
void printConf(char *fname)
{
    int *p = getconf(fname);
    typeof(Conf_Info) *ptr1 = &Conf_Info;

    ptr1-> process =     *(p+1);
    ptr1-> monitor =     *(p+0);
    ptr1-> mouse =       *(p+2);
    ptr1-> hardDrive =   *(p+3);
    ptr1-> printer =     *(p+6);
    ptr1-> keyboard =    *(p+4);
    ptr1-> memory =      *(p+5);

    printf("Configuration File Data\n");

    printf("File Name is:%s\n",fname);

    printf("Monitor = %d ms/cycle\n",Conf_Info.monitor);

    printf("Processor = %d ms/cycle\n",Conf_Info.process);

    printf("Mouse = %d ms/cycle\n",Conf_Info.mouse);

    printf("Hard Drive = %d ms/cycle\n",Conf_Info.hardDrive);

    printf("Keyboard = %d ms/cycle\n",Conf_Info.keyboard);

    printf("Memory = %d ms/cycle\n",Conf_Info.memory);

    printf("Printer = %d ms/cycle\n",Conf_Info.printer);

    printf("Logged to: monitor and logfile_1.lgf\n\n");


}



#define ElementType1 int //store type
#define ElementType2 char //store type
#define MAXSIZE 20 //max store size
#define ERROR -99 //ElementType for error notation

typedef struct {
    ElementType1 data[MAXSIZE];
    ElementType2 *name[MAXSIZE];
    int front; // start of Q
    int rear; // end of Q
    int size; //number of element
}Queue;

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
void DestroySequeue(Queue *q)
{
    if (NULL != q)
    {
        free(q);
    }
    printf("Heap Space is free.\n");
}

int IsFullQ(Queue* q) {
    return (q->size == MAXSIZE);
}

void AddQ(Queue* q, ElementType1 item1,ElementType2 *item2 ) {
    if (IsFullQ(q)) {
        printf("Queue is full!\n");
        return;
    }
    q->rear++;
    q->rear %= MAXSIZE;
    q->size++;
    q->data[q->rear] = item1;
    q->name[q->rear] = item2;
}

int IsEmptyQ(Queue* q) {
    return (q->size == 0);
}

ElementType1 DeleteQ(Queue* q) {
    if (IsEmptyQ(q)) {
        printf("Empty Queue!\n");
        return ERROR;
    }
    q->front++;
    q->front %= MAXSIZE; //0 1 2 3 4 5
    q->size--;
    q->name[q->front];
    return q->data[q->front];
}

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
        printf("%d\t%s\n", q->data[index],q->name[index]);
    }
    printf("\n");
}

void cal(Queue* q) {
    if (IsEmptyQ(q)) {
        printf("Empty Queue!\n");
        return;
    }
    printf("Meta-Data Metrics\n");
    int index = q->front;
    int i;
    for (i = 0; i < q->size; i++) {
        index++;
        index %= MAXSIZE;

        if(strcmp(q->name[index],"P{run}") == 0)
        printf("%s %d - %d ms\n",q->name[index], q->data[index],(q->data[index])*Conf_Info.process);

        if(strcmp(q->name[index],"M{allocate}") == 0)
        printf("%s %d - %d ms\n",q->name[index], q->data[index],(q->data[index])*Conf_Info.memory);

        if(strcmp(q->name[index],"O{monitor}") == 0)
        printf("%s %d - %d ms\n",q->name[index], q->data[index],(q->data[index])*Conf_Info.monitor);

        if(strcmp(q->name[index],"I{hard drive}") == 0)
        printf("%s %d - %d ms\n",q->name[index], q->data[index],(q->data[index])*Conf_Info.hardDrive);

        if(strcmp(q->name[index],"I{mouse}") == 0)
        printf("%s %d - %d ms\n",q->name[index], q->data[index],(q->data[index])*Conf_Info.mouse);

        if(strcmp(q->name[index],"O{printer}") == 0)
        printf("%s %d - %d ms\n",q->name[index], q->data[index],(q->data[index])*Conf_Info.process);

        if(strcmp(q->name[index],"M{block}") == 0)
        printf("%s %d - %d ms\n",q->name[index], q->data[index],(q->data[index])*Conf_Info.memory);

        if(strcmp(q->name[index],"O{hard drive}") == 0)
        printf("%s %d - %d ms\n",q->name[index], q->data[index],(q->data[index])*Conf_Info.hardDrive);

        if(strcmp(q->name[index],"I{keyboard}") == 0)
        printf("%s %d - %d ms\n",q->name[index], q->data[index],(q->data[index])*Conf_Info.keyboard);

    }
    printf("\n");
}





int *readmeta(char *fname) //return an address for a Q
{
    char *pStr = NULL;
    pStr=getfileall(fname); //get Mata file information
    char arry[30][20];
    char tmpChar = '}';
    int line =0;
    SplitStrByStr(pStr, tmpChar, arry, &line); //to split the whole string by '}'
    char *option[option_num] = {"P{run","M{allocate","O{monitor","I{hard","I{mouse","O{printer","M{block","O{hard","I{key"};
                                //to detect the key works in option matrix
    int b[option_num];
    int i,j,k =0;

    Queue* q = CreateQueue();
 for(i = 0; i < 20; i++)
	 {
		for( j = 0; j < option_num; j++)
		if(strstr(arry[i],option[j]))
		{
			k = getv2(arry[i+1]);

			 switch(j)
			{
			   case 0:
//				printf("P{run}%d\n",k);
				AddQ(q, k,"P{run}");
				  break;
			   case 1:
//				printf("M{allocate}%d\n",k);
                AddQ(q, k,"M{allocate}");
				  break;
			   case 2:
//				printf("O{monitor}%d\n",k);
                AddQ(q, k,"O{monitor}");
				  break;
			   case 3:
//				printf("I{hard drive}%d\n",k);
                AddQ(q, k,"I{hard drive}");
				  break;
			   case 4:
//				printf("I{mouse}%d\n",k);
                AddQ(q, k,"I{mouse}");
				  break;
			   case 5:
//				printf("O{printer}%d\n",k);
                AddQ(q, k,"O{printer}");
				  break;
			   case 6:
//				printf("M{block}%d\n",k);
                AddQ(q, k,"M{block}");
				  break;
			   case 7:
//				printf("O{hard drive}%d\n",k);
                AddQ(q, k,"O{hard drive}");
				  break;
			   default:
//				printf("I{keyboard}%d\n",k);
                AddQ(q, k,"I{keyboard}");
				  break;
			}

		}
	 }
    return q;

}
//
// Main Function Implementation ///////////////////////////////////
//

int main(int argc,char* argv[])
{

    printConf("config_1.conf");
    int *q= readmeta("test_1a.mdf");
    cal(q);

    DestroySequeue(q);
    return 0;
}

//
// Free Function Implementation ///////////////////////////////////
/**
* @Turn the already existing string matrix into an int value and return
*
* @it use ';' as a sign to seperate.
*
* @return an int value
*
*/

int getv2(char s1[])
 {

    char s2[20];

    strncpy(s2, s1, strlen(s1)-strlen(";"));

    int n = atoi(s2);

    return n;
}

//
// Free Function Implementation ///////////////////////////////////
/**
* @Split the whole string into different string array for next step
*
* @ no return
*
*/

void SplitStrByStr( char *sources, char str, char arry[10][20], int* count){

	int tmpCount = 0;
	char* sourcesCp1 = NULL;
	char* sourcesCp2 = NULL;
	sourcesCp1 = sources;
	sourcesCp2 = sources;

	do{
		//Find the position of the first occurrence of the character c in the string s
		sourcesCp1 = strchr(sourcesCp1, str);
		if (sourcesCp1 != NULL){
			if (sourcesCp1 - sourcesCp2 > 0){
				//Returns the next position to find the character.
				// Copy the previous data to the array area.
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

//
// Free Function Implementation ///////////////////////////////////
/**
* @ get the information from Conf file
*
* @  return an int style 1x7 matrix
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


    static int temp[7];
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
     char *cof[c_num] = {"Monitor","Processor","Mouse","Hard","Keyboard","Memory","Printer"};

     for(i=0;i<p;i++)
     {
         for (j=0;j<c_num;j++)
        {
             if(strstr(res[i],cof[j]))
            {	//because this file only the 4th line have one more space
                if(j==3)sscanf(res[i],"%s %s %s %s %s %d ", buf1,buf2,buf3,buf4,buf5,&digit );
                else sscanf(res[i],"%s %s %s %s %d ", buf1,buf2,buf3,buf4,&digit );
                temp[j] =digit;
            }
        }
     }
     return temp;

}

//
// Free Function Implementation ///////////////////////////////////
/**
* @ Read the file from Meta file and get all line
*
* @ no a string pointer
*
*/
char *getfileall(char *fname)
{
	FILE *fp;
	char *str;
	char txt[1000];
	int filesize;
	if ((fp=fopen(fname,"r"))==NULL){
		printf("Can not open the file%s error\n",fname);
		return NULL;
	}

	fseek(fp,0,SEEK_END);

	filesize = ftell(fp);
	str=(char *)malloc(filesize);
	str[0]=0;

	rewind(fp);
	while((fgets(txt,1000,fp))!=NULL){
		strcat(str,txt);
	}
	fclose(fp);
	return str;
}
