
// Program Description/Support /////////////////////////////////////
/*
Only works for linux instead of windows codeblock

default work space:   cd mnt/c/work/cf/

use command to complie:

gcc -pthread -o sim main.c
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
#include <time.h>
#include "pthread.h"
#include "unistd.h"

typedef struct __DATA
{
    int     proc;
    int     data1;
    int     data2;
    double  vdouble;
    char    *words;
    // char    *word2;
}DATA;

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
#define ElementType1 int //store type
#define ElementType2 char //store type
#define MAXSIZE 100 //max store size
#define ERROR -99 //ElementType for error notation


//
// Class Definitions //////////////////////////////////////////////
//

//
// Free Function Prototypes ///////////////////////////////////////
//

int *getconf(char *fileName );
char *getfileall(char *fname);

char *MyStrCpy(char *dest,const char *scr);
char *remove_space(char *str2, const char *str1);
int printConf(char *fname);

typedef struct {
    ElementType1 data[MAXSIZE];
    ElementType2 *name[MAXSIZE];
    int front; // start of Q
    int rear; // end of Q
    int size; //number of element
}Queue;

Queue* CreateQueue();
void DestroySequeue(Queue *q);
int IsFullQ(Queue* q);
void AddQ(Queue* q, ElementType1 item1,ElementType2 *item2);
int IsEmptyQ(Queue* q);
ElementType1 DeleteQ(Queue* q);
void PrintQueue(Queue* q);
int * readmeta2(char *fileName);
int getQv(Queue* q,int offset);
char *getQs(Queue* q,int offset);
void SimulatorTimer(int waitTime);
int checksuffix(char *fconf,char *suffix,int num);
int SimulatorTest(char *fconf,char *fmeta);
void splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);
static void _split_whole_name(const char *whole_name, char *fname, char *ext);
void* threadWait(void* param);

//
// Main Function Implementation ///////////////////////////////////
//

int main(int argc,char* argv[])
{
    char *cof = "config_1.conf";
    char *meta = "test_1a.mdf";
    
    /*
    if (argc < 2)
    {  
        printf("error!\n");
        printf("The right format should be: ./sim conffile metafile\n");
	printf("A referrence command should be: ./sim config_1.conf test_1a.mdf\n");
  
        return -1;
    }
 
    //printf("The first string of your command is:%s\n", argv[0]);
   // printf("The second string of your command is:%s\n", argv[1]);
   // printf("The third string of your command is:%s\n", argv[2]); 


    if(!checksuffix(argv[1],".conf",6))
    {
        printf("Input conf file suffix error!\n");
        printf("It should be: .conf!\n");
        return 0;
    }

    if(!checksuffix(argv[2],".mdf",5))
    {
        printf("Input meta file suffix error!\n");
        printf("It should be: .mdf!\n");
        return 0;
    }
    */
	// SimulatorTest(argv[1],argv[2]);
   SimulatorTest(cof,meta);
    return 0;
}


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

        return 1;
    }
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
void DestroySequeue(Queue *q)
{
    if (NULL != q)
    {
        free(q);
    }
//    printf("Heap Space is free\n");
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
        char *pi = c[j];
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

    }
        AddQ(q, 0,text2[1]);//when read file come to an end

        return q;

}

int getQv(Queue* q,int offset) {
    if (IsEmptyQ(q)) {
        printf("Empty Queue!\n");
        return -1;
    }
//    printf("Print out Queue:\n");
    int index = q->front;
    int i;

    index = 0+offset;


    index %= MAXSIZE;
    return q->data[index];


}

char *getQs(Queue* q,int offset) {
    if (IsEmptyQ(q)) {
        printf("Empty Queue!\n");
        return -1;
    }

    int index = q->front;
    int i;

    index = 0+offset;


    index %= MAXSIZE;

    return q->name[index];


}

void SimulatorTimer(int waitTime)//this is a ms unit wait
{
    for(int i = 0;i<waitTime;i++)
    {
        for(int j =0;j<505000;j++){}
    }

}
int SimulatorTest(char *fconf,char *fmeta)
{



 if(printConf(fconf))
     {

     }
     else return 0;

    clock_t start_t, end_t, total_t;
    start_t = clock();


    char *text4[] =
    {
        "P",
        "M",
        "I",
        "O"

     };

    char *text5[] =
    {
        "harddrive",
        "mouse",
        "printer",
        "keyboard"
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

    int i = 0;
    int j = 0;
    int k = 0;
    int proc = 0;

    int *q = readmeta2(fmeta);
    if(!q){}

    else
    {

        if(strncmp(getQs(q,i),text2[0],8)==0)
        {
            end_t = clock();
            total_t = (end_t - start_t);
            printf("%.3f - Simulator program starting\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
            ++i;
            ++proc;
        }


        if(strncmp(getQs(q,i),text3[0],8)==0)
        {
            ++i;



            if(strncmp(getQs(q,i),text3[1],8)==0)
            {
                ++i;
LOOP:
                end_t = clock();
                total_t = (end_t - start_t);
                printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);

                end_t = clock();
                total_t = (end_t - start_t);
                printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);



                while(strncmp(getQs(q,i),text3[2],8)!=0)//inside process
                {

//                     printf("i = %d\n",i);
                     for(j = 0; j<4;j++)
                    {
//                        printf("getQs(q,i) = %s\n",getQs(q,i));
                        if(strncmp(getQs(q,i),text4[j],1)==0)
                        {
                            k = j;
                        }

                    }
//                    printf("k = %d\n",k);
                   switch(k)
                    {

                        case 0:
//                                printf("This is P\n");


                                if(strstr(getQs(q,i),"run"))
                                {
//                                    printf("This is P{run}\n");
                                    end_t = clock();
                                    total_t = (end_t - start_t);
                                    printf("%.3f - Process %d: start processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);

                                    SimulatorTimer(getQv(q,i)*Conf_Info.process);

                                    end_t = clock();
                                    total_t = (end_t - start_t);
                                    printf("%.3f - Process %d: end processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);

                                }

//                            if(strncmp(getQs(q,i),text4[j],1)==0)
                                else
                                {
                                    printf("Meta file keyword input error!\n");
                                    return 0;
                                }

                            break;

                        case 1:
//                                printf("This is M\n");
                                if(strstr(getQs(q,i),"allocate"))
                                {
//                                    printf("This is M{allocate}\n");
                                    end_t = clock();
                                    total_t = (end_t - start_t);
                                    printf("%.3f - Process %d: allocating memory\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);

                                    SimulatorTimer(getQv(q,i)*Conf_Info.memory);

                                    end_t = clock();
                                    total_t = (end_t - start_t);
                                    printf("%.3f - Process %d: memory allocated at 0x00000010\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);

                                }


                                if(strstr(getQs(q,i),"block"))
                                {
//                                    printf("This is M{block}\n");

                                    end_t = clock();
                                    total_t = (end_t - start_t);
                                    printf("%.3f - Process %d: start memory blocking\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);

                                    SimulatorTimer(getQv(q,i)*Conf_Info.memory);

                                    end_t = clock();
                                    total_t = (end_t - start_t);
                                    printf("%.3f - Process %d: end memory blocking\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);



                                }

                            if(!(strstr(getQs(q,i),"allocate"))&!(strstr(getQs(q,i),"block")))
                                {
                                    printf("Meta file keyword input error!\n");
                                    return 0;
                                }

                            break;

                        case 2:
                                if(strstr(getQs(q,i),"keyboard"))
                                {

                                        pthread_t pid_1;
                                        DATA data = {0};
                                        data.proc = proc;
                                        data.data1 = getQv(q,i);
                                        data.data2 = Conf_Info.keyboard;
                                        data.vdouble = start_t;
                                        data.words = "keyboard Input";
                                        pthread_create(&pid_1, NULL, threadWait, &data);

                                        void* rtn;
                                        pthread_join(pid_1, &rtn);

                                        printf("%s\n", (char*)rtn);

                                }


                                if(strstr(getQs(q,i),"harddrive"))
                                {
                                    
                                        pthread_t pid_1;
                                        DATA data = {0};
                                        data.proc = proc;
                                        data.data1 = getQv(q,i);
                                        data.data2 = Conf_Info.hardDrive;
                                        data.vdouble = start_t;
                                        data.words = "hard drive Input";
                                        pthread_create(&pid_1, NULL, threadWait, &data);

                                        void* rtn;
                                        pthread_join(pid_1, &rtn);

                                        printf("%s\n", (char*)rtn);


                                }


                                if(strstr(getQs(q,i),"mouse"))
                                {
                                    
                                        pthread_t pid_1;
                                        DATA data = {0};
                                        data.proc = proc;
                                        data.data1 = getQv(q,i);
                                        data.data2 = Conf_Info.mouse;
                                        data.vdouble = start_t;
                                        data.words = "mouse Input";
                                        pthread_create(&pid_1, NULL, threadWait, &data);

                                        void* rtn;
                                        pthread_join(pid_1, &rtn);

                                        printf("%s\n", (char*)rtn);
                                    


                                }

                            if(!(strstr(getQs(q,i),"mouse"))&!(strstr(getQs(q,i),"harddrive"))&!(strstr(getQs(q,i),"keyboard")))
                                {
                                    printf("Meta file keyword input error!\n");
                                    return 0;
                                }


                            break;

                        case 3:


                                if(strstr(getQs(q,i),"monitor"))

                                {
                                        pthread_t pid_1;
                                        DATA data = {0};
                                        data.proc = proc;
                                        data.data1 = getQv(q,i);
                                        data.data2 = Conf_Info.monitor;
                                        data.vdouble = start_t;
                                        data.words = "monitor output";
                                        pthread_create(&pid_1, NULL, threadWait, &data);

                                        void* rtn;
                                        pthread_join(pid_1, &rtn);

                                        printf("%s\n", (char*)rtn);                                    

                                }

                                if(strstr(getQs(q,i),"printer"))
                                {
                                        pthread_t pid_1;
                                        DATA data = {0};
                                        data.proc = proc;
                                        data.data1 = getQv(q,i);
                                        data.data2 = Conf_Info.printer;
                                        data.vdouble = start_t;
                                        data.words = "printer output";
                                        pthread_create(&pid_1, NULL, threadWait, &data);

                                        void* rtn;
                                        pthread_join(pid_1, &rtn);

                                        printf("%s\n", (char*)rtn);                                         

                                }

                                if(strstr(getQs(q,i),"harddrive"))
                                {
//                                    printf("This is O{hard drive}\n");
                                        pthread_t pid_1;
                                        DATA data = {0};
                                        data.proc = proc;
                                        data.data1 = getQv(q,i);
                                        data.data2 = Conf_Info.hardDrive;
                                        data.vdouble = start_t;
                                        data.words = "hard drive output";
                                        pthread_create(&pid_1, NULL, threadWait, &data);

                                        void* rtn;
                                        pthread_join(pid_1, &rtn);

                                        printf("%s\n", (char*)rtn);        


                                }


                                if(!(strstr(getQs(q,i),"monitor"))&!(strstr(getQs(q,i),"harddrive"))&!(strstr(getQs(q,i),"printer")))
                                {
                                    printf("Meta file keyword input error!\n");
                                    return 0;
                                }

                            break;

                    }
                ++i;
                }
            }

        }
//         printf("getQs(q,i) = %s\n",getQs(q,i));
//         ++i;
//          printf("getQs(q,i) = %s\n",getQs(q,i));



         if(strncmp(getQs(q,i),text3[2],8)==0)
        {
            end_t = clock();
            total_t = (end_t - start_t);
            printf("%.3f - OS: removing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
            i++;


        }

        if(strncmp(getQs(q,i),text3[1],8)==0)
        {
//            printf("Go to loop\n");
            i++;
            ++proc;
            goto LOOP;

        }


         if(strncmp(getQs(q,i),text3[3],8)==0)
        {
            end_t = clock();
            total_t = (end_t - start_t);
//            printf("%.3f - OS: removing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
            i++;

        }

        if(strncmp(getQs(q,i),text2[1],8)==0)
        {
            end_t = clock();
            total_t = (end_t - start_t);
            printf("%.3f - Simulator program ending\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
            i++;
        }
    }


     DestroySequeue(q);
}


int checksuffix(char *fconf,char *suffix,int num)
{
   char drive[255];
   char dir[255];
   char fname[255];
   char ext[10];
    splitpath( fconf, drive, dir, fname, ext );
//    printf( "  Ext: %s\n", ext );
    if(!strncmp(ext,suffix,num))   return 1;
    else return 0;

}



void splitpath(const char *path, char *drive, char *dir, char *fname, char *ext)
{
	char *p_whole_name;

	drive[0] = '\0';
	if (NULL == path)
	{
		dir[0] = '\0';
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	if ('/' == path[strlen(path)])
	{
		strcpy(dir, path);
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	p_whole_name = rindex(path, '/');
	if (NULL != p_whole_name)
	{
		p_whole_name++;
		_split_whole_name(p_whole_name, fname, ext);

		snprintf(dir, p_whole_name - path, "%s", path);
	}
	else
	{
		_split_whole_name(path, fname, ext);
		dir[0] = '\0';
	}
}

static void _split_whole_name(const char *whole_name, char *fname, char *ext)
{
	char *p_ext;

	p_ext = rindex(whole_name, '.');
	if (NULL != p_ext)
	{
		strcpy(ext, p_ext);
		snprintf(fname, p_ext - whole_name + 1, "%s", whole_name);
	}
	else
	{
		ext[0] = '\0';
		strcpy(fname, whole_name);
	}
}

void* threadWait(void* param)
{
    DATA* data = (DATA*)param;
    clock_t  end_t, total_t;

    // printf("param1: %d, param2: %d, param3: %f\n",
            // data->data1, data->data2,data->vdouble);
    // printf("word: %s\n",data->words);        
    end_t = clock();
    total_t = (end_t - (data->vdouble));
    printf("%.3f - Process %d: start %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->proc,data->words);

    SimulatorTimer((data->data1)*(data->data2));

    end_t = clock();
    total_t = (end_t - (data->vdouble));
    printf("%.3f - Process %d: end %s",(total_t*0.1*10)/CLOCKS_PER_SEC,data->proc,data->words);            

	return (void*)" ";

}
