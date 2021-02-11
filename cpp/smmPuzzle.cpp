
#include <algorithm>
#include "..\hpp\smmPuzzle.hpp"

void smmPuzzle::insertTile(int tileID, smmTile<char> const& aTile)
{
	myTiles.insert(std::make_pair(tileID, aTile));
	all.push_back(tileID);
}

void smmPuzzle::SolveMe(void)
{
	smmTile<char> *tileFerma, *tileMobile;
	std::vector<int> vDiff;
	/*std::vector<int>::iterator vDiffIter;*/
	int sorg, dest;
	std::pair<int, int> oldCoord;
	int dX, dY;

	//sort all!
	std::sort(all.begin(), all.end());

	smmConst::direction theDirection;
	//pesca il primo
	toDo.push_back(all.front());
	myTiles[toDo.front()].Stick();
	mapIDs_position.insert(std::make_pair(toDo.front(), std::make_pair(0, 0)));
	std::deque<int> tmpDeque;
	//singles = all;//same order
	//singles.pop_front();
	
	

	while (!toDo.empty())
	{
		std::sort(toDo.begin(), toDo.end());
		std::sort(solved.begin(), solved.end());

		sorg = toDo.front();
		
		//Attaccati a N,S,O,W
		//singles = all - solved
		vDiff.clear();
		tmpDeque = all;
		

		while(!tmpDeque.empty())
		{
			if ((!toDo.empty()) && (toDo.front() == tmpDeque.front()))
			{
				toDo.pop_front();
				toDo.push_back(tmpDeque.front());
			}
			else if ((!solved.empty()) && (solved.front() == tmpDeque.front()))
			{
				solved.pop_front();
				solved.push_back(tmpDeque.front());
			}
			else
			{
				singles.push_back(tmpDeque.front());
			}
			tmpDeque.pop_front();
		}
		tileFerma = &myTiles[sorg];
		toDo.pop_front();
#ifdef DEBUG
		std::cout << sorg << ":" << std::endl;
		std::cout << *tileFerma << std::endl;
#endif //! DEBUG
		while (!singles.empty())
		{
			dest = singles.front();
			singles.pop_front();
			tileMobile = & myTiles[dest];
			
			dX = 0;
			dY = 0;
#ifdef DEBUG
			std::cout << " TEST " << dest << std::endl;
			std::cout << *tileMobile << std::endl;
#endif //! DEBUG
			theDirection = tileMobile->AttachTo(*tileFerma);
			switch (theDirection)
			{
			case (smmConst::direction::NORTH):
				dY--;
				break;
			case (smmConst::direction::SOUTH):
				dY++;
				break;
			case (smmConst::direction::EAST):
				dX++;
				break;
			case (smmConst::direction::WEST):
				dX--;
				break;
			}
			
			if (theDirection == smmConst::direction::FAILED)
				continue;
			//si è attaccata
			tileMobile->Stick();			//attaccala
			toDo.push_back(dest);
			
			

#ifdef DEBUG
			std::cout << " Si attacca con " << dest << " sul lato " << theDirection << std::endl;
			//std::cout << *tileMobile << std::endl;
			std::cout << "****************************************" << std::endl;

			std::cout << *tileFerma << std::endl;
			std::cout << *tileMobile << std::endl;
#endif // !DEBUG


			oldCoord = mapIDs_position[sorg];	//coordinate della destinazione
			oldCoord.first += dX;
			oldCoord.second += dY;
			mapIDs_position.insert(std::make_pair(dest, oldCoord));
		}

		solved.push_back(sorg);
	}

	
}

smmMatrix<int> smmPuzzle::GetSolutionMatrix(void)
{
	//SolveMe was called;
	//assume it is solve
	long long int const ONE = 1;
	long long int minX, minY, maxX, maxY;
	long long int aNum;
	std::map<int, std::pair<int, int>>::iterator myIt;
	std::vector<char> v1, v2;
	minX = this->mapIDs_position.begin()->second.first;	//the 1st in the pair; the pair is the 2nd.
	minY = this->mapIDs_position.begin()->second.second;//the 1st in the pair; the pair is the 2nd.
	maxX = minX;
	maxY = minY;
	
	for (myIt = this->mapIDs_position.begin(); myIt != this->mapIDs_position.end(); ++myIt)
	{
		aNum = myIt->second.first;
		minX = aNum < minX ? aNum : minX;
		maxX = aNum > maxX ? aNum : maxX;

		aNum = myIt->second.second;
		minY = aNum < minY ? aNum : minY;
		maxY = aNum > maxY ? aNum : maxY;
	}
	this->solvedPosition.clear();
	this->solvedPosition.Resize((size_t) (maxX - minX + ONE), (size_t) (maxY - minY + ONE));
	//Remember: X is Columns, Y is Rows
	for (myIt = this->mapIDs_position.begin(); myIt != this->mapIDs_position.end(); ++myIt)
	{
		this->solvedPosition.setAt(myIt->second.second - minY, myIt->second.first - minX,  myIt->first);
	}
#ifdef DEBUG	
	std::cout << solvedPosition << std::endl;
#endif
	//controlliamo tutti gli est, poi tutti i sud
	for (long int r = 0; r < solvedPosition.numRows(); ++r)
	{
		for (long int c = 0; c < solvedPosition.numCols() - 1; ++c)
		{
			v1 = myTiles[solvedPosition.at(r, c)].Side(smmConst::EAST);
			v2 = myTiles[solvedPosition.at(r, c+1)].Side(smmConst::WEST);
			
#ifdef DEBUG
			std::cout << solvedPosition.at(r, c)<<std::endl;
			std::cout << myTiles[solvedPosition.at(r, c)] << std::endl;
			std::cout << solvedPosition.at(r, c + 1) << std::endl;
			std::cout << myTiles[solvedPosition.at(r, c+1)] << std::endl;
			std::cout << v1 << std::endl;
			std::cout << v2 << std::endl;
#endif // !DEBUG			
			std::reverse(v2.begin(), v2.end());
			if (v1 != v2)
				throw new std::exception("Problem with Puzzle! Final conf doesn't match");
		}
		
	}

	for (long int c = 0; c < solvedPosition.numCols(); ++c)
	{
		for (long int r = 0; r < solvedPosition.numRows() - 1; ++r)
		{
			v1 = myTiles[solvedPosition.at(r, c)].Side(smmConst::SOUTH);
			v2 = myTiles[solvedPosition.at(r + 1, c)].Side(smmConst::NORTH);
			std::reverse(v2.begin(), v2.end());
			if (!std::equal(v1.begin(), v1.end(), v2.begin()))
				throw new std::exception("Problem with Puzzle! Final conf doesn't match");
		}

	}
	return this->solvedPosition;
}

smmMatrix<char> smmPuzzle::GetSolutionPic(void)
{
	//prendiamo ogni riga e attacchiamola!
	smmMatrix<char> howToAttach;
	smmMatrix<char> aTile;
	std::vector<char> aV, sV;
	size_t r, c, rIns, cIns, rLoop, cLoop;
	howToAttach.Resize(								//-2 because trim the borders
		(myTiles.begin()->second.numRows()-2) *
		solvedPosition.numRows(),
		(myTiles.begin()->second.numCols() -2) *
		solvedPosition.numCols());

	rIns = 0;
	for (r = 0; r < this->solvedPosition.numRows(); r++)
	{
		cIns = 0;
		for (c = 0; c < this->solvedPosition.numCols(); c++)
		{
			aTile = myTiles[solvedPosition.at(r, c)].ConvertToSmmMatrix();
			
			aTile.delRow(aTile.numRows() - 1);
			aTile.delRow(0);
			aTile.delCol(aTile.numCols() - 1);
			aTile.delCol(0);
			for (rLoop = 0; rLoop < aTile.numRows(); ++rLoop)
				for (cLoop = 0; cLoop < aTile.numCols(); ++cLoop)
					howToAttach.setAt(rIns + rLoop, cIns + cLoop, aTile.at(rLoop, cLoop));
			cIns += aTile.numCols();
		}
		rIns += aTile.numRows();
	}
	return howToAttach;

}

smmTile<char> smmPuzzle::GetTile(int tileNum)
{	
	return this->myTiles[tileNum];
}



void smmPuzzle::print()
{
	std::cout << this->GetSolutionPic();
}

size_t smmPuzzle::HowManyTroubledWaters(void)
{
	smmTile<char> SeaMonsterTile;
	smmMatrix<char> SeaMonster;
	SeaMonsterTile.readFromFile(".\\input\\SeaMonster.txt",'-');	//need '-' as spacer; whitespaces and >> operator mess with each other
	int i, nMonster = 0;
	bool isMonster;
	size_t lastR, lastC, r, c;
	smmMatrix<char> mySolution = GetSolutionPic();
	std::vector<std::pair<size_t, size_t>> myMonsterPos;
	std::vector<std::pair<size_t, size_t>>::iterator monsterIter;
	

	SeaMonsterTile.turnLeft();
	for (i = 0; i < 8; i++)
	{
		
		myMonsterPos.clear();
		SeaMonsterTile.turnRight();
		if (i == 4) SeaMonsterTile.Transpose();
		SeaMonster = SeaMonsterTile.ConvertToSmmMatrix();
		for (r = 0; r < SeaMonster.numRows(); ++r)
			for (c = 0; c < SeaMonster.numCols(); ++c)
				if (SeaMonster.at(r, c) == '#') myMonsterPos.push_back(std::make_pair(r, c));

		lastR = mySolution.numRows() - SeaMonster.numRows();
		lastC = mySolution.numCols() - SeaMonster.numCols();

		for (r = 0; r < lastR; ++r)
		{
			for (c = 0; c < lastC; ++c)
			{
				isMonster = true;
				for (monsterIter = myMonsterPos.begin(); monsterIter != myMonsterPos.end(); ++monsterIter)
				{
					if (mySolution.at(r + monsterIter->first, c + monsterIter->second) == '.')	//use ==.; use O for monster found!
					{
						isMonster = false;
						break;	//stays inside c loop
					}
				}
				if (isMonster)	//do the same shit, but substitute value!
				{
					for (monsterIter = myMonsterPos.begin(); monsterIter != myMonsterPos.end(); ++monsterIter)
					{
						mySolution.setAt(r + monsterIter->first, c + monsterIter->second, 'O');
					}
				}
			}
		}
	}
#ifdef DEBUG
	std::cout << mySolution << std::endl;
#endif
	return mySolution.howMany('#');
}
