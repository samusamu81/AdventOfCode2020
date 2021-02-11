#include "..\hpp\AoC20.hpp"
#include "..\hpp\smmComuni.hpp"
std::pair<size_t, size_t> AoC01_20(std::string myFileName)
{
	const int FIND_ME = 2020;
	std::vector<int> myInput;
	std::vector<int>::iterator myIter;

	std::tuple <bool, int, int> sumIs;
	size_t ans1 = 0, ans2 = 0;
	int findDiff = 0;		//useful to find 3 numbers such that their sum is something
	myInput = myParser(myFileName, findDiff); //dummy findDiff
	sumIs = findSum(FIND_ME, myInput);

	ans1 = (size_t) std::get<1>(sumIs) * (size_t) std::get<2>(sumIs);
	std::sort(myInput.begin(), myInput.end());
	//reverse(myInput.begin(), myInput.end());
	for (myIter = myInput.begin(); myIter != myInput.end(); ++myIter)
	{
		findDiff = *myIter;
		myInput.erase(myIter);
		sumIs = findSum(FIND_ME - findDiff, myInput);
		if (std::get<0>(sumIs)) break;
	}
	ans2 = (size_t) findDiff * (size_t) std::get<1>(sumIs) * (size_t) std::get<2>(sumIs);
	return std::make_pair(ans1, ans2);
}