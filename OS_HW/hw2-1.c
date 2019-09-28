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
*          Initial development of SIM02
*
* @note None
*/
// Program Description/Support /////////////////////////////////////
/*
To do:
Thread Usage
Timer
Readme
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
#include <setjmp.h>



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

//for error handling
#define TRY do { jmp_buf ex_buf__; switch( setjmp(ex_buf__) ) { case 0: while(1) {
#define CATCH(x) break; case x:
#define FINALLY break; } default: {
#define ETRY break; } } }while(0);
#define THROW(x) longjmp(ex_buf__, x)

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

char *MyStrCpy(char *dest,const char *scr)
{
    while (*scr!='\0')
    {
        *(dest++)=*(scr++);
    }
    *dest='\0';
    return dest;
}

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
        return 1;
    }



}



#define ElementType1 int //store type
#define ElementType2 char //store type
#define MAXSIZE 100 //max store size
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

char *strreplace2(const char *src, const char *from, const char *to)
{
   size_t size    = strlen(src) + 1;
   size_t fromlen = strlen(from);
   size_t tolen   = strlen(to);
   char *value = malloc(size);
   char *dst = value;
   if ( value != NULL )
   {
      for ( ;; )
      {
         const char *match = strstr(src, from);
         if ( match != NULL )
         {
            size_t count = match - src;
            char *temp;
            size += tolen - fromlen;
            temp = realloc(value, size);
            if ( temp == NULL )
            {
               free(value);
               return NULL;
            }
            dst = temp + (dst - value);
            value = temp;
            memmove(dst, src, count);
            src += count;
            dst += count;
            memmove(dst, to, tolen);
            src += fromlen;
            dst += tolen;
         }
         else /* No match found. */
         {
            strcpy(dst, src);
            break;
         }
      }
   }
   return value;
}

int * readmeta2(char *fileName)
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

        "P{run}",
        "M{allocate}",
        "O{monitor}",
        "I{harddrive}",
        "I{mouse}",
        "O{printer}",
        "M{block}",
        "I{keyboard}",
        "O{harddrive}"

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

    Queue* q = CreateQueue();
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
                AddQ(q, 0,text2[i]);
            }

        }
        if(strstr(res[i],text3[3]))
        {
            if(!strstr(res[i+1],text2[1]))
            {
                printf("In line %d,It should have those inforamtion:\n%s\n",i+1+1,text2[1]);
                printf("please check the input Meta file\n");
                return NULL;
            }
        line_num = i+1;
//        printf("line_num is %d\n",line_num);
        }
        // printf("i=%d %s\n",i,res[i]);
     }
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

//                printf("before: %s\n",tmp);
//                printf("after: %s\n",c[j]);
                tmp = strtok(NULL, delim);
                j++;
            }
            k=j;
//            printf("k = %d\n\n",k);

    }

    int num = 0;
    char str[30];

    for(j=0;j<k;j++)
    {
        char *pj = c[j];
        char *pi = NULL;
        pi=strreplace2(pj,"}","} ");
        //                  sscanf(pi,"%s %d", &str,&num );
        //                printf("value = %d\t str = %s\n",num,str);
        //                AddQ(q, num,str);


        while (*pi)
        { // While there are more characters to process...

            if ( isdigit(*pi) || ( (*pi=='-'||*pi=='+') && isdigit(*(pi+1)) ))
            {

                // Found a number
                int val = strtol(pi, &pi, 10); // Read number

        //                printf("C[%d] = %s %ld\n",j,c[j],val); // and print it.
                AddQ(q, val,c[j]);
            }
            else
            {
                // Otherwise, move on to the next character.
                pi++;

            }
        }



//        printf("C[%d] = %s   value = %d\n",j,buf1,digit2);
        if(strncmp(c[j],"P{run}",5)==0|strncmp(c[j],"M{allocate}",10)==0|strncmp(c[j],"O{monitor}",10)==0
       |strncmp(c[j],"I{hard",6)==0|strncmp(c[j],"I{mouse}",8)==0|strncmp(c[j],"O{printer}",10)==0
       |strncmp(c[j],"M{block}",6)==0|strncmp(c[j],"I{keyboard}",10)==0|strncmp(c[j],"O{hard",6)==0
       |strncmp(c[j],"S{begin}",8)==0|strncmp(c[j],"A{begin}",8)==0|strncmp(c[j],"S{finish}",9)==0
       |strncmp(c[j],"A{finish}",9)==0)
        {

        }
        else
        {

            error_flag =1;

        }
    }
    AddQ(q, 0,text2[1]);
            if(error_flag)
            {

                printf("There is input error, please check input file!\n");
                return NULL;
            }
            else
            {



//                printf("Meta file error check done.\n");
            }

        return q;

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
    int i2 = 0;
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
int getQv(Queue* q,int offset) {
    if (IsEmptyQ(q)) {
        printf("Empty Queue!\n");
        return;
    }
    printf("Print out Queue:\n");
    int index = q->front;
    int i;

    index = 0+offset;


    index %= MAXSIZE;
    return q->data[index];

//    *str = q->name[index];
//    printf("%d\t%s\n", q->data[index],q->name[index]);
}

char *getQs(Queue* q,int offset) {
    if (IsEmptyQ(q)) {
        printf("Empty Queue!\n");
        return;
    }
//    printf("Print out Queue:\n");
    int index = q->front;
    int i;

    index = 0+offset;


    index %= MAXSIZE;

    return q->name[index];
//    printf("%d\t%s\n", q->data[index],q->name[index]);

}
//
// Main Function Implementation ///////////////////////////////////
//

int main(int argc,char* argv[])
{

    // if(printConf("config_1.conf"))
    // {

    // }
    // else return 0;


    char *text1[] = {

        "P{run}",
        "M{allocate}",
        "O{monitor}",
        "I{harddrive}",
        "I{mouse}",
        "O{printer}",
        "M{block}",
        "I{keyboard}",
        "O{harddrive}"
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

    int i=0;
//    char str[20];
    int *q = readmeta2("test_1a.mdf");
    if(!q){}
    else{

        if(strncmp(getQs(q,i),text2[0],8)==0)
        {
            printf("- Simulator program starting.\n");
            i++;
        }
        if(strncmp(getQs(q,i),text3[0],8)==0)
        {
            printf("- OS: preparing process 1.\n");
            i++;
        }
        if(strncmp(getQs(q,i),text3[1],8)==0)
        {
            printf("- OS: starting process 1.\n");
            i++;
        }









    }

    // int *q= readmeta("test_1a.mdf");

    // cal(q);

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
     char *text[] =
     {
        "Start Simulator Configuration File",
        "Version/Phase:",
        "File Path: Test_1a.mdf",
        "Monitor display time {msec}:",
        "Processor cycle time {msec}:",
        "Mouse cycle time {msec}:",
        "Hard drive cycle time {msec}:",
        "Keyboard cycle time {msec}:",
        "Memory cycle time {msec}:",
        "Printer cycle time {msec}:",
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
                {	//because this file only the 4th line have one more space
                    if(j==3)sscanf(res[i],"%s %s %s %s %s %d ", buf1,buf2,buf3,buf4,buf5,&digit );
                    else sscanf(res[i],"%s %s %s %s %d ", buf1,buf2,buf3,buf4,&digit );
                    temp[j] =digit;
                }

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
