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


    int min(int arr[3])
    {
        int result = 0;
        int ind = 0;
        int i = 0;

        if(arr[0]==0 & arr[1]==0 & arr[2]==0)  return -1;

        for (i =0;i<3;i++)
        {

            if(arr[i]>0)
            {
                result = arr[i];
                ind = i;
                break;
            }

//            printf("arr[%d] = %d\n",i,arr[i]);
        }

        for ( i =0;i<3;i++)
        {
            if(result>arr[i] & arr[i]>0)
            {
                result = arr[i];
                ind = i;
            }
        }
        return ind;
    }







    int main()
    {
        /*
       int arr1 []= {0,0,0};
        printf("\tThe min index is %d\n",min(arr1));

        int arr2 []= {0,2,0};
        printf("\tThe min index is %d\n",min(arr2));


        int arr3 []= {3,2,0};
        printf("\tThe min index is %d\n",min(arr3));


         int arr4 []= {3,2,1};
        printf("\tThe min index is %d\n",min(arr4));
        */

        int s1 = 0;//current value
        int s2 = 0;
        int s3 = 0;

        int gap = 0;

        int ss1 = 0;
        int ss2 = 0;//counter
        int ss3 = 0;

        int tit = 0;

        int arr[3];
        int i = 0;
        Queue *q1 = CreateQueue();
        Queue *q2 = CreateQueue();
        Queue *q3 = CreateQueue();
        AddQ(q1, 200,"A",0);
        ++ss1;
        AddQ(q1, 100,"B",0);
        ++ss1;
        AddQ(q1, 66,"C",0);
        ++ss1;

        AddQ(q2, 320,"A",0);
        ++ss2;
        AddQ(q2, 120,"B",0);
        ++ss2;

        AddQ(q3, 240,"A",0);
        ++ss3;
        AddQ(q3, 140,"B",0);
        ++ss3;
        AddQ(q3, 120,"C",0);
        ++ss3;

        s1 = getQv(q1,0);
        s2 = getQv(q2,0);
        s3 = getQv(q3,0);



        arr[0] = cal_sjf(q1,s1,ss1);
        arr[1] = cal_sjf(q2,s2,ss2);
        arr[2] = cal_sjf(q3,s3,ss3);


        printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,s1,ss1),cal_sjf(q2,s2,ss2),cal_sjf(q3,s3,ss3));
        printf("\tThe min index is %d\n",min(arr));


        printf("%d -- now start s%d\n\n",tit,min(arr)+1);

        // when detect new data   100 is the time of gap


        if(min(arr)==0)
        {
            gap = (cal_sjf(q1,s1,ss1)>100)? 100:cal_sjf(q1,s1,ss1);
            tit = tit + gap;
            s1 = s1 -gap;

        }

        else if(min(arr)==1)
        {
            gap = (cal_sjf(q2,s2,ss2)>100)? 100:cal_sjf(q2,s2,ss2);
            tit = tit + gap;
            s2 = s2 -gap;

        }
        else if(min(arr)==2)
        {
            gap = (cal_sjf(q3,s3,ss3)>100)? 100:cal_sjf(q3,s3,ss3);
            tit = tit + gap;
            s3 = s3 - gap;

        }

        AddQ(q1, 200,"E",0);
        arr[0] = cal_sjf(q1,s1,ss1);
        arr[1] = cal_sjf(q2,s2,ss2);
        arr[2] = cal_sjf(q3,s3,ss3);

        printf("\tNew task1 added in %d\n",tit);
        printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,s1,ss1),cal_sjf(q2,s2,ss2),cal_sjf(q3,s3,ss3));
//        printf("\tThe min index is %d\n",min(arr));
        printf("%d -- now start s%d\n\n",tit,min(arr)+1);



    if(min(arr)==0)
        {
            gap = (cal_sjf(q1,s1,ss1)>100)? 100:cal_sjf(q1,s1,ss1);
            tit = tit + gap;
            s1 = s1 -gap;

        }

        else if(min(arr)==1)
        {
            gap = (cal_sjf(q2,s2,ss2)>100)? 100:cal_sjf(q2,s2,ss2);
            tit = tit + gap;
            s2 = s2 -gap;

        }
        else if(min(arr)==2)
        {
            gap = (cal_sjf(q3,s3,ss3)>100)? 100:cal_sjf(q3,s3,ss3);
            tit = tit + gap;
            s3 = s3 - gap;

        }


        AddQ(q3, 200,"E",0);
        arr[0] = cal_sjf(q1,s1,ss1);
        arr[1] = cal_sjf(q2,s2,ss2);
        arr[2] = cal_sjf(q3,s3,ss3);

        printf("\tNew task2 added in %d\n",tit);
        printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,s1,ss1),cal_sjf(q2,s2,ss2),cal_sjf(q3,s3,ss3));
        printf("%d -- now start s%d\n\n",tit,min(arr)+1);



        if(min(arr)==0)
        {
            gap = (cal_sjf(q1,s1,ss1)>100)? 100:cal_sjf(q1,s1,ss1);
            tit = tit + gap;
            s1 = s1 -gap;

        }

        else if(min(arr)==1)
        {
            gap = (cal_sjf(q2,s2,ss2)>100)? 100:cal_sjf(q2,s2,ss2);
            tit = tit + gap;
            s2 = s2 -gap;

        }
        else if(min(arr)==2)
        {
            gap = (cal_sjf(q3,s3,ss3)>100)? 100:cal_sjf(q3,s3,ss3);
            tit = tit + gap;
            s3 = s3 - gap;

        }

        AddQ(q2, 500,"E",0);
        arr[0] = cal_sjf(q1,s1,ss1);
        arr[1] = cal_sjf(q2,s2,ss2);
        arr[2] = cal_sjf(q3,s3,ss3);

        printf("\tNew task3 added in %d\n",tit);
        printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,s1,ss1),cal_sjf(q2,s2,ss2),cal_sjf(q3,s3,ss3));
        printf("%d -- now start s%d\n\n",tit,min(arr)+1);


        if(min(arr)==0)
        {
            gap = (cal_sjf(q1,s1,ss1)>100)? 100:cal_sjf(q1,s1,ss1);
            tit = tit + gap;
            s1 = s1 -gap;

        }

        else if(min(arr)==1)
        {
            gap = (cal_sjf(q2,s2,ss2)>100)? 100:cal_sjf(q2,s2,ss2);
            tit = tit + gap;
            s2 = s2 -gap;

        }
        else if(min(arr)==2)
        {
            gap = (cal_sjf(q3,s3,ss3)>100)? 100:cal_sjf(q3,s3,ss3);
            tit = tit + gap;
            s3 = s3 - gap;

        }


        AddQ(q1, 12,"E",0);
        arr[0] = cal_sjf(q1,s1,ss1);
        arr[1] = cal_sjf(q2,s2,ss2);
        arr[2] = cal_sjf(q3,s3,ss3);

        printf("\tNew task4 added in %d\n",tit);
        printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,s1,ss1),cal_sjf(q2,s2,ss2),cal_sjf(q3,s3,ss3));
        printf("%d -- now start s%d\n\n",tit,min(arr)+1);

        if(min(arr)==0)
        {
            gap = (cal_sjf(q1,s1,ss1)>100)? 100:cal_sjf(q1,s1,ss1);
            tit = tit + gap;
            s1 = s1 -gap;

        }

        else if(min(arr)==1)
        {
            gap = (cal_sjf(q2,s2,ss2)>100)? 100:cal_sjf(q2,s2,ss2);
            tit = tit + gap;
            s2 = s2 -gap;

        }
        else if(min(arr)==2)
        {
            gap = (cal_sjf(q3,s3,ss3)>100)? 100:cal_sjf(q3,s3,ss3);
            tit = tit + gap;
            s3 = s3 - gap;

        }

        AddQ(q3, 50,"E",0);
        arr[0] = cal_sjf(q1,s1,ss1);
        arr[1] = cal_sjf(q2,s2,ss2);
        arr[2] = cal_sjf(q3,s3,ss3);

        printf("\tNew task5 added in %d\n",tit);
        printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,s1,ss1),cal_sjf(q2,s2,ss2),cal_sjf(q3,s3,ss3));
        printf("%d -- now start s%d\n\n",tit,min(arr)+1);

        printf("\tThere is no interrupt at all\n");


        if(min(arr)==0)
        {
            gap = cal_sjf(q1,s1,ss1);
            tit = tit + gap;
            s1 = s1 -gap;
        }

        else if(min(arr)==1)
        {
            gap = cal_sjf(q2,s2,ss2);
            tit = tit + gap;
            s2 = s2 -gap;

        }
        else if(min(arr)==2)
        {
            gap = cal_sjf(q3,s3,ss3);
            tit = tit + gap;
            s3 = s3 - gap;
        }
        arr[0] = cal_sjf(q1,s1,ss1);
        arr[1] = cal_sjf(q2,s2,ss2);
        arr[2] = cal_sjf(q3,s3,ss3);
        printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,s1,ss1),cal_sjf(q2,s2,ss2),cal_sjf(q3,s3,ss3));
        printf("%d -- now start s%d\n\n",tit,min(arr)+1);


        if(min(arr)==0)
        {
            gap = cal_sjf(q1,s1,ss1);
            tit = tit + gap;
            s1 = s1 -gap;
        }

        else if(min(arr)==1)
        {
            gap = cal_sjf(q2,s2,ss2);
            tit = tit + gap;
            s2 = s2 -gap;

        }
        else if(min(arr)==2)
        {
            gap = cal_sjf(q3,s3,ss3);
            tit = tit + gap;
            s3 = s3 - gap;
        }
        arr[0] = cal_sjf(q1,s1,ss1);
        arr[1] = cal_sjf(q2,s2,ss2);
        arr[2] = cal_sjf(q3,s3,ss3);
        printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,s1,ss1),cal_sjf(q2,s2,ss2),cal_sjf(q3,s3,ss3));
        printf("%d -- now start s%d\n\n",tit,min(arr)+1);


        if(min(arr)==0)
        {
            gap = cal_sjf(q1,s1,ss1);
            tit = tit + gap;
            s1 = s1 -gap;
        }

        else if(min(arr)==1)
        {
            gap = cal_sjf(q2,s2,ss2);
            tit = tit + gap;
            s2 = s2 -gap;

        }
        else if(min(arr)==2)
        {
            gap = cal_sjf(q3,s3,ss3);
            tit = tit + gap;
            s3 = s3 - gap;
        }

        arr[0] = cal_sjf(q1,s1,ss1);
        arr[1] = cal_sjf(q2,s2,ss2);
        arr[2] = cal_sjf(q3,s3,ss3);
        printf("\tv1 = %d\tv2 = %d\tv3 = %d\n",cal_sjf(q1,s1,ss1),cal_sjf(q2,s2,ss2),cal_sjf(q3,s3,ss3));

        if(min(arr)<0)
        printf("%d -- Now finish\n",tit);


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




