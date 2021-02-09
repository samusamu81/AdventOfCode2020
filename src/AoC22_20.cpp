#include <sstream>
#include <set>
#include <map>
#include "AoC20.hpp"
#include "smmComuni.hpp"

std::string AoC22_20Deck2str(std::deque<int> const& someDeck)
{
	std::deque<int>* deckRoller = new  std::deque<int>(someDeck.begin(), someDeck.end());
	std::ostringstream oss;

	while (!deckRoller->empty())
	{
		oss << deckRoller->front() << ' ';
		deckRoller->pop_front();
	}
	delete deckRoller;
	return oss.str();
}
void AoC22_20_StdFight(std::deque<int>* const deckA, std::deque<int>* const deckB, std::set<std::string>* myGames)
{
	std::ostringstream oss;
	int i, j;

	while (!deckA->empty() && !deckB->empty())
	{
		oss.clear();
		oss.str("");

		oss << AoC22_20Deck2str(*deckA) << '\t' << AoC22_20Deck2str(*deckB);

		if (myGames->count(oss.str()) > 0) throw new std::exception("Palyer 1 win; unable to exit; infinite loop");
		myGames->insert(oss.str());
		i = deckA->front();
		j = deckB->front();

		deckA->pop_front();
		deckB->pop_front();
		if (i > j)
		{
			deckA->push_back(i);
			deckA->push_back(j);
		}
		else
		{
			deckB->push_back(j);
			deckB->push_back(i);
		}
	}

}
bool AoC22_20_RecFight_AWins(std::deque<int>* const deckA, std::deque<int>* const deckB, std::set<std::string>* myGames)
{
	static std::map<std::string, bool> whoWins;
	auto foundGame = whoWins.begin();
	std::deque<int>* deckANew, * deckBNew;
	std::ostringstream oss;
	std::set<std::string>* aGameRecorder;
	int i, j;

	while (!deckA->empty() && !deckB->empty())
	{
		oss.clear();
		oss.str("");

		oss << AoC22_20Deck2str(*deckA) << '\t' << AoC22_20Deck2str(*deckB);
		//std::cout << deckA->size() << '\t' << deckB->size() << std::endl;

		if (myGames->count(oss.str()) > 0)
		{
			//std::cout << "CYCLIC GAME: " << oss.str() << std::endl;

			return true;
		}
		myGames->insert(oss.str());
		i = deckA->front();
		j = deckB->front();

		deckA->pop_front();
		deckB->pop_front();
		if (								//gioco ricorsivo
			((int)deckA->size() >= i) &&
			((int)deckB->size() >= j)
			)
		{
			foundGame = whoWins.find(oss.str());
			if (foundGame != whoWins.end())
			{
				//std::cout << "KNOWN GAME: " << oss.str() << " A wins? " << foundGame->second;

				return foundGame->second;
			}
			// copy and pop
			deckANew = new std::deque<int>(deckA->begin(), deckA->begin() + i);
			deckBNew = new std::deque<int>(deckB->begin(), deckB->begin() + j);
			aGameRecorder = new std::set<std::string>();
			if (AoC22_20_RecFight_AWins(deckANew, deckBNew, aGameRecorder))
			{
				deckA->push_back(i);
				deckA->push_back(j);
				whoWins.insert(std::make_pair(oss.str(), true));
			}
			else
			{
				deckB->push_back(j);
				deckB->push_back(i);
				whoWins.insert(std::make_pair(oss.str(), false));
			}
			delete deckANew;
			delete deckBNew;
			delete aGameRecorder;
			deckANew = deckBNew = nullptr;
			aGameRecorder = nullptr;
		}	//if recursive
		else   //gioco standard
		{
			if (i > j)
			{
				deckA->push_back(i);
				deckA->push_back(j);
				whoWins.insert(std::make_pair(oss.str(), true));
			}
			else
			{
				deckB->push_back(j);
				deckB->push_back(i);
				whoWins.insert(std::make_pair(oss.str(), false));
			}

		}


	}

	//fine partita: se deck B è vuoto, ha vinto A (return true)
	return deckB->empty();
}

std::pair<size_t, size_t> AoC22_20(std::string myFileName)
{

	//GET LINES AS STRING
	const int lineP1start = 1, lineP1end = 25;
	const int  lineP2start = 28, lineP2end = 52;
	//const int lineP1start = 1, lineP1end = 5;
	//const int  lineP2start = 8, lineP2end = 12;
	std::vector<std::string>myLines = lineParser(myFileName);
	std::deque <int> deckA, deckB, * deckWinner, deckA2, deckB2;
	std::set<std::string> myGames;
	int i, j;
	std::pair<long long int, long long int> myAnsw;
	for (i = lineP1start; i <= lineP1end; i++)
		deckA.push_back(std::stoi(myLines[i]));
	for (i = lineP2start; i <= lineP2end; i++)
		deckB.push_back(std::stoi(myLines[i]));

	deckA2 = std::deque<int>(deckA.begin(), deckA.end());
	deckB2 = std::deque<int>(deckB.begin(), deckB.end());


	AoC22_20_StdFight(&deckA, &deckB, &myGames);

	deckWinner = deckA.empty() ? &deckB : &deckA;

	//punteggio
	i = 1;
	j = 0;
	while (!deckWinner->empty())
	{
		j += i * deckWinner->back();
		deckWinner->pop_back();
		i++;
	}
	myAnsw.first = j;

	myGames.clear();
	deckWinner =
		AoC22_20_RecFight_AWins(&deckA2, &deckB2, &myGames) ?
		&deckA2 : &deckB2;
	//punteggio
	i = 1;
	j = 0;
	while (!deckWinner->empty())
	{
		j += i * deckWinner->back();
		deckWinner->pop_back();
		i++;
	}
	myAnsw.second = j;



	return myAnsw;
}