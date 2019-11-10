    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

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
void PrintArryData(char arry[100][20], int cnt){
	for (int i = 0; i < cnt; i++){
		printf("%s\n", arry[i]);
	}
}

void main(){
	int line = 0;
	int i  =0;
	int p_num =0;
//	char* pStr = "Rose_Girl1,Rose_Girl2,Rose_Girl3,Rose_Girl4,Rose_Girl5,";

	    char name[]={"S{begin}0; A{begin}0; P{run}11; M{allocate}2; A{finish}0;A{begin}0;\
O{hard drive}6; A{finish}0; A{begin}0; P{run}4;I{keyboard}18; M{allocate}4;A{finish}0;\
A{begin}0; P{run}11; M{allocate}2; A{finish}0;A{begin}0;\
O{hard drive}6; A{finish}0; A{begin}0; P{run}4;I{keyboard}18; M{allocate}4;\
P{run}6; A{finish}0; S{finish}0."};

    char* pStr  = name;


    char tmpChar = '}';
    char arry[100][20];
    SplitStrByStr(pStr, tmpChar, arry, &line);

    printf("line = %d\n", line);

    for(i = 0; i < line; i++)
    {
        if(strstr(arry[i],"A{finish"))
            ++p_num;
    }

    printf("p_num = %d\n", p_num);
    PrintArryData(arry, line);


	system("pause");
}
