#include "nDim_string.hpp"
#include "smmComuni.hpp"

//TreD_string::TreD_string()
//{
//	x = y = z = 0;
//}
//
//TreD_string::TreD_string(int x_coord, int y_coord, int z_coord)
//{
//	x = x_coord;
//	y = y_coord;
//	z = z_coord;
//}
//
//TreD_string::TreD_string(TreD_string const& lVal)
//{
//	this->x = lVal.x;
//	this->y = lVal.y;
//	this->z = lVal.z;
//}
//
//TreD_string::TreD_string(std::string const& str)
//{
//	std::istringstream iss(str);
//	std::vector<int> myVals = VString2Int(Parser(&iss, ','));
//	x = myVals[0];
//	y = myVals[1];
//	z = myVals[2];
//}
//
//std::string TreD_string::ToString()
//{
//	std::ostringstream oss;
//	oss << x << ',' << y << ',' << z;
//	return oss.str();
//}
//
//std::vector<std::string> TreD_string::vicini(void)
//{
//	int MYSELF = 14;//this is the "myself" element
//	std::vector<std::string> myAnsw;
//	int i, j, k;
//	for (i = -1; i <= 1; i++)
//		for (j = -1; j <= 1; j++)
//			for (k = -1; k <= 1; k++)
//			{
//				MYSELF--;
//				if (MYSELF == 0) 
//					continue;
//				myAnsw.push_back(TreD_string(x + i, y + j, z + k).ToString());
//			}
//	return myAnsw;
//}
//
//QuattroD_string::QuattroD_string()
//{
//	w = x = y = z = 0;
//}
//
//QuattroD_string::QuattroD_string(int w_coord, int x_coord, int y_coord, int z_coord)
//{
//	w = w_coord;
//	x = x_coord;
//	y = y_coord;
//	z = z_coord;
//}
//
//QuattroD_string::QuattroD_string(QuattroD_string const& lVal)
//{
//	this->w = lVal.w;
//	this->x = lVal.x;
//	this->y = lVal.y;
//	this->z = lVal.z;
//}
//
//QuattroD_string::QuattroD_string(std::string const& str)
//{
//	std::istringstream iss(str);
//	std::vector<int> myVals = VString2Int(Parser(&iss, ','));
//	w = myVals[0];
//	x = myVals[1];
//	y = myVals[2];
//	z = myVals[3];
//
//}
//
//std::string QuattroD_string::ToString()
//{
//	std::ostringstream oss;
//	oss << w << ',' << x << ',' << y << ',' << z;
//	return oss.str();
//}
//
//std::vector<std::string> QuattroD_string::vicini(void)
//{
//	int MYSELF = 14;//this is the "myself" element
//	std::vector<std::string> myAnsw;
//	int i, j, k;
//	for (i = -1; i <= 1; i++)
//		for (j = -1; j <= 1; j++)
//			for (k = -1; k <= 1; k++)
//			{
//				MYSELF--;
//				if (MYSELF == 0)
//					continue;
//				myAnsw.push_back(QuattroD_string(x + i, y + j, z + k).ToString());
//			}
//	return myAnsw;
//}

nDim_string::nDim_string() {}
nDim_string::nDim_string(std::vector <int> const& initVec) 
{
	this->myCoordVec = initVec;
}
nDim_string::nDim_string(nDim_string const& lVal) 
{
	this->myCoordVec = lVal.myCoordVec;
}
nDim_string::nDim_string(std::string const& str) 
{
	int dummy = 0;
	std::istringstream iss(str);
	this->myCoordVec = VectorConverter(Parser(&iss, ','), dummy);
}

std::string nDim_string::ToString() 
{
	std::vector<int>::iterator myIter;
	std::ostringstream oss;
	for (myIter = myCoordVec.begin(); myIter != myCoordVec.end(); ++myIter)
		oss << *myIter << ',';

	return oss.str().substr(0, oss.str().length() - 1);
}
std::vector<std::string> nDim_string::vicini(void) 
{	
	//mettiamo dietro
	std::vector<std::string> answ, ones, zeros, minus; 
	std::vector<std::string>::iterator myIt;
	std::string iStr;
	answ.push_back("");
	int i;
	for (i = 0; i < (int) myCoordVec.size(); i++)
	{
		ones = answ;
		minus = answ;
		zeros = answ;
		iStr = std::to_string(myCoordVec[i] + 1);
		for (myIt = ones.begin(); myIt != ones.end(); ++myIt)
			*myIt += (i > 0 ? "," : "") + iStr;
		iStr = std::to_string(myCoordVec[i] - 1);
		for (myIt = minus.begin(); myIt != minus.end(); ++myIt)
			*myIt += (i > 0 ? "," : "") + iStr;
		iStr = std::to_string(myCoordVec[i]);
		for (myIt = zeros.begin(); myIt != zeros.end(); ++myIt)
			*myIt += (i > 0 ? "," : "") + iStr;
		answ = ones;
		answ.insert(answ.end(), minus.begin(), minus.end());
		answ.insert(answ.end(), zeros.begin(), zeros.end());
	}
	answ.pop_back();
	return answ;
}