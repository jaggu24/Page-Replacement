#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	FILE *fptr;
	char ab[50],sq[10];
	fptr=fopen("r1.txt","r");
	if(fptr==NULL)
	{
		printf("No such file ");
		return 2;
	}
	int a,size=20;
	char *buf;
	buf=(char *)malloc(size);
	while(!feof(fptr))
	{
		getdelim(&buf,&size,',',fptr);
		if(buf[1]=='\n')
			printf("Hi");
		if(buf[strlen(buf)-1]==',')
			buf[strlen(buf)-1]='\0';
		a=atoi(buf);
		printf("%d\t",a);
//		printf("%s    ",buf);
	}
	return 0;
}
