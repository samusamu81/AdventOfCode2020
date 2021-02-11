#pragma once
#include <vector>
#include <algorithm>
#include <exception>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "..\hpp\smmComuni.hpp"
template <class tipo> class smmMatrix
{
public:
	std::vector<tipo> const getRow(size_t r) const;
	std::vector<tipo> const getCol(size_t c) const;
	void setRow(size_t r, std::vector<tipo> v);
	void setCol(size_t c, std::vector<tipo> v);
	void delRow(size_t r);
	void delCol(size_t c);
	void insertRow(size_t rPos, std::vector<tipo> v);
	void insertCol(size_t cPos, std::vector<tipo> v);
	size_t const & numRows() const;
	size_t const & numCols() const;
	const tipo & at(size_t r, size_t c) const;
	void setAt(size_t r, size_t c, const tipo & val);
	void Transpose (void);
	void Resize(size_t r, size_t c);
	void setAll(tipo val);
	void Replace(tipo oldVal, tipo newVal);
	void clear();
	void readFromFile(std::string fileName, char transformSpaceInto = ' ');
	void readFromStream(std::istream * fl, char transformSpaceInto = ' ');
	size_t const howMany(tipo equal2Me) const;
	size_t const howManyInRow(size_t r, tipo equal2Me) const;
	size_t const howManyInCol(size_t c, tipo equal2Me) const;
	size_t const howManyInSubMatr(size_t row_start, size_t col_start, size_t numRows, size_t numCols, tipo equal2Me) const;
	smmMatrix<tipo> const SubMatrix(size_t row_start, size_t col_start, size_t numRows, size_t numCols) const;
	//size_t const howManySubMatrix(smmMatrix<tipo> const& look4me);
	smmMatrix<tipo> const  FindNonEmptyInDirections(size_t row_pos, size_t col_pos, tipo empty) const;
	bool operator ==(smmMatrix<tipo> const& rval);
	bool operator !=(smmMatrix<tipo> const& rval);
	template<typename tipo_2>
	friend std::ostream& operator<<(std::ostream& out, const smmMatrix<tipo_2> & o);
	mutable bool isTransposed = false;
protected:
	std::vector<tipo> rawElement = std::vector<tipo>();
	size_t nR = 0, nC = 0;
	size_t const pos_k(size_t rNum, size_t cNum) const;//NB: only for non transposed
};

template<class tipo>
inline std::vector<tipo> const smmMatrix<tipo>::getRow(size_t r) const
{
	std::vector<tipo> myAnsw(nC);
	if (isTransposed)	//per le trasposte, fai e disfa
	{
		isTransposed = false;
		myAnsw = this->getCol(r);
		isTransposed = true;
		return myAnsw;
	}
	
	std::copy(rawElement.begin() + r * nC, rawElement.begin() + r * nC + nC, myAnsw.begin());//devi superare di 1!
	return myAnsw;
}

template<class tipo>
inline std::vector<tipo> const smmMatrix<tipo>::getCol(size_t c) const
{
	std::vector<tipo> myAnsw(nR);
	if (isTransposed)
	{
		isTransposed = false;
		myAnsw = this->getRow(c);
		isTransposed = true;
		return myAnsw;
	}
	int i;
	
	for (i = 0; i < (int) nR; ++i)
		myAnsw[i] = rawElement[c + i * nC];
	return myAnsw;
}



template<class tipo>
inline const tipo& smmMatrix<tipo>::at(size_t r, size_t c) const
{
	size_t myk;
	myk = !isTransposed ? this->pos_k(r, c) : this->pos_k(c, r);
	return rawElement[myk];
	// TODO: inserire l'istruzione return qui
}

template<class tipo>
inline void smmMatrix<tipo>::setAt(size_t r, size_t c, tipo const & val)
{
	//cast away the const!
	size_t myk;
	myk = !isTransposed ? this->pos_k(r, c) : this->pos_k(c, r);
	rawElement[myk] = val;
	return;
}

template<class tipo>
inline void smmMatrix<tipo>::Transpose(void)
{
	isTransposed = !isTransposed;
	//std::swap(nR, nC);
}

template<class tipo>
inline void smmMatrix<tipo>::Resize(size_t r, size_t c)
{
	nR = r;
	nC = c;
	rawElement.clear();
	rawElement.resize(r * c);	//resize! Forza allocazione
}

template<class tipo>
inline void smmMatrix<tipo>::setAll(tipo val)
{
	std::fill(rawElement.begin(), rawElement.end(), val);
}

template<class tipo>
inline void smmMatrix<tipo>::Replace(tipo oldVal, tipo newVal)
{
	std::replace(rawElement.begin(), rawElement.end(), oldVal, newVal);
}

template<class tipo>
inline void smmMatrix<tipo>::clear()
{
	nC = nR = 0;
	rawElement.clear();
}

template<class tipo>
inline void smmMatrix<tipo>::readFromFile(std::string fileName, char transformSpaceInto)
{
	//before reading file, transform space into something else
	std::ifstream ifs;
	ifs.open(fileName);
	readFromStream(&ifs, transformSpaceInto);
	ifs.close();

}

template<class tipo>
inline void smmMatrix<tipo>::readFromStream(std::istream *is, char transformSpaceInto)
{
	//before reading file, transform space into something else
	tipo unVal;
	std::vector<tipo> unaRiga;
	std::string dummy;
	std::istringstream iss;
	this->clear();
	
	while (is->good())
	{
		std::getline(*is, dummy);
		if (transformSpaceInto != ' ')
			std::replace(dummy.begin(), dummy.end(), ' ', transformSpaceInto);
		iss.str(dummy);
		iss.clear();
		unaRiga.clear();
		while (iss.good())
		{
			iss >> unVal;
			unaRiga.push_back(unVal);
		}
		while (dummy.length() < unaRiga.size())
			unaRiga.pop_back();
		this->insertRow(this->nR, unaRiga);
	}

}

template<class tipo>
inline size_t const smmMatrix<tipo>::howMany(tipo equal2Me) const
{
	return std::count(rawElement.begin(), rawElement.end(), equal2Me);
}

template<class tipo>
inline size_t const smmMatrix<tipo>::howManyInRow(size_t r,tipo equal2Me) const
{
	std::vector<tipo> v = this->getRow(r);
	return std::count(v.begin(), v.end(), equal2Me);
}

template<class tipo>
inline size_t const smmMatrix<tipo>::howManyInCol(size_t c, tipo equal2Me) const
{
	std::vector<tipo> v = this->getCol(c);
	return std::count(v.begin(), v.end(), equal2Me);
}

template<class tipo>
inline size_t const smmMatrix<tipo>::howManyInSubMatr(size_t row_start, size_t col_start, size_t numRows, size_t numCols, tipo equal2Me) const
{
	size_t myAnsw = 0, i, j;
	if (isTransposed)
	{
		isTransposed = false;
		myAnsw = howManyInSubMatr(col_start, row_start, numCols, numRows, equal2Me);
		isTransposed = true;
		return myAnsw;
	}
	//by definitio it is not tranposed!
	//redefine numRows to best use of for loop
	numRows += row_start;
	numCols += col_start;
	for (i = row_start; i < numRows; ++i)
		for (j = col_start; j < numCols; ++j)
			myAnsw += rawElement[pos_k(i, j)] == equal2Me ? 1 : 0;

	return myAnsw;
}

template<class tipo>
inline smmMatrix<tipo> const smmMatrix<tipo>::SubMatrix(size_t row_start, size_t col_start, size_t numRows, size_t numCols) const
{
	smmMatrix<tipo> myAnsw;
	if (isTransposed)
	{
		isTransposed = false;
		myAnsw = SubMatrix(col_start, row_start, numCols, numRows);
		isTransposed = true;
		return myAnsw;
	}
	size_t i;

	myAnsw.Resize(numRows, numCols);
	auto o1 = rawElement.begin();
	auto o2 = o1;
	auto d1 = myAnsw.rawElement.begin();
	for (i = row_start; i < row_start + numRows; ++i)
	{
		o1 = rawElement.begin() + this->pos_k(i, col_start);
		o2 = o1 + numCols;
		
		std::copy(o1,o2,d1);
		d1 = d1 + numCols;
	}

	return myAnsw;
}

template<class tipo>
inline smmMatrix<tipo> const smmMatrix<tipo>::FindNonEmptyInDirections(size_t row_pos, size_t col_pos, tipo empty) const
{
	size_t i, j;
	smmMatrix <tipo> myAnsw;
	myAnsw.Resize(3, 3);
	myAnsw.setAt(1, 1, this->at(row_pos, col_pos));
	//cerca sinistra
	for (j = col_pos - 1; j > 0; --j)	//W
		if (this->at(row_pos, j) != empty) break;
	myAnsw.setAt(1, 0, this->at(row_pos, j));
	
	for (j = col_pos + 1; j < (int) nC - 1; ++j)	//E
		if (this->at(row_pos, j) != empty) break;
	myAnsw.setAt(1, 2, this->at(row_pos, j));

	for (i = row_pos - 1; i > 0; --i)	//N
		if (this->at(i, col_pos) != empty) break;
	myAnsw.setAt(0, 1, this->at(i, col_pos));

	for (i = row_pos + 1; i < (int) nR - 1; ++i)	//S
		if (this->at(i, col_pos) != empty) break;
	myAnsw.setAt(2, 1, this->at(i, col_pos));

	for (j = col_pos - 1, i = row_pos - 1; (j > 0 && i > 0); --j, --i)	//NW
		if (this->at(i, j) != empty) break;
	myAnsw.setAt(0, 0, this->at(i, j));

	for (j = col_pos + 1, i = row_pos - 1; (j < (int) nC - 1&& i > 0); ++j, --i)	//NE
		if (this->at(i, j) != empty) break;
	myAnsw.setAt(0, 2, this->at(i, j));

	for (j = col_pos - 1, i = row_pos + 1; (j > 0 && i < (int) nR - 1); --j, ++i)	//SW
		if (this->at(i, j) != empty) break;
	myAnsw.setAt(2, 0, this->at(i, j));

	for (j = col_pos + 1, i = row_pos + 1; (j < (int) nC - 1 && i < (int) nR - 1); ++j, ++i)	//SE
		if (this->at(i, j) != empty) break;
	myAnsw.setAt(2, 2, this->at(i, j));

	return myAnsw;
}

template<class tipo>
inline bool smmMatrix<tipo>::operator==(smmMatrix<tipo> const& rval)
{
	bool answ;
	answ = this->isTransposed == rval.isTransposed;
	
	answ = answ ?
		(nR == rval.nR) && (nC == rval.nC) :
		(nC == rval.nR) && (nR == rval.nC);
	
	if (!answ) return answ;
	for (size_t i = 0; i < this->numRows(); i++)	//confronta "riga per riga"
		answ = answ && (this->getRow(i) == rval.getRow(i));
		
	return answ;
}

template<class tipo>
inline bool smmMatrix<tipo>::operator!=(smmMatrix<tipo> const& rval)
{
	return !((*this) == rval);
}

template<class tipo>
inline size_t const smmMatrix<tipo>::pos_k(size_t rNum, size_t cNum) const
{
	//funziona per le matrici non trasposte. Attenzione ad usarla per le trasposte.
	//nessun check: se la matrice è trasposta potrebbe essere stata chiamata in maniera corretta
	size_t myAnsw = rNum * nC + cNum;
	return myAnsw;
}

template<class tipo>
inline void smmMatrix<tipo>::setRow(size_t r, std::vector<tipo> v)
{
	if (isTransposed)
	{
		isTransposed = !isTransposed;
		this->setCol(r, v);
		isTransposed = !isTransposed;
		return;
	}
		
	if (v.size() != nC) throw new std::exception();
	std::copy(v.begin(), v.end(), rawElement.begin()+r*nC);
	return;
}

template<class tipo>
inline void smmMatrix<tipo>::setCol(size_t c, std::vector<tipo> v)
{
	if (isTransposed)
	{	
		isTransposed = !isTransposed;
		this->setRow(c, v);
		isTransposed = !isTransposed;
	}
	if (v.size() != nR) throw new std::exception();
	int i;
	for (i = 0; i < (int) nR; ++i)
		rawElement[c + i * nC] = v[i];
	return;
}

template<class tipo>
inline void smmMatrix<tipo>::delRow(size_t r)
{
	if (isTransposed)
	{
		isTransposed = !isTransposed;
		delCol(r);
		isTransposed = !isTransposed;
		return;
	}
		

	if (r != nR - 1)
		//NB: copy back vuole iterator END di destinazione
		std::copy_backward(rawElement.begin() + nC * (r+1), rawElement.end(), rawElement.end() - nC);
	rawElement.resize(rawElement.size() - nC);
	nR--;
}

template<class tipo>
inline void smmMatrix<tipo>::delCol(size_t c)
{
	if (isTransposed)
	{
		isTransposed = !isTransposed;
		delRow(c); 
		isTransposed = !isTransposed;
		return;
	}
	std::vector<tipo> oldRawElement;
	oldRawElement = this->rawElement;
	
	this->rawElement.clear();
	rawElement.reserve(oldRawElement.size());

	for (unsigned int k = 0; k < oldRawElement.size(); ++k)
	{
		rawElement.push_back(oldRawElement[k]);
		if (k % nC == c) rawElement.pop_back();
	}
	nC--;
}

template<class tipo>
inline void smmMatrix<tipo>::insertRow(size_t rPos, std::vector<tipo> v)
{
	size_t deltaPosStart, deltaPosEnd;
	if (isTransposed)
	{
		this->isTransposed = false;
		insertCol(rPos, v);
		this->isTransposed = true;
		return;
	}
	if (nR == 0 && nC == 0)
	{
		nC = v.size();
		nR = 1;
		rawElement = v;
		return;
	}
	if (rPos > nR) throw new std::exception();
	rawElement.resize(rawElement.size() + nC);
	deltaPosStart = rPos * nC;		//prima posizione sporca
	deltaPosEnd = (rPos+1) * nC;	//nota
	std::copy_backward(rawElement.begin() + deltaPosStart, rawElement.end() - nC, rawElement.end());
	std::copy(v.begin(), v.end(), rawElement.begin() + deltaPosStart);
	nR++;
}

template<class tipo>
inline void smmMatrix<tipo>::insertCol(size_t cPos, std::vector<tipo> v)
{
	if (isTransposed)
	{
		this->isTransposed = false;
		insertRow(cPos, v);
		this->isTransposed = true;
		return;
	}	
	if (nR == 0 && nC == 0)
	{
		nR = v.size();
		nC = 1;
		rawElement.resize(nR);
		std::copy(v.begin(), v.end(), rawElement.begin());
		return;
	}

	if (cPos > nC) throw new std::exception();
	size_t j;
	smmMatrix theOther;
	theOther.Resize(this->nR, this->nC + 1);
	for (j = 0; j < (int) cPos; ++j)
		theOther.setCol(j, this->getCol(j));
	theOther.setCol(cPos, v);
	for (j = cPos + 1; j <= nC; ++j)
		theOther.setCol(j, this->getCol(j-1));

	std::swap(theOther.rawElement, this->rawElement);
	nC++;
}

template<class tipo>
inline size_t const & smmMatrix<tipo>::numRows() const
{
	return isTransposed? nC : nR;
}

template<class tipo>
inline size_t const & smmMatrix<tipo>::numCols() const
{
	return isTransposed? nR : nC;
}

template<typename tipo_2>		//sembra sia necessario tipo2 per non incasinare il sistema. Se gli metti tipo uguale alla classe, muore male iil linker
inline std::ostream& operator<<(std::ostream& out, const smmMatrix<tipo_2>& o)
{

	size_t i, myR;
	//erroraccio!
	myR = o.numRows();	//as you want it to be printed
	
	for (i = 0; i < myR; ++i)
	{
		out << o.getRow(i) << std::endl;
	}

	return out;
}
