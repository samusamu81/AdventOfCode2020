#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <regex>
#include "smmComuni.hpp"

std::pair<size_t, std::string> AoC21_20(std::string myFileName)
{
	std::pair<size_t, std::string> myAnsw;
	std::vector<std::string> fContent = lineParser(myFileName), VIngr, VAllerg, tmpV;
	std::vector<std::string>::iterator strIter;
	std::regex myTRegex("([^\\(]*) \\((.*)\\)");
	
	//	(			capture
	//	[^			anything which is not 
	//	\\(			an open parenthesis
	//	]
	//	*			as many times as possible
	//	)			end of group 1
	//				a whitespace
	//	\\(			an open par
	//	(.*)		capture anything
	//	\\)			a closed par
	std::map <std::string, std::set<std::string>> mapAllergensToFood;
	std::map <std::string, std::string> mapUniqueAllergenToFood;
	std::istringstream iss;
	std::string aLine, ingrStr, allergStr;
	std::vector<std::string> allIngrV; //keep sorted
	std::set<std::string> allIngrSet, tmpSet; //keep sorted
	std::multiset<std::string> allIngrMultiSet;

	std::string s;

	while (fContent.size() > 0)		//pop one by one
	{
		
		aLine = fContent.back();
		fContent.pop_back();
		ingrStr = std::regex_replace(aLine, myTRegex, "$1");
		allergStr = std::regex_replace(aLine, myTRegex, "$2");
		allergStr = DeleteThisChar(allergStr, ',');
		iss.clear();
		iss.str(ingrStr);
		ingrStr = "";//dummify
		VIngr = myParser(&iss, ingrStr);

		iss.clear();
		iss.str(allergStr);
		allergStr = "";//dummify
		VAllerg = myParser(&iss, allergStr);
		
		allIngrV.resize(allIngrSet.size());
		std::copy(allIngrSet.begin(), allIngrSet.end(), allIngrV.begin());
		std::sort(VIngr.begin(), VIngr.end());
		allIngrMultiSet.insert(VIngr.begin(),VIngr.end());
		allIngrSet.insert(VIngr.begin(), VIngr.end());
		
		std::reverse(VAllerg.begin(), VAllerg.end());
		VAllerg.pop_back();//remove "contains"
		tmpSet.clear();
		tmpSet.insert(VIngr.begin(), VIngr.end());
		while (VAllerg.size() > 0)
		{
			if (mapAllergensToFood.count(VAllerg.back()) > 0)
			{
				tmpV.clear();
				tmpV.resize(mapAllergensToFood[VAllerg.back()].size());
				std::copy(mapAllergensToFood[VAllerg.back()].begin(), mapAllergensToFood[VAllerg.back()].end(), tmpV.begin());
				std::sort(tmpV.begin(), tmpV.end());	//in theory already sorted
				//tmpv contains already present allergens
				mapAllergensToFood[VAllerg.back()].clear();
				std::set_intersection(tmpV.begin(), tmpV.end(), VIngr.begin(), VIngr.end(), std::inserter(mapAllergensToFood[VAllerg.back()], mapAllergensToFood[VAllerg.back()].begin()));
			}
			else
			{
				mapAllergensToFood.insert(std::make_pair(VAllerg.back(), tmpSet));
			}
			VAllerg.pop_back();
		}
	}

	tmpSet.clear();
	tmpV.clear();
	for (auto const& someAll : mapAllergensToFood)
		tmpSet.insert(someAll.second.begin(), someAll.second.end());
	
	std::set_difference(allIngrSet.begin(), allIngrSet.end(), tmpSet.begin(), tmpSet.end(), std::back_inserter(tmpV));	//Contains all "safe" ingridient list

	for (auto const& someIngr : tmpV)
		myAnsw.first += allIngrMultiSet.count(someIngr);

	//part 2
	while (mapAllergensToFood.size() > 0)
	{
		//copia fuori i singoli
		for (auto const& someAll : mapAllergensToFood)
			if (someAll.second.size() == 1)
				mapUniqueAllergenToFood.insert(std::make_pair(someAll.first, *(someAll.second.begin())));
		//elimina eventuali singoli
		for (auto const& identified : mapUniqueAllergenToFood)
			if (mapAllergensToFood.count(identified.first) > 0) mapAllergensToFood.erase(identified.first);

		//elimina dalla lista quelli identificati
		for (auto const& identified : mapUniqueAllergenToFood)
		{
			for (auto const& someAll : mapAllergensToFood)
				if (mapAllergensToFood[someAll.first].count(identified.second) > 0)	//presente
					mapAllergensToFood[someAll.first].erase(identified.second);
		}

	}
	s = "";
	for (auto const& identified : mapUniqueAllergenToFood)
		s += (identified.second) + ",";
	
	s.pop_back();
	myAnsw.second = s;
	return myAnsw;

}