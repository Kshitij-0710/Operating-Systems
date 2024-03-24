#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int p = fork();

	if (p == 0)
	{
		int mat1[2][2] = {{2, 2}, {3, 5}};
		int mat2[2][2] = {{2, 8}, {2, 10}};

		int sum1[2][2];
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				sum1[i][j] = mat1[i][j] + mat2[i][j];
			}
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				printf("%d ", sum1[i][j]);
			}
			printf("\n");
		}
	}
	else
	{
		int n;
		scanf("%d", &n);
		int ctr = 0;
		for (int i = 2; i <= n; i++)
		{
			if (n % i == 0)
			{
				ctr = 2;
				break;
			}
		}
		if (ctr == 2)
		{
			printf("%d is not prime\n", n);
		}
		else
		{
			printf("%d is  prime\n", n);
		}
	}
}
