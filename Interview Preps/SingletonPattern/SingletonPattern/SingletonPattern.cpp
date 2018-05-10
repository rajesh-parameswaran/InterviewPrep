#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
mutex mtx;

class Singleton
{
private:
	static Singleton *single;
	Singleton()
	{
		//private constructor
	}
public:
	
	~Singleton()
	{
		
	}

	static Singleton* getInstance()
	{
		if (single == NULL)
		{
			lock_guard<mutex> lck(mtx);
			if (single == NULL)
			{
				single = new Singleton();
				cout << "returning new object" << endl;
			}
		}
		else
		{
			cout << "returning existing object" << endl;
		}
		return single;
	}

	void method()
	{
		cout << "Method of the singleton class" << endl;
	}
};
Singleton* Singleton::single = NULL;

int main()
{
	Singleton *sc1, *sc2;
	sc1 = Singleton::getInstance();
	sc1->method();
	sc2 = Singleton::getInstance();
	sc2->method();

	return 0;
}