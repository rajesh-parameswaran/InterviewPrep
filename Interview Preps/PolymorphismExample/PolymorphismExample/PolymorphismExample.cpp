// PolymorphismExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class CShape
{
	int nWidth;
	int nHeight;

public:
	CShape() : nWidth(0), nHeight(0)
	{

	}

	CShape(int nWidth, int nHeight)
	{
		this->nWidth = nWidth;
		this->nHeight = nHeight;
	}

	int getHeight()
	{
		return nHeight;
	}

	int getWidth()
	{
		return nWidth;
	}

	virtual int area()
	{
		cout << "CShape::area ";
		return nWidth*nHeight;
	}

	virtual void Display() = 0;
};

class CSquare : public CShape
{
public:
	CSquare(int nWidth, int nHeight) : CShape(nWidth,nHeight)
	{
		
	}

	int area()
	{
		cout << "CSquare::area ";
		return CShape::getHeight() * CShape::getWidth();
	}

	virtual void Display()
	{
		cout << "CSquare::Display" << endl;
	}
};

class CRectangle : public CShape
{
public:
	CRectangle(int nWidth, int nHeight) : CShape(nWidth, nHeight)
	{

	}

	int area()
	{
		cout << "CRectangle::area ";
		return CShape::getHeight() * CShape::getWidth();
	}

	virtual void Display()
	{
		cout << "CRectangle::Display" << endl;
	}
};

template <typename T>
T  Max(T const& a, T const& b) {
	return a < b ? b : a;
}
class CTest
{
public:
	virtual ~CTest();
	virtual void Display() {}
	virtual void Temp() {}
};

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{

		CShape *pShape = NULL;

		CSquare pSquare(10, 20);
		CRectangle pRect(10, 20);

		pShape = &pSquare;

		cout << pShape->area() << endl;
		pShape->Display();

		pShape = &pRect;

		cout << pShape->area() << endl;
		pShape->Display();

		int n1 = 22, n2 = 33;
		double d1 = 55.89, d2 = 55.98;

		cout << endl << "Max of " << n1 << " and " << n2 << " is " << Max(n1, n2);
		cout << endl << "Max of " << d1 << " and " << d2 << " is " << Max(d1, d2);

		cout << endl << endl;

		cout << "Size of class: CTest :  " << sizeof(CTest) << endl;

		cout << "TypeId: " << typeid(pShape).name() << endl;
		cout << "TypeId: " << typeid(pSquare).name() << endl;

	}
	catch (...)
	{
		
		cout << "Exception";
	}

	return 0;
}

