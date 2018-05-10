// SmartPointer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class CRefCount
{
	int nCount;

public:
	void AddRef()
	{
		nCount++;
		cout << "Ref Count: " << nCount << endl;
	}

	int Release()
	{
		nCount--;
		cout << "Release Count: " << nCount << endl;
		return nCount;
	}
};

template <class T>
class CSmartPointer
{
	T *ptr;
	CRefCount *pRC;
public:
	CSmartPointer(T *objPtr = NULL) : ptr(objPtr), pRC(0)
	{
		pRC = new CRefCount();
		pRC->AddRef();
		cout << "Constructor invoked.." << endl;
	}

	~CSmartPointer()
	{
		cout << "Destructor invoked.." << endl;

		if (pRC->Release() == 0)
		{
			cout << "Object Destructed.." << endl;
			delete ptr;
			delete pRC;
		}
	}

	CSmartPointer(const CSmartPointer& objPtr)
	{
		cout << "copy constructor invoked.." << endl;
		ptr = objPtr.ptr;
		pRC = objPtr.pRC;
		pRC->AddRef();
	}

	CSmartPointer& operator=(const CSmartPointer& objPtr)
	{
		cout << "assignment operator invoked.." << endl;
		if (this != &objPtr)
		{
			cout << "objects are non-identical.." << endl;
			if (pRC->Release() == 0)
			{
				cout << "object destroyed and assigned.." << endl;
				delete ptr;
				delete pRC;
			}
			ptr = objPtr.ptr;
			pRC = objPtr.pRC;
			pRC->AddRef();
		}
		else
		{
			cout << "self assigned.." << endl;
		}
		return *this;
	}
	
	T& operator*()
	{
		cout << "operator* invoked.." << endl;
		return *ptr;
	}

	void Display()
	{
		cout << "Display invoked..: " << *ptr << endl;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{

	CSmartPointer<int> ptr(new int(25));

	ptr.Display();

	CSmartPointer<int>ptr1 = ptr; // Copy Constructor
	
	//*ptr = 50;

	ptr.Display();

	cout << "Value of ptr: " << *ptr << endl;

	
	CSmartPointer<int>ptr2;
	ptr2 = ptr1; // Assignment operator

	ptr2.Display();


	cout << "Char ptr" << endl;
	CSmartPointer<char> ptr4(new char('C'));
	ptr4.Display();
	cout << "Char ptr1" << endl;
	return 0;
}

