
#almost done for SFJ

#include<stdio.h>
#include<string.h>
#include <stdlib.h>

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
     printf("Before code: %s\n\n",name);



//     printf("sjf = %d\n",SJF_op(name3));
//     printf("ps = %d\n",PS_op(name3));
    char* pStr  = name;
    int pp_num =0;
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

        for (i =0; i<=1;i++)
        {
           printf("%d ", SJF_op(c[i]));
           printf("%s\n\n",c[i]);
        }


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
                printf("arr[%d] = %d\n\n",i, aa[i]);
                printf("c[%d] = %s\n\n",i, c[aa[i]]);
                strcat(e,c[aa[i]]);
            }

            strcat(e,"S{finish}0.");
        printf("\nfinial = %s\n",e);


    }


}


/*
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
     printf("Before code: %s\n\n",name);



//     printf("sjf = %d\n",SJF_op(name3));
//     printf("ps = %d\n",PS_op(name3));
    char* pStr  = name;
    int pp_num =0;
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

        for (i =0; i<=1;i++)
        {
           printf("%d ", SJF_op(c[i]));
           printf("%s\n\n",c[i]);
        }


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
                printf("arr[%d] = %d\n\n",i, aa[i]);
                printf("c[%d] = %s\n\n",i, c[aa[i]]);
                strcat(e,c[aa[i]]);
            }

            strcat(e,"S{finish}0.");
        printf("\nfinial = %s\n",e);


    }


}
*/



int main()
{
//     int arr[100];
//    int* ptr = fun(arr);
//    printf("%d %d\n", ptr[0], ptr[1]);

    char name4[]={"S{begin}0; A{begin}0; P{run}11; M{allocate}2; A{finish}0;A{begin}0;\
O{hard drive}6; A{finish}0; A{begin}0; P{run}4;I{keyboard}18; M{allocate}4;A{finish}0;\
A{begin}0; P{run}11; M{allocate}2; A{finish}0;A{begin}0;\
O{hard drive}6; A{finish}0; A{begin}0; P{run}4;I{keyboard}18; M{allocate}4;\
P{run}6; A{finish}0; S{finish}0."};

    char name2[]={"S{begin}0; A{begin}0; P{run}11; M{allocate}2; A{finish}0;\
A{begin}0; P{run}4;\
I{keyboard}18; M{allocate}4; P{run}6; A{finish}0; S{finish}0"};



    char name[]={"S{begin}0; A{begin}0; P{run}11; M{allocate}2; A{finish}0;\
A{begin}0; O{hard drive}6; A{finish}0; A{begin}0; P{run}4;\
I{keyboard}18; M{allocate}4; P{run}6; A{finish}0; S{finish}0."};


    char name1[]={"S{begin}0; A{begin}0; P{run}4;I{keyboard}18; M{allocate}4;\
P{run}6; A{finish}0; S{finish}0."};
//    printf("Name code: %s\n\n",name3);

    headle_SFJ(name1);


/*
//    char *str = "abcde123abcd123";
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
     printf("Before code: %s\n\n",name);

//    char dd[500]={};
//    char dd2[500]={};
//    char dd3[500]={};
//    char dd4[500]={};

//     printf("sjf = %d\n",SJF_op(name3));
//     printf("ps = %d\n",PS_op(name3));
    char* pStr  = name;
    int pp_num =0;
    char tmpChar = '}';
    char arry[100][20];
    SplitStrByStr(pStr, tmpChar, arry, &line);

    printf("line = %d\n", line);

    for(i = 0; i < line; i++)
    {
        if(strstr(arry[i],"A{finish"))
            ++pp_num;
    }

    printf("pp_num = %d\n", pp_num);

    char c[20][500]={};
    int  d[20] ={};
    char e[5000]={};

    if(pp_num==1)
    {
        printf("%s\n\n",name);

    }
    if(pp_num==2)
    {
        strcpy(c[1],crush(name,0));
        strcpy(c[0],crush(name,1));

        for (i =0; i<=1;i++)
        printf("%s\n\n",c[i]);
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


            printf("print out\n",i);
            for (i =1; i<=pp_num;i++)
            {
                remove_space(c[i],c[i]);
                printf("%s\n",c[i]);
                d [i-1]= SJF_op(c[i]);
                printf("SJF[%d] = %d\n\n",i-1,d[i-1]);

            }
            int aa[pp_num+1];
            for (i=1;i<=pp_num;i++)
            {
                aa[i] =i;
            }

             sort(aa,d, pp_num);
             printf("After sort\n");





            strcpy(e,"S{begin}0;");
//            printf("c[%d] = %s\n\n",i, c[aa[i]]);
            for (i =1; i<=pp_num;i++)
            {
                printf("arr[%d] = %d\n\n",i, aa[i]);
                printf("c[%d] = %s\n\n",i, c[aa[i]]);
                strcat(e,c[aa[i]]);
            }

            strcat(e,"S{finish}0.");
        printf("finial = %s\n",e);
    }


*/


/*


//  printf("%d\n",check_sub(name2));

*/
    return 0;

}







