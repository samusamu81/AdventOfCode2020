#pragma once
#include <sstream>
#include <vector>

//class TreD_string
//{
//public:
//	TreD_string();
//	TreD_string(int x_coord, int y_coord, int z_coord);
//	TreD_string(TreD_string const & lVal);
//	TreD_string(std::string const & str);
//
//	std::string ToString();
//	std::vector<std::string> vicini(void);
//private:
//	int x, y, z;
//
//};
//
//class QuattroD_string
//{
//public:
//	QuattroD_string();
//	QuattroD_string(int w, int x_coord, int y_coord, int z_coord);
//	QuattroD_string(QuattroD_string const& lVal);
//	QuattroD_string(std::string const& str);
//
//	std::string ToString();
//	std::vector<std::string> vicini(void);
//private:
//	int w, x, y, z;
//
//};


class nDim_string	//Classe che trasforma coordinate testuali in vettore di interi
{
public:
	nDim_string();
	nDim_string(std::vector <int> const & initList);
	nDim_string(nDim_string const& lVal);
	nDim_string(std::string const& str);

	std::string ToString();
	std::vector<std::string> vicini(void);
private:
	std::vector<int> myCoordVec;

};
