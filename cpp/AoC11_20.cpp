#include "..\hpp\smmComuni.hpp"
#include "..\hpp\AoC20.hpp"
#include "..\hpp\smmMatrix.hpp"

std::pair<size_t, size_t> AoC11_20(std::string myFileName)
{
	//This implementation is slow; The submatrix search shall be optimized
	std::cout << "This implementation is slow; The submatrix search shall be optimized" << std::endl;
	const int SEAT_LIM_1st = 4, SEAT_LIM_2nd = 5;
	size_t i, j, nS;
	char tmp;
	std::pair<long long int, long long int> myAnsw;
	smmMatrix<char> myMatr, myClip, orig;

	myMatr.readFromFile(myFileName);
	myClip.Resize(myMatr.numRows() + 2, myMatr.numCols());
	myClip.setAll('.');

	myMatr.insertRow(0, myClip.getRow(0));
	myMatr.insertRow(myMatr.numRows(), myClip.getRow(0));
	myMatr.insertCol(0, myClip.getCol(0));
	myMatr.insertCol(myMatr.numCols(), myClip.getCol(0));


	myClip.Resize(myMatr.numRows(), myMatr.numCols());
	myClip.setAll('.');
	orig = myMatr; //per parte 2
	
	while (myClip != myMatr)
	{
		for (i = 1; i < (int)myMatr.numRows() - 1; ++i)
		{
			for (j = 1; j < (int)myMatr.numCols() - 1; ++j)
			{
				if (myMatr.at(i, j) == '.') continue;
				//sedie occupate
				nS = myMatr.SubMatrix(i - 1, j - 1, 3, 3).howMany('#');
				nS -= myMatr.at(i, j) == '#' ? 1 : 0;  //non contare me.
				switch (myMatr.at(i, j))
				{
				case 'L':  //era libera
					tmp = nS == 0 ? '#' : 'L';
					break;
				case '#':
					tmp = nS >= SEAT_LIM_1st ? 'L' : '#';
					break;
				case '.':
					tmp = '.';
					break;
				}
				myClip.setAt(i, j, tmp);
			}

		}
		std::swap(myClip, myMatr);
	}

	myAnsw.first = myClip.howMany('#');

	myMatr = orig;
	//stesso corpo, invece che submatrix restituisci le direzioni;
	//cambia il limite 

	myClip.setAll('.');
	while (myClip != myMatr)
	{
		for (i = 1; i < (int)myMatr.numRows() - 1; ++i)
		{
			for (j = 1; j < (int)myMatr.numCols() - 1; ++j)
			{
				if (myMatr.at(i, j) == '.') continue;
				//sedie occupate
				nS = myMatr.FindNonEmptyInDirections(i, j, '.').howMany('#');
				nS -= myMatr.at(i, j) == '#' ? 1 : 0;  //non contare me.
				switch (myMatr.at(i, j))
				{
				case 'L':  //era libera
					tmp = nS == 0 ? '#' : 'L';
					break;
				case '#':
					tmp = nS >= SEAT_LIM_2nd ? 'L' : '#';
					break;
				case '.':
					tmp = '.';
					break;
				}

				myClip.setAt(i, j, tmp);
			}

		}
//		std::cout << myClip<<std::endl<<"**********************"<< std::endl;
		std::swap(myClip, myMatr);
	}

	myAnsw.second = myClip.howMany('#');

	return myAnsw;
}