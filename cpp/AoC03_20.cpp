#include "AoC20.hpp"
#include "smmComuni.hpp"

int AoC3_20_CountTrees(std::vector<std::string> myInput, unsigned int hMove, unsigned int vMove)
{
	const char ALBERO = '#';
	unsigned int r, c;
	int counter;	//row and column
	counter = 0;
	for (r = 0, c = 0; r < myInput.size(); r += vMove, c += hMove)
	{
		c = c % myInput[r].length();
		counter += myInput[r].at(c) == ALBERO ? 1 : 0;
	}
	return counter;
}

std::pair<size_t, size_t> AoC3_20(std::string myFileName)
{
	std::vector<std::string> myInput;
	std::vector<std::string>::iterator  myIter;
	std::string s;
	std::vector<bool> puoi;
	size_t ans1 = 0, ans2 = 1;
	unsigned int hMove = 3, vMove = 1;
	std::vector<unsigned int> hMoves = { 1, 3, 5, 7, 1 }, vMoves = { 1, 1, 1, 1, 2 };
	int vectorPos;

	myInput = lineParser(myFileName);

	ans1 = AoC3_20_CountTrees(myInput, hMove, vMove);
	for (vectorPos = 0; vectorPos < (int)hMoves.size(); ++vectorPos)
	{
		ans2 *= AoC3_20_CountTrees(myInput, hMoves[vectorPos], vMoves[vectorPos]);
	}

	return std::make_pair(ans1, ans2);
}