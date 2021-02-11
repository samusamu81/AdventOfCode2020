#include "..\hpp\smmComuni.hpp"
#include <sstream>
#include <fstream>

std::string CleanWhiteSpace(std::string str)
{
	std::regex isWhiteSpace(" ");
	return std::regex_replace(str, isWhiteSpace, "");
}
std::string DeleteThisChar(std::string str, char c)
{
	std::string s;
	s.push_back(c);
	std::regex isWhiteSpace(s);
	return std::regex_replace(str, isWhiteSpace, "");
}
std::tuple<bool, int, int> findSum(int wantedValue, std::vector<int> v)
{
	std::set<int> mySet = std::set<int>(v.begin(), v.end());
	std::set<int>::iterator myIter;
	int a = 0, b = 0;
	for (myIter = mySet.begin(); myIter != mySet.end(); ++myIter)
	{
		a = *myIter;
		b = wantedValue - a;
		if (mySet.count(a) + mySet.count(b) == 2) break;
	}

	return std::make_tuple(myIter != mySet.end(), a, b);
}


std::vector<std::string> lineParser(std::istream* is)
{
	std::vector<std::string> answ;
	std::string dummy;
	while (is->good())
	{
		std::getline(*is, dummy);
		answ.push_back(dummy);
	}
	return answ;
}

std::vector<std::string> lineParser(std::string fileName)
{
	std::ifstream myFileInp;
	std::vector<std::string> answ;
	myFileInp.open(fileName.c_str(), std::ifstream::in);
	answ = lineParser(&myFileInp);
	myFileInp.close();
	return answ;
}

std::vector<std::string> Parser(std::istream* is, char delimiter, std::regex excludeMe)
{
	std::vector<std::string> answ;
	std::string currToken;
	while (is->good())
	{
		std::getline(*is, currToken, delimiter);
		if (!std::regex_match(currToken, excludeMe))
			answ.push_back(currToken);
	}
	
	return answ;
}
std::vector<std::string> Parser(std::string fileName, char delimiter, std::regex excludeMe)
{
	std::ifstream myFileInp;
	std::vector<std::string> answ;
	myFileInp.open(fileName.c_str(), std::ifstream::in);
	answ = Parser(&myFileInp, delimiter, excludeMe);
	myFileInp.close();
	return answ;
}

void multiLineMerger(std::istream* is, std::ostream* os, char delimiter)
{

	//if input is spread on many lines with whitelines between them
	//outpu is single line, with a given delimiter
	std::ostringstream ostrs;
	std::string str;
	std::vector<std::string> toMerge = lineParser(is);
	std::vector<std::string>::iterator myIter;
	toMerge.push_back("");//ensure one empty line at end
	
	for (myIter = toMerge.begin(); myIter != toMerge.end(); ++myIter)
	{
		if (myIter->length() > 0)
		{
			ostrs << *myIter << delimiter;
		}
		else
		{
			str = ostrs.str();
			str.pop_back();
			*os << str << std::endl;
			ostrs.str("");
			ostrs.clear();
		}
	}


	return;
}
void multiLineMerger(std::string inputFileName, std::string outputFileName, char delimiter)
{
	std::ifstream *ifsPtr = new std::ifstream(inputFileName);
	std::ofstream *ofsPtr;
	
	ofsPtr = new std::ofstream(outputFileName);
	
	return multiLineMerger(ifsPtr, ofsPtr, delimiter);
}
//std::vector<int> VString2Int(std::vector <std::string> const& lval)
//{
//	std::vector<std::string>::const_iterator theStrings;
//	std::vector<int> myAnsw;
//
//	myAnsw.reserve(lval.size());
//
//	for (theStrings = lval.begin(); theStrings != lval.end(); ++theStrings)
//		myAnsw.push_back(stoi(*theStrings));
//	return myAnsw;
//}

std::vector<size_t> Vint2Vpos(std::vector<int> const& source)
{
	//cerchiamo il massimo di source
	int newSize = *std::max_element(source.begin(), source.end()) + 1;
	size_t i;
	std::vector<size_t> myAnsw(newSize);
	for (i = 0; i < source.size(); ++i)
		myAnsw[source[i]] = i;
	return myAnsw;
}

std::ostream& operator<< (std::ostream& out, const std::vector<bool>& v)
{
	char c;
	std::ostringstream preOut;
	std::string aStr;
	for (auto const& itV : v)
	{
		c = itV ? smmConst::trueSym : smmConst::falseSym;
		preOut << c << smmConst::separator;;
	}

	if (!v.empty())
	{
		aStr = preOut.str();
		aStr.erase(aStr.length() - 1, 1);
	}
	out << aStr;
	return out;
}
//template <typename T>
//std::vector<T> const ExtractColumn(std::vector<std::vector<T>> myMatr, unsigned int colNum)
//{
//	std::vector<T> myAnsw;
//	unsigned int rowNum;
//	for (rowNum = 0; rowNum < myMatr.size(); ++rowNum)
//		myAnsw.push_back(myMatr[rowNum][colNum]);
//	return myAnsw;
//
//}


