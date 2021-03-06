//Makefile
//    all: main.c
//	gcc -w -pthread -o sim main.c
// Program Header Information ////////////////////////////////////////
/**
* @file main.c
*
* @brief program for SIM04
* 
* @details Simulation of a simle, one-program OS simulator
*
* @version 1.00
*          C.S. Student (14 Nov 2019)
*          Initial development of SIM04
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
    #include <time.h>
	#include <semaphore.h>
    #include "pthread.h"
    #include "unistd.h"
	
//
// Global Constant Definitions ////////////////////////////////////
//
    #define c_num 13
    #define MAX_LINE 50
    #define  option_num 9
    #define ElementType1 double //store type
    #define ElementType2 char //store type
	#define ElementType3 unsigned int //store type
    #define MAXSIZE 100 //max store size
    #define ERROR -99 //ElementType for error notation
	unsigned int mem_call = 0 ; //to get an allocated initial address
	
	static sem_t s; 		//to define one signal variable 
	int UsedPrinters=0;
	int UsedHD=0;
	int pp_num =0;
//
// Class Definitions //////////////////////////////////////////////
//
    typedef struct __DATA
    {
        int     proc;
        int     data1;
        int     data2;
        double  vdouble;
        char    *words;
        long    t1; //store start time for a I/O operation 
        long    t2; //store end time for a I/O operation 
        long    it1;//pass inital time in sec 
        long    it2;//pass inital time in usec 		
		
		
        // char    *word2;
    }DATA;

    struct _pcb{
        int pid;    //when there is a new process pid+1
        int state; // 1：start 2: ready：3: running  4: waiting  5： Exit

    }PCB;

    struct conf
      {
       // struct that records Config information read from Config file
	   int p_num;
	   int scheducode;
       int process;
       int monitor;
       int mouse;
       int hardDrive;
       int printer;
       int keyboard;
       int memory;
	   int sysmem;
	   int memsize;
	   int printerq;
	   int harddriveq;
    //   bool logbothtrue;
    //   char dataFile[15];
    //   char outputFile[15];
      }Conf_Info;
      
    typedef struct {
        ElementType1 data[MAXSIZE];
        ElementType2 *name[MAXSIZE];
		ElementType3 data2[MAXSIZE];
        int front; // start of Q
        int rear; // end of Q
        int size; //number of element
    }Queue;


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
    Queue* CreateQueue();
    void DestroySequeue(Queue *q);
    int IsFullQ(Queue* q);
    void AddQ(Queue* q, ElementType1 item1,ElementType2 *item2,ElementType3 item3);
    int IsEmptyQ(Queue* q);
    ElementType1 DeleteQ(Queue* q);
    void PrintQueue(Queue* q);
    int * readmeta2(char *fileName);
    ElementType1 getQv(Queue* q,int offset);
    ElementType2 *getQs(Queue* q,int offset);
	ElementType3 getQv2(Queue* q,int offset);
	
    void SimulatorTimer(int waitTime);
    int checksuffix(char *fconf,char *suffix,int num);
    int SimulatorTest(char *fconf,char *fmeta);
    void splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);
    static void _split_whole_name(const char *whole_name, char *fname, char *ext);
    void* threadWait(void* param);
    void Printtime(Queue* q);
    void writeF(Queue* q);
	int allocateHardDrive();
	int allocatePrinter();
	unsigned int allocateMemory();
	void printstructure();
	char *crush(char*name,int direction);
	void SplitStrByStr( char* sources, char str, char arry[10][20], int* count);
	int SJF_op(char* pStr);
	int PS_op(char* pStr);
	void sort(int*aa, int *a, int l);
	void sort2(int*aa, int *a, int l);
	int delete_sub_str(const char *str, const char *sub_str, char *result_str);
	void headle_SFJ(char *name);
	int wr1D(int a[100]);
	void readmeta(char *fileName);
	int * checkmeta(char *fileName);
	void headle_FIFO(char *name);
	void headle_PS(char *name);
//
// Main Function Implementation ///////////////////////////////////
//
	
    int main(int argc,char* argv[])
    {
        char *cof = "config_2.conf";
        char *meta = "test_1c.mdf";
        /*
        if (argc < 2)
        {  
            printf("error!\n");
            printf("The right format should be: ./sim conffile\n");
            printf("A referrence command should be: ./sim config_1.conf\n");
            return -1;
        }
     
        // suffix check conf file
        if(!checksuffix(argv[1],".conf",6))
        {
            printf("Input conf file suffix error!\n");
            printf("It should be: .conf!\n");
            return 0;
        }
        // suffix check meta file
        if(!checksuffix(meta,".mdf",5))
        {
            printf("Input meta file suffix error!\n");
            printf("It should be: .mdf!\n");
            return 0;
        }
*/

		// headle_SFJ(name4);
		
		
		SimulatorTest(cof,meta);
        // SimulatorTest(argv[1],argv[2]); 
       // SimulatorTest(argv[1],meta);
        return 0;
    }

//
// Free Function Implementation ///////////////////////////////////
/**
* @brief Function reads Config file
*
* @details Function reads Config file and record to Config table
*
* @pre char* fileName contains the name of Config file
*
* @pre struct* Config contains the Config table
*
* @post if the Config file doesn't exist, end the program
*
* @post all Config information recorded in Config table
*
* @return 0 means file reading error; return 1 means finish reading.
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


        static int temp[c_num];
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
         char *cof[c_num] = {"Processor Quantum Number","CPU Scheduling Code","Monitor display","Processor cycle",
							"Mouse cycle","Hard drive cycle","Keyboard cycle",
							"Memory cycle","Printer cycle","System memory","Memory block",
							"Printer quantity","Hard drive quantity"};
         char *text[] =
         {
            "Start Simulator Configuration File",
            "Version/Phase:",
            "File Path: Test_4a.mdf",
			"Processor Quantum Number:",
			"CPU Scheduling Code:",
            "Monitor display time {msec}:",
            "Processor cycle time {msec}:",
            "Mouse cycle time {msec}:",
            "Hard drive cycle time {msec}:",
            "Keyboard cycle time {msec}:",
            "Memory cycle time {msec}:",
            "Printer cycle time {msec}:",
			"System memory {kbytes}:",
			"Memory block size {kbytes}:",
			"Printer quantity:",
			"Hard drive quantity:",
            "Log:",
            "Log File Path:",
            "End Simulator Configuration File"
         };

			// printf("p = %d\n",p);
		
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
                    {	
						
						if(j ==1)
						{
							sscanf(res[i],"%s %s %s %s", buf1,buf2,buf3,buf4);
							// printf("%s\n", buf4);
							if(strcmp(buf4, "SJF") == 0)
							{
								// printf("This is SJF\n");
								digit = 0;
							}
							else if(strcmp(buf4, "FIFO") == 0)
							{
								// printf("This is FIFO\n");
								digit = 1;
							}
							else if(strcmp(buf4, "PS") == 0)
							{
								// printf("This is PS\n");
								digit = 2;
							}
							else 
							{
								printf("Input CPU Scheduling Code error!\n");
								return NULL;
							}
						}
                        if(j==5)sscanf(res[i],"%s %s %s %s %s %d ", buf1,buf2,buf3,buf4,buf5,&digit );
						if(j==0|j==9|j ==12)sscanf(res[i],"%s %s %s %d ", buf1,buf2,buf3,&digit );
						if(j==11)sscanf(res[i],"%s %s  %d ", buf1,buf2,&digit );
						
                        else sscanf(res[i],"%s %s %s %s %d ", buf1,buf2,buf3,buf4,&digit );
                        temp[j] =digit;
                    }

                }
             }
         }
		 // for(int p2 = 0; p2<c_num;p2++)
		 // {
		 // printf("%d\t",temp[p2]);
		 // }
		  printf("\n");
         return temp;

    }

/**
* @brief Function print out conf info. table
*
* @return 0 means file reading error; return 1 means finish reading.
*
*/
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
			
			ptr1-> p_num = 		 *(p+0);
			ptr1-> scheducode =  *(p+1);
            ptr1-> process =     *(p+0+2);
            ptr1-> monitor =     *(p+1+2);
            ptr1-> mouse =       *(p+2+2);
            ptr1-> hardDrive =   *(p+3+2);
            ptr1-> printer =     *(p+4+2);
            ptr1-> keyboard =    *(p+5+2);
            ptr1-> memory =      *(p+6+2);
			
			ptr1-> sysmem =		*(p+7+2);
			ptr1-> memsize =	*(p+8+2);
			ptr1-> printerq =	*(p+9+2);
			ptr1-> harddriveq=	*(p+10+2);
			// printf("Now print\n");
			// for (int i=0;i<13;i++)
			// {
				// printf("%d\t",*(p+i));
			// }
			
			
            return 1;
        }
    }
/**
* 
* @ To check if the reading result is correct
*
*/	
	void printstructure()
	{
		
		printf("Processor Quantum Number: %d\n",Conf_Info.p_num); 
		printf("CPU Scheduling Code: %d\n",Conf_Info.scheducode); 
		printf("Monitor display time {msec}: %d\n",Conf_Info.process); 
		printf("Processor cycle time {msec}: %d\n",Conf_Info.monitor); 
		printf("Mouse cycle time {msec}:%d\n",Conf_Info.mouse); 
		printf("Hard drive cycle time {msec}: %d\n",Conf_Info.hardDrive); 
		printf("Keyboard cycle time {msec}: %d\n",Conf_Info.printer); 
		printf("Memory cycle time {msec}: %d\n",Conf_Info.keyboard); 
		printf("Printer cycle time {msec}:%d\n",Conf_Info.memory); 
		printf("System memory {kbytes}: %d\n",Conf_Info.sysmem); 
		printf("Memory block size {kbytes}: %d\n",Conf_Info.memsize); 
		printf("Printer quantity: %d\n",Conf_Info.printerq); 
		printf("Hard drive quantity: %d\n",Conf_Info.harddriveq); 
		
	}
/**
* @brief Function create a Queue  
*
* @return head of address of q
*
*/    
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
    
/**
* @brief Function Destroy a Queue to release the memory  
*/       
    
    void DestroySequeue(Queue *q)
    {
        if (NULL != q)
        {
            free(q);
        }
    //    printf("Heap Space is free\n");
    }
    
/**
* @brief Function to check if a Queue is full.
*
* @return 0 means Queue is not full; return 1 means Queue is full.
*
*/
    int IsFullQ(Queue* q) {
        return (q->size == MAXSIZE);
    }
/**
* @brief Function add data into the Queue
*
* @pre item1 is a number, item2 is a string
*
*/     
    void AddQ(Queue* q, ElementType1 item1,ElementType2 *item2,ElementType3 item3  ) {
        if (IsFullQ(q)) {
            printf("Queue is full!\n");
            return;
        }
        q->rear++;
        q->rear %= MAXSIZE;
        q->size++;
        q->data[q->rear] = item1;
		q->data2[q->rear] = item3;
        q->name[q->rear] = item2;
    }
/**
* @brief Function to check if a Queue is Empty.
*
* @return 0 means Queue is not Empty; return 1 means Queue is Empty.
*
*/
    int IsEmptyQ(Queue* q) {
        return (q->size == 0);
    }
    
/**
* @brief Function to remove one cell in a Queue.
*/
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
/**
* @brief Function printout all the info. in a Queue.
*/
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
			printf("%ld\t  %s\t %d\n", q->data[index],q->name[index],q->data2[index]);
            // printf("%ld\t  %s\t 0x%08x\n", q->data[index],q->name[index],q->data2[index]);
        }
        printf("\n");
    }

/**
* @brief Function to get the info. from a Queue
*
* @pre Queue* q is the address for queue, offset is the Serial number of cell
*
* @return a value from a queue based on its offset
*
*/
    ElementType1 getQv(Queue* q,int offset) {
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
	
	ElementType3 getQv2(Queue* q,int offset) {
        if (IsEmptyQ(q)) {
            printf("Empty Queue!\n");
            return -1;
        }
    //    printf("Print out Queue:\n");
        int index = q->front;
        int i;

        index = 0+offset;


        index %= MAXSIZE;
        return q->data2[index];


    }
/**
* @brief Function to get the info. from a Queue
*
* @pre Queue* q is the address for queue, offset is the Serial number of cell
*
* @return a string from a queue based on its offset
*
*/
    ElementType2 *getQs(Queue* q,int offset) {
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
	
	
	
/**
* @brief Function to read the info. from meta file
*
* The info. are splited by ";", and seperate the number and string stored into the queue
*
* @return the address for the queue
*
*/



    int *checkmeta(char *fileName)
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
			"S",
			"A",
            "P",
            "M",
            "O",
            "I"
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
		 
        // Queue* q = CreateQueue();
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
                    // AddQ(q, 0,text2[i],0);
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
		 
		 // Queue* q = CreateQueue();
		 
		 
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
                   // printf("before: %s\n",tmp);
                   // printf("after: %s\n",c[j]);
                    tmp = strtok(NULL, delim);
                    j++;
                }
                k=j;
               // printf("k = %d\n\n",k);

        }

        int num = 0;
        char str[30];

        for(j=0;j<k;j++)
        {
			// printf("C[%d] = %s \n",j,c[j]);
			if (strncmp(c[j],text1[0], 1) == 0)			//when it is S
			{
				if((strncmp(c[j],"S{begin}", 8) == 0)||(strncmp(c[j],"S{finish}", 9) == 0)){}
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be S{begin}or S{finish}.\n");
					return NULL;
				}
			}
			else if (strncmp(c[j],text1[1], 1) == 0)	//when it is A
			{
				if((strncmp(c[j],"A{begin}", 8) == 0)||(strncmp(c[j],"A{finish}", 9) == 0)){}
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be A{begin}or A{finish}.\n");
					return NULL;
				}
			}						
			else if (strncmp(c[j],text1[2], 1) == 0)	//when it is P
			{
				if(strncmp(c[j],"P{run}", strlen("P{run}")) == 0){}
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be P{run}.\n");
					return NULL;
				}
			}							
			else if (strncmp(c[j],text1[3], 1) == 0)//when it is M
			{
				if((strncmp(c[j],"M{allocate}", strlen("M{allocate}")) == 0)||(strncmp(c[j],"M{block}", strlen("M{block}")) == 0)){}	
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be M{allocate} or M{block}.\n");
					return NULL;
				}
			}
			else if (strncmp(c[j],text1[4], 1) == 0)	//when it is O
			{
				if((strncmp(c[j],"O{monitor}", strlen("O{monitor}")) == 0)||(strncmp(c[j],"O{printer}", strlen("O{printer}")) == 0)||(strncmp(c[j],"O{harddrive}",strlen("O{harddrive}")) == 0)){}	
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be O{monitor},O{printer} or O{hard drive}.\n");
					return NULL;
				}
			}							
			else if (strncmp(c[j],text1[5], 1) == 0)	//when it is I
			{
				if((strncmp(c[j],"I{harddrive}", strlen("I{harddrive}")) == 0)||(strncmp(c[j],"I{mouse}", strlen("I{mouse}")))||(strncmp(c[j],"I{keyboard}", strlen("I{keyboard}")) == 0)){}	
				else 
				{
					printf("Please check the key word in Meta file.\n");
					printf("It should be I{hard drive},I{mouse} or I{keyboard}.\n");
					return NULL;
				}
			}							

        }

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
                    AddQ(q, 0,text2[i],0);
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
                    AddQ(q, val,c[j],0);
                }
                else
                {
                    // Otherwise, move on to the next character.
                    pi++;

                }
            }

        }
            AddQ(q, 0,text2[1],0);//when read file come to an end

            return q;

    }

/**
* @brief Function to delay
*
* @pre waitTime is a ms unit for simulation.
*
* @No return 
*
*/

    void SimulatorTimer(int waitTime)//this is a ms unit wait
    {

		usleep(1000*waitTime);
    }
	

	

	
/**
* @brief Function the main part for simulation
*
* @pre char *fconf means input conf file,char *fmeta means input meta file
*
* @post it simulate the OS operation and get the start and end time for each process or thread
*
* and store those info into 2nd queue for future print out and generating the output file.
*
* @return 0 means there is some error in keywords of conf or meta files.
*
*/
    int SimulatorTest(char *fconf,char *fmeta)
    {
     if(printConf(fconf))
         {

         }
         else return 0;
		// printstructure();
        clock_t start_t, end_t;
		clock_t total_t;
        // start_t = clock();

		
			
		float time_use=0;
		struct timeval start;
		struct timeval end;//struct timezone tz;
		gettimeofday(&start,NULL); //gettimeofday(&start,&tz);


		   

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
        struct _pcb *p=(struct _pcb *)malloc(sizeof(struct _pcb));
		
		if(checkmeta(fmeta))
		readmeta(fmeta);
		else
		{ 
			return 0;

		}
		
        Queue* q2 = CreateQueue();
        int *q = readmeta2("sfj.txt");
		
		sem_init(&s, 0, 1);
		pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_lock( &count_mutex ); 	
        if(!q){}

        else
        {

            if(strncmp(getQs(q,i),text2[0],8)==0)
            {
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
				total_t = time_use;
                // printf("%.3f - Simulator program starting\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
                ++i;
                ++proc;
                
                p->state = 1;
                p->pid =proc;
                AddQ(q2, total_t,"Simulator program starting",0);
                 
            }


            if(strncmp(getQs(q,i),text3[0],8)==0)
            {
                ++i;
                


                if(strncmp(getQs(q,i),text3[1],8)==0)
                {
                    ++i;
    LOOP:
                    p->state = 2;
                    p->pid =proc;
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
					total_t = time_use;
                    // printf("%.3f - OS: preparing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
                    AddQ(q2, total_t,"OS: preparing process",0);
					gettimeofday(&end,NULL);
					time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
					total_t = time_use;
                    // printf("%.3f - OS: starting process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
                    AddQ(q2, total_t,"OS: starting process",0);


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
										gettimeofday(&end,NULL);
										time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
										total_t = time_use;
										p->state = 3;
                                        AddQ(q2, total_t,"start processing action",0);
                                        SimulatorTimer(getQv(q,i)*Conf_Info.process);

										gettimeofday(&end,NULL);
										time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
										total_t = time_use;
										p->state = 2;
                                        // printf("%.3f - Process %d: end processing action\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
                                        AddQ(q2, total_t,"end processing action",0);
                                    }

    //                            if(strncmp(getQs(q,i),text4[j],1)==0)
                                    // else
                                    // {
                                        // printf("Meta file keyword input error!\n");
                                        // return 0;
                                    // }

                                break;

                            case 1:
    //                                printf("This is M\n");
                                    if(strstr(getQs(q,i),"allocate"))
                                    {
    //                                    printf("This is M{allocate}\n");
										gettimeofday(&end,NULL);
										time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
										total_t = time_use;
                                        // printf("%.3f - Process %d: allocating memory\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
                                        AddQ(q2, total_t,"allocating memory",0);
                                        SimulatorTimer(getQv(q,i)*Conf_Info.memory);
										p->state = 3;
										gettimeofday(&end,NULL);
										time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
										total_t = time_use;
                                        // printf("%.3f - Process %d: memory allocated at 0x00000010\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
										p->state = 2;
								
										AddQ(q2, total_t,"memory allocated at",allocateMemory());
		
                                        
                                    }


									
									
                                    if(strstr(getQs(q,i),"block"))
                                    {
    //                                    printf("This is M{block}\n");

										gettimeofday(&end,NULL);
										time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
										total_t = time_use;
										p->state = 3;
                                        // printf("%.3f - Process %d: start memory blocking\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
                                        AddQ(q2, total_t,"start memory blocking",0);
                                        SimulatorTimer(getQv(q,i)*Conf_Info.memory);
										p->state = 2;
										gettimeofday(&end,NULL);
										time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
										total_t = time_use;
                                        // printf("%.3f - Process %d: end memory blocking\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
                                        AddQ(q2, total_t,"end memory blocking",0);


                                    }

                                // if(!(strstr(getQs(q,i),"allocate"))&!(strstr(getQs(q,i),"block")))
                                    // {
                                        // printf("Meta file keyword input error!\n");
                                        // return 0;
                                    // }

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
											gettimeofday(&end,NULL);
											// gettimeofday(&end,NULL);
											data.it1 = start.tv_sec;
                                            data.it2 = start.tv_usec;
											p->state = 3;
                                            pthread_create(&pid_1, NULL, threadWait, &data);

                                            void* rtn;
                                            pthread_join(pid_1, &rtn);
                                            // printf("%d  %d\n", data.t1, data.t2);  
                                            p->state = 2;
                                            AddQ(q2, data.t1,"start keyboard Input",0);
                                            AddQ(q2, data.t2,"end keyboard Input",0);
                                            printf("%s\n", (char*)rtn);
                                            

                                    }


                                    if(strstr(getQs(q,i),"harddrive"))
                                    {
                                        
                                            pthread_t pid_1;
                                            DATA data = {0};
                                            data.proc = proc;
                                            data.data1 = getQv(q,i);
                                            data.data2 = Conf_Info.hardDrive;
											gettimeofday(&end,NULL);
											// gettimeofday(&end,NULL);
											data.it1 = start.tv_sec;
                                            data.it2 = start.tv_usec;
                                            data.vdouble = start_t;
                                            data.words = "hard drive Input";
											sem_wait(&s);
											p->state = 3;
                                            pthread_create(&pid_1, NULL, threadWait, &data);

                                            void* rtn;
                                            pthread_join(pid_1, &rtn);
                                            sem_post(&s);
											p->state = 2;
											AddQ(q2, data.t1,"start hard drive input",0);
                                            // AddQ(q2, data.t1,"start hard drive input on HDD",allocateHardDrive()-1);
                                            AddQ(q2, data.t2,"end hard drive input",0);
                                            printf("%s\n", (char*)rtn);
                                    }


                                    if(strstr(getQs(q,i),"mouse"))
                                    {
                                        
                                            pthread_t pid_1;
                                            DATA data = {0};
                                            data.proc = proc;
                                            data.data1 = getQv(q,i);
                                            data.data2 = Conf_Info.mouse;
											gettimeofday(&end,NULL);
											// gettimeofday(&end,NULL);
											data.it1 = start.tv_sec;
                                            data.it2 = start.tv_usec;
                                            data.vdouble = start_t;
                                            data.words = "mouse Input";
											p->state = 3;
                                            pthread_create(&pid_1, NULL, threadWait, &data);

                                            void* rtn;
                                            pthread_join(pid_1, &rtn);
											p->state = 2;
                                            AddQ(q2, data.t1,"start mouse Input",0);
                                            AddQ(q2, data.t2,"end mouse Input",0);
                                            printf("%s\n", (char*)rtn);
                                        
                                    }

                                // if(!(strstr(getQs(q,i),"mouse"))&!(strstr(getQs(q,i),"harddrive"))&!(strstr(getQs(q,i),"keyboard")))
                                    // {
                                        // printf("Meta file keyword input error!\n");
                                        // return 0;
                                    // }


                                break;

                            case 3:
                                    if(strstr(getQs(q,i),"monitor"))
                                    {
                                            pthread_t pid_1;
                                            DATA data = {0};
                                            data.proc = proc;
                                            data.data1 = getQv(q,i);
                                            data.data2 = Conf_Info.monitor;
											gettimeofday(&end,NULL);
											// gettimeofday(&end,NULL);
											data.it1 = start.tv_sec;
                                            data.it2 = start.tv_usec;
                                            data.vdouble = start_t;
                                            data.words = "monitor output";
											p->state = 3;
                                            pthread_create(&pid_1, NULL, threadWait, &data);

                                            void* rtn;
                                            pthread_join(pid_1, &rtn);
                                            p->state = 2;
                                            AddQ(q2, data.t1,"start monitor output",0);
                                            AddQ(q2, data.t2,"end monitor output",0);                             
                                            printf("%s\n", (char*)rtn);                                    

                                    }

                                    if(strstr(getQs(q,i),"printer"))
                                    {
                                            pthread_t pid_1;
                                            DATA data = {0};
                                            data.proc = proc;
                                            data.data1 = getQv(q,i);
                                            data.data2 = Conf_Info.printer;
											// gettimeofday(&end,NULL);
											data.it1 = start.tv_sec;
                                            data.it2 = start.tv_usec;
                                            data.vdouble = start_t;
                                            data.words = "printer output";
											sem_wait(&s);
											p->state = 3;
                                            pthread_create(&pid_1, NULL, threadWait, &data);

                                            void* rtn;
                                            pthread_join(pid_1, &rtn);
											sem_post(&s);
											p->state = 2;
											AddQ(q2, data.t1,"start printer output ",0);
                                            // AddQ(q2, data.t1,"start printer output on PRIN",allocatePrinter()-1);
                                            AddQ(q2, data.t2,"end printer output",0);
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
											// gettimeofday(&end,NULL);
											data.it1 = start.tv_sec;
                                            data.it2 = start.tv_usec;
                                            data.vdouble = start_t;
                                            data.words = "hard drive output";
											
											p->state = 3;
											sem_wait(&s);
                                            pthread_create(&pid_1, NULL, threadWait, &data);

                                            void* rtn;
                                            pthread_join(pid_1, &rtn);
											sem_post(&s);
											p->state = 2;
											AddQ(q2, data.t1,"start hard drive output",0);
                                            // AddQ(q2, data.t1,"start hard drive output on HDD",allocateHardDrive()-1);
                                            AddQ(q2, data.t2,"end hard drive output",0);
                                            printf("%s\n", (char*)rtn);        

                                    }


                                    // if(!(strstr(getQs(q,i),"monitor"))&!(strstr(getQs(q,i),"harddrive"))&!(strstr(getQs(q,i),"printer")))
                                    // {
                                        // printf("Meta file keyword input error!\n");
                                        // return 0;
                                    // }

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
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
				total_t = time_use;
                // printf("%.3f - OS: removing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
                i++;
                p->state = 5;
                AddQ(q2, total_t,"OS: removing process",0);

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
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
				total_t = time_use;
				p->state = 4;
    //            printf("%.3f - OS: removing process %d\n",(total_t*0.1*10)/CLOCKS_PER_SEC,proc);
                i++;

            }

            if(strncmp(getQs(q,i),text2[1],8)==0)
            {
				gettimeofday(&end,NULL);
				time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
				total_t = time_use;
                // printf("%.3f - Simulator program ending\n",(total_t*0.1*10)/CLOCKS_PER_SEC);
                i++;
                AddQ(q2, total_t,"Simulator program ending",0);
            }
        }
		pthread_mutex_unlock( &count_mutex );
         // printf("\n\n");
         Printtime(q2);
         writeF(q2);
         DestroySequeue(q);
         DestroySequeue(q2);
    }

/**
* @brief Function to check 
*
* @pre char *fconf means input conf file,char *fmeta means input meta file
*
* @return 0 means there is some suffix error for conf or meta files.
*
*/
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

/**
* @brief Function to split the file name and get the suffix 
*/

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
		float time_use=0;
		// clock_t end_t;
        clock_t   total_t;
		struct timeval end;//struct timezone tz; //
        // printf("param1: %d, param2: %d, param3: %f\n",
                // data->data1, data->data2,data->vdouble);
        // printf("word: %s\n",data->words);        
		gettimeofday(&end,NULL);
		time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
		total_t = time_use;
        // printf("%.3f - Process %d: start %s\n",(total_t*0.1*10)/CLOCKS_PER_SEC,data->proc,data->words);
        data->t1 = total_t;
        SimulatorTimer((data->data1)*(data->data2));

		gettimeofday(&end,NULL);
		time_use=(end.tv_sec - (data->it1))*1000000+(end.tv_usec - (data->it2));
		total_t = time_use;
        // printf("%.3f - Process %d: end %s",(total_t*0.1*10)/CLOCKS_PER_SEC,data->proc,data->words);            
        data->t2 = total_t;
        return (void*)"";
    }
/**
* @brief Function to print out the simulation result in a required format based on the 2nd Queue.
*
* @No return 
*
*/
    void Printtime(Queue* q)
    {
		
		
		
		int a[100];
		int i;
		FILE *fp = fopen("2.txt","r");
		if(fp == NULL)
		{
			
		}
		for(i = 0; !feof(fp); i++)
			fscanf(fp, "%d", &a[i]);

		fclose(fp);

		
		// for(i=0; i < pp_num; i++)
			// printf("%d ", a[i]);
		// printf("\n");
	
        if (IsEmptyQ(q)) 
        {
            printf("Empty Queue!\n");

        }
        // printf("Print out Queue:\n");
        int index = q->front;
        // int i;
        int numP = -1;
        for (i = 0; i < q->size; i++) 
        {
            index++;
            index %= MAXSIZE;

            
            if(strstr(q->name[index],"preparing process"))
                {++numP;}
            

            
            if(strstr(q->name[index],"OS"))
            {
                printf("%.3f - %s process %d\n", (q->data[index])/1000000,q->name[index],a[numP]);
            }
            else
            {
                 if(strstr(q->name[index],"Simulator"))
                {
                    printf("%.3f - %s\n", (q->data[index])/1000000,q->name[index]);
                }
                else
                {
					if(strstr(q->name[index],"memory allocated at"))
					{
						// printf("%.3f - process %d: %s 0x%08x\n", (q->data[index])/1000000,a[numP],q->name[index]);
						printf("%.3f - process %d: %s 0x%08x\n", (q->data[index])/1000000,a[numP],q->name[index],q->data2[index]);
					}
					else if(strstr(q->name[index],"start hard drive"))
					{
						printf("%.3f - process %d: %s\n", (q->data[index])/1000000,a[numP],q->name[index]);
						// printf("%.3f - process %d: %s %d\n", (q->data[index])/1000000,a[numP],q->name[index],q->data2[index]);
					}
					else if(strstr(q->name[index],"start printer"))
					{
						printf("%.3f - process %d: %s\n", (q->data[index])/1000000,a[numP],q->name[index]);
						// printf("%.3f - process %d: %s %d\n", (q->data[index])/1000000,a[numP],q->name[index],q->data2[index]);
					}
					else
					{
						printf("%.3f - process %d: %s\n", (q->data[index])/1000000,a[numP],q->name[index]);
					}
                }
            }
        }
        printf("\n");
    }

/**
* @brief Function to write a txt file in a required format based on the 2nd Queue.
*
* @No return 
*
*/
    void writeF(Queue* q)
    {
	int a[100];
	int i;
	FILE *fp = fopen("2.txt","r");
	if(fp == NULL)
	{
		
	}
	for(i = 0; !feof(fp); i++)
		fscanf(fp, "%d", &a[i]);

	fclose(fp);

	
	// for(i=0; i < pp_num; i++)
		// printf("%d ", a[i]);
	// printf("\n");
	
	
	
		
    // FILE *fp = NULL;

       fp = fopen("output.txt", "w+");


        if (IsEmptyQ(q)) 
        {
            printf("Empty Queue!\n");

        }
        // printf("Print out Queue:\n");
        int index = q->front;
        // int i;
        int numP = -1;
        for (i = 0; i < q->size; i++) 
        {
            index++;
            index %= MAXSIZE;

            
            if(strstr(q->name[index],"preparing process"))
                {numP++;}
            

            
                if(strstr(q->name[index],"OS"))
            {
                fprintf(fp,"%.3f - %s process %d\n", (q->data[index])/1000000,q->name[index],a[numP]);
            }
            else
            {
                 if(strstr(q->name[index],"Simulator"))
                {
                    fprintf(fp,"%.3f - %s\n", (q->data[index])/1000000,q->name[index]);
                }
                else
                {
					if(strstr(q->name[index],"allocated at"))
					{
						// fprintf(fp,"%.3f - process %d: %s 0x%08x\n", (q->data[index])/1000000,a[numP],q->name[index]);
						fprintf(fp,"%.3f - process %d: %s 0x%08x\n", (q->data[index])/1000000,a[numP],q->name[index],q->data2[index]);
					}
					else if(strstr(q->name[index],"start hard drive"))
					{
						fprintf(fp,"%.3f - process %d: %s\n", (q->data[index])/1000000,a[numP],q->name[index]);
						// fprintf(fp,"%.3f - process %d: %s %d\n", (q->data[index])/1000000,a[numP],q->name[index],q->data2[index]);
					}
					else if(strstr(q->name[index],"start printer"))
					{
						fprintf(fp,"%.3f - process %d: %s\n", (q->data[index])/1000000,a[numP],q->name[index]);
						// fprintf(fp,"%.3f - process %d: %s %d\n", (q->data[index])/1000000,a[numP],q->name[index],q->data2[index]);
					}					
					
					
					else
					{
						fprintf(fp,"%.3f - process %d: %s\n", (q->data[index])/1000000,a[numP],q->name[index]);
					}
                }
            }
        }
       fclose(fp);
    }
/**
* @brief Function to implement a HD counter. If it value = max, then reset
*
* @ return a Hard drive Number
*
*/	
	int allocateHardDrive(){
		UsedHD++;
		if (UsedHD >Conf_Info.harddriveq){
			UsedHD=1;
			return UsedHD;
		}
		return UsedHD;
	}
/**
* @brief Function to implement a Printer counter. If it value = max, then reset
*
* @ return a Hard drive Number
*
*/	
	int allocatePrinter(){
		UsedPrinters++;
		if (UsedPrinters >Conf_Info.printerq){
			UsedPrinters=1;
			return UsedPrinters;
		}
		return UsedPrinters;
	}
	unsigned int allocateMemory()
	{
		unsigned int address;
		address = mem_call*128;
		mem_call++;
		return address;
	}
	
char *crush(char*name,int direction)
{
    char dd[500]={};
    char dd2[500]={};
    char dest[500]={};


//    printf("Before swap:\n%s\n",name);


    if(strstr(name, "A{finish}"))
    {
        char *c1=strstr(name, "A{finish}");
    //    printf("%s\n",c1);
    //
    //    printf("%ld\n",name);
    //    printf("%ld\n",c1);
        int k1 = c1 - name;

         strncpy(dd2,name,k1+11);
         strcpy(dest,name+k1);

    //    printf("%s\n",dest);


        char *c2=strstr(dest, "A{begin}");
    //    printf("%s\n",c2);
        int k2 = c2 - dest;
         strcpy(dd,dest+k2);

    //     strcpy(dd,"A{finish}");
    //
    //     strcpy(dd2,"A{finish}");

    //    printf("%s\n",dd);

    //    strncpy(dd2,name,k1+k2);
    //    printf("%s\n",dd2);
    //    strcat(dd,dd2);
    //    printf("After swap:\n%s\n",dd);
        char*s = (char*)calloc(500,sizeof(char*));
        if (s)
            {
                if(!direction)
                    strcpy(s,dd2 );
                else
                    strcpy(s,dd );

            }
        return s;
    }
    else
    {
        return 0;
    }
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

int SJF_op(char* pStr)
{
    int line =0;
    char tmpChar = ';';
    char arry[100][20];
    int num = 0 ;
    int i = 0;
    int j = 0;
    char *option[4] = {"P","M","O","I"};
    SplitStrByStr(pStr, tmpChar, arry, &line);

//    printf("operation number = %d\n", line);
    for(i = 0; i < line; i++)
    {
        for( j = 0; j < 4; j++)
        if(strstr(arry[i],option[j]))
            ++num;
    }
    return num;
}

int PS_op(char* pStr)
{
    int line =0;
    char tmpChar = ';';
    char arry[100][20];
    int num = 0 ;
    int i = 0;
    int j = 0;
    char *option[2] = {"O","I"};
    SplitStrByStr(pStr, tmpChar, arry, &line);

//    printf("operation number = %d\n", line);
    for(i = 0; i < line; i++)
    {
        for( j = 0; j < 2; j++)
        if(strstr(arry[i],option[j]))
            ++num;
    }
    return num;
}


void sort2(int*aa, int *a, int l)
{
    int i, j;
    int v;
    int temp;

    for(i = 0; i < l - 1; i ++)
        for(j = i+1; j < l; j ++)
        {
            if(a[i] < a[j])
            {
//                printf("i = %d, j =%d\n",i,j);
                temp =aa[i+1];
                aa[i+1] = aa[j+1];
                aa[j+1] = temp;

                v = a[i];
                a[i] = a[j];
                a[j] = v;
            }
        }

//    for (i=1;i<=l;i++)
//    {
//        printf("%d\t ", aa[i]);
//    }

}

void sort(int*aa, int *a, int l)
{
    int i, j;
    int v;
    int temp;

    for(i = 0; i < l - 1; i ++)
        for(j = i+1; j < l; j ++)
        {
            if(a[i] > a[j])
            {
//                printf("i = %d, j =%d\n",i,j);
                temp =aa[i+1];
                aa[i+1] = aa[j+1];
                aa[j+1] = temp;

                v = a[i];
                a[i] = a[j];
                a[j] = v;
            }
        }

//    for (i=1;i<=l;i++)
//    {
//        printf("%d\t ", aa[i]);
//    }

}


int delete_sub_str(const char *str, const char *sub_str, char *result_str)
{
    int count = 0;
    int str_len = strlen(str);
    int sub_str_len = strlen(sub_str);

    if (str == NULL)
    {
        result_str = NULL;
        return 0;
    }

    if (str_len < sub_str_len || sub_str == NULL)
    {
        while (*str != '\0')
        {
            *result_str = *str;
            str++;
            result_str++;
        }

        return 0;
    }

    while (*str != '\0')
    {
        while (*str != *sub_str && *str != '\0')
        {
            *result_str = *str;
            str++;
            result_str++;
        }

        if (strncmp(str, sub_str, sub_str_len) != 0)
        {
            *result_str = *str;
            str++;
            result_str++;
            continue;
        }
        else
        {
            count++;
            str += sub_str_len;
        }
    }

    *result_str = '\0';

    return count;
}
//int* fun(int *arr)
//{
//    /* 操作 arr[] */
//    arr[0] = 10;
//    arr[1] = 20;
//
//    return arr;
//}



void headle_FIFO(char *name)
{
    char *sub_str1 = "S{begin}0;";
    char *sub_str2 = "S{finish}0";
    char *sub_str3 = ".";
    char *str = name;
    char res[1000];

    delete_sub_str(str, sub_str1, res);
    char *str2 = res;
    delete_sub_str(str2,sub_str2, res);
    char *str3 = res;
    delete_sub_str(str3,sub_str3, res);
//    printf("%s\n", res);

    strcpy(name,res);

        int line =0;
      int i =0;
    char* pStr  = name;

    char tmpChar = '}';
    char arry[100][20];
    SplitStrByStr(pStr, tmpChar, arry, &line);

//    printf("line = %d\n", line);

    for(i = 0; i < line; i++)
    {
        if(strstr(arry[i],"A{finish"))
            ++pp_num;
    }
	char e[5000]={};
         strcpy(e,"S{begin}0;");

        strcat(e,name);

        strcat(e,"S{finish}0.");

	int aa[pp_num];
	for(i = 1;i<=pp_num;i++)
	{
		aa[i] = i;
	}
	wr1D(aa);
    FILE *fp = NULL;
   fp = fopen("sfj.txt", "w+");
   fprintf(fp,"%s\n","Start Program Meta-Data Code:");
   fprintf(fp,"%s",e);
   fprintf(fp,"\n%s\n","End Program Meta-Data Code.");
    fclose(fp);
}


void headle_PS(char *name)
{
    char *sub_str1 = "S{begin}0;";
    char *sub_str2 = "S{finish}0";
    char *sub_str3 = ".";
    char *str = name;
    char res[1000];

    delete_sub_str(str, sub_str1, res);
    char *str2 = res;
    delete_sub_str(str2,sub_str2, res);
    char *str3 = res;
    delete_sub_str(str3,sub_str3, res);
//    printf("%s\n", res);


    strcpy(name,res);

        int line =0;
      int i =0;
    char* pStr  = name;

    char tmpChar = '}';
    char arry[100][20];
    SplitStrByStr(pStr, tmpChar, arry, &line);

//    printf("line = %d\n", line);

    for(i = 0; i < line; i++)
    {
        if(strstr(arry[i],"A{finish"))
            ++pp_num;
    }

//    printf("pp_num = %d\n", pp_num);

    char c[20][500]={};
    int  d[20] ={};
    char e[5000]={};

    if(pp_num==1)
    {
         strcpy(e,"S{begin}0;");

        strcat(e,name);

        strcat(e,"S{finish}0.");
        printf("\nfinial = %s\n",e);
//        printf("%s\n\n",name);

    }


    if(pp_num==2)
    {
        strcpy(c[1],crush(name,0));
        strcpy(c[0],crush(name,1));

        // for (i =0; i<=1;i++)
        // {
           // printf("%d ", SJF_op(c[i]));
           // printf("%s\n\n",c[i]);
        // }


        strcpy(e,"S{begin}0;");


        if(PS_op(c[0])<PS_op(c[1]))
        {
            strcat(e,c[1]);
            strcat(e,c[0]);
        }
        else
        {
            strcat(e,c[0]);
            strcat(e,c[1]);
        }

        strcat(e,"S{finish}0.");
        printf("\nfinial = %s\n",e);

    }


    else if(pp_num>2)
    {
        strcpy(c[1],crush(name,0));
        strcpy(c[0],crush(name,1));

        for(i=2;i<pp_num-1;i++)
         {
//             printf("Hi\n");

            strcpy(c[i],crush(c[0],0));
            strcpy(c[0],crush(c[0],1));


//            printf("%d\n",i);
//            printf("%s\n\n",c[0]);
         }

            strcpy(c[pp_num-1],crush(c[0],0));
            strcpy(c[pp_num],crush(c[0],1));


//            printf("print out\n",i);
            for (i =1; i<=pp_num;i++)
            {
                remove_space(c[i],c[i]);
//                printf("%s\n",c[i]);
                d [i-1]= PS_op(c[i]);
//                printf("SJF[%d] = %d\n\n",i-1,d[i-1]);

            }
            int aa[pp_num+1];
            for (i=1;i<=pp_num;i++)
            {
                aa[i] =i;
            }

             sort2(aa,d, pp_num);
//             printf("After sort\n");





            strcpy(e,"S{begin}0;");
//            printf("c[%d] = %s\n\n",i, c[aa[i]]);
            for (i =1; i<=pp_num;i++)
            {
                // printf("arr[%d] = %d\n\n",i, aa[i]);
                // printf("c[%d] = %s\n\n",i, c[aa[i]]);
                strcat(e,c[aa[i]]);
            }

            strcat(e,"S{finish}0.");
        // printf("\nfinial = %s\n",e);

			wr1D(aa);
    }
    FILE *fp = NULL;
   fp = fopen("sfj.txt", "w+");
   fprintf(fp,"%s\n","Start Program Meta-Data Code:");
   fprintf(fp,"%s",e);
   fprintf(fp,"\n%s\n","End Program Meta-Data Code.");
    fclose(fp);
	
}

  


void headle_SFJ(char *name)
{
   char *sub_str1 = "S{begin}0;";
    char *sub_str2 = "S{finish}0";
    char *sub_str3 = ".";
    char *str = name;
    char res[1000];

    delete_sub_str(str, sub_str1, res);
    char *str2 = res;
    delete_sub_str(str2,sub_str2, res);
    char *str3 = res;
    delete_sub_str(str3,sub_str3, res);
//    printf("%s\n", res);


    strcpy(name,res);

        int line =0;
      int i =0;
     // printf("Before code: %s\n\n",name);



//     printf("sjf = %d\n",SJF_op(name3));
//     printf("ps = %d\n",PS_op(name3));
    char* pStr  = name;

    char tmpChar = '}';
    char arry[100][20];
    SplitStrByStr(pStr, tmpChar, arry, &line);

//    printf("line = %d\n", line);

    for(i = 0; i < line; i++)
    {
        if(strstr(arry[i],"A{finish"))
            ++pp_num;
    }

//    printf("pp_num = %d\n", pp_num);

    char c[20][500]={};
    int  d[20] ={};
    char e[5000]={};

    if(pp_num==1)
    {
         strcpy(e,"S{begin}0;");

        strcat(e,name);

        strcat(e,"S{finish}0.");
        printf("\nfinial = %s\n",e);
//        printf("%s\n\n",name);

    }


    if(pp_num==2)
    {
        strcpy(c[1],crush(name,0));
        strcpy(c[0],crush(name,1));

        // for (i =0; i<=1;i++)
        // {
           // printf("%d ", SJF_op(c[i]));
           // printf("%s\n\n",c[i]);
        // }


        strcpy(e,"S{begin}0;");


        if(SJF_op(c[0])>SJF_op(c[1]))
        {
            strcat(e,c[1]);
            strcat(e,c[0]);
        }
        else
        {
            strcat(e,c[0]);
            strcat(e,c[1]);
        }

        strcat(e,"S{finish}0.");
        printf("\nfinial = %s\n",e);

    }


    else if(pp_num>2)
    {
        strcpy(c[1],crush(name,0));
        strcpy(c[0],crush(name,1));

        for(i=2;i<pp_num-1;i++)
         {
//             printf("Hi\n");

            strcpy(c[i],crush(c[0],0));
            strcpy(c[0],crush(c[0],1));


//            printf("%d\n",i);
//            printf("%s\n\n",c[0]);
         }

            strcpy(c[pp_num-1],crush(c[0],0));
            strcpy(c[pp_num],crush(c[0],1));


//            printf("print out\n",i);
            for (i =1; i<=pp_num;i++)
            {
                remove_space(c[i],c[i]);
//                printf("%s\n",c[i]);
                d [i-1]= SJF_op(c[i]);
//                printf("SJF[%d] = %d\n\n",i-1,d[i-1]);

            }
            int aa[pp_num+1];
            for (i=1;i<=pp_num;i++)
            {
                aa[i] =i;
            }

             sort(aa,d, pp_num);
//             printf("After sort\n");





            strcpy(e,"S{begin}0;");
//            printf("c[%d] = %s\n\n",i, c[aa[i]]);
            for (i =1; i<=pp_num;i++)
            {
                // printf("arr[%d] = %d\n\n",i, aa[i]);
                // printf("c[%d] = %s\n\n",i, c[aa[i]]);
                strcat(e,c[aa[i]]);
            }

            strcat(e,"S{finish}0.");
        // printf("\nfinial = %s\n",e);

			wr1D(aa);
    }
    FILE *fp = NULL;
   fp = fopen("sfj.txt", "w+");
   fprintf(fp,"%s\n","Start Program Meta-Data Code:");
   fprintf(fp,"%s",e);
   fprintf(fp,"\n%s\n","End Program Meta-Data Code.");
    fclose(fp);
	
}
int wr1D(int a[100])
{
    FILE *fp = NULL;
   fp = fopen("2.txt", "w+");
   if(fp ==NULL) return -1;
   for(int i =1;i<=pp_num;i++)
   fprintf(fp,"%d ",a[i]);
    fclose(fp);
    return 0;
}



void readmeta(char *fileName)
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
		char name [5000];
        int p=0;    //pointer of res[]
        pFile = fopen (fileName , "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            while ( fgets (mystring , 100 , pFile) != NULL )    //read a line every time

            {
                int len = strlen(mystring);
                //if(mystring[len-1]=='\n')
                //    mystring[len-1] = '\0';
			    mystring[len] = '\0';

                char* tmp = (char*)malloc(500*sizeof(char));
                memcpy(tmp,mystring,len);//usage memcpy(dest, src, strlen(src));
                res[p++] = tmp;
                // puts (mystring);//put string every time
            }
            fclose (pFile);

			
        }
	
			i = 1;
			strcpy(name,res[i]);
			// printf("line = %d\n",i);
			// printf("it = %s\n",res[i]);
			// printf("\ncontent : %s\n",name);
			// printf("len of is %d\n",strlen(name));
			
			// printf("p = %d\n",p);
			for(i =2;i<p-1;i++)
			{
				// printf("line = %d\n",i);
				// printf("it = %s\n",res[i]);
				strcat(name,res[i]);
				
			}
			// printf("name = %s\n",name);
			
			if(!Conf_Info.scheducode)
			{
				headle_SFJ(name);
			}
			else if (Conf_Info.scheducode)
			{
				headle_FIFO(name);
			}
			else if (Conf_Info.scheducode==2)
			{
				headle_PS(name);
			}

			
    }
	
/**
* @brief Function copy string
*
* @return a copied string
*
*/
    char *MyStrCpy(char *dest,const char *scr)
    {
        while (*scr!='\0')
        {
            *(dest++)=*(scr++);
        }
        *dest='\0';
        return dest;
    }
/**
* @brief Function remove_space out of a string
*
* @return a no space string
*
*/
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
