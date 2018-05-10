// DisplayPatternSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int n = 10;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if ((i == 0) || (j == 0) || (i == n) || (j == n) || (i == j) || (j == (n - i)))
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
	return 0;
}

