// EggDroppingProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

class EggDroppingProblem
{
public:
	long CalculateEggs(int nEggs, int nFloors)
	{
		int **T = new int*[nEggs + 1];

		for (int nIndex = 0; nIndex <= nEggs; nIndex++)
		{
			T[nIndex] = new int[nFloors + 1];
		}

		// Index [0] will not be used

		// Initialize the first floor to the same number of floors
		for (int nIndex = 0; nIndex <= nFloors; nIndex++)
		{
			T[1][nIndex] = nIndex;
		}

		int nVal = 0;
		// Calculate for the rest of the floors
		for (int nLoopEggs = 2; nLoopEggs <= nEggs; nLoopEggs++)
		{
			for (int nLoopFloors = 1; nLoopFloors <= nFloors; nLoopFloors++)
			{
				T[nLoopEggs][nLoopFloors] = 10000;

				for (int k = 1; k <= nLoopFloors; k++){
					nVal = 1 + max(T[nLoopEggs - 1][k - 1], T[nLoopEggs][nLoopFloors - k]);
					if (nVal < T[nLoopEggs][nLoopFloors]){
						T[nLoopEggs][nLoopFloors] = nVal;
					}
				}
			}

		}

		nVal = T[nEggs][nFloors];

		for (int nIndex = 0; nIndex < nEggs + 1; nIndex++)
		{
			delete []T[nIndex];
		}

		delete []T;

		return nVal;

	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	int nFloor, nEggs;

	printf("Enter the Number of Floors: ");
	scanf_s("%d", &nFloor);
	printf("\nEnter the Number of Eggs: ");
	scanf_s("%d", &nEggs);

	EggDroppingProblem objEggDroppingProblem;

	printf("Number of Iterations for %d eggs with %d floor is: %d \n\n", nEggs, nFloor, objEggDroppingProblem.CalculateEggs(nEggs, nFloor));

	return 0;
}

