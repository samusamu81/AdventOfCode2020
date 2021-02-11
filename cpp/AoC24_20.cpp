#include<set>
#include<map>
#include <regex>
#include <iostream>
#include "..\hpp\smmComuni.hpp"
#include "..\hpp\smmComplex.hpp"
#include "..\hpp\AoC20.hpp"

std::set<smmComplex<int>> MustBeFlipped(std::multiset<smmComplex<int>> oldTiles_n_turns)
{
	smmComplex<int> orig;
	static std::map<std::string, smmComplex<int>> dirs;
	static bool firstTime = true;
	std::multiset<smmComplex<int>> myInter;
	std::set<smmComplex<int>> newFlips;
	std::set<smmComplex<int>>::iterator aTilePtr;
	size_t counter;
	if (firstTime)
	{
		orig.Set(4, 0);						//W
		dirs.insert(std::make_pair("W", orig));
		orig.Set(-4, 0);					//E
		dirs.insert(std::make_pair("E", orig));
		orig.Set(2, 3);						//NW
		dirs.insert(std::make_pair("NW", orig));
		orig.Set(-2, 3);					//NE
		dirs.insert(std::make_pair("NE", orig));
		orig.Set(2, -3);					//SW
		dirs.insert(std::make_pair("SW", orig));
		orig.Set(-2, -3);					//SE
		dirs.insert(std::make_pair("SE", orig));
		firstTime = false;
	}

	for (aTilePtr = oldTiles_n_turns.begin(); aTilePtr != oldTiles_n_turns.end(); ++aTilePtr)
	{
		
		if (oldTiles_n_turns.count(*aTilePtr) % 2 == 0) continue;
		myInter.insert((*aTilePtr) + dirs["NE"]);
		myInter.insert((*aTilePtr) + dirs["NW"]);
		myInter.insert((*aTilePtr) + dirs["SE"]);
		myInter.insert((*aTilePtr) + dirs["SW"]);
		myInter.insert((*aTilePtr) + dirs["E"]);
		myInter.insert((*aTilePtr) + dirs["W"]);
	}
	for (auto& interm : myInter)
	{
		counter = myInter.count(interm);
		//was black and pointed by 0 or more than 2
		if ((counter > 2)
			&& (oldTiles_n_turns.count(interm) %2 > 0))
				newFlips.insert(interm);
		//white pointed by 2
		if ((counter == 2) && (oldTiles_n_turns.count(interm) %2 == 0))
			newFlips.insert(interm);
	}
	for (aTilePtr = oldTiles_n_turns.begin(); aTilePtr != oldTiles_n_turns.end(); ++aTilePtr)
	{
		if (oldTiles_n_turns.count(*aTilePtr) % 2 == 0) continue;	//white

		if (myInter.count(*aTilePtr) == 0)	//is black and no one is pointing
			newFlips.insert(*aTilePtr);
	}

	return newFlips;

}

void CleanMe(std::multiset<smmComplex<int>> & tiles_n_turns)	//keep the odd
{
	std::vector<smmComplex<int>> myV;

	myV.reserve(tiles_n_turns.size());


	for (auto b = tiles_n_turns.begin(); b != tiles_n_turns.end(); ++b)
	{
		if (tiles_n_turns.count(*b) % 2 == 0) continue;	//keep going
														//this is odd. add once
		if (myV.size() == 0)
			myV.push_back(*b);
		else if(myV.back() != *b)
			myV.push_back(*b);

	}

	tiles_n_turns.clear();
	tiles_n_turns.insert(myV.begin(), myV.end());

}
std::pair<size_t, size_t> AoC24_20(std::string myInput)
{
	const int N_TURNI = 100;
	std::pair<size_t, size_t> myAnsw = std::make_pair(0,0);
	std::multiset<smmComplex<int>> blacksIfEven;	//check later only for odd numbers!
	smmComplex<int> orig;
	orig.Set(0, 0);
	std::set<smmComplex<int>> toFlip;
	std::map<char, smmComplex<int>> dirs;
	std::regex NE("ne"), NW("nw"), E("e"), W("w"), SE("se"), SW("sw");
	std::vector<std::string> myLines = lineParser(myInput);
	int i;
	//remember to match east and west LAST

	//sart from "j" on a qwerty keybiard;
	//nw there is u, ne there is i
	//sw there is n, sw there is m
	//east is k and west is h
	orig.Set(4, 0);						//W
	dirs.insert(std::make_pair('k', orig));
	orig.Set(-4, 0);						//E
	dirs.insert(std::make_pair('h', orig));
	orig.Set(2, 3);						//NW
	dirs.insert(std::make_pair('i', orig));
	orig.Set(-2, 3);					//NE
	dirs.insert(std::make_pair('u', orig));
	orig.Set(2, -3);					//SW
	dirs.insert(std::make_pair('m', orig));
	orig.Set(-2, -3);					//SE
	dirs.insert(std::make_pair('n', orig));

	for (auto& l : myLines)
	{
		l = std::regex_replace(l, NE, "u");
		l = std::regex_replace(l, NW, "i");
		l = std::regex_replace(l, SE, "n");
		l = std::regex_replace(l, SW, "m");
		l = std::regex_replace(l, E, "h");
		l = std::regex_replace(l, W, "k");
	}
	for (std::string & l : myLines)
	{
		orig.Set(0, 0);
		for (char & c : l)
		{
			orig += dirs[c];
		}
		blacksIfEven.insert(orig);
	}
	CleanMe(blacksIfEven);
	myAnsw.first = blacksIfEven.size();	//after clean, only one survive
	for (i = 0; i < N_TURNI; ++i)
	{
		toFlip = MustBeFlipped(blacksIfEven);
		for (auto& TF : toFlip)
			blacksIfEven.insert(TF);
		CleanMe(blacksIfEven);	//keep only "ones"; might be better out of for loop

	}
	myAnsw.second = blacksIfEven.size();	//after clean, only one survive

	return myAnsw;
}