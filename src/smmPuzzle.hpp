#pragma once

#include <map>
#include <deque>
#include "smmTile.hpp"
#include "smmMatrix.hpp"

class smmPuzzle
{
public:
	void insertTile(int tileID, smmTile<char> const& aTile);
	void SolveMe(void);
	smmMatrix <int> GetSolutionMatrix(void);	//return tile positions
	smmMatrix <char> GetSolutionPic(void);
	smmTile <char> GetTile(int tileNum);
	size_t HowManyTroubledWaters(void);
	//size_t CountHashNoMonster(smmMatrix<char> myMonster);
	void print();
private:
	std::map<int, std::pair<int, int>> mapIDs_position;
	std::map<int, smmTile<char>> myTiles;
	smmMatrix <int> solvedPosition;
	std::deque<int> singles, solved, all, toDo;
	
	
};

