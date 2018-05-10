// JSON Serializer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <algorithm>

#define JSON_BEGIN_TAG					"{"
#define JSON_END_TAG					"}"
#define JSON_TAB						"\t"
#define JSON_DELIMETER					":"
#define JSON_LINE_DELIMETER				","
#define JSON_KEY_VALUE_STRING_FORMATER	"\"%s\": \"%s\""
#define JSON_NEW_LINE					"\n"
#define JSON_PAIR						std::pair<std::string, std::string>
#define JSON_MAP						std::map<std::string, std::string>
#define JSON_MAP_ITERATOR				JSON_MAP::iterator


using namespace std;

class CJSONParser
{
	JSON_MAP m_mapJson;

public:
	
	void AddPair(std::string key, std::string value)
	{
		m_mapJson.insert(JSON_PAIR(key, value));
	}
	

	std::string GetValue(std::string key)
	{
		JSON_MAP_ITERATOR it = m_mapJson.find(key);
		if (it != m_mapJson.end())
			return (m_mapJson.find(key)->second.c_str());
		else
			return "";
	}

	std::string Serialize()
	{
		std::string strJSON;
		
		char szStr[_MAX_PATH] = { 0 };
		int nIndex = 0;

		if (strJSON.length() > 0)
			strJSON.clear();

		strJSON.append(JSON_BEGIN_TAG);
		
		for (JSON_MAP_ITERATOR it = m_mapJson.begin(); it != m_mapJson.end(); ++it, nIndex++)
		{
			if (nIndex != 0)
				strJSON.append(JSON_LINE_DELIMETER);

			strJSON.append(JSON_NEW_LINE);

			strJSON.append(JSON_TAB);
			sprintf_s(szStr, JSON_KEY_VALUE_STRING_FORMATER, it->first.c_str(), it->second.c_str());
			strJSON.append(szStr);

			
		}
		strJSON.append(JSON_NEW_LINE);
		strJSON.append(JSON_END_TAG);
		
		return strJSON;
	}

	int DeSerialize(std::string strJSON)
	{

		size_t pos = 0;
		int nTokens = 0;
		std::string token;
		std::string key;
		std::string value;

		if (m_mapJson.size() > 0)
			m_mapJson.clear();

		cout << "Before: " << strJSON.c_str() << endl;
		strJSON.erase(std::remove(strJSON.begin(), strJSON.end(), '\"'), strJSON.end());
		strJSON.erase(std::remove(strJSON.begin(), strJSON.end(), '{'), strJSON.end());
		strJSON.erase(std::remove(strJSON.begin(), strJSON.end(), '}'), strJSON.end());
		cout << "After: " << strJSON.c_str() << endl;


		remove_if(strJSON.begin(), strJSON.end(), isspace);

		cout << "After Space: " << strJSON.c_str() << endl;
		size_t pos1 = 0;

		while ((pos = strJSON.find(JSON_LINE_DELIMETER)) != std::string::npos)
		{
			token = strJSON.substr(0, pos);
			std::cout << "Token: " << token.c_str() << std::endl;

			// split key:value and add to map
			pos1 = token.find(JSON_DELIMETER);
			key = token.substr(0, pos1);
			value = token.erase(0, pos1 + strlen(JSON_LINE_DELIMETER));

			AddPair(key, value);

			std::cout << "Key: " << key.c_str() << " Value: " << value.c_str() << endl;
			
			strJSON.erase(0, pos + strlen(JSON_LINE_DELIMETER));
			nTokens++;
		}

		return nTokens;

	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	CJSONParser pJsonObj;

	pJsonObj.AddPair("QBLicense", "2783-4851-0990-498");
	pJsonObj.AddPair("EOC", "467924");
	pJsonObj.AddPair("SKU", "bel");
	pJsonObj.AddPair("Source", "install");

	std::cout << pJsonObj.Serialize().c_str();


	std::string strMessage = "{ \"QBLicense\": \"2783-4851-0990-498\","
		"\"EOC\" : \"467924\","
		"\"SKU\" : \"bel\","
		"\"Source\" : \"install\","
		"\"MajorVersion\" : \"27\","
		"\"MinorVersion\" : \"3\","
		"\"Trial\" : \"false\","
		"\"Nfr\" : \"false\","
		"\"ReleaseLevel\" : \"4\""
	"}";

	std::cout << endl;
	CJSONParser pJsonObj1;
	cout << pJsonObj1.DeSerialize(strMessage);

	
	CJSONParser pJsonObj2;
	cout << endl << "pushing new values" << endl;
	pJsonObj2.AddPair("QBLicense", "2783-4851-0990-498");
	pJsonObj2.AddPair("EOC", "467924");
	pJsonObj2.AddPair("SKU", "bel");
	pJsonObj2.AddPair("Source", "install");

	std::cout << "Serialized String: " << pJsonObj2.Serialize().c_str() << endl;

	cout << "License : " << pJsonObj2.GetValue("QBLicense").c_str() << endl;
	cout << "Val : " << pJsonObj2.GetValue("Val").c_str() << endl;
	std::cout << endl;
	return 0;
}

