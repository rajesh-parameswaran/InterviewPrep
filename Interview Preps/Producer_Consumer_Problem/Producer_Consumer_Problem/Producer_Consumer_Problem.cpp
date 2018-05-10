#include "stdafx.h"
#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 
using namespace std;

using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using namespace std;

static const int MagicNumber = 30;    
                        // Magic number used for the sample, remove it for production code 
void Producer(mutex &m_mutex, queue<int> &m_queue, condition_variable  &m_alarm, bool &m_isNotified, bool &m_haveData)
{
	for (int i = 0; i < MagicNumber; ++i)
	{
		sleep_for(milliseconds(500));                    // Executing some long operation 
		lock_guard<mutex> lock(m_mutex);                // Enter critical section 
		cout << "producer " << i << endl;
		m_queue.push(i);                                // Add data chunk to the queue 
		m_isNotified = true;                            // Consumer can be woken up and it is not a fluke (see spurious wakeups) 
		m_alarm.notify_one();                            // Notify consumer 
	}

	lock_guard<mutex> lock(m_mutex);                    // Work is done, app can exit 
	m_isNotified = true;
	m_haveData = false;
	m_alarm.notify_one();
}

void Consumer(mutex &m_mutex, queue<int> &m_queue, condition_variable  &m_alarm, bool &m_isNotified, bool &m_haveData)
{
	while (m_haveData)                                    // In production, this check will be done on whether there is more data in the queue 
	{
		unique_lock<mutex> lock(m_mutex);                // Must aquire unique_lock with condition variables 

		while (!m_isNotified)                            // Prevents from spurious wakeup 
		{
			m_alarm.wait(lock);                            // Wait for a signal from producer thread 
		}

		while (!m_queue.empty())                        // Process data and remove it from the queue 
		{
			cout << "consumer " << m_queue.front() << endl;
			m_queue.pop();
		}

		m_isNotified = false;                            // Protect from spurious wakeup 
	}
}
int main()
{
	condition_variable    m_alarm;                            // Notifies threads that more work is available 
	mutex                m_mutex;                            // Synchronizes access to shared variables 
	queue<int>            m_queue;                            // Accumulates data chunks 
	bool                m_isNotified = false;                // This is a guard to prevent accidental spurious wakeups 
	bool                m_haveData = true;                // Only used for this sample to end consumer thread, not required in production code 

	thread producer(Producer, ref(m_mutex), ref(m_queue), ref(m_alarm), ref(m_isNotified), ref(m_haveData));

	thread consumer(Consumer, ref(m_mutex), ref(m_queue), ref(m_alarm), ref(m_isNotified), ref(m_haveData));

	// Join threads and finish app 
	producer.join();
	consumer.join();

	return 0;
}