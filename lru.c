#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct mainmemory
{
    int* frame;
    int size;
};
struct mainmemory* create(int si)
{
    struct mainmemory* s=(struct mainmemory *)malloc(sizeof(struct mainmemory));
    s->size=0;
    s->frame=(int *)malloc(si * sizeof(int));
    return s;
};
int element_present(int *ar,int item,int capacity)
{
    int i;
    for(i=0;i<capacity;i++)
    {
        if(ar[i]==item)
            return 1;
    }
    return 0;
}
int lru_check(int *array,int capacity)
{
    int i=0,min=99,index;
    for(i=0;i<capacity;i++)
    {
        if(array[i]<min)
        {
            min=array[i];
            index=i;
        }
    }
    return index;
}
int find_index(int *arr,int item,int capacity)
{
    int i;
    for(i=0;i<capacity;i++)
        if(arr[i]==item)
            return i;
}
int page_replacement(int n,int capacity,int* pages)                //MAIN LRU ALGORITHM IMPLEMENTED
{
    struct mainmemory *mm;
    mm=create(capacity);                                             //CREATED A MAINMEMORY WHICH HOLDS THE FRAMES
    int refer[capacity];                                            //STORES THE REFERENCE VALUE (WHEN THE ELEMENT IS REFERED RECENTLY)
    int i=0,pagefault=0;
    for(i=0;i<capacity;i++)
        mm->frame[i]=-1;                                     //INITIALISING ALL THE VALUE OF FRAMES AS -1
    for(i=0;i<n;i++)                                            //RUNNING THE LOOP FOR ALL PAGES REFERED(N)
    {
        if(mm->size<capacity)                                //IF SOME FRAMES ARE NOT ASSIGNED TO ANY PAGE
        {
            if(element_present(mm->frame,pages[i],capacity)==0)      //FUNCTION RETURNS 0 IF THE PAGE IS PRESENT IN MAINMEMORY
            {
                pagefault++;
                int index=mm->size;                          //MAINMEMORY SIZE IS THE INDEX OF NEXT PAGE TO STORE IN FRAME ARRAY
                mm->frame[index]=pages[i];
                refer[index]=i;                                 //STORES THE VALUE OF I AS THE REFERENCE VALUE FOR THAT PAGE
                mm->size++;
                //printf("inserted value %d in index %d\n",mm->frame[index],index);
            }
            else                                            //IF THE ELEMENT IS PRESENT IN MAIN MEMORY
            {
                int index=find_index(mm->frame,pages[i],capacity);         //FIND THE INDEX OF THE PAGE IN MAINMEMORY
                refer[index]=i;                                         //CHANGING THE REFERENCE VALUE FOR THAT PAGE AS I
            }
        }
        else                                                   // IF ALL THE FRAMES ARE FULL IN MAINMEMORY
        {
            if(element_present(mm->frame,pages[i],capacity)==0)             //IF THE PAGE IS NOT PRESENT IN MAINMEMORY
            {
                int index=lru_check(refer,capacity);                        //RETURNS THE INDEX OF THE PAGE WHICH IS LEAST RECENTLY USED
                //printf("Changed the value %d in index %d \n",pages[i],index);
                mm->frame[index]=pages[i];                      //CHANGING THE FRAME IN THAT INDEX TO NEW PAGE
                refer[index]=i;                                 //ALSO CHANGES THE REFERENCE VALUE TO THE NEW PAGE IN THE SAME INDEX
                pagefault++;
            }
            else
            {
                int index=find_index(mm->frame,pages[i],capacity);       //SAME INSTRUCTION IN THE FIRST IF CONDITION
                refer[index]=i;
            }
        }
    }
    return pagefault;
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
/*
void main()
{
    int pages[13]={7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int out=page_replacement(13,4,pages);            //NO OF PAGES,NO OF FRAMES,PAGES REFERED ARRAY
    printf("# of pagefault is %d\n",out);
}
*/
