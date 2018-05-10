// CreatingThreads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <strsafe.h>

using namespace std;

#define MAX_THREADS	50

DWORD WINAPI MyThreadFunction(LPVOID lparam);

typedef struct MyData
{
	int data1;
	int data2;
} MYDATA, *PMYDATA;

int _tmain(int argc, _TCHAR* argv[])
{
	PMYDATA pDataArray[MAX_THREADS];
	DWORD dwThreadIds[MAX_THREADS];
	HANDLE hThreads[MAX_THREADS];

	for (int nIndex = 0; nIndex < MAX_THREADS; nIndex++)
	{
		pDataArray[nIndex] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));

		if (pDataArray[nIndex] == NULL)
		{
			ExitProcess(2);
		}

		pDataArray[nIndex]->data1 = (1000 * nIndex) + nIndex;
		pDataArray[nIndex]->data2 = (1000 * nIndex) + nIndex + 1;


		hThreads[nIndex] = CreateThread(NULL, 0, MyThreadFunction, pDataArray[nIndex], 0, &dwThreadIds[nIndex]);
		cout << endl << endl << "Creating Thread:: " << nIndex << endl;

		if (hThreads[nIndex] == NULL)
		{
			cout << "Error creating thread" << endl;
			ExitProcess(3);
		}
	}

	cout << endl << "Waiting for Threads to complete execution:: " << endl;
	WaitForMultipleObjects(MAX_THREADS, hThreads, TRUE, INFINITE);

	for (int nIndex = 0; nIndex < MAX_THREADS; nIndex++)
	{
		CloseHandle(hThreads[nIndex]);
		if (pDataArray[nIndex] != NULL)
		{
			HeapFree(GetProcessHeap(), 0, pDataArray[nIndex]);
			pDataArray[nIndex] = NULL;
		}
	}
	return 0;
}

DWORD WINAPI MyThreadFunction(LPVOID lParam)
{
	PMYDATA pMyData;

	pMyData = (PMYDATA) lParam;

	if (pMyData != NULL)
	{
		cout << "Parameters:: Data1 :: " << pMyData->data1 << " :: Data2 :: " << pMyData->data2 << endl;
	}

	return 0;

}