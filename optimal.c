#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int is_available(int *pages,int n,int check)
{
	int flag=0;
	for(int i=0;i<n;i++)
	{
		if(pages[i]==check)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		return 0;
	}
	return 1;
}
int give_index(int *str,int start,int end,int check)
{
	int flag=0;
	for(int i=start;i<end;i++)
	{
		if(check==str[i])
		{
			flag=1;
			return i;
		}
	}
	if(flag==0)
	{
		return 1000;
	}
	return 0;
}
int next_available(int *next,int n,int *str,int size,int *pages,int from)
{
	for(int i=0;i<n;i++)
	{
		next[i]=give_index(str,from,size,pages[i]);
	}
	return 0;
}
int choose(int *next,int n)
{
	int max=0,index=0;
	for(int i=0;i<n;i++)
	{
		if(max<next[i])
		{
			max=next[i];
			index=i;
		}
	}
	return index;
}
int main()
{
	int *str;
	int size=0,pages_count=3,hits=0,faults=0;					//Initilizing variables
	int *pages_available,*next_future;
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
        while(!feof(fptr))								//Checking no. of elements in file
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
	str=(int *)malloc(sizeof(int)*size+1);						//Allocate desired size
	int length = 0;
	while(!feof(fptr))								//Read Storing elements into str
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
	for(;pages_count<=6;pages_count++)						//Check for different sizes
	{
		pages_available=(int *)malloc(sizeof(int)*pages_count);
		next_future=(int *)malloc(sizeof(int)*pages_count);			//Allocate for pages and next available pages
		hits=0;faults=0;
		for(int i=0;i<size;i++)							//Run algorith for the elements of str
		{
			if(is_available(pages_available,pages_count,str[i]))
			{
				hits+=1;
			}
			else
			{
				faults+=1;
				next_available(next_future,pages_count,str,size,pages_available,i);
				int replace=choose(next_future,pages_count);
				pages_available[replace]=str[i];
			}
		}
		printf("%d,",faults);
		free(pages_available);							//Free theor memories
		free(next_future);
	}
	printf("\n");
	free(str);
	return 0;
}

