#include <string.h>
#include <stdio.h>
#define ElementType int
#define N 20 //ElementType的特殊值，标志错误
#define ERROR -99 //ElementType的特殊值，标志错误
typedef struct Node {
    ElementType data;
    struct Node* next;
}QNode;

typedef struct {
    QNode* front; //指向对头节点
    QNode* rear; //指向队尾节点
}Queue;
Queue* CreateQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        printf("Not enough space\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void AddQ(Queue* q, ElementType item) {
    QNode* qNode = (QNode*)malloc(sizeof(QNode));
    if (!qNode) {
        printf("Not enough space\n");
        return;
    }
    qNode->data = item;
    qNode->next = NULL;
    if (q->front == NULL) {
        q->front = qNode;
    }
    if (q->rear == NULL) {
        q->rear = qNode;
    }
    else {
        q->rear->next = qNode;
        q->rear = qNode;
    }
}

int IsEmptyQ(Queue* q){
    return (q->front == NULL);
}

ElementType DeleteQ(Queue* q) {
    if (IsEmptyQ(q)) {
        printf("Empty Q\n");
        return ERROR;
    }
    QNode* temp = q->front;
    ElementType item;
    if (q->front == q->rear) { //若队列只有一个元素
        q->front = NULL;
        q->rear = NULL;
    }
    else {
        q->front = q->front->next;
    }
    item = temp->data;
    free(temp);
    return item;
}

void PrintQueue(Queue* q) {
    if (IsEmptyQ(q)) {
        printf("Empty Q\n");
        return;
    }
    printf("print Q\n");
    QNode* qNode = q->front;
    while (qNode != NULL) {
        printf("%d " , qNode->data);
        qNode = qNode->next;
    }
    printf("\n");
}

void detect(char *lf,char *rt,char *buf,int *out,int *s)
{


    char *ptr = NULL;
	char *end = NULL;
	//char ip[32] = {0};
//	printf("lf:%s\n",lf);
//	printf("rt:%s\n",rt);
//	printf("buf:%s\n",buf);

	ptr = strstr(buf,lf);
    if(!ptr)
    {
        printf("Input wrong, there is no match with %s\n",lf);
        return 0;
    }
    else
    {
        ptr = ptr + strlen(lf);
    //	printf("sizeof(lf)/sizeof(char):%d\n",strlen(lf));
        end = strstr(ptr,rt);

//        printf("end:%s\n",end);
//    	printf("ptr:%s\n",ptr);

        char* ip = (char*)malloc((end-ptr)/sizeof(char));
        if(!ip)   exit(1);
    //    printf("%d\n",(end-ptr)/sizeof(char));
        memcpy(ip,ptr,(end-ptr)/sizeof(char));
        //printf("ip:%s\n",ip);
        int num = atoi(ip);
//        printf("number = %d\n",num);
        free(ip);
        ip = NULL;
    //    printf("buf len:%d\n",strlen(buf));
    //    printf("end len:%d\n",strlen(end));
         *out=num;
         *s = (strlen(buf)-strlen(end));
    }
}
int getv2(char s1[]) ///////////// problem
 {

    char s2[20];

    strncpy(s2, s1, strlen(s1)-strlen(";"));

    int n = atoi(s2);
    printf("%d\n",n);
    return n;
}

int getv(char *inputStr) ///////////// problem
 {


    int j = 0;

    for(int i=0; inputStr[i] ;i++){
        //5
        if(inputStr[i] >= '0' && inputStr[i] <= '9'){
            inputStr[j] = inputStr[i];
            j++;
        }
    }

    //6
    inputStr[j] = '\0';


    int n = atoi(inputStr);
    printf("%d\n",n);
    return n;
}

int find2(char buf[], char aim[])
{

    char *delim = "}";
    char *p = NULL;

    int sum = 0;
    int f =0;
    char str[50];
    int num1 =0;
     strtok(buf, delim);
    while((p = strtok(NULL, delim)))
    {
         printf("%s\n",p);
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

//		char* pStr = "P{run}5; P{run}5;P{run}5; P{run}5;";

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

//    ok(arry[30][20] ,"P{");
    int sum =0;
	    for(i=0;i<N;i++)
    {

        if(strstr(arry[i],"P{run"))
            {
                sum=sum+getv2(arry[i+1]);
             }
	}
	printf("run P = %d\n",sum);



    sum =0;
	    for(i=0;i<N;i++)
    {

        if(strstr(arry[i],"M{allocate"))
            {
                sum=sum+getv2(arry[i+1]);
             }
	}
	printf("allocate = %d\n",sum);

	    sum =0;
	    for(i=0;i<N;i++)
    {

        if(strstr(arry[i],"O{monitor"))
            {
                sum=sum+getv2(arry[i+1]);
             }
	}
	printf("monitor = %d\n",sum);


	    sum =0;
	    for(i=0;i<N;i++)
    {

        if(strstr(arry[i],"hard"))
            {
                sum=sum+getv2(arry[i+1]);
             }
	}
	printf("hard = %d\n",sum);

	    sum =0;
	    for(i=0;i<N;i++)
    {

        if(strstr(arry[i],"I{mouse"))
            {
                sum=sum+getv2(arry[i+1]);
             }
	}
	printf("mouse = %d\n",sum);


	    sum =0;
	    for(i=0;i<N;i++)
    {

        if(strstr(arry[i],"O{printer"))
            {
                sum=sum+getv2(arry[i+1]);
             }
	}

	printf("printer = %d\n",sum);

	    sum =0;
	    for(i=0;i<N;i++)
    {

        if(strstr(arry[i],"M{block"))
            {
                sum=sum+getv2(arry[i+1]);
             }
	}
	printf("block = %d\n",sum);


	    sum =0;
	    for(i=0;i<N;i++)
    {

        if(strstr(arry[i],"I{keyboard"))
            {
                sum=sum+getv2(arry[i+1]);
             }
	}
	printf("keyboard = %d\n",sum);




	system("pause");
}
