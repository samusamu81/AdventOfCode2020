#include <map>
#include "smmComuni.hpp"
#include "AoC20.hpp"


std::pair<size_t, size_t> AoC14_20readMaskAND_OR(std::string myMask)
{
	std::string::iterator cPtr;
	long long int E, O, ONE;
	E = 0;
	O = 0;
	ONE = 1;
	for (cPtr = myMask.begin(); cPtr != myMask.end(); ++cPtr)
	{
		E = E << 1;
		O = O << 1;
		switch (*cPtr)
		{
		case 'X'://Spinge 1 in E, spinge 0 in O
			E = E | ONE;
			break;
		case '1'://forza 1
			E = E | ONE;
			O = O | ONE;
			break;
		case '0'://forza 0
			break;
		}
	}
	return std::make_pair(E, O);
}
std::vector <long long unsigned int> AoC14_20giveNewPos(std::string myMask, long long unsigned int aPos)
{
	std::vector <long long unsigned int> growing, doubling;
	std::vector <long long unsigned int>::iterator myIter;
	std::string finale;
	std::string::iterator cPtr;
	growing.push_back(0);
	std::reverse(myMask.begin(), myMask.end());
	for (cPtr = myMask.begin(); cPtr != myMask.end(); ++cPtr)
	{
		switch (*cPtr)
		{
		case '1':
		case 'X':
			finale.push_back(*cPtr);
			break;
		case '0':
			if (aPos % 2) finale.push_back('1'); else finale.push_back('0');
			break;
		}
		aPos = aPos >> 1;
	}

	std::reverse(finale.begin(), finale.end());
	for (cPtr = finale.begin(); cPtr != finale.end(); ++cPtr)
	{
		for (myIter = growing.begin(); myIter != growing.end(); ++myIter)
			(*myIter) = *myIter << 1;	//right shift
		switch (*cPtr)
		{
		case '1':
			for (myIter = growing.begin(); myIter != growing.end(); ++myIter)
				(*myIter)++;
			break;
		case 'X':
			doubling = growing;
			for (myIter = growing.begin(); myIter != growing.end(); ++myIter)
				(*myIter)++;
			growing.insert(growing.end(), doubling.begin(), doubling.end());
			break;
		}
	}
	return growing;
}
std::pair<size_t, size_t>  AoC14_20(std::string myFileName)
{
	std::vector<std::string> myGroups = lineParser(myFileName);
	std::vector<std::string>::iterator myIter;
	std::regex maskString("(mask = )(.*)"); //capture what is after
	std::regex memPos_Val("mem.(\\d*). = (\\d*)"); //capture what is after
//	std::regex memVal ("mem[\\d*] = (\d*)"); //
	std::map<int, long long unsigned int> myValuesA;
	std::map<int, long long unsigned int>::iterator myValIterA;
	std::vector<long long unsigned int> myNewPos;
	std::vector<long long unsigned int>::iterator newPosIter;
	std::map<long long unsigned int, long long unsigned int> myValuesB;
	std::map<long long unsigned int, long long unsigned int>::iterator myValIterB;

	int pos;
	unsigned long long int val;
	std::istringstream iss;
	std::string str, aMask;
	std::pair<long long int, long long int> masksE_O;
	std::pair<long long int, long long int> answ;

	//prima parte
	for (myIter = myGroups.begin(); myIter != myGroups.end(); ++myIter)
	{
		if (std::regex_match(*myIter, maskString))
		{
			str = std::regex_replace(*myIter, maskString, "$2");	//tieni solo il secondo capturing group
			masksE_O = AoC14_20readMaskAND_OR(str);
		}
		if (std::regex_match(*myIter, memPos_Val))
		{
			str = std::regex_replace(*myIter, memPos_Val, "$1");
			iss.str(str);
			iss.clear();
			iss >> pos;

			str = std::regex_replace(*myIter, memPos_Val, "$2");
			iss.str(str);
			iss.clear();
			iss >> val;

			val = val & masksE_O.first;
			val = val | masksE_O.second;

			myValuesA.erase(pos);	//se non presente è OK!
			myValuesA.insert(std::make_pair(pos, val));
		}
	}
	answ.first = 0;
	for (myValIterA = myValuesA.begin(); myValIterA != myValuesA.end(); ++myValIterA)
		answ.first += myValIterA->second;
	//fine prima parte

	//seconda parte
	for (myIter = myGroups.begin(); myIter != myGroups.end(); ++myIter)
	{
		if (std::regex_match(*myIter, maskString))
		{
			aMask = std::regex_replace(*myIter, maskString, "$2");	//tieni solo il secondo capturing group
		}
		if (std::regex_match(*myIter, memPos_Val))
		{
			str = std::regex_replace(*myIter, memPos_Val, "$1");
			iss.str(str);
			iss.clear();
			iss >> pos;

			str = std::regex_replace(*myIter, memPos_Val, "$2");
			iss.str(str);
			iss.clear();
			iss >> val;

			myNewPos = AoC14_20giveNewPos(aMask, pos);
			for (newPosIter = myNewPos.begin(); newPosIter != myNewPos.end(); ++newPosIter)
			{
				myValuesB.erase(*newPosIter);	//se non presente è OK!
				myValuesB.insert(std::make_pair(*newPosIter, val));
			}

		}
	}
	answ.second = 0;
	for (myValIterB = myValuesB.begin(); myValIterB != myValuesB.end(); ++myValIterB)
		answ.second += myValIterB->second;
	return answ;
}