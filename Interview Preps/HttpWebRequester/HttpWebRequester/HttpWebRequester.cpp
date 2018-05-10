// HttpWebRequester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <windows.h>
#include <string>
#include <stdio.h>

using std::string;

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996 )

HINSTANCE hInst;
WSADATA wsaData;
SOCKET connectToServer(char *szServerName, WORD portNum);
int getHeaderLength(char *content);
char *readData(long &bytesReturnedOut, char **headerOut);
std::string GetLastErrorAsString();

int main()
{
	const int bufLen = 1024;
	long fileSize;
	char *memBuffer, *headerBuffer;

	memBuffer = headerBuffer = NULL;

	if (WSAStartup(0x101, &wsaData) != 0)
		return -1;

	memBuffer = readData(fileSize, &headerBuffer);
	printf("data returned:\n%s", memBuffer);
	if (fileSize != 0)
	{
		delete(memBuffer);
		delete(headerBuffer);
	}

	WSACleanup();
	return 0;
}




SOCKET connectToServer(char *szServerName, WORD portNum)
{
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	SOCKET conn;

	conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (conn == INVALID_SOCKET)
		return NULL;

	if (inet_addr(szServerName) == INADDR_NONE)
	{
		hp = gethostbyname(szServerName);
	}
	else
	{
		addr = inet_addr(szServerName);
		hp = gethostbyaddr((char*)&addr, sizeof(addr), AF_INET);
	}

	if (hp == NULL)
	{
		closesocket(conn);
		return NULL;
	}

	server.sin_addr.s_addr = *((unsigned long*)hp->h_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(portNum);
	if (connect(conn, (struct sockaddr*)&server, sizeof(server)))
	{
		printf("%s", GetLastErrorAsString().c_str());

		closesocket(conn);
		return NULL;
	}
	return conn;
}

int getHeaderLength(char *content)
{
	const char *srchStr1 = "\r\n\r\n", *srchStr2 = "\n\r\n\r";
	char *findPos;
	int ofset = -1;

	findPos = strstr(content, srchStr1);
	if (findPos != NULL)
	{
		ofset = findPos - content;
		ofset += strlen(srchStr1);
	}

	else
	{
		findPos = strstr(content, srchStr2);
		if (findPos != NULL)
		{
			ofset = findPos - content;
			ofset += strlen(srchStr2);
		}
	}
	return ofset;
}

std::string GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}

char *readData(long &bytesReturnedOut, char **headerOut)
{
	const int bufSize = 512;
	char readBuffer[bufSize], sendBuffer[bufSize];
	char *tmpResult = NULL, *result;
	SOCKET conn;
	string server, filepath, filename;
	long totalBytesRead, thisReadSize, headerLen;
	char *tempBuf = "POST /api/v2/entitlements HTTP/1.1 \r\nAccept: application/json\r\nContent-Type: application/json\r\nauthorization: Intuit_APIKey intuit_apikey=preprdakyresEm8fEWmc3b2JLj8N5z4dpKEObzrF\r\nintuit_tid: cb24f553-8c98-44f7-a398-b797d662e61c\r\nHost: quickbooksratable-qal.api.intuit.com\r\nContent-Length: 196\r\nConnection: Keep-Alive\r\n\r\n{\r\n\"EOC\": \"550956\",\r\n\"MajorVersion\": \"27\",\r\n\"MinorVersion\": \"3\",\r\n\"Nfr\": \"false\",\r\n\"QBLicense\": \"9245-8601-6933-296\",\r\n\"ReleaseLevel\": \"4\",\r\n\"SKU\": \"bel\",\r\n\"Source\": \"install\",\r\n\"Trial\": \"false\"\r\n}";

	char *tempBuf1 = "GET /admin/orders/count.json HTTP/1.1 \r\nauthorization: Basic MjhjZTgzNmViNWQ1NDRkMjA5ODU1YWVjZDY3NDg1MTQ6NDQwOTU0OTE3Y2YxMDg5ZjQ1YjVhY2MwNTJlYmUyODk=\r\nHost: abcassociates.myshopify.com\r\n\r\n";

	///////////// step 1, connect //////////////////////
	//conn = connectToServer("50.89.147.58", 80);
	//conn = connectToServer("quickbooksratable-qal.api.intuit.com", 80);
	conn = connectToServer("abcassociates.myshopify.com", 80); 

	int nSend = send(conn, tempBuf1, strlen(tempBuf1), 0);

	//    SetWindowText(edit3Hwnd, sendBuffer);
	printf("Buffer being sent:\n%s", sendBuffer);

	///////////// step 3 - get received bytes ////////////////
	// Receive until the peer closes the connection
	totalBytesRead = 0;
	while (1)
	{
		memset(readBuffer, 0, bufSize);
		thisReadSize = recv(conn, readBuffer, bufSize, 0);

		if (thisReadSize <= 0)
			break;

		tmpResult = (char*)realloc(tmpResult, thisReadSize + totalBytesRead);

		memcpy(tmpResult + totalBytesRead, readBuffer, thisReadSize);
		totalBytesRead += thisReadSize;
	}

	headerLen = getHeaderLength(tmpResult);
	long contenLen = totalBytesRead - headerLen;
	result = new char[contenLen + 1];
	memcpy(result, tmpResult + headerLen, contenLen);
	result[contenLen] = 0x0;
	char *myTmp;

	myTmp = new char[headerLen + 1];
	strncpy(myTmp, tmpResult, headerLen);
	myTmp[headerLen] = NULL;
	delete(tmpResult);
	*headerOut = myTmp;

	bytesReturnedOut = contenLen;
	closesocket(conn);
	return(result);
}