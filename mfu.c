#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct mainmemory
{
    int* frame;
    int size;
};
struct frequency
{
    int *fqbit;
};
struct arrival
{
    int *appearance;
};
struct frequency* createsc(int si)
{
    struct frequency* s=(struct frequency*)malloc(sizeof(struct frequency));
    s->fqbit=(int *)malloc(si * sizeof(int));
    return s;
};
struct arrival* createav(int si)
{
    struct arrival* s=(struct arrival*)malloc(sizeof(struct arrival));
    s->appearance=(int *)malloc(si * sizeof(int));
    return s;
};
struct mainmemory* create(int si)
{
    struct mainmemory* s=(struct mainmemory *)malloc(sizeof(struct mainmemory));
    s->frame=(int *)malloc(si * sizeof(int));
    s->size=0;
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
int frequency_item(int *array,int value,int capacity)
{
    int count=0,i;
    for(i=0;i<capacity;i++)
    {
        if(array[i]==value)
            count++;
    }
    return count;
}
int find_max_index(int *array,int capacity)
{
    int i=0,max=-99,index;
    for(i=0;i<capacity;i++)
    {
        if(array[i]>max)
        {
            max=array[i];
            index=i;
        }
    }
    return index;
}
int page_replacement(int n,int capacity,int* pages)                //MAIN MOST FREQUENTY USED ALGORITHM
{
    struct mainmemory *mm;
    mm=create(capacity);                                        //CREATED A MAINMEMORY WHICH HOLDS THE FRAMES

    struct frequency *array;                                    //CREATING A FREQUENCY ARRAY WHICH STORES HOW MANY TIMES
    array=createsc(capacity);                                   //          THE PAGE IS REFERED

    struct arrival *entry;                                      //CREATING THE ENTRY ARRAY WHICH STORES WHEN THE PAGE IS STORED
    entry=createav(capacity);                                   //      IN MAIN MEMORY STORES "i" VALUE

    int i=0,pagefault=0;

    for(i=0;i<capacity;i++)
    {
        array->fqbit[i]=0;                                  //INITIALISING ALL THE SECOND CHANCE ARRAY TO 0
        mm->frame[i]=-1;                                     //INITIALISING ALL THE VALUE OF FRAMES AS -1
    }

    for(i=0;i<n;i++)                                            //RUNNING THE LOOP FOR ALL PAGES REFERED
    {
        if(mm->size<capacity)                                                   //ALL FRAMES ARE NOT OCCUPIED
        {
            if(element_present(mm->frame,pages[i],capacity)==0)                 //THE PAGE IS NOT PRESENT IN MAIN MEMORY
            {
                int index=find_index(mm->frame,-1,capacity);                    //FIND THE NEXT AVAILABLE INDEX WHERE PAGE CAN BE INSERTED
                mm->frame[index]=pages[i];                                      //INSERTING PAGE IN THAT INDEX IN MAIN MEMORY
                entry->appearance[index]=i;                                     //STORES I VALUE FOR IDENTIFY WHICH PAGE COMES WHEN
                array->fqbit[index]++;                                          //INCREASING THE FREQUENCY OF THAT PAGE
                mm->size++;
                //printf("Inserted an element %d in index %d\n",pages[i],index);
                pagefault++;
            }
            else
            {
                int index=find_index(mm->frame,pages[i],capacity);             //RETURNS THE INDEX OF THAT PAGE IN MAINMEMORY
                array->fqbit[index]++;                                         //INCREASING THE FREQUENCY OF THAT PAGE REFERED
                //printf("MM size is not full but refered page %d in index %d\n",pages[i],index);
            }
        }
        else                                                                //IF MAINMEMORY IS FULL
        {
            if(element_present(mm->frame,pages[i],capacity)==0)                //IF THE PAGE IS PRESENT IN THE MAIN MEMORY
            {
                int index=find_max_index(array->fqbit,capacity);               //FIND THE INDEX WHICH CONTAINS MAXIMUM FREQUENCY
                int maxvalue=array->fqbit[index];                              //STORES THE FREQUENCY
                int freq=frequency_item(array->fqbit,maxvalue,capacity);       //FIND NO OF FRAMES HAVING SAME MAXIMUM FREQUENCY VALUE
                pagefault++;
                if(freq==1)                                                     //IF ONLY ONE PAGE HAVING MAXIMUM FREQUENCY
                {
                    mm->frame[index]=pages[i];                                  //STORES THAT PAGE IN CORRESPOINDING INDEX IN MAINMEMORY
                    array->fqbit[index]=1;                                      //CHANGING FREQUENCY TO 1
                    //printf("Entry is %d page %d is inserted in index %d\n",entry->appearance[index],pages[i],index);
                    entry->appearance[index]=i;                                 //CHANGING THE ENRTY VALUE TO i BECAUSE OF FRAME CHANGE
                }
                else                                                            //IF MORE THAN ONE FRAME HAVING SAME MAXIMUM FREQUENCY
                {
                    int same[freq];                                             //CREATING AN ARRAY OF SIZE OF FREQ(NO OF PAGE HAVING SAME MAX FREQ)
                    int j,poi=0;
                    for(j=0;j<capacity;j++)                                     //FINDING THE INDEX OF FRAME WHICH HAVING SAME MAXIMUM FREQUENCY
                    {
                        if(poi==freq)
                            break;
                        if(array->fqbit[j]==maxvalue)
                        {
                            same[poi]=j;
                            poi++;
                        }
                    }
                    poi=99;
                    for(j=0;j<freq;j++)                                       //FOR EACH SAME MAX FREQ CHECK WHICH FRAME COMES FIRST THAT FRAME IS
                    {                                                         //            REPLACED
                        if(entry->appearance[same[j]]<entry->appearance[poi])
                            poi=same[j];
                    }
                    //printf("EEntry is %d page %d is inserted in index %d\n",entry->appearance[poi],pages[i],poi);
                    mm->frame[poi]=pages[i];
                    array->fqbit[poi]=1;
                    entry->appearance[poi]=i;
                }
            }
            else                                                                    //IF REFERED PAGE IS PRESENT IN MAINMEMORY
            {
                int index=find_index(mm->frame,pages[i],capacity);                      //SAME AS ABOVE IF STATEMENT
                array->fqbit[index]++;
                //printf("MM size is full but refered page %d in index %d\n",pages[i],index);
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
        out=page_replacement(i,size,str);
        printf("%d,",size-out);
    }
    printf("\n");
    return 0;
}

/* void main()
{
    int pages[15]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2};
    int out=page_replacement(15,3,pages);            //NO OF PAGES,NO OF FRAMES,PAGES REFERED ARRAY
    printf("# of pagefault is %d\n",out);
} */

