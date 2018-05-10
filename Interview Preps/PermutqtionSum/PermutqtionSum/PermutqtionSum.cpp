// PermutqtionSum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void getExprUtil(vector<string>& res, string curExp, string input, int target, int pos, int curVal, int last)
{
	cout <<  curExp << " :: " << input << " :: " << target << " :: " << pos << " :: " << curVal << " :: " << last;
	if (pos == input.length())
	{
		cout << "  Inside pos == input.length() ";
		if (curVal == target)
		{
			cout << "  curVal == target ";
			res.push_back(curExp);
		}
		cout << endl;
		return;
	}
	
	cout << endl;

	for (int i = pos; i < input.length(); i++)
	{
		if (i != pos && input[pos] == '0')
		{
			cout << " i != pos && input[pos] == '0' ";
			cout << endl;
			break;
		}

		string part = input.substr(pos, i + 1 - pos);

		cout << endl <<  "  ::: " << part.c_str() << " ::: " << endl;
		int cur = atoi(part.c_str());

		if (pos == 0)
		{
			cout << "  pos == 0 ";
			cout << endl;
			getExprUtil(res, curExp + part, input, target, i + 1, cur, cur);
		}
		else
		{
			getExprUtil(res, curExp + "+" + part, input, target, i + 1, curVal + cur, cur);
			getExprUtil(res, curExp + "-" + part, input, target, i + 1, curVal - cur, -cur);
			getExprUtil(res, curExp + "*" + part, input, target, i + 1, curVal - last + last * cur, last * cur);
			getExprUtil(res, curExp + "/" + part, input, target, i + 1, curVal - last + last / cur, last / cur);
		}
	}
	cout << endl;
}

// method to print result
void printResult(vector<string> res, int target)
{
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << " ";
	cout << ":::" << target << ":::" << endl;
}

// Driver code to test above methods
int main()
{
	vector<string> res;
	string input;
	bool flag = true;
	int target;

	//while (flag)
	//{
		

		cout << endl << "input string: ";
		cin >> input;

		cout << endl << "Target: ";
		cin >> target;

		getExprUtil(res, "", input, target, 0, 0, 0);
		printResult(res, target);

		res.clear();

		cout << endl << "Want to repeat: (y/n)?";
		cin >> input;

		if (input.compare("n") == 0)
			flag = false;
	//}
	return 0;
}