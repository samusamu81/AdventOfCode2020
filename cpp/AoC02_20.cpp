#include <sstream>
#include "AoC20.hpp"
#include "smmComuni.hpp"

bool AoC2_20A_good(std::string s)
{
	//format is int-int char: string
	std::istringstream iss;
	size_t l, h, f; //low high found
	char dummy, c;
	iss.str(s);
	iss >> l >> dummy >> h >> c >> dummy >> s;

	f = std::count(s.begin(), s.end(), c);
	return (l <= f && h >= f);
}
bool AoC2_20B_good(std::string s)
{
	//format is int-int char: string
	std::istringstream iss;
	int l, h; //low high found
	char dummy, c;
	iss.str(s);
	iss >> l >> dummy >> h >> c >> dummy >> s;
	s = " " + s;
	//!(expr) transforms to boolean; if a != b means XOR when a and b are bool
	return !(s.at(l) == c) != !(s.at(h) == c);

}
std::pair<size_t, size_t> AoC2_20(std::string myFileName)
{
	std::vector<std::string> myInput;
	std::vector<std::string>::iterator  myIter;
	std::string s;
	std::vector<bool> puoi;
	int ans1 = 0, ans2 = 0;
	myInput = lineParser(myFileName);
	for (myIter = myInput.begin(); myIter != myInput.end(); ++myIter)
	{
		ans1 += AoC2_20A_good(*myIter) ? 1 : 0;
		ans2 += AoC2_20B_good(*myIter) ? 1 : 0;
	}

	return std::make_pair(ans1, ans2);
}