#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct queue
{
    int rear,front,size;
    int capacity;
    int *array;
};
struct queue* createqueue(int capacity)
{
    struct queue* queue = (struct queue*) malloc(sizeof(struct queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}
int isfull(struct queue *q)
{
    return(q->size==q->capacity);
}
int isempty(struct queue *q)
{
    return(q->size==0);
}
void enqueue(struct queue *q,int val)
{
    if(isfull(q))
        return;
    q->rear=q->rear+1;
    int k=q->rear;
    q->array[k]=val;
    //printf("enqued element is %d\n",q->array[k]);
    q->size=q->size+1;
}
int dequeue(struct queue *q)
{
    if(isempty(q))
        return 0;
    int k=q->array[q->front];
    q->front=q->front+1;
    q->size=q->size-1;
    //printf("deleted element is %d\n",k);
    return k;
}
int set_present(int *ar,int item,int capacity)
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
int page_replacement(int capacity,int n,int* array)
{
    int place=0,pagefault=0,i;
    struct queue *q;
    q=createqueue(capacity);
    int set[capacity];
    for(i=0;i<capacity;i++)
        set[i]=-1;
    for(i=0;i<n;i++)
    {
        if(q->size<capacity)
        {
            if(set_present(set,array[i],capacity)==0)
            {
                enqueue(q,array[i]);
                set[place]=array[i];
                place=place+1;
                pagefault=pagefault+1;
            }
        }
        else
        {
            if(set_present(set,array[i],capacity)==0)
            {
                int dele=dequeue(q);
                int index=find_index(set,dele,capacity);
                set[index]=array[i];
                enqueue(q,array[i]);
                pagefault=pagefault+1;
            }
        }
    }
    return pagefault;
}
int main()
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
    for(int i=4;i<=7;i++)
    {
        out=page_replacement(i,size,str);
        printf("%d,",out);
    }
    printf("\n");
    return 0;
}
