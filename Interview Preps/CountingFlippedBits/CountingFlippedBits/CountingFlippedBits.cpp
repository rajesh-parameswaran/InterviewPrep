// CountingFlippedBits.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int GetFlipCount(int nVal)
{
	int nCount = 0;
	while (nVal)
	{
		nCount = nCount + (nVal & 1);
		nVal = nVal >> 1;
	}
	return nCount;
}
int FlipCount(int a, int b)
{
	return GetFlipCount(a^b);
}
int _tmain(int argc, _TCHAR* argv[])
{
	int nVal1, nVal2;
	printf("\n Enter First Number: ");
	scanf_s("%d", &nVal1);

	printf("\n Enter Second Number: ");
	scanf_s("%d", &nVal2);

	printf("\n Flip Count: %d \n\n", FlipCount(nVal1, nVal2));

	return 0;
}

