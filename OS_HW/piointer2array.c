

#include <stdio.h>
#include"string.h"




#include <stdio.h>
// Include the above library.

char *MyStrCpy(char *dest,const char *scr)
{
    while (*scr!='\0')
    {
        *(dest++)=*(scr++);
    }
    dest='\0';
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

int main(void)
{
    char *b = " A{ae}:11";
    char *d = "P{run}";

    char a[10],c[10];
    int i,j =0;
    MyStrCpy(a,b);
    remove_space(c,a);
//    puts(b);

    printf("\n%s",a);

    printf("\n%s\n",c);
    if(strncmp(c,d,5)==0|strncmp(c,"A{ae}",4)==0)
        printf("yeah\n");

//        printf("\n%d\n",strncmp(d,b,5));

    return 0;
}
