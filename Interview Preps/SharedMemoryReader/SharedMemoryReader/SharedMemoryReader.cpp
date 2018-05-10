// SharedMemoryReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <time.h>
#define gcSharedMemorySize	512

const int MAX_LENGTH = 32;


int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int nVal = 0;
	char szArray[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char strRand[MAX_PATH] = { 0 };

	for (int nIndex = 0; nIndex < MAX_LENGTH; nIndex++)
	{

		strRand [nIndex] =  szArray[(rand() % 62)];
	}
	std::cout << strRand << std::endl;

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	char strInput[MAX_PATH] = { 0 };

	strcpy_s(strInput, "C:\\SharedMemoryWriter.exe ");
	strcat_s(strInput, strRand);

	HANDLE hMapFile = CreateFileMappingA(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		gcSharedMemorySize,
		strRand);

	if (hMapFile == nullptr)
	{
		std::cout << "Could not create shared memory";

		return 0;
	}

	LPWSTR pBuf = (LPWSTR)MapViewOfFile(hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		gcSharedMemorySize);


	if (!CreateProcessA(NULL,   // No module name (use command line)
		strInput,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return 0;
	}

	HANDLE hMapFile1 = OpenFileMappingA(
		FILE_MAP_ALL_ACCESS,
		NULL,
		strRand);

	if (hMapFile1 == nullptr)
	{
		std::cout << "Could not open shared memory";

		return 0;
	}
	LPWSTR pBuf1 = (LPWSTR)MapViewOfFile(hMapFile1,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		gcSharedMemorySize);

	std::wcout << std::endl << L"Buf: " << pBuf1 << std::endl;

	UnmapViewOfFile(pBuf1);
	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile1);
	CloseHandle(hMapFile);

	return 0;
}

