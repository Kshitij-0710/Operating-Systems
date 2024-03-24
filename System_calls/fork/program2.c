#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int p=fork();
	
	if(p==0)
	{
		for(int i=0;i<11;i+=2)
		{
			printf("This is a child process\n");
			printf("%d\n",i);
		}
	}
	else
	{
		for(int i=1;i<11;i+=2)
		{
			printf("This is a parent process\n");
			printf("%d\n",i);
		}
	}
	return 0;
}
