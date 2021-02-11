#include <map>
#include <tuple>
#include <regex>
#include "AoC20.hpp"
#include "smmComuni.hpp"
#include "smmMatrix.hpp"
int AoC16_20A_IsNotValidTicket(std::vector<int> const & limits, std::vector<int> const& myTicket)
{
	//restutisce somma dei campi invalidi in un biglietto
	//smmConst::not_found if no match
	std::map <std::string, std::vector<int>>::const_iterator myRangeIter;
	std::vector<int>::const_iterator myTicketIter;

	bool thisRec = false;
	int myAnsw = smmConst::not_found;
	for (myTicketIter = myTicket.begin(); myTicketIter != myTicket.end(); ++myTicketIter)
	{
		if (
			(*myTicketIter < limits[0])
			||
			((*myTicketIter > limits[1]) && (*myTicketIter < limits[2]))
			||
			(*myTicketIter > limits[3]))
		{	
			if (myAnsw == smmConst::not_found) myAnsw = 0;
			myAnsw += *myTicketIter;
		}
	}
	return myAnsw;
}

bool AoC16_20B_IsValidTicket(std::vector<int> const& limits, std::vector<int> const& myTicket)
{
	//usare con vettore rappresentante i campi e contro un singolo limite
	//restutisce somma dei campi invalidi in un biglietto
	std::map <std::string, std::vector<int>>::const_iterator myRangeIter;
	std::vector<int>::const_iterator myTicketIter;

	bool thisRec = false;
	int myAnsw = 0;
	for (myTicketIter = myTicket.begin(); myTicketIter != myTicket.end(); ++myTicketIter)
	{
		if (
			(*myTicketIter < limits[0])
			||
			((*myTicketIter > limits[1]) && (*myTicketIter < limits[2]))
			||
			(*myTicketIter > limits[3]))
				return false;
	}
	return true;
}
//std::vector<bool> AoC16_20B_givePossibleRanges(std::vector<std::pair<int, int>> const& myRanges, std::vector<int> myRecords)
//{
//	//myRecords: vettore contenente tutti gli n-esimi campi (per es: la 4a colonna del file di input)
//	//myRanges: tutti i range di validità
//	//Restituisce un vettore di lunghezza pari ranges/2
//	//La posizione n risponde alla domanda:
//	// tutti i valori in myRecords cadono in myRange (2n) oppure in myRanges(2n+1)?
//	std::vector<bool> myAnsw;
//	size_t i;
//	for (i = 0; i < myRanges.size(); i += 2)
//	{
//		myAnsw.push_back(
//			std::all_of(myRecords.begin(), myRecords.end(), [myRanges, i](int k)
//				{return
//				(k >= myRanges[i].first && k <= myRanges[i].second) ||
//				(k >= myRanges[i + (size_t)1].first && k <= myRanges[i + (size_t)1].second);
//				}));
//	}
//	return myAnsw;
//}

std::vector<int> AoC16_20_gridSolve(smmMatrix<bool> myGrid)
{
	std::vector<int> myAnsw;
	std::set<size_t> col_to_do, row_to_do, col_done, row_done;
	std::set<size_t>::iterator ctd, rtd;
	std::vector<bool> vFalse, aV;
	std::vector<bool>::iterator myIter;
	size_t totTrue = myGrid.howMany(true);
	size_t i, j;
	
	
	vFalse.resize(myGrid.numRows());
	vFalse.assign(myGrid.numRows(), false);
	myAnsw.resize(myGrid.numRows());

	for (i = 0; i < myGrid.numRows(); ++i)
	{
		//if (myGrid.howManyInRow(i, true))
			row_to_do.insert(i);
		//if (myGrid.howManyInCol(i, true))
			col_to_do.insert(i);
	}

	while (totTrue > 0)		//once found I delete it
	{

		for (rtd = row_to_do.begin(); rtd!=row_to_do.end(); ++rtd)										//Check ROWS
		{	
			if (myGrid.howManyInRow(*rtd, true) == 1)
			{
				aV = myGrid.getRow(*rtd);	//get the 
				myIter = std::find(aV.begin(), aV.end(), true);
				j = (myIter - aV.begin()) / sizeof(bool);
				myAnsw[*rtd] = (int) j;
				row_done.insert(*rtd);	//check
				col_done.insert(j);				//se c'era roba, elimina
			}
		}
#ifdef DEBUG
		std::cout << myGrid << std::endl << "***********************************" << std::endl;
#endif // DEBUG

		for (rtd = row_done.begin(); rtd != row_done.end(); ++rtd)										//Set Rows
		{
			row_to_do.erase(*rtd);
			myGrid.setRow(*rtd, vFalse);
		}
		for (ctd = col_done.begin(); ctd != col_done.end(); ++ctd)										//Set Cols
		{
			col_to_do.erase(*ctd);
			myGrid.setCol(*ctd, vFalse);
		}
#ifdef DEBUG
		std::cout << myGrid << std::endl << "***********************************" << std::endl;
#endif // DEBUG
		row_done.clear();
		col_done.clear();


		for (ctd = col_to_do.begin(); ctd != col_to_do.end(); ++ctd)									//Check COLS
		{
			if (myGrid.howManyInCol(*ctd, true) == 1)
			{
				aV = myGrid.getCol(*ctd);	//get the 
				myIter = std::find(aV.begin(), aV.end(), true);
				i = (myIter - aV.begin()) / sizeof(bool);
				myAnsw[i] = (int) *ctd;
				row_done.insert(i);	//check
				col_done.insert(*ctd);	//check
			}
		}
#ifdef DEBUG
		std::cout << myGrid << std::endl << "***********************************" << std::endl;
#endif // DEBUG
		for (rtd = row_done.begin(); rtd != row_done.end(); ++rtd)										//Set Row
		{
			row_to_do.erase(*rtd);
			myGrid.setRow(*rtd, vFalse);
		}
		for (ctd = col_done.begin(); ctd != col_done.end(); ++ctd)										//Set Col
		{
			col_to_do.erase(*ctd);
			myGrid.setCol(*ctd, vFalse);
		}
#ifdef DEBUG
		std::cout << myGrid << std::endl << "***********************************" << std::endl;
#endif // DEBUG
		row_done.clear();
		col_done.clear();


		totTrue = myGrid.howMany(true);																	//recount and exit for!
	}
	return myAnsw;
}


void AoC16_20_Parser(std::string myFileName, smmMatrix<int>& tickets, std::vector<std::vector<int>> & myLimits)
{
	//read everything as text
	std::vector<std::string> myLines = lineParser(myFileName);
	std::stringstream ioss;
	//Find myLimits
	size_t i;
	std::vector<int> v_lim(4);
	smmMatrix<int> myMatrix;
	std::regex get_beg("(.*): (\\d+)-(\\d+) or (\\d+)-(\\d+)");
	std::regex noNumbers("[^\\d]+");
	std::regex virgola(",");
	myLimits.clear();
	for (i = 0; i < myLines.size(); ++i)
	{
		if (myLines[i].length() == 0) break;
		v_lim[0] = std::stoi(std::regex_replace(myLines[i], get_beg, "$2"));
		v_lim[1] = std::stoi(std::regex_replace(myLines[i], get_beg, "$3"));
		v_lim[2] = std::stoi(std::regex_replace(myLines[i], get_beg, "$4"));
		v_lim[3] = std::stoi(std::regex_replace(myLines[i], get_beg, "$5"));
		myLimits.push_back(v_lim);
	}
	
	//popola ioss
	// continua da i attuale
	for (; i < myLines.size(); ++i)
	{
		if (myLines[i].length() == 0) continue;
		if (std::regex_match(myLines[i], noNumbers)) continue;
		ioss << std::regex_replace(myLines[i], virgola, " ");
		if (i == myLines.size() - 1) break;	//avoid last endl;
		ioss << std::endl;
	}
	//leggilo in blocco
	//togli ultimo aCapo!
	myMatrix.readFromStream(&ioss);

	for (i = 0; i < myMatrix.numCols(); ++i)
	{
		tickets.insertRow(i, myMatrix.getCol(i));
	}
	tickets.Transpose();
}


std::pair<size_t, size_t>  AoC16_20(std::string myFileName)
{
	smmMatrix<int> tickets;//contains all tickets including mine at row(0)
	std::pair<size_t, size_t> myAnsw;
	smmMatrix<bool> canItBe;
	int i, j, thisTicketOff;
	std::vector<int> vInt,vLimExtreme(4), myTicket;				//vLimExtreme: min of myLimits, max of mediumLow, min of mediumHigh, max of myLimits; vInt: generic vector of int
	std::vector<std::vector<int>> myLimits;		//contains limits for fields
	std::vector<std::vector<int>>::iterator myIter;
	bool myDebBool;
	AoC16_20_Parser(myFileName, tickets, myLimits);

	vInt.reserve(tickets.numRows() / 4);			//just a number
	//cerca i biglietti "rotti"

	
	for (i = 0; i < 4; ++i)
	{
		vLimExtreme[i] = myLimits.begin()->at(i);
	}
	for (myIter = myLimits.begin(); myIter != myLimits.end(); ++myIter)
	{
		vLimExtreme[0] = std::min(myIter->at(0), vLimExtreme[0]);
		vLimExtreme[2] = std::min(myIter->at(2), vLimExtreme[2]);

		vLimExtreme[1] = std::max(myIter->at(1), vLimExtreme[1]);
		vLimExtreme[3] = std::max(myIter->at(3), vLimExtreme[3]);
	}

	//populate vInt with wrong tickets
	for (i = 0; i < tickets.numRows(); ++i)
	{
		thisTicketOff = AoC16_20A_IsNotValidTicket(vLimExtreme, tickets.getRow(i));
		if (thisTicketOff != smmConst::not_found)
		{
			myAnsw.first += thisTicketOff;
			vInt.push_back(i);
		}

	}
	//std::cout << tickets << std::endl;

	while (vInt.size() > 0)
	{
		tickets.delRow(vInt.back());
		vInt.pop_back();
	}

	//std::cout << tickets << std::endl;


	//
	canItBe.Resize(tickets.numCols(), myLimits.size());
	
	//pochi accessi alla matrice!
	//populate vInt with fields (matrix columns)
	for (j = 0; j < tickets.numCols(); ++j)
	{
		vInt = tickets.getCol(j);
		i = 0;
		for (myIter = myLimits.begin(); myIter != myLimits.end(); ++myIter, ++i)
		{
			myDebBool = AoC16_20B_IsValidTicket(*myIter, vInt);
			canItBe.setAt(j, i, myDebBool);	//not the other way around!
		}
	}
	//std::cout << canItBe << std::endl;

	vInt = AoC16_20_gridSolve(canItBe);	//if vInt[7] = 4, it means that the 7th of the whole tickets corresponds to the 4th field
	
	myTicket = vInt; //temp
	for (i = 0; i < myTicket.size(); ++i)
		vInt[myTicket[i]] = i;			//now it is the "opposite" and vInt[4] = 7 (the 4th original field corresponds to the new 7th field


	myTicket.clear();

	myAnsw.second = 1;
	//std::cout << vInt<<std::endl;

	//std::cout << tickets.getRow(0) << std::endl;
	myTicket = tickets.getRow(0);
	for (i = 0; i < 6; ++i)
		myAnsw.second *= myTicket[vInt[i]];
	return myAnsw;
}


//std::pair<size_t, size_t>  AAAAoC16_20(std::string myFileName)
//{
//	std::ifstream ifs;
//	std::istringstream iss;
//	std::vector <std::string> ranges;
//	
//	std::vector<std::pair<int, int>> myVectorValidate;
//	std::vector<int> aTicket, myTicket;
//	std::vector<std::string> allOtherTickets;
//	std::vector<std::string>::iterator anotherTicket;
//	std::vector<std::vector<int>> possibilita;
//	std::pair <int, int> anElement;
//	std::string aLine, someTemp;
//	int n_iniziali_linea = 20;
//	int my_ticket_linea = 23;
//	int other_tickets_linea = 26;
//	int i, totalizzatore, biglietto_corrente_non_buono;
//	unsigned int r, c;
//	std::pair<long long int, long long int> myAns;
//	const int ALL_ONES = 1048575, //20 1 di fila in binario000
//		DEP_MIN = 14, DEP_MAX = 20; //blocchi di "departure"
//	ifs.open(myFileName);
//	for (i = 0; i < n_iniziali_linea; ++i)
//	{
//		std::getline(ifs, aLine);
//		//Ricorda che regex sono base 1
//		someTemp = std::regex_replace(aLine, get_beg, "$2");
//		anElement.first = std::stoi(someTemp);
//		someTemp = std::regex_replace(aLine, get_beg, "$3");
//		anElement.second = std::stoi(someTemp);
//		myVectorValidate.push_back(anElement);
//
//		someTemp = std::regex_replace(aLine, get_beg, "$4");
//		anElement.first = std::stoi(someTemp);
//		someTemp = std::regex_replace(aLine, get_beg, "$5");
//		anElement.second = std::stoi(someTemp);
//		myVectorValidate.push_back(anElement);
//	}
//	for (; i < my_ticket_linea; ++i)
//		std::getline(ifs, aLine);//consuma due righe, poi salva
//
//	iss.str(aLine);
//	myTicket = VectorConverter(Parser(&iss, ','), i);
//
//	totalizzatore = AoC16_20A_IsNotValidTicket(myVectorValidate, aTicket);
//	for (; i < other_tickets_linea; ++i)
//		std::getline(ifs, aLine);//consuma righe
//
//	allOtherTickets = lineParser(&ifs);
//	ifs.close();
//
//	for (anotherTicket = allOtherTickets.begin();
//		anotherTicket != allOtherTickets.end();
//		++anotherTicket)
//	{
//		iss.str(*anotherTicket);
//		iss.clear();
//		aTicket = VectorConverter(Parser(&iss, ','), i);
//		biglietto_corrente_non_buono = AoC16_20A_IsNotValidTicket(myVectorValidate, aTicket);
//		totalizzatore += biglietto_corrente_non_buono;
//		//second part
//		if (biglietto_corrente_non_buono == 0) //ovvero biglietto corrente è ok
//
//	possibilita.push_back(AoC16_20B_NumeroCampo(myVectorValidate, aTicket));	
//	}
//
//	myAns.first = totalizzatore;
//
//	possibilita.push_back(possibilita[0]); //duplica primo elemento
//	for (c = 0; c < possibilita[0].size(); ++c)
//	{
//		possibilita[0][c] = ALL_ONES;
//		for (r = 1; r < possibilita.size(); ++r)
//			possibilita[0][c] = possibilita[0][c] & possibilita[r][c];
//
//	}
//	//possibilità 0, c contiene le possibilità
//
//	myAns.second = 1;
//	for (c = 0; c < possibilita[0].size(); ++c)
//	{
//		r = 0;
//		while (possibilita[0][c] > 0 && possibilita[0][c] % 2 == 0)
//		{
//			r++;
//			possibilita[0][c] /= 2;
//		}
//		possibilita[0][c] = r; //contiene il numero di campo
//		if (r >= DEP_MIN && r <= DEP_MAX)
//		{
//			myAns.second *= myTicket[c];
//		}
//	}
//
//	return myAns;
//}

