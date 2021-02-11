#include <map>
#include "smmComuni.hpp"
#include "AoC20.hpp"

//second
long long int AoC13_20_2(std::multimap<int, int> BusID_rit)
{//Rit_busID deve contenere l'autobus e il ritardo voluto.
	long long int startTime = 0;
	long long int currStep = 1;
	size_t howMany = BusID_rit.size(), i;
	std::multimap<int, int>::iterator myIter;
	startTime = 0;
	for (myIter = BusID_rit.begin(); myIter != BusID_rit.end(); ++myIter)
	{
		for (i = 0; i < myIter->first; ++i)
		{
			if ((startTime + i * currStep + myIter->second) % myIter->first == 0)
				break;
		}
		startTime += i * currStep;
		currStep *= myIter->first;
	}
	return startTime;//currStep dovrebbe essere produttoria totale...
}

std::pair<size_t, size_t> AoC13_20(std::string myFileName)
{

	//first
	std::vector<std::string> dummy;
	std::vector<std::string>::iterator iter;
	std::istringstream iss;
	std::regex toExclude("x");
	std::string txtList;
	std::pair<long long int, long long int> answ;
	int earliest, busID, resto;
	unsigned long long int myMinTime, myMinBusId;
	std::multimap<int, int> BusID_time;
	unsigned int init_iter = 0;

	dummy = lineParser(myFileName);
	iss.str(dummy[0]);
	iss >> earliest;
	txtList = dummy[1];
	iss.str(txtList);
	iss.clear();
	dummy = Parser(&iss, ',', toExclude);
	myMinTime = 0;
	myMinTime--;	//largest possible integer! Questa è una porcata immonda!
	myMinBusId = 0;
	for (iter = dummy.begin(); iter != dummy.end(); ++iter)
	{
		iss.str(*iter);
		iss.clear();
		iss >> busID;
		resto = earliest % busID;
		resto = (busID - resto);
		myMinTime = resto < myMinTime ? resto : myMinTime;
		myMinBusId = resto == myMinTime ? busID : myMinBusId;	//hai trovato il tempo minimo
	}

	answ.first = myMinTime * myMinBusId;

	//secondo

	//txtList = "7,13,x,x,59,x,31,19";
	//txtList = "1789,37,47,1889";
	iss.str(txtList);
	iss.clear();
	dummy = Parser(&iss, ',');

	for (resto = 0; resto < dummy.size(); ++resto)
	{
		if (dummy[resto].compare("x") == 0) continue;
		iss.str(dummy[resto]);
		iss.clear();
		iss >> busID;

		BusID_time.insert(std::make_pair(busID, resto));
	}

	answ.second = AoC13_20_2(BusID_time);


	return answ;
}