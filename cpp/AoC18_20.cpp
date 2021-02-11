#include <regex>
#include <sstream>
#include "..\hpp\AoC20.hpp"
#include "..\hpp\smmComuni.hpp"
std::string AoC18_20_CalcNoParB(std::string str)
{
	std::vector<long long int> vLong;
	std::istringstream iss(str);
	std::ostringstream oss;

	long long int a, b;
	char myOp;

	iss >> a;
	vLong.push_back(a);
	while (iss.good())
	{
		iss >> myOp >> b;
		switch (myOp)
		{
		case '+':
			a = *vLong.rbegin();//LAST
			vLong.pop_back();
			vLong.push_back(a + b);
			break;
		case '*':
			vLong.push_back(b);
			break;
		}
	}
	a = 1;
	for (auto l = vLong.begin(); l != vLong.end(); ++l)
		a *= (*l);
	oss << a;
	return oss.str();
}


std::string AoC18_20_CalcNoParA(std::string str)
{
	std::istringstream iss(str);
	std::ostringstream oss;

	long long int a, b;
	char myOp;

	iss >> a;
	while (iss.good())
	{
		iss >> myOp >> b;
		switch (myOp)
		{
		case '+':
			a += b;
			break;
		case '*':
			a *= b;
			break;
		}
	}
	oss << a;
	return oss.str();
}


std::pair<size_t, size_t> AoC18_20(std::string myFileName)
{
	std::regex innerMostReg("(.*)\\(([^\\(\\)]*)\\)(.*)");
	//Cattura qualunque cosa   (.*)					 (.*) all'inizio o alla fine
	//Cerca una ( aperta       \\( 
	//Poi cattura				  (          )
	//tutto ciò che non è ()       [^\\(\\)]
	//Tutte le volte che puoi				*
	//seguito da una parentesi )		       \\)
	//Ricordati di eliminare il primo e l'ultimo carattere

	std::string tbd, aStr;
	std::smatch myMatch;
	std::vector<std::string> myLines = lineParser(myFileName);
	size_t aVal, tVal = 0;
	std::istringstream iss;
	std::pair<size_t, size_t> myAns;
	for (auto strPtr = myLines.begin(); strPtr != myLines.end(); ++strPtr)
	{
		aStr = *strPtr;
		//	std::cout << aStr << std::endl;;

		while (std::regex_match(aStr, innerMostReg))	//finchè puoi matchare
		{

			tbd = std::regex_replace(aStr, innerMostReg, "$2");
			tbd = AoC18_20_CalcNoParA(tbd);//fa il conto
			aStr = std::regex_replace(aStr, innerMostReg, "$1") + tbd +
				std::regex_replace(aStr, innerMostReg, "$3");
			//	std::regex_search(aStr, myMatch, innerMostReg);
			//	std::cout << aStr << std::endl;
		}

		aStr = AoC18_20_CalcNoParA(aStr);//fa il 
		//std::cout << aStr << std::endl;
		iss.str(aStr);
		iss.clear();
		iss >> aVal;
		tVal += aVal;
		
	}
	myAns.first = tVal;	
	

	tVal = 0;
	for (auto strPtr = myLines.begin(); strPtr != myLines.end(); ++strPtr)
	{
		aStr = *strPtr;
		//std::cout << aStr << std::endl;;

		while (std::regex_match(aStr, innerMostReg))	//finchè puoi matchare
		{

			tbd = std::regex_replace(aStr, innerMostReg, "$2");
			tbd = AoC18_20_CalcNoParB(tbd);//fa il conto
			aStr = std::regex_replace(aStr, innerMostReg, "$1") + tbd +
				std::regex_replace(aStr, innerMostReg, "$3");
			//			std::regex_search(aStr, myMatch, innerMostReg);
			//			std::cout << aStr << std::endl;
		}

		aStr = AoC18_20_CalcNoParB(aStr);//fa il 
		//std::cout << aStr << std::endl;
		iss.str(aStr);
		iss.clear();
		iss >> aVal;
		tVal += aVal;
	}
	myAns.second = tVal;

	return myAns;


}