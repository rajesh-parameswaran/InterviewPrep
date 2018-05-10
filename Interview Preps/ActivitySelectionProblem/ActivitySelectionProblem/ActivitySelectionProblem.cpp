// ActivitySelectionProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void Sort(int nMaxCnt, int* startActivity, int* finishActivity)
{
	int tempSwap;
	for (int i = 0; i < nMaxCnt - 1; i++)
	{
		for (int j = 0; j < (nMaxCnt - i - 1); j++)
		{
			if (finishActivity[j] >= finishActivity[j + 1])
			{
				tempSwap = finishActivity[j];
				finishActivity[j] = finishActivity[j + 1];
				finishActivity[j + 1] = tempSwap;

				tempSwap = startActivity[j];
				startActivity[j] = startActivity[j + 1];
				startActivity[j + 1] = tempSwap;
			}
		}
	}
}

void FindMaxActivity(int nMaxCnt, int* startActivity, int * finishActivity)
{
	if (nMaxCnt > 0)
	{
		int nPos = 0;
		cout << "Activities: ";
		cout << "{" << startActivity[0] << ":" << finishActivity[0] << "}";
		for (int nIndex = 1; nIndex < nMaxCnt; nIndex++ )
		{
			if (startActivity[nIndex] >= finishActivity[nPos])
			{
				nPos = nIndex;
				cout << ", {" << startActivity[nIndex] << ":" << finishActivity[nIndex] << "}";
			}

		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	
	int nActivityCnt = 0;
	int *startActivity;
	int *finishActivity;
	int nIndex = 0;
	int nActiviyTime = 0;

	cout << "Enter the count of Activities: ";
	cin >> nActivityCnt;

	startActivity = new int[nActivityCnt];
	finishActivity = new int[nActivityCnt];

	cout << "Enter the Start time for Activities for " << nActivityCnt << " followed by space: ";
	while (nIndex < nActivityCnt)
	{
		

		cin >> nActiviyTime;
		startActivity[nIndex++] = nActiviyTime;
	}

	nIndex = 0;
	cout << "Enter the Finish time for Activities for " << nActivityCnt << " followed by space: ";
	while (nIndex < nActivityCnt)
	{


		cin >> nActiviyTime;
		finishActivity[nIndex++] = nActiviyTime;
	}

	// Sort the Array
	Sort(nActivityCnt, startActivity, finishActivity);


	cout << endl;
	for (int nIndex = 0; nIndex < nActivityCnt; nIndex++)
	{
		cout << startActivity[nIndex] << "\t" << endl;
	}
	
	cout << endl;
	for (int nIndex = 0; nIndex < nActivityCnt; nIndex++)
	{
		cout << finishActivity[nIndex] << "\t" << endl;
	}

	// Find Max Activity
	FindMaxActivity(nActivityCnt, startActivity, finishActivity);

	

	return 0;
}

