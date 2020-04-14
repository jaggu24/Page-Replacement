#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct mainmemory
{
    int* frame;
    int size;
};
struct ref_use
{
    int **use;
};
struct mainmemory* create(int si)
{
    struct mainmemory* s=(struct mainmemory *)malloc(sizeof(struct mainmemory));
    s->frame=(int *)malloc(si * sizeof(int));
    s->size=0;
    return s;
};
struct ref_use* createusebit(int si)
{
    struct ref_use* s=(struct ref_use *)malloc(sizeof(struct ref_use));
    s->use=(int **)malloc(si * sizeof(int *));
    int i;
    for(i=0;i<si;i++)
        s->use[i]=(int *)malloc(4 * sizeof(int));
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
int lower_value(int **use,int capacity)
{
    int val[capacity],i;
    //printf("Inside finding decimal\n");
    for(i=0;i<capacity;i++)
        val[i]=(use[i][3]*8)+(use[i][2]*4)+(use[i][1]*2)+(use[i][0]);
    int min=99,index;
    for(i=0;i<capacity;i++)
    {
        //printf("value of decimal in each index is %d\n",val[i]);
        if(val[i]<min)
        {
            min=val[i];
            index=i;
        }
    }
    //printf("coming out of decimal\n");
    return index;
}
void time_interval(int **use,int capacity)
{
    int i,j;
    for(i=0;i<capacity;i++)
        for(j=1;j<capacity;j++)
            use[i][j-1]=use[i][j];
    for(i=0;i<capacity;i++)
        use[i][3]=0;
}
int find_index(int *arr,int item,int capacity)
{
    int i;
    for(i=0;i<capacity;i++)
        if(arr[i]==item)
            return i;
}
void renue_use(int **use,int index)
{
    int j;
    for(j=0;j<4;j++)
        use[index][j]=0;
    use[index][3]=1;
}
int page_replacement(int n,int capacity,int* pages)                //MAIN ADDITIONAL BIT ALGORITHM IMPLEMENTED
{
    struct mainmemory *mm;
    mm=create(capacity);                                        //CREATED A MAINMEMORY WHICH HOLDS THE FRAMES
    //printf("mod but is %d\n",mod[0]);
    struct ref_use *array;                                    //CREATING AN ARRAY TO STORE USE BIT FOR ALL FRAMES IN MAIN MEMORY
    array=createusebit(capacity);

    int i=0,j,pagefault=0;

    for(i=0;i<capacity;i++)
    {
        mm->frame[i]=-1;                                     //INITIALISING ALL THE VALUE OF FRAMES AS -1
    }
    for(i=0;i<capacity;i++)
        for(j=0;j<capacity;j++)
            array->use[i][j]=0;                             //INITIALISING ALL USEBITS TO 0

    for(i=0;i<n;i++)                                            //RUNNING THE LOOP FOR ALL PAGES REFERED
    {
        if(pages[i]==-1)                                    //INDICATES THE TIME INTERVAL
        {
            time_interval(array->use,capacity);               //IT SHIFTS ALL THE USE BIT TO ONE RIGHT POSITION(3->2,2->1,1->0)
            continue;
        }
        if(mm->size<capacity)                                //IF SOME FRAMES ARE NOT ASSIGNED TO ANY PAGE
        {
            if(element_present(mm->frame,pages[i],capacity)==0)      //FUNCTION RETURNS 0 IF THE PAGE IS NOT PRESENT IN MAINMEMORY
            {
                pagefault++;
                int index=mm->size;                          //MAINMEMORY SIZE IS THE INDEX OF NEXT PAGE TO STORE IN FRAME ARRAY
                mm->frame[index]=pages[i];
                array->use[index][3]=1;                     //CHANGE THE 3RD BIT OF USE ARRAY OF THAT FRAME TO 1
                mm->size++;
                //printf("inserted value %d in index %d\n",mm->frame[index],index);
            }
            else                                            //IF THE ELEMENT IS PRESENT IN MAIN MEMORY
            {
                int index=find_index(mm->frame,pages[i],capacity);         //FIND THE INDEX OF THE PAGE IN MAINMEMORY
                //printf("Size is not full refered page %d index %d\n",pages[i],index);
                array->use[index][3]=1;
            }
        }
        else                                                   // IF ALL THE FRAMES ARE FULL IN MAINMEMORY
        {
            if(element_present(mm->frame,pages[i],capacity)==0)             //IF THE PAGE IS NOT PRESENT IN MAINMEMORY
            {
                pagefault++;
                //print(array->use);
                int index=lower_value(array->use,capacity);         //RETURNS THE INDEX OF THE FRAME WHICH HAS LOWER DECIMAL USE ARRAY VALUE
                renue_use(array->use,index);                        //SINCE WE ARE CHANGING THAT CORRESPONING FRAME CHANGE THE USE BITS
                mm->frame[index]=pages[i];
                //printf("Inserted a page %d in index %d\n",pages[i],index);
            }
            else
            {
                int index=find_index(mm->frame,pages[i],capacity);       //SAME INSTRUCTION IN THE FIRST IF CONDITION
                array->use[index][3]=1;
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
// void main()
// {
//     int pages[]={3, 2, 3, -1, 8, 0, 3, -1, 3, 0, 2, -1, 6, 3, 4, 7};            //HERE -1 INDICATES THE TIME INTERVAL
//     int out=page_replacement(16,5,pages);            //NO OF PAGES,NO OF FRAMES,PAGES REFERED
//     printf("# of pagefault is %d\n",out);
// }
