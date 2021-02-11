#include <regex>
#include "..\hpp\smmPuzzle.hpp"
#include "..\hpp\smmComuni.hpp"

std::pair<size_t, size_t> AoC20_20(std::string myFileName)
{
	//read tiles
	smmPuzzle myPuzzle;
	std::vector<std::string> vLines = lineParser(myFileName);
	std::vector<std::string>::iterator aL;
	smmMatrix<int> mySolution;
	smmTile <char> aTile;
	std::pair<size_t, size_t> myAnsw;
	std::vector<char> v;
	std::regex myTRegex("Tile (\\d+):");
	int i;
	if (vLines.back().length() > 0) vLines.push_back("");
	for (auto aL = vLines.begin(); aL != vLines.end(); ++aL)
	{
		if (std::regex_match(*aL, myTRegex))
		{
			i = std::stoi(std::regex_replace(*aL, myTRegex, "$1"));
		}
		else if (aL->length() == 0)
		{
			myPuzzle.insertTile(i, aTile);
			aTile.clear();
		}
		else
		{
			v.clear();
			v.resize(aL->size());
			std::copy(aL->begin(), aL->end(), v.begin());
			aTile.insertRow(aTile.numRows(), v);
		}
	}

	myPuzzle.SolveMe();




	mySolution = myPuzzle.GetSolutionMatrix();
	//product of 4 corner
#ifdef DEBUG



	for (size_t x = 0; x < mySolution.numRows(); ++x)
	{
		for (size_t y = 0; y < mySolution.numCols(); ++y)
		{
			std::cout << mySolution.at(x, y) << std::endl;
			std::cout << myPuzzle.GetTile(mySolution.at(x, y)) << std::endl;
			std::cout << myPuzzle.GetTile(mySolution.at(x, y)).ConvertToSmmMatrix() << std::endl;

		}
	}	
	std::cout<<myPuzzle.GetSolutionPic();
#endif
	
	myAnsw.first = mySolution.at(0, 0);
	myAnsw.first *= mySolution.at(mySolution.numRows() - 1, 0);
	myAnsw.first *= mySolution.at(0, mySolution.numCols() - 1);
	myAnsw.first *= mySolution.at(mySolution.numRows() - 1, mySolution.numCols() - 1);

	myAnsw.second = myPuzzle.HowManyTroubledWaters();
	return myAnsw;
}