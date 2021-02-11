#include <sstream>
#include <fstream>
#include <iostream>

#include "smmComuni.hpp"
#include "AoC20.hpp"

std::pair<size_t, size_t> AoC6_20(std::string myFileName)
{
	std::stringstream ioss;
	std::ifstream ifs(myFileName);
	std::vector<std::string> myGroups;
	std::vector<char> myG, otherG, answG;
	std::string str;
	std::vector<char>::iterator myPos;
	std::pair<size_t, size_t> myAnsw;
	int thisGroup;
	myAnsw = std::make_pair(0, 0);
	multiLineMerger(&ifs, &ioss);
	ifs.close();

	myGroups = lineParser(&ioss);
	if (myGroups.back().length() == 0) myGroups.pop_back();		//sanity check: an empty line is appended at end

	//prima parte;
	for (auto l = myGroups.begin(); l != myGroups.end(); ++l)
	{

		myG = std::vector<char>(l->begin(), l->end());
		std::sort(myG.begin(),myG.end());
		myPos = std::unique(myG.begin(), myG.end());

		myAnsw.first += (myPos - myG.begin()) / sizeof(char);
		myAnsw.first -= myG[0] == ' ' ? 1 : 0;	//myPos is "1 past the end"; if it starts with whitespace, decrement twice;

		ioss.clear();
		ioss.str(*l);
		answG.resize(26);//as many as letters

		//start with 1st string;
		//keep intersecting with each string
		//count length
		
		thisGroup = 0;
		ioss >> str;
		myG = std::vector<char>(str.begin(), str.end());
		std::sort(myG.begin(), myG.end());
		answG = myG;
		while (ioss.good())
		{
			otherG = answG; //this way I keep the running total in otherG
			ioss >> str;
			myG = std::vector<char>(str.begin(), str.end());
			std::sort(myG.begin(), myG.end());
			std::sort(otherG.begin(), otherG.end());				//Bullshit! already sorted but doesn't run otherwise...
			myPos = std::set_intersection(myG.begin(), myG.end(), otherG.begin(), otherG.end(), answG.begin());
			answG.erase(myPos, answG.end());	//clean the empty!
 		}
		myAnsw.second += answG.size();
		
		//myAnsw.second -= answG[0] == ' ' ? 1 : 0;	//myPos is "1 past the end"; if it starts with whitespace, decrement twice;
	}


	return myAnsw;
}