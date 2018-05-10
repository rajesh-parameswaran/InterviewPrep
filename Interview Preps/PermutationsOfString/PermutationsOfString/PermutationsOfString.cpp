// PermutationsOfString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;
int nCnt = 0;
void swap(char &str1, char &str2)
{
	char temp;
	temp = str1;
	str1 = str2;
	str2 = temp;
}


void Permute(string str1, int startIndex, int endIndex)
{
	int i;
	if (startIndex == endIndex)
	{
		nCnt++;
		cout << str1 << endl;
	}
	else
	{
		for (i = startIndex; i <= endIndex; i++)
		{
			swap(str1[startIndex], str1[i]);
			Permute(str1, startIndex +1, endIndex);
			swap(str1[startIndex], str1[i]);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	string permute;
	int nLen;

	while (permute.compare("end") != 0)
	{
		nLen = nCnt = 0;
		cout << "Enter permute string: ";
		cin >> permute;

		nLen = permute.length();
		Permute(permute, 0, nLen - 1);

		cout << "Combinations: " << nCnt;
		printf("\n\n");
	}
	return 0;
}

