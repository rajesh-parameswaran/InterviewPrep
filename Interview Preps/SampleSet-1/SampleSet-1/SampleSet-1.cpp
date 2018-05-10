// SampleSet-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>


using namespace std;

class CBase
{
public:
	CBase()
	{
		cout << "Calling Base::Constructor" << endl;
	}

	virtual ~CBase()
	{
		cout << "Calling Base::Destructor" << endl;
	}


	virtual void Print()
	{
		cout << "CBase::Print" << endl;

	}


};

class CDerived : public CBase
{
public:
	CDerived()
	{
		cout << "Calling Derived::Constructor" << endl;
	}

	~CDerived()
	{
		cout << "Calling Derived::Destructor" << endl;
	}

	void Data()
	{

	}

	void Print()
	{
		cout << "CDerived::Print" << endl;
	}

};

class CDerived2 : public CBase
{
public:
	CDerived2()
	{
		cout << "Calling Derived2::Constructor" << endl;
	}

	~CDerived2()
	{
		cout << "Calling Derived2::Destructor" << endl;
	}

	void Data()
	{

	}

	void Print()
	{
		cout << "CDerived2::Print" << endl;
	}

};

class CDerived3 : public CBase
{
public:
	CDerived3()
	{
		cout << "Calling Derived3::Constructor" << endl;
	}

	~CDerived3()
	{
		cout << "Calling Derived3::Destructor" << endl;
	}

	void Data()
	{

	}

	

};

int &fun()
{
	static int x = 10;
	cout << "X: " << x << endl;
	return x;
}

void Temp1(char* &x, char* &y)
{
	char *temp = x;
	x = y;
	y = temp;
}

class Point
{
	int x, y;
public:
	Point() {  }
	Point(const Point &p) { x = p.x; y = p.y; }
	int getX() { return x; }
	int getY() { return y; }
};

class Point1 {
public:
	Point1() { cout << "Normal Constructor called\n"; }
	Point1(const Point1 &t) { cout << "Copy constructor called\n"; }
};

class A
{
protected:
	int x;
public:
	A()
	{
		x = 10;
	}
	int getX()
	{
		return x;
	}
};

class B : public A
{
public:
	void SetX(int temp)
	{
		A::x = temp;
	}

	
};

class Test
{
	/* Class data members */
public:
	Test(Test &t) { /* Copy data members from t*/ }
	Test()        { /* Initialize data members */ }
};

Test fun1()
{
	cout << "fun1() Called\n";
	Test t;
	return t;
}


class VTableTestBase
{
	//int x;
public:
	VTableTestBase()
	{

	}
	virtual ~VTableTestBase()
	{

	}
	virtual void Print(){}
	
	
};


class VTableTestBase2
{
	//int y;
public:
	VTableTestBase2()
	{

	}
	virtual ~VTableTestBase2()
	{

	}
	virtual void Print2()
	{
	}

};


class VTableNewDerived : public VTableTestBase, public VTableTestBase2
{
	//int z;
public:
	VTableNewDerived()
	{

	}
	virtual ~VTableNewDerived()
	{

	}
	virtual void Print3(){}

};

class VTableTestDerived1 : public VTableTestBase
{
	//int x;
public:
	VTableTestDerived1()
	{

	}
	virtual void Print()
	{
		cout << "VTableTestDerived1::Print" << endl;
	}
	virtual void Print2()
	{
		cout << "VTableTestDerived1::Print2" << endl;
	}

	virtual void Print3()
	{
		cout << "VTableTestDerived1::Print3" << endl;
	}

};

void Fun1(int a, char b)
{
	cout << "Int::Char -> " << a << " :: " << b << endl;
}


// Explicit and Implicit Constructor
class CExplicitConstruct
{
	int x;
public:
	CExplicitConstruct(int nVal) :x(nVal)
	{
		cout << "Value Initialized at constructor: " << x << endl;
	}

	friend void Display(CExplicitConstruct obj);
};

void Display(CExplicitConstruct obj)
{
	cout << "Display::Val of Object: " << obj.x << endl;
}

// _tmain macro decides which one to use based on the character set.
// if UNICODE, it uses wmain, else uses main
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Sample Print";

	CBase *pBase = new CBase();

	CDerived *pDerived = new CDerived();
	pDerived->Print();

	CDerived2 *pDerived2 = new CDerived2();

	CBase *pBase1 = new CDerived();
	pBase1->Print();

	pBase1 = pDerived;
	pBase1->Print();

	pBase1 = pDerived2;

	pBase1->Print();

	pBase->Print();

	CDerived3 *pDerived3 = new CDerived3;

	pBase = pDerived3;

	pBase->Print();
	delete pBase;


	int a = 10;

	int *aa = &a;

	int &aaa = a;

	cout << a << endl;

	cout << *aa << endl;

	cout << aa << endl;

	cout << aaa << endl;

	fun() = 30;

	cout << fun() << endl;

	char * str1 = "GEEKS";
	char * str2 = "OFF";
	Temp1(str1, str2);

	cout << "str1: " << str1 << endl;
	cout << "str2: " << str2 << endl;

	int x = 10;
	int *ptr = &x;
	int *ptr2 = ptr;
	cout << (*ptr2) << endl;
	cout << ptr << endl; 
	
	Point p1;
	Point p2 = p1;
	cout << "x = " << p2.getX() << " y = " << p2.getY() << endl;

	Point1 *t1, *t2;
	t1 = new Point1();
	t2 = new Point1(*t1);
	Point1 t3 = *t1;
	Point1 t4;
	t4 = t3;


	A obj1;

	cout << obj1.getX() << endl;
	B obj2;

	cout << obj2.getX() << endl;
	obj2.SetX(20);
	cout << obj2.getX() << endl;

	Test obj6;
	Test obj7 = fun1();


	cout << sizeof(VTableTestBase) << endl;

	VTableTestDerived1 v2;
	cout << sizeof(v2) << endl;

	cout << sizeof(VTableNewDerived) << endl;

	// Function Pointer
	void(*Fun1_ptr)(int, char) = Fun1;
	
	Fun1_ptr(10, 'C');

	Display(5000);

	signed char n = 130, m = -130;

	cout << "N : " << (int)n << "  M : " << (int)m << std::endl;
	return 0;
}

