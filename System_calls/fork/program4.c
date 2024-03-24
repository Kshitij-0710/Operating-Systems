#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int p=fork();
	
	if(p==0)
	{
		int q=fork();
	}
	else
	{
		printf("This is not a child process");
	}
}
