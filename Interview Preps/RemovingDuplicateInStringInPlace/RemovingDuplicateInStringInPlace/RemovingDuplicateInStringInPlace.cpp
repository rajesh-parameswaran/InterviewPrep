// RemovingDuplicateInStringInPlace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <set>
using namespace std;

void removeDuplicates(char* str, int nLen)
{
	char str1[255] = { 0 };
	int index = 0;
	int j;

	for (int i = 0; i < nLen; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (str[i] == str[j])
				break;
		}

		if (i == j)
		{
			str[index] = str[j];
			str1[index] = str[j];
			index++;
		}
		
	}
	str1[index] = '\0';
	str[index] = '\0';
	cout << str << endl;
	cout << str1 << endl;
}




void removeDuplicateByMap(char str[], int n)
{
	// create a set using string characters
	// excluding '\0'
	set<char>s (str, (str + n));
	
	int nIndex = 0;
	for (auto x:s)
	{
		str[nIndex++] = x;
	}
	str[nIndex] = '\0';
	
}


int _tmain(int argc, _TCHAR* argv[])
{
	char str[] = "Hello World String";
	removeDuplicates(str, strlen(str));

	char str1[] = "Hello World String";
	int n = sizeof(str1) / sizeof(str1[0]);
	removeDuplicateByMap(str1, n - 1);
	cout << endl << str1 << endl;

	return 0;
}

