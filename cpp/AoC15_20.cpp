#include <unordered_map>
#include <map>
#include <iostream>
#include "smmComuni.hpp"
#include "AoC20.hpp"

//this takes long! Be patient
std::pair<size_t, size_t>  AoC15_20(std::string myFileName)
{
	const int MAX_I_PART_1 = 2020 - 1, MAX_I_PART_2 = 30000000 - 1;
	std::string dummy;
	std::string myInp = myParser(myFileName, dummy)[0];
	std::istringstream toParse(myInp);
	int dummy_int = 0;
	unsigned int i, spokenNumber, newSpokenNumber;
	std::vector<std::string> inizio = Parser(&toParse, ',');

	std::unordered_map<int, int> num_n_turno;
	std::unordered_map<int, int>::iterator map_iter;
	std::pair<long long int, long long int> answ;

	for (i = 0; i < inizio.size() - 1; i++)		// non aggiungere ultimo numero..
	{
		dummy_int = std::stoi(inizio[i]);
		num_n_turno.insert(std::make_pair(dummy_int, i + 1));
	}
	spokenNumber = stoi(inizio[inizio.size() - 1]);	//qusto è l'ultimo numero, 

	while (i < MAX_I_PART_1)// with i++ inside ottengo 10
	{
		i++;	//turno del rimosso
		//cerca l'ultimo numero detto
		map_iter = num_n_turno.find(spokenNumber);
		newSpokenNumber = map_iter != num_n_turno.end() ? i - map_iter->second : 0; //se l' hai trovato, quanti turni fa altrimenti 0

		//OLD IMPLEMENTATION
		//num_n_turno.erase(spokenNumber);	//se il numero era già stato detto, devo cancellarlo e aggiornarlo
		//num_n_turno.insert(std::make_pair(spokenNumber, i));
		//NEW IMPLEMENTATION
		num_n_turno[spokenNumber] = i;

		spokenNumber = newSpokenNumber;
	}
	answ.first = spokenNumber;

	num_n_turno.clear();


	for (i = 0; i < inizio.size() - 1; i++)		// non aggiungere ultimo numero..
	{
		dummy_int = std::stoi(inizio[i]);
		num_n_turno.insert(std::make_pair(dummy_int, i + 1));
	}
	spokenNumber = stoi(inizio[inizio.size() - 1]);	//qusto è l'ultimo numero, 

	while (i < MAX_I_PART_2)// with i++ inside ottengo 10
	{
		i++;	//turno del rimosso
		//cerca l'ultimo numero detto
		map_iter = num_n_turno.find(spokenNumber);
		newSpokenNumber = map_iter != num_n_turno.end() ? i - map_iter->second : 0; //se l' hai trovato, quanti turni fa altrimenti 0

		//OLD IMPLEMENTATION
		//num_n_turno.erase(spokenNumber);	//se il numero era già stato detto, devo cancellarlo e aggiornarlo
		//num_n_turno.insert(std::make_pair(spokenNumber, i));
		//NEW IMPLEMENTATION
		num_n_turno[spokenNumber] = i;

		spokenNumber = newSpokenNumber;
		//if (i % 1048576 == 0) std::cout << i << std::endl;
	}
	answ.second = spokenNumber;

	return answ;
}