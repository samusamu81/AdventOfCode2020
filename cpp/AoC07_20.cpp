#include <map>
#include <sstream>
#include <string>
#include <set>
#include <regex>
#include <vector>
#include <deque>
#include "..\hpp\smmComuni.hpp"

size_t HowManyInsideIncludingMySelf(std::string const & outermost, std::map <std::string, std::vector<std::pair<int, std::string>>> *Structure)
{
	//recursive search!
	size_t myAnsw = 0;
	if (Structure->count(outermost) == 0) return 1;
	std::vector<std::pair<int, std::string>> myChildren;
	myChildren = Structure->at(outermost);
	for (auto const& unVal : myChildren)
		myAnsw += unVal.first * HowManyInsideIncludingMySelf(unVal.second, Structure);
	
	myAnsw++;
	return myAnsw;
}

std::pair<size_t, size_t> AoC07_20(std::string myFileName)
{
	const std::string MAGIC_BAG = "shiny gold";
	std::pair<size_t, size_t> myAnsw;
	std::map <std::string, std::set<std::string>> WhoContains;
	std::map <std::string, std::vector<std::pair<int, std::string>>> whatsInside;
	std::vector<std::pair<int, std::string>> vCont;
	int i;
	std::set<std::string> discovered, visited;
	std::string str, mySubj, linePart;
	std::set < std::string> stringSet;
	std::istringstream iss;
	std::vector <std::string> myFileContent;
	std::smatch res;
	std::regex subj("(\\S* \\S*).*"), 
		obj("(\\d*) (\\S* \\S*) bags?[\\.,] ?"),
		noBags(".* no other bags\\.");	//regex must match whole line???
	std::deque<std::string> myQueue;
	//capture numbers (\d)
	//whitespace
	//capture two strings (\S* \S*)		only a-zA-Z
	//whitespace
	//bag or bags
	//. or ,
	// maybe a whitespace

	//build maps
	myFileContent =lineParser(myFileName);	//all lines

	
	for (std::string const& aLine : myFileContent)
	{
		vCont.clear();
		mySubj = std::regex_replace(aLine, subj, "$1");

		if (std::regex_match(aLine, noBags)) continue;
		std::regex_search(aLine, res, obj);
		while (res.size() > 0)							//if match, then RES contains the following: res[0] is whole match
		{
			i = stoi(res[1]);							//res[1] is $1 (1st capturing group), so the number
			str = res[2];								//res[2] is $2 (2nd capturing group), so the string 
			vCont.push_back(std::make_pair(i, str));

			

			if (WhoContains.count(str) == 0)	//must add this one if not there
				WhoContains.insert(std::make_pair(str, std::set<std::string>()));

			WhoContains[str].insert(mySubj);

			//stringSet = WhoContains[str];		//get and set; cannot 
			//stringSet.insert(mySubj);
			//WhoContains[str] = stringSet;

			linePart = res.suffix().str();			//keep close to the next line! CANNOT USE str, linePart must stay "clean". If you overwrite, "res" gets "dirty"
			std::regex_search(linePart, res, obj);	//update the rest!

		}
		whatsInside.insert(std::make_pair(mySubj, vCont));

	
	}

	//part 1
	myQueue.assign(WhoContains[MAGIC_BAG].begin(), WhoContains[MAGIC_BAG].end());	//inizializzata
	while (myQueue.size() > 0)
	{
		if (visited.count(myQueue.front()) == 0)
		{
			myAnsw.first++;	//should be new!
			discovered = WhoContains[myQueue.front()];
			myQueue.insert(myQueue.end(), discovered.begin(), discovered.end());
			visited.insert(myQueue.front());
		}
		myQueue.pop_front();
	}

	//part 2
	myAnsw.second = HowManyInsideIncludingMySelf(MAGIC_BAG, &whatsInside);
	myAnsw.second--; //There is one too many!

	return myAnsw;
}