// SampleSet-3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void PrintArray(int *arr, int nSize)
{
	cout << endl << "Printing Array: ";
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		cout << arr[nIndex] << "  ";
	}
}

void PrintOutput(int *arr, int nSize)
{
	cout << endl << endl << "Printing Output: ";
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		cout << arr[nIndex] << "  ";
	}

	cout << endl;
}
void SelectionSort(int *arr, int nSize)
{
	int temp = 0;
	for (int nLoop = 0; nLoop < nSize - 1; nLoop++)
	{
		for (int nSubLoop = nLoop + 1; nSubLoop < nSize; nSubLoop++)
		{
			if (arr[nLoop] > arr[nSubLoop])
			{
				temp = arr[nLoop];
				arr[nLoop] = arr[nSubLoop];
				arr[nSubLoop] = temp;
			}
		}
		PrintArray(arr, nSize);
	}
	PrintArray(arr, nSize);
}

void BubbleSort(int *arr, int nSize)
{
	int temp = 0;
	for (int nLoop = 0; nLoop < nSize - 1; nLoop++)
	{
		for (int nSubLoop = 0; nSubLoop < (nSize - nLoop - 1); nSubLoop++)
		{
			if (arr[nSubLoop] > arr[nSubLoop+1])
			{
				temp = arr[nSubLoop];
				arr[nSubLoop] = arr[nSubLoop + 1];
				arr[nSubLoop + 1] = temp;
			}
		}
		PrintArray(arr, nSize);
	}
	PrintArray(arr, nSize);
}
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;    
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void BinarySearch(int *arr, int nSize)
{
	int nMin = 0;
	int nMax = nSize - 1;
	int nMid = (nMin + nMax) / 2;
	int nKey = 0;

	cout << "Enter a Number to Find: ";
	cin >> nKey;
	
	while (nMin <= nMax)
	{
		if (arr[nMid] == nKey)
		{
			cout << endl << "Element Found: " << arr[nMid] << endl;
			break;
		}
		else if (arr[nMid] < nKey)
			nMin = nMid + 1;
		else
			nMax = nMid - 1;

		nMid = (nMin + nMax) / 2;
	}

	if (nMin > nMax)
	{
		cout << "Element " << nKey << " Not Found: " << endl;
	}
	
}

void GetInput(int *arr, int nSize)
{
	int nIndex = 0;
	int nVal = 0;
	do
	{
		cin >> nVal;
		arr[nIndex++] = nVal;
	} while (nIndex < nSize);

}
int _tmain(int argc, _TCHAR* argv[])
{
	try
	{

		int nCount = 0;
		int nIter = 0;

		cout << endl << "Number of Sets: ";
		cin >> nIter;

		for (int nLoop = 0; nLoop < nIter; nLoop++)
		{
			cout << "Iteration: " << nLoop + 1 << endl;

			cout << "Size of Array: ";
			cin >> nCount;

			int *nArr = new int[nCount];
			ZeroMemory(nArr, (nCount * sizeof(int)));

			

			GetInput(nArr, nCount);
			
			quickSort(nArr, 0, nCount - 1);

			//BubbleSort(nArr, nCount);

			BinarySearch(nArr, nCount);

			PrintOutput(nArr, nCount);

			delete[]nArr;
		}
	}
	catch (...)
	{
		cout << "Exception Caught!!" << endl;
	}
	return 0;
}

