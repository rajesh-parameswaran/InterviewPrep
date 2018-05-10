// NQueenProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Position
{
public:
	int row;
	int col;


	Position()
	{
		row = col = 0;
	}

	Position(int xVal, int yVal)
	{
		row = xVal;
		col = yVal;
	}
};

class NQueenProblem
{
	
public:

	Position* solveNQueenProblem(int nVal)
	{
		Position *positions = new Position[nVal];

		bool bHasSolution = solveNQueensProblemUtil(nVal, 0, positions);
		if (bHasSolution)
			return positions;
		else
			return new Position[0];

		return positions;

	}

	bool solveNQueensProblemUtil(int nVal, int nRow, Position *position)
	{
		if (nVal == nRow)
		{
			return true;
		}

		int nCol;

		for (nCol = 0; nCol < nVal; nCol++)
		{
			bool bFoundSafe = true;

			for (int nQueen = 0; nQueen < nRow; nQueen++)
			{
				if ((position[nQueen].col == nCol) || (position[nQueen].row - position[nQueen].col == nRow - nCol) || (position[nQueen].row + position[nQueen].col == nRow + nCol))
				{
					bFoundSafe = false;
					break;
				}
			}

			if (bFoundSafe)
			{
				// Found the Position, save it
				position[nRow] = Position(nRow, nCol);
				// Start with the next row
				if (solveNQueensProblemUtil(nVal, nRow + 1, position))
				{
					return true;
				}

			}
		}
		return false;
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	NQueenProblem *s = new NQueenProblem();


	int nSize = 0;

	printf( "Enter Number of Queens: ");
	scanf_s("%d", &nSize);

	Position *positions = s->solveNQueenProblem(nSize);
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		printf("\n (%d, %d) ", positions[nIndex].row, positions[nIndex].col);
	}

	printf("\n\n");

	for (int x = 0; x < nSize; x++)
	{
		for (int y = 0; y < nSize; y++)
		{
			if (positions[x].col == y)
				printf(" Q ");
			else
				printf(" x ");
		}
		printf("\n");
	}

	printf("\n\n");

	return 0;
}

