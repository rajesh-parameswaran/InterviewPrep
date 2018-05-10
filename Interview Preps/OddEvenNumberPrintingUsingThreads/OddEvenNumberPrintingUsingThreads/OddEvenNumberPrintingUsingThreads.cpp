// OddEvenNumberPrintingUsingThreads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <initializer_list>

using namespace std;

void ThreadFun(int nVal1, int nVal2, mutex &mtx)
{
	cout << "Inside thread Fun" << endl;
	lock_guard<mutex> lck(mtx);
	cout << nVal1 << "  ::  " << nVal2 << endl;
	cout << this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::seconds(3));
}
int _tmain(int argc, _TCHAR* argv[])
{
	initializer_list<int> il = { 1, 2, 3, 4, 5 };

	int nVal1 = 50;
	int nVal2 = 100;
	mutex mtx;
	thread t1(ThreadFun, nVal1, nVal2, ref(mtx));
	this_thread::sleep_for(chrono::milliseconds(5000));
	thread t2(ThreadFun, 22, 33, ref(mtx));

	cout << this_thread::get_id() << endl;

	
	t1.join();
	t2.join();
	return 0;
}

 