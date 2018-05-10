// ObserverPattern-CricketScoreBoard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class CObserver
{
public:
	virtual void Update(int nRuns, int nWicket, float fOvers) = 0;
};

class CSubject
{
public:
	virtual void registerObserver(CObserver *objObserver) = 0;
	virtual void unregisterObserver(CObserver *objObserver) = 0;
	virtual void notifyObservers() = 0;

};

class CCricketData : public CSubject
{
	int m_nRuns;
	int m_nWickets;
	float m_fOvers;
	list<CObserver*> m_list;

public:
	CCricketData() :m_nRuns(0), m_nWickets(0), m_fOvers(0.0)
	{
		
	}

	void registerObserver(CObserver *objObserver)
	{
		m_list.push_back(objObserver);
	}

	void unregisterObserver(CObserver *objObserver)
	{
		m_list.remove(objObserver);
	}

	void notifyObservers()
	{
		list<CObserver*>::iterator it;

		for (it = m_list.begin(); it != m_list.end(); it++)
		{
			((CObserver*)*it)->Update(m_nRuns, m_nWickets, m_fOvers);
		}
	}

	int getWickets()
	{
		return 3;
	}

	int getRuns()
	{
		return 100;
	}

	float getOvers()
	{
		return 12.5;
	}

	void dataChanged()
	{
		m_nRuns = getRuns();
		m_nWickets = getWickets();
		m_fOvers = getOvers();

		notifyObservers();
	}

};


class CAverageScoreTicker : public CObserver
{
	float m_runRate;
	int m_projectedScore;
public:
	CAverageScoreTicker() :m_runRate(0.0), m_projectedScore(0)
	{

	}

	void Update(int nRuns, int nWicket, float fOvers)
	{
		m_runRate = nRuns / fOvers;
		m_projectedScore = (int)m_runRate * 50;

		Display();
	}

	void Display()
	{
		cout << "Average Score Ticker: Runrate: " << m_runRate << " Projected Score: " << m_projectedScore << endl;
	}

};


class CCurrentScoreTicker : public CObserver
{

	float m_fover;
	int m_nRuns;
	int m_nWicket;
public:
	CCurrentScoreTicker() :m_fover(0.0), m_nRuns(0), m_nWicket(0)
	{

	}

	void Update(int nRuns, int nWicket, float fOvers)
	{
		m_nRuns = nRuns;
		m_nWicket = nWicket;
		m_fover = fOvers;

		Display();
	}

	void Display()
	{
		cout << "Current Score Ticker: Runs: " << m_nRuns << " Wicket: " << m_nWicket << " Overs: " << m_fover << endl;
	}


};


int _tmain(int argc, _TCHAR* argv[])
{

	CAverageScoreTicker *objCAverageScoreTicker = new CAverageScoreTicker();
	CCurrentScoreTicker *objCCurrentScoreTicker = new CCurrentScoreTicker();

	CCricketData objCCricketData;

	objCCricketData.registerObserver(objCAverageScoreTicker);
	objCCricketData.registerObserver(objCCurrentScoreTicker);
	objCCricketData.dataChanged();

	cout << "Removing Current Score Ticker" << endl << endl;

	objCCricketData.unregisterObserver(objCCurrentScoreTicker);
	objCCricketData.dataChanged();
	
	objCCricketData.unregisterObserver(objCAverageScoreTicker);

	delete objCAverageScoreTicker;
	delete objCCurrentScoreTicker;

	return 0;
}

