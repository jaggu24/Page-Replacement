#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct mainmemory
{
    int* frame;
};
struct secondchance
{
    int *scbit;
    int pointer;
};
struct secondchance* createsc(int si)
{
    struct secondchance* s=(struct secondchance*)malloc(sizeof(struct secondchance));
    s->pointer=0;
    s->scbit=(int *)malloc(si * sizeof(int));
    return s;
};
struct mainmemory* create(int si)
{
    struct mainmemory* s=(struct mainmemory *)malloc(sizeof(struct mainmemory));
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
int find_index(int *arr,int item,int capacity)
{
    int i;
    for(i=0;i<capacity;i++)
        if(arr[i]==item)
            return i;
}
int page_replacement(int n,int capacity,int* pages)                //MAIN SECOND CHANCE ALGORITHM IMPLEMENTED
{
    struct mainmemory *mm;
    mm=create(capacity);                                        //CREATED A MAINMEMORY WHICH HOLDS THE FRAMES

    struct secondchance *second;
    second=createsc(capacity);

    int i=0,pagefault=0;

    for(i=0;i<capacity;i++)
    {
        second->scbit[i]=0;                                  //INITIALISING ALL THE SECOND CHANCE ARRAY TO 0
        mm->frame[i]=-1;                                     //INITIALISING ALL THE VALUE OF FRAMES AS -1
    }

    for(i=0;i<n;i++)                                            //RUNNING THE LOOP FOR ALL PAGES REFERED
    {
        if(element_present(mm->frame,pages[i],capacity)==0)         //IF THE PAGE IS NOT PRESENT IN THE MAIN MEMORY
        {
            while(second->scbit[second->pointer]!=0)                //RUNNING LOOP WHILE THE SECOND CHANCE BIT IS 0
            {
                second->scbit[second->pointer]=0;                   //UPDATING THE SECOND CHANCE BIT TO 0 AS WE TRAVERSED IT
                //printf("\nUpdated the index %d from 1 to 0\n",second->pointer);
                second->pointer=(second->pointer+1)%capacity;       //INCREMENTING THE VALUE OF POINTER
            }
            //printf("\nInserted value %d in the index %d\n",pages[i],second->pointer);
                                                                    //NOW THE POINTER CONTAINS INDEX WHERE SECOND CHANCE BIT IS 0
            mm->frame[second->pointer]=pages[i];                    //CHANGING THE FRAME IN MAIN MEMORY
            second->pointer=(second->pointer+1)%capacity;           //INCREMENTING THE POINTER
            pagefault++;
        }
        else
        {
            int index=find_index(mm->frame,pages[i],capacity);         //RETURNS THE INDEX OF THE PAGE IN MAIN MEMORY
            //printf("\nUpdated the value of index %d from %d to 1\n",index,second->scbit[second->pointer]);
            second->scbit[index]=1;                                    //CHANGING THE SECOND CHANCE BIT TO 1
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
/* void main()
{
    int pages[20]={2,5,10,1,2,2,6,9,1,2,10,2,6,1,2,1,6,9,5,1};
    int out=page_replacement(20,4,pages);            //NO OF PAGES,NO OF FRAMES,PAGES REFERED ARRAY
    printf("# of pagefault is %d\n",out);
}
 */
