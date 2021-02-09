#include <map>	//only for std::make_pair
#include <algorithm>
#include "smmComuni.hpp"
#include "AoC20.hpp"

int str2Int(std::string s)
{
	int myAnsw = 0;
	std::reverse(s.begin(), s.end());

 	while (s.length() > 0)
	{//keep popping back
		myAnsw*=2;
		switch (s.back())
		{
		case 'F':
		case 'L':
			break;
		case 'R':
		case 'B':
			myAnsw += 1;
			break;
		default:
			throw new std::exception("Unexpected token in input");
		}
		s.pop_back();
	}
	return myAnsw;
}

std::pair<size_t, size_t> AoC5_20(std::string myFileName)
{
	std::vector<std::string> myTickets;
	std::vector<int> posID;
	std::vector<int>::iterator itInt;
	int myMax;
	std::vector<std::string>::iterator itStr;
	myTickets = lineParser(myFileName);

	posID.reserve(myTickets.size());
	for (itStr = myTickets.begin(); itStr != myTickets.end(); ++itStr)
	{
		posID.push_back(str2Int(*itStr));
	}
	itInt = std::max_element(posID.begin(), posID.end());
	myMax = *itInt;
	//part 2
	std::sort(posID.begin(),posID.end());
	for (itInt = posID.begin() + 1; itInt != posID.end(); ++itInt)
	{
		if (*itInt - *(itInt - 1) > 1) break;
	}


	return std::make_pair(myMax, *itInt - 1);
}