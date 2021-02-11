#include <vector>
#include <list>
#include <string>

std::vector<int> AoC23_20_Solver(std::vector<int> const& nums, unsigned int const& nRound)
{
	//concettualmente è una single list/forward list che chiude su se stessa.
	//Ogni posizione del vettore myLinks contiene il numero che SEGUE
	//Quindi se in posizione 7 è presente il 9 vuol dire che dopo il 7 ci sarà il 9
	//La posizione 0 è speciale ed è usata per tenere traccia dell'elemento corrente
	//2231 significa un loop 123 partendo da 2 (quindi 231231231 etc)
	//E' richiesto di tagliare 3 elementi e inserirli a valle di un numero
	//Per farlo bisogna:
	//1 - Sapere dove iniziare a tagliare: siccome vet[0] contiene elemento corrente, vet[vet[0]] contiene il primo elemento da tagliare
	//2 - Tagliare fuori i tre elementi (chain_start è il primo dei tre elementi, chain_end l'ultimo)
	//3 - Scoprire qual è il valore voluto (non può appartenere ai 3 elementi tagliati)
	//4 - Aggiornare l'elemento puntato dal trio e metterlo uguale a quello puntato dal val voluto
	//5 - Puntare il val voluto all'inizio del trio
	//6 - Mettere in vet[0] il prossimo da analizzare
	int lastSpoken = 0;
	std::vector<int> myLinks, myAnsw;
	int chain_start, chain_end, wantedVal;
	int forb1, forb2, forb3;
	unsigned int r;
	myLinks.resize(nums.size() + 1);	//elementi esistono.

	for (auto it = nums.begin(); it != nums.end(); ++it)
	{
		myLinks[lastSpoken] = *it;
		lastSpoken = *it;
	}
	myLinks[lastSpoken] = myLinks[0];

	for (r = 0; r < nRound; r++)
	{

		//1 - Sapere dove iniziare a tagliare: siccome vet[0] contiene elemento corrente, vet[vet[0]] contiene il primo elemento da tagliare
		chain_start = myLinks[myLinks[0]];		//myLinks0 contiene la prima posizione, quindi myLinks[myLinks[0] contiene 1 di 3
		forb1 = chain_start;
		forb2 = myLinks[forb1];	//myLinks[chain_start] è 2 di 3
		forb3 = myLinks[forb2];//3 di 3
		chain_end = forb3;

		//2 - Tagliare fuori i tre elementi (chain_start è il primo dei tre elementi, chain_end l'ultimo)
		myLinks[myLinks[0]] = myLinks[chain_end];	//il valore attuale deve puntare dove prima puntava la catena.

		//3 - Scoprire qual è il valore voluto (non può appartenere ai 3 elementi tagliati)
		wantedVal = myLinks[0];
		do										//trova il valore voluto
		{
			wantedVal--;
			if (wantedVal == 0) wantedVal = (int)nums.size();
		} while ((wantedVal == forb1) || (wantedVal == forb2) || (wantedVal == forb3));
		//4 - Aggiornare l'elemento puntato dal trio e metterlo uguale a quello puntato dal val voluto
		myLinks[chain_end] = myLinks[wantedVal];	//così la loro uscita è OK!
		//5 - Puntare il val voluto all'inizio del trio
		myLinks[wantedVal] = chain_start;
		//6 - Mettere in vet[0] il prossimo da analizzare
		myLinks[0] = myLinks[myLinks[0]];

	}

	myAnsw.reserve(myLinks.size());

	lastSpoken = 1;
	myAnsw.push_back(1);
	while (myLinks[lastSpoken] != 1)
	{
		lastSpoken = myLinks[lastSpoken];
		myAnsw.push_back(lastSpoken);
	}

	return myAnsw;
}

std::pair<size_t, size_t> AoC23_20(std::string myInput)
{
	std::pair<long long int, long long int> myAnsw;
	std::vector<int> myList, myListCopy;
	std::list<int> myList3;
	std::list<int>::iterator myLiterator;
	const int N_ROUND1 = 100, N_ROUND2 = 10000000, MAX_LIST = 1000000;
	int i;

	for (i = 0; i < (int)myInput.length(); i++)
		myList.push_back(myInput.at(i) - '0');	//offset rispetto a 0

	myListCopy = myList;		//copia per il 2° round
	myList = AoC23_20_Solver(myList, N_ROUND1);
	//output dovrebbe partire da 1.

	myAnsw.first = 0;
	for (i = 1; i < 9; i++)//hard coded!
	{
		myAnsw.first *= 10;
		myAnsw.first += myList[i];
	}

	myList = myListCopy;

	myList.resize(MAX_LIST);

	for (i = 9; i < MAX_LIST; ++i)
	{
		myList[i] = i + 1;
	}
	myList = AoC23_20_Solver(myList, N_ROUND2);

	myAnsw.second = (long long int) myList[1] * (long long int) myList[2];
	return myAnsw;
}