#include "stdafx.h"
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

//Creating 3 condition variable to perform synchronization in 3 different functions using wait and notify function on condition variable
condition_variable cv1, cv2, cv3;
//creating mutex variable to lock and unlock the resource    
mutex m1;
void function1()
{
	//creating unique_lock on the mutex so that we don't have to take care whether mutex is unlocked or not, as mutex gets unlocked as soon as unique_lock is out of scope (using concept of RAII)
	unique_lock<mutex> lock(m1);
	for (int i = 0; i<10; i += 3)
	{
		cout << "Thread :1 - " << i << endl;

		//We notify function2 using notify_one function, once we are done printing values from function one and makes function1 in wait state by calling wait function
		cv2.notify_one();
		cv1.wait(lock);
	}

}
void function2()
{
	unique_lock<mutex> lock(m1);
	for (int i = 1; i<10; i += 3)
	{
		cout << "Thread :2 - " << i << endl;

		//We notify function3 using notify_one function, once we are done printing values from function2 and makes function2 in wait state by calling wait function
		cv3.notify_one();
		cv2.wait(lock);
	}
}

void function3()
{
	unique_lock<mutex> lock(m1);
	for (int i = 2; i<10; i += 3)
	{
		cout << "Thread :3 - " << i << endl;

		//We notify function1 using notify_one function, once we are done printing values from function3 and makes function3 in wait state by calling wait function
		cv1.notify_one();
		cv3.wait(lock);
	}
}

int main()
{
	//creating 3 threads (t1, t2 & t3) and associating functions with each thread
	thread t1(function1);
	thread t2(function2);
	thread t3(function3);

	t1.join();
	t2.join();
	t3.join();

	
	return 0;
}