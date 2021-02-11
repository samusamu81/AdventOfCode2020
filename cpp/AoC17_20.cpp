#include <iostream>
#include "AoC20.hpp"
#include "smmComuni.hpp"
#include "nDim_string.hpp"

long long int AoC17_20Solver(std::set<std::string> livePos)
{
	std::set<std::string> temp_set2, temp_set3;
	std::set<std::string>::iterator scout;
	std::multiset<std::string> futurePos;
	std::multiset<std::string>::iterator searchToRemove;
	std::vector<std::string> neigh;
	size_t gencounter, c;
	const size_t MAX_GEN = 6;
	for (gencounter = 0; gencounter < MAX_GEN; ++gencounter)
	{
		//std::cout << "Generazione " << gencounter << std::endl;
		futurePos.clear();
		//trova dove testare
		for (scout = livePos.begin(); scout != livePos.end(); ++scout)
		{
			neigh = nDim_string(*scout).vicini();
			futurePos.insert(neigh.begin(), neigh.end());
		}
		//std::cout << "numero di vicini generati " << futurePos.size() << std::endl;
		temp_set2.clear();
		temp_set3.clear();

		for (searchToRemove = futurePos.begin(); searchToRemove != futurePos.end(); ++searchToRemove)
		{
			c = futurePos.count(*searchToRemove);
			if (c == 3)
			{
				temp_set3.insert(*searchToRemove);
				++searchToRemove;
				++searchToRemove;
			}
			else if (c == 2)
			{
				temp_set2.insert(*searchToRemove);
				++searchToRemove;
			}
		}	//pulizia della mappa.
		futurePos.clear();
		futurePos.insert(temp_set2.begin(), temp_set2.end());
		futurePos.insert(temp_set2.begin(), temp_set2.end());

		futurePos.insert(temp_set3.begin(), temp_set3.end());
		futurePos.insert(temp_set3.begin(), temp_set3.end());
		futurePos.insert(temp_set3.begin(), temp_set3.end());

		temp_set2.clear();
		//temp_set3.clear();
		//std::cout << "di validi " << futurePos.size() << std::endl;
		for (searchToRemove = futurePos.begin(); searchToRemove != futurePos.end(); ++searchToRemove)
		{
			if (futurePos.count(*searchToRemove) == 3) //sicuramente impostare a vivo
			{
				temp_set2.insert(*searchToRemove); // sicuramente vivo
				++searchToRemove;
				++searchToRemove;
			}
			else if (futurePos.count(*searchToRemove) == 2)
			{
				if (livePos.count(*searchToRemove) > 0)
					temp_set2.insert(*searchToRemove);
				++searchToRemove;
			} // resta vivo
			else
				std::cout << "NON DEVI LEGGERMI" << std::endl;
		}
		livePos.clear();
		//std::cout << "Nuovo numero di elementi vivi " << temp_set2.size() << std::endl;
		livePos.insert(temp_set2.begin(), temp_set2.end());
	}
	return livePos.size();
}

std::pair<size_t, size_t>  AoC17_20(std::string myFileName)
{
	const int MAX_GEN = 6;
	std::vector<std::string> myLines = lineParser(myFileName);
	int i, j, k = 0, w = 0;
	std::pair<long long int, long long int> myAns;
	std::set<std::string> livePos;
	for (i = 0; i < (int)myLines.size(); ++i)
		for (j = 0; j < (int)myLines[i].length(); ++j)		//probabilmente contiene un line terminator
			if (myLines[i][j] == '#')	//live
				livePos.insert(nDim_string(std::to_string(i) + ","
					+ std::to_string(j) + ","
					+ std::to_string(k)).ToString());

	myAns.first = AoC17_20Solver(livePos);

	livePos.clear();

	for (i = 0; i < (int)myLines.size(); ++i)
		for (j = 0; j < (int)myLines[i].length(); ++j)		//probabilmente contiene un line terminator
			if (myLines[i][j] == '#')	//live
				livePos.insert(nDim_string(std::to_string(k) + ","
					+ std::to_string(i) + ","
					+ std::to_string(j) + ","
					+ std::to_string(k)).ToString());

	myAns.second = AoC17_20Solver(livePos);
	//contatore di generazioni

	return myAns;
}