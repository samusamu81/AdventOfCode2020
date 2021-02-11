
#include <sstream>
#include <map>
#include <regex>
#include <iostream>
#include "..\hpp\smmComuni.hpp"
#include "..\hpp\AoC20.hpp"

bool IsGoodTicket_1st(std::string s)
{
	//format is int-int char: string
	static bool firstRound = true;
	static std::map<std::string, std::regex> keyW;
	std::map<std::string, std::regex>::iterator it;

	if (firstRound)
	{
		keyW.insert(std::make_pair("byr", std::regex("\\bbyr:")));
		keyW.insert(std::make_pair("iyr", std::regex("\\biyr:")));
		keyW.insert(std::make_pair("eyr", std::regex("\\beyr:")));
		keyW.insert(std::make_pair("hgt", std::regex("\\bhgt:")));
		keyW.insert(std::make_pair("hcl", std::regex("\\bhcl:")));
		keyW.insert(std::make_pair("ecl", std::regex("\\becl:")));
		keyW.insert(std::make_pair("pid", std::regex("\\bpid:")));
	}; //cid omesso
	firstRound = false;

	for (it = keyW.begin(); it != keyW.end(); ++it)
	{
		if (std::regex_search(s, it->second)) continue;
		return false;
	}
	return true;
}
bool IsGoodTicket_2nd(std::string s)
{
	//format is int-int char: string
	static bool firstRound = true;
	static std::map<std::string, std::regex> keyW;
	static std::map<std::string, int> minS, maxS, currV;
	std::map<std::string, std::regex>::iterator it;
	std::map<std::string, std::regex>::iterator itmM;
	std::string heightType, tStr;
	int myVal;
	if (firstRound)//inizializza
	{
		keyW.insert(std::make_pair("byr", std::regex(".*\\bbyr:(\\d{4})\\b.*")));
		keyW.insert(std::make_pair("iyr", std::regex(".*\\biyr:(\\d{4})\\b.*")));
		keyW.insert(std::make_pair("eyr", std::regex(".*\\beyr:(\\d{4})\\b.*")));
		keyW.insert(std::make_pair("hgt", std::regex(".*\\bhgt:(\\d{2,3})(cm|in)\\b.*")));
		keyW.insert(std::make_pair("hcl", std::regex(".*\\bhcl:(#[0-9|a-f]{6})\\b.*")));
		keyW.insert(std::make_pair("ecl", std::regex(".*\\becl:(amb|blu|brn|gry|grn|hzl|oth)\\b.*")));
		keyW.insert(std::make_pair("pid", std::regex(".*\\bpid:(\\d{9})\\b.*")));
		minS.insert(std::make_pair("byr", 1920));
		maxS.insert(std::make_pair("byr", 2002));
		minS.insert(std::make_pair("iyr", 2010));
		maxS.insert(std::make_pair("iyr", 2020));
		minS.insert(std::make_pair("eyr", 2020));
		maxS.insert(std::make_pair("eyr", 2030));
		minS.insert(std::make_pair("hgt_cm", 150));
		maxS.insert(std::make_pair("hgt_cm", 193));
		minS.insert(std::make_pair("hgt_in", 59));
		maxS.insert(std::make_pair("hgt_in", 76));
	}; //cid omesso
	firstRound = false;

	for (it = keyW.begin(); it != keyW.end(); ++it)
	{	
		if (!std::regex_match(s, it->second)) return false;
		if (it->first == "hcl") continue;
		if (it->first == "ecl") continue;
		if (it->first == "pid") continue;
		tStr = std::regex_replace(s, it->second, "$1");
		myVal = std::stoi(tStr);
		if (it->first == "hgt")
		{
			heightType = "hgt_" + std::regex_replace(s, it->second, "$2");	//unità di misura
			if (myVal < minS[heightType]) return false;
			if (myVal > maxS[heightType]) return false;
			continue;
		}

		if (myVal < minS[it->first]) return false;
		if (myVal > maxS[it->first]) return false;
	}


	return true;
}

std::pair<size_t, size_t> AoC04_20(std::string myFileName)
{
	std::vector<std::string> myTickets;
	std::vector<std::string>::iterator it;
	int i = 0, j = 0;
	multiLineMerger(myFileName, "AoC4_20_TEMP.txt");
	myTickets = lineParser("AoC4_20_TEMP.txt");

	for (it = myTickets.begin(); it != myTickets.end(); ++it)
	{
		i += IsGoodTicket_1st(*it) ? 1 : 0;
		j += IsGoodTicket_2nd(*it) ? 1 : 0;

	}
	return std::make_pair(i, j);
}