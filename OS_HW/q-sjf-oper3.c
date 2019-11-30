    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <malloc.h>
    #include <time.h>


    #define time_cyc 50
    #define c_num 13
    #define MAX_LINE 50
    #define  option_num 9
    #define ElementType1 long //store type
    #define ElementType2 char //store type
	#define ElementType3 long //store type
    #define MAXSIZE 100 //max store size
    #define ERROR -99 //ElementType for error notation
	unsigned int mem_call = 0 ; //to get an allocated initial address

    typedef struct {
        ElementType1 data[MAXSIZE];
        ElementType2 *name[MAXSIZE];
		ElementType3 data2[MAXSIZE];
        int front; // start of Q
        int rear; // end of Q
        int size; //number of element
    }Queue;

    Queue* CreateQueue();
    void DestroySequeue(Queue *q);
    int IsFullQ(Queue* q);
    void AddQ(Queue* q, ElementType1 item1,ElementType2 *item2,ElementType3 item3);
    int IsEmptyQ(Queue* q);
    ElementType1 DeleteQ(Queue* q);
    void PrintQueue(Queue* q);


    ElementType1 getQv(Queue* q,int offset);
    ElementType2 *getQs(Queue* q,int offset);
	ElementType3 getQv2(Queue* q,int offset);

    int cal_sjf(Queue* q,int s1,int ss)
    {
        int v1 = s1;
        int i =0;
        for(i =ss;i>0;i--)
        {
            v1 =v1 + getQv(q,i);
        }
        return v1;
    }


    int min(int arr[5])
    {
        int result = 0;
        int ind = 0;
        int i = 0;

        if(arr[0]==0 & arr[1]==0 & arr[2]==0& arr[3]==0 & arr[4]==0)  return -1;

        for (i =0;i<5;i++)
        {

            if(arr[i]>0)
            {
                result = arr[i];
                ind = i;
                break;
            }

//            printf("arr[%d] = %d\n",i,arr[i]);
        }

        for ( i =0;i<5;i++)
        {
            if(result>arr[i] & arr[i]>0)
            {
                result = arr[i];
                ind = i;
            }
        }
        return ind;
    }



    int update(int inter_t,int *s1,int *s2,int *s3,int *s4,int *s5,int *gap,
               int ss1,int ss2,int ss3,int ss4,int ss5,int *tit,int arr[],
               Queue *q1,Queue *q2,Queue *q3,Queue *q4,Queue *q5)
    {

        arr[0] = cal_sjf(q1,*s1,ss1);
        arr[1] = cal_sjf(q2,*s2,ss2);
        arr[2] = cal_sjf(q3,*s3,ss3);
        arr[3] = cal_sjf(q4,*s4,ss4);
        arr[4] = cal_sjf(q5,*s5,ss5);
        int temp = min(arr);

//        printf("min(arr) = %d \n",temp);
        if(temp<0)
        {
            printf("%d -- Now finish\n",*tit);
        }
        else
        {
            printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,*s1,ss1),cal_sjf(q2,*s2,ss2),cal_sjf(q3,*s3,ss3));
            printf("\tThe min index is %d\n",min(arr));
            printf("%d -- now start s%d\n\n",*tit,min(arr)+1);

             if(temp==0)
            {
                *gap = (cal_sjf(q1,*s1,ss1)>inter_t)? inter_t:cal_sjf(q1,*s1,ss1);
                *tit = *tit + *gap;
                *s1 = *s1 - *gap;

            }

            else if(temp==1)
            {
                *gap = (cal_sjf(q2,*s2,ss2)>inter_t)? inter_t:cal_sjf(q2,*s2,ss2);
                *tit = *tit + *gap;
                *s2 = *s2 -*gap;

            }
            else if(temp==2)
            {
                *gap = (cal_sjf(q3,*s3,ss3)>inter_t)? inter_t:cal_sjf(q3,*s3,ss3);
                *tit = *tit + *gap;
                *s3 = *s3 - *gap;

            }
            else if(temp==3)
            {
                *gap = (cal_sjf(q4,*s4,ss4)>inter_t)? inter_t:cal_sjf(q4,*s4,ss4);
                *tit = *tit + *gap;
                *s4 = *s4 - *gap;

            }
            else if(temp==4)
            {
                *gap = (cal_sjf(q5,*s5,ss5)>inter_t)? inter_t:cal_sjf(q5,*s5,ss5);
                *tit = *tit + *gap;
                *s5 = *s5 - *gap;

            }


        }
        return s1,s2,s3,s4,s5,tit,gap;

    }



    int main()
    {

        int i = 0;


//        printf("i=%d\n",(unsigned)(-1)>>1);
        int s1 = 0;//current value
        int s2 = 0;
        int s3 = 0;
        int s4 = 0;
        int s5 = 0;


        int gap = 0;

        int ss1 = 0;
        int ss2 = 0;//counter
        int ss3 = 0;
        int ss4 = 0;
        int ss5 = 0;

        int tit = 0;
        int arr[5];

        Queue *q1 = CreateQueue();
        Queue *q2 = CreateQueue();
        Queue *q3 = CreateQueue();
        Queue *q4 = CreateQueue();
        Queue *q5 = CreateQueue();

        AddQ(q1, 200,"A",0);
        ++ss1;
        AddQ(q1, 100,"B",0);
        ++ss1;
        AddQ(q1, 266,"C",0);
        ++ss1;



        s1 = getQv(q1,0);
        s2 = getQv(q2,0);
        s3 = getQv(q3,0);
        s4 = getQv(q4,0);
        s5 = getQv(q5,0);

        printf("\ts1 = %d\ts2 = %d\ts3 = %d\n",s1,s2,s3);
        // when detect new data   100 is the time of gap

        update(100, &s1, &s2, &s3, &s4, &s5 ,&gap, ss1, ss2, ss3, ss4, ss5, &tit, arr, q1, q2, q3,q4,q5);




        AddQ(q2, 320,"A",0);
        ++ss2;
        AddQ(q2, 420,"B",0);
        ++ss2;

        update(100, &s1, &s2, &s3, &s4, &s5 ,&gap, ss1, ss2, ss3, ss4, ss5, &tit, arr, q1, q2, q3,q4,q5);

        AddQ(q3, 240,"A",0);
        ++ss3;
        AddQ(q3, 140,"B",0);
        ++ss3;
        AddQ(q3, 520,"C",0);
        ++ss3;



        update(100, &s1, &s2, &s3, &s4, &s5 ,&gap, ss1, ss2, ss3, ss4, ss5, &tit, arr, q1, q2, q3,q4,q5);
        AddQ(q4, 500,"E",0);
        ++ss4;
        AddQ(q4, 240,"A",0);
        ++ss4;
        AddQ(q4, 140,"B",0);
        ++ss4;


        update(100, &s1, &s2, &s3, &s4, &s5 ,&gap, ss1, ss2, ss3, ss4, ss5, &tit, arr, q1, q2, q3,q4,q5);

         AddQ(q5, 500,"E",0);
        ++ss5;
        AddQ(q5, 340,"A",0);
        ++ss5;
        AddQ(q5, 140,"B",0);
        ++ss5;


         update(100, &s1, &s2, &s3, &s4, &s5 ,&gap, ss1, ss2, ss3, ss4, ss5, &tit, arr, q1, q2, q3,q4,q5);



        printf("No interrup!\n");
        while(min(arr)>=0)
        {
            update((unsigned)(-1)>>1, &s1, &s2, &s3, &s4, &s5 ,&gap, ss1, ss2, ss3, ss4, ss5, &tit, arr, q1, q2, q3,q4,q5);
//            update((unsigned)(-1)>>1, &s1, &s2, &s3, &gap, ss1, ss2, ss3, &tit, arr, q1, q2, q3);
        }
        return 0;

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
//            printf("Empty Queue!\n");
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
//            printf("Empty Queue!\n");
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
//            printf("Empty Queue!\n");
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
//            printf("Empty Queue!\n");
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

