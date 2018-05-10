// SharedMemoryWriter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

#define gcSharedMemorySize	512

int main(int argc, char *argv[])
{
	if (argc >= 2)
	{

		HANDLE hMapFile1 = OpenFileMappingA(
			FILE_MAP_ALL_ACCESS,
			NULL,
			argv[1]);

		if (hMapFile1 == nullptr)
		{
			std::cout << "Could not open shared memory";

			return 0;
		}
		LPWSTR pBuf = (LPWSTR)MapViewOfFile(hMapFile1,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			gcSharedMemorySize);

		char *memoryContents = "QuickBooks Enterprise 2018";
		
		CopyMemory((PVOID)pBuf, memoryContents, (strlen(memoryContents) * sizeof(char)));

		UnmapViewOfFile(pBuf);

		CloseHandle(hMapFile1);
	}
	return 0;
}