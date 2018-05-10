// JobSequencingProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct JobDetails
{
	string strJobID;
	int deadline;
	int profit;

	JobDetails()
	{
		strJobID = "";
		deadline = 0;
		profit = 0;
	}
};


void Sort(int nSize, JobDetails *pJobDetails)
{
	JobDetails pTempJobDetails;

	for (int i = 0; i < nSize - 1; i++)
	{
		for (int j = 0; j < (nSize - i - 1); j++)
		{
			if (pJobDetails[j].profit < pJobDetails[j + 1].profit)
			{
				pTempJobDetails = pJobDetails[j];
				pJobDetails[j] = pJobDetails[j + 1];
				pJobDetails[j + 1] = pTempJobDetails;
			}
		}
	}
}

void PrintJobDetails(int nSize, JobDetails *pJobDetails)
{
	cout << endl << endl;

	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		cout << "Job Id: " << pJobDetails[nIndex].strJobID << " Job Deadline: " << pJobDetails[nIndex].deadline << " Job Profit: " << pJobDetails[nIndex].profit << endl;
	}
}

void ScheduleJobs(int nSize, JobDetails *pJobDetails)
{
	string *strResult = new string[nSize];
	bool *slot = new bool[nSize];

	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		strResult[nIndex] = "-";
		slot[nIndex] = false;
	}

	for (int i = 0; i < nSize; i++)
	{
		cout << endl << "min(" << nSize << "," << pJobDetails[i].deadline - 1 << ")";
		for (int j = min(nSize, pJobDetails[i].deadline) - 1; j >= 0; j--)
		{
			if (slot[j] == false)
			{
				slot[j] = true;
				strResult[i] = pJobDetails[i].strJobID;
				break;
			}
		}
	}


	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		if (strResult[nIndex] != "-")
			cout << " " << strResult[nIndex]; 
	}

	delete[]strResult;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nSize, nInput, nIndex;
	JobDetails *pJobDetails;
	string strInput;

	cout << endl << "Enter the number of elements: ";
	cin >> nSize;

	pJobDetails = new JobDetails[nSize];

	nIndex = 0;
	strInput = "";
	cout << endl << "Enter the Job ID's: ";
	do
	{
		cin >> strInput;
		(pJobDetails + nIndex)->strJobID = strInput;
		nIndex++;
	}
	while (nIndex < nSize);

	nIndex = 0;
	cout << endl << "Enter the Job deadline's: ";
	do
	{
		cin >> nInput;
		(pJobDetails + nIndex)->deadline = nInput;
		nIndex++;
	} while (nIndex < nSize);

	nIndex = 0;
	cout << endl << "Enter the Job Profit's: ";
	do
	{
		cin >> nInput;
		(pJobDetails + nIndex)->profit = nInput;
		nIndex++;
	} while (nIndex < nSize);

	PrintJobDetails(nSize, pJobDetails);

	// Sort based on profit
	Sort(nSize, pJobDetails);


	// Schedule Jobs
	ScheduleJobs(nSize, pJobDetails);

	PrintJobDetails(nSize, pJobDetails);

	delete[]pJobDetails;

	return 0;
}

