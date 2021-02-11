#include <set>
#include <map>
#include <regex>
#include <sstream>
#include "..\hpp\smmComuni.hpp"


std::pair<size_t, size_t> AoC19_20(std::string myFileName)
{
	//plan:
	// 1 - Read rules and leave only the strings to be checked
	//		1a - 
	// 2 - Build Regex (part 1)
	//		2a - Loop throug rules and identify which one has no numbers
	//		2b - if it has no number, then subsitute everywhere with "(:  )"around = non capturing groups
	// 3 - Count Matches (1st part)
	// 4 - Explanation for 2nd part 
	//		Rule 0: 8 11
	//		Rule 8: 42 8		(was 42)
	//		Rule 11: 42 11 31	(was 42 31)
	// By combining them, rule 0 becomes is 42 z number of times, followed by 42 y number of times 31 y number of times
	//which means 42 x number of times followed by 31 y number of times
	//So there are 1 or more 42s followed by one or more 31s (match with regex)
	//		Count how many time you can remove 42s from Start Of Line
	//		Count how many time you can remove 31s from End Of Line
	//if x > y, it is a hit
	int const START_OF_LINE = 42, END_OF_LINE = 31;
	std::vector<std::string>myLines = lineParser(myFileName);
	std::vector<std::string>::iterator lineIter;
	std::vector<std::string>myRules;
	std::set<int> setToDo, setDone;
	std::map<size_t, std::string>myRulesMap;
	std::regex isNum("\\d"), isWhiteSpace(" ");
	std::regex isChar(".*(a|b).*");	//not digit
	std::regex* rule0, * rule0_part2, * ruleSoL, * ruleEoL;
	std::regex* regPtr;
	std::regex regX("^x+"), regY("y+$");
	std::ostringstream oss;
	std::stringstream ioss;
	//int howManyX, howManyY;
	std::string myNewString1, myNewString2;
	int i, j;	//used for rules!
	size_t x, y, oldLen;
	std::smatch res;
	std::string str;
	std::pair<size_t, size_t> myAnsw;
	//1 
	std::regex isRule("(\\d+):(.*)");
	for (lineIter = myLines.begin(); std::regex_match(*lineIter, isRule); ++lineIter)
	{
		i = stoi(std::regex_replace(*lineIter, isRule, "$1"));
		str = std::regex_replace(*lineIter, isRule, "$2");

		if (str.find_first_of('a') != std::string::npos || str.find_first_of('b') != std::string::npos)	//non contiene numeri
		{
			str = std::regex_replace(str, isChar, "$1");
			setToDo.insert(i);
		}
		myRulesMap.insert(std::make_pair(i, str));
	}
	myRules.resize(myRulesMap.rbegin()->first + (size_t)1);//+1 off by one

	for (auto mapIter = myRulesMap.begin(); mapIter != myRulesMap.end(); ++mapIter)
		myRules[mapIter->first] = mapIter->second;


	//DISCARD RULES FROM INPUT: +1 skip riga bianca
	myLines = std::vector<std::string>(lineIter + 1, myLines.end());
	//BUILD RULE ZERO: 
	str = myRules[0];
	//WHILE NOT ONLY LETTERS OR "|PIPE"
	while (setToDo.size() > 0)
	{
		i = *setToDo.begin();	//devo sostituire questa regola in tutte le altre
		oss.str("");
		oss << "\\b" << i << "\\b";	//i seguito da word boundaries (no match su 5 in 59)
		regPtr = new std::regex(oss.str());

		//Con cosa sostituisco?
		oss.clear();
		oss.str("");
		oss << "(?:";
		//DELETE WHITESPASCES
		ioss.str(myRules[i]);
		ioss.clear();

		while (ioss.good())
		{
			ioss >> str;
			oss << str;
		}
		oss << ")";	//oss contiene la regola giusta giusta
		j = -1;
		for (auto vIter = myRules.begin(); vIter != myRules.end(); ++vIter)
		{
			++j;
			if (setDone.find(j) != setDone.end()) continue;
			if (i == j) continue;
			*vIter = std::regex_replace(*vIter, *regPtr, oss.str());

			if (vIter->find_first_of("0123456789") == std::string::npos)
				if (setDone.find(j) == setDone.end())
					setToDo.insert(j);
		}
		delete regPtr;
		regPtr = nullptr;
		setDone.insert(i);
		setToDo.erase(i);
	}

	std::transform(myRules.begin(), myRules.end(), myRules.begin(), CleanWhiteSpace);

	

	
	rule0 = new std::regex("\\b" + myRules[0] + "\\b");	//ensure word boundaries
	rule0_part2 = new std::regex("\\b(" + myRules[42] + ")+(" + myRules[31] + ")+\\b");
	ruleSoL = new std::regex("^(" + myRules[START_OF_LINE] + ")(.*)");
	ruleEoL = new std::regex("(.*)(" + myRules[END_OF_LINE] + ")$");

	for (lineIter = myLines.begin(); lineIter != myLines.end(); ++lineIter)
	{
		//	std::regex_match(*lineIter, myMatch, myRules[0]);
		myAnsw.first += std::regex_match(*lineIter, *rule0) ? 1 : 0;
		if (std::regex_match(*lineIter, *rule0_part2))
		{
			x = 0;
			y = 0;
			str = *lineIter;
			
			do 
			{
				oldLen = str.length();
				str = std::regex_replace(str, *ruleSoL, "$2");
				x++;

			} while (str.length() != oldLen);
			
			do
			{
				oldLen = str.length();
				str = std::regex_replace(str, *ruleEoL, "$1");
				y++;
			} while (str.length() != oldLen);
			myAnsw.second += x > y ? 1 : 0;
		}
	}
	delete rule0, rule0_part2, ruleSoL, ruleEoL;
	return myAnsw;
}
