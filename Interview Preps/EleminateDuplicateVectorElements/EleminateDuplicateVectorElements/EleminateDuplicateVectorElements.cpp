// EleminateDuplicateVectorElements.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		int nSize = nums.size();
		int nDupCnt = 0;
		for (int nIndex = 0; nIndex < nSize - 1; nIndex++)
		{
			if (nums.at(nIndex) == nums.at(nIndex + 1))
			{
				nums.erase(nums.begin() + nIndex);
				nSize = nums.size();
				nDupCnt++;
			}

		}
		return nDupCnt;
	}
};

void trimLeftTrailingSpaces(string &input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
		return !isspace(ch);
	}));
}

void trimRightTrailingSpaces(string &input) {
	input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
	vector<int> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	char delim = ',';
	while (getline(ss, item, delim)) {
		output.push_back(stoi(item));
	}
	return output;
}

string integerVectorToString(vector<int> list, int length = -1) {
	if (length == -1) {
		length = list.size();
	}

	if (length == 0) {
		return "[]";
	}

	string result;
	for (int index = 0; index < length; index++) {
		int number = list[index];
		result += to_string(number) + ", ";
	}
	return "[" + result.substr(0, result.length() - 2) + "]";
}

int main() {
	string line;
	while (getline(cin, line)) {
		vector<int> nums = stringToIntegerVector(line);

		int ret = Solution().removeDuplicates(nums);

		string out = integerVectorToString(nums, ret);
		cout << out << endl;
	}
	return 0;
}