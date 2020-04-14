#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int checked(int *pages,int n,int element)
{
    int flag=0;
    for(int i=0;i<=n;i++)
    {
        if(pages[i]==element)
        {
            return 1;
        }
    }
    return 0;
}
int page_replacement(int size,int n,int *array)
{
    int *pages,j=0,fault=0;
    size_t size_page=size;
    pages=(int *)calloc(size_page,sizeof(int));
    for(int i=0;i<size;i++)
    {
//        printf("a%d  ",array[i]);
        int check=checked(pages,n,array[i]);
//        printf("C%d ",check);
        if(check==0)
        {
            pages[j]=array[i];
            j+=1;
            j%=n;
            fault+=1;
        }
    }
    free(pages);
    return fault;
}
int main(int argc, char *argv[])
{
    int *str,size=0;
    FILE *fptr;
    char ab[50],sq[10];
    fptr=fopen("r1.txt","r");
    if(fptr==NULL)
    {
            printf("No such file ");
            return 2;
    }
    int a;
    size_t size2=20;
    char *buf;
    buf=(char *)malloc(size2);
    while(!feof(fptr))                                                              //Checking no. of elements in file
    {
            getdelim(&buf,&size2,',',fptr);
            if(buf[1]=='\n')
                    break;
            if(buf[strlen(buf)-1]==',')
                    buf[strlen(buf)-1]='\0';
            a=atoi(buf);
            size+=1;
    }
    fclose(fptr);
    fptr=fopen("r1.txt","r");
    str=(int *)malloc(sizeof(int)*size+1);                                          //Allocate desired size
    int length = 0;
    while(!feof(fptr))                                                              //Read Storing elements into str
    {
            getdelim(&buf,&size2,',',fptr);
            if(buf[1]=='\n')
                    break;
            if(buf[strlen(buf)-1]==',')
                    buf[strlen(buf)-1]='\0';
            a=atoi(buf);
            str[length]=a;
            length+=1;
    }
    fclose(fptr);
    int out;
    int end1=atoi(argv[2]),inc1=atoi(argv[3]);
    for(int i=atoi(argv[1]);i<=end1;i+=inc1)
    {
        out=page_replacement(size,i,str);
        printf("%d,",out);
    }
    printf("\n");
    return 0;
}
