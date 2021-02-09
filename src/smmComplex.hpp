#pragma once
#include <iostream>
template <class tipo> class smmComplex
{
public:
	/*template<class T> smmComplex(T re = 0, T im = 0) 
	{ 
		this->Re = re;
		this->Im = im;
	};
	template<class T> smmComplex(smmComplex <T> const & rhs)
	{
		this->Re = rhs.Re;
		this->Im = rhs.Im;
	};*/
	
	void Set(tipo re, tipo im);
	void operator+=(const smmComplex<tipo>& rval);
	void operator-=(const smmComplex<tipo>& rval);
	void operator*=(const smmComplex<tipo>& rval);

	smmComplex<tipo> operator+(const smmComplex<tipo>& rval) const;
	smmComplex<tipo> operator-(const smmComplex<tipo>& rval) const;
	smmComplex<tipo> operator*(const smmComplex<tipo>& rval) const;
	const smmComplex<tipo>& operator=(const smmComplex<tipo>& rval);
	smmComplex<tipo> operator*(const tipo & rval) const;
	bool operator< (smmComplex<tipo> const& rhs) const;
	bool operator<= (smmComplex<tipo> const& rhs) const;
	bool operator== (smmComplex<tipo> const& rhs) const;
	bool operator> (smmComplex<tipo> const& rhs) const;	//NOT <=
	bool operator>= (smmComplex<tipo> const& rhs) const;//NOT <
	bool operator!= (smmComplex<tipo> const& rhs) const;//NOT ==

	void operator*=(const tipo & rval);
	void TurnRight(int nTimes);
	void TurnLeft(int nTimes);
	tipo Re, Im;
	template <typename T2>
	friend std::ostream& operator<<(std::ostream& out, const smmComplex<T2>& o);
private:
	void L90(void);
};


template<class tipo>
inline void smmComplex<tipo>::operator+=(const smmComplex<tipo>& rval)
{
	this->Re += rval.Re;
	this->Im += rval.Im;
}

template<class tipo>
inline void smmComplex<tipo>::operator-=(const smmComplex<tipo>& rval)
{
	this->Re -= rval.Re;
	this->Im -= rval.Im;
}

template<class tipo>
inline void smmComplex<tipo>::Set(tipo re, tipo im)
{
	this->Re = re;
	this->Im = im;
}
template<class tipo>
inline void smmComplex<tipo>::operator*=(const smmComplex<tipo>& rval)
{
	smmComplex<tipo> answ(*this);
	(*this) = answ * rval;
}

template<class tipo>
inline smmComplex<tipo> smmComplex<tipo>::operator*(const smmComplex<tipo>& rval)  const
{
	//ac-bd ac+bd
	smmComplex<tipo> answ(this->r * rval.r - this->i * rval.i,
		this->r * rval.i + this->i * rval.r);
	return answ;
}

template<class tipo>
inline const smmComplex<tipo>& smmComplex<tipo>::operator=(const smmComplex<tipo>& rval)
{
	// TODO: inserire l'istruzione return qui
	this->r = rval.r;
	this->i = rval.i;
}

template<class tipo>
inline smmComplex<tipo> smmComplex<tipo>::operator*(const tipo& rval) const
{
	smmComplex<tipo> X(*this);
	X *= rval;
	return X;
}

template<class tipo>
inline void smmComplex<tipo>::operator*=(const tipo& rval)
{
	this->Re *= rval;
	this->Im *= rval;
}

template<class tipo>
inline void smmComplex<tipo>::TurnRight(int nTimes)
{
	TurnLeft(-nTimes);
}

template<class tipo>
inline void smmComplex<tipo>::TurnLeft(int nTimes)
{
	while (nTimes < 0) nTimes += 4;
	nTimes = nTimes % 4;
	for (int n = 0; n < nTimes; ++n)
		this->L90();
	return;
}
template<class tipo>
inline smmComplex<tipo> smmComplex<tipo>::operator+(const smmComplex<tipo>& rval) const
{
	smmComplex<tipo> myAnsw(*this);
	myAnsw += rval;
	return myAnsw;
}

template<class tipo>
inline smmComplex<tipo> smmComplex<tipo>::operator-(const smmComplex<tipo>& rval) const
{
	smmComplex<tipo> myAnsw(*this);
	myAnsw -= rval;
	return myAnsw;
}
template<class tipo>
inline bool smmComplex<tipo>::operator<(smmComplex<tipo> const& rhs) const
{
	if (this->Re < rhs.Re)
		return true;
	else if (this->Re == rhs.Re)
		return this->Im < rhs.Im;
	else
		return false;
}
template<class tipo>
inline bool smmComplex<tipo>::operator<=(smmComplex<tipo> const& rhs) const
{
	if (this->Re < rhs.Re)
		return true;
	else if (this->Re == rhs.Re)
		return this->Im <= rhs.Im;
	else
		return false;
}
template<class tipo>
inline bool smmComplex<tipo>::operator==(smmComplex<tipo> const& rhs) const
{
	return this->Re == rhs.Re && this->Im == rhs.Im;
}
template<class tipo>
inline bool smmComplex<tipo>::operator!=(smmComplex<tipo> const& rhs) const
{
	return this->Re != rhs.Re || this->Im != rhs.Im;
}
template<class tipo>
inline bool smmComplex<tipo>::operator>(smmComplex<tipo> const& rhs) const
{
	return !((*this) <= rhs);
}
template<class tipo>
inline bool smmComplex<tipo>::operator>=(smmComplex<tipo> const& rhs) const
{
	return !((*this) < rhs);
}



template<class tipo>
inline void smmComplex<tipo>::L90(void)
{
	tipo x;
	x = this->Re;
	this->Re = -this->Im;
	this->Im = x;
}
template<class T2>
std::ostream& operator<<(std::ostream& out, const smmComplex<T2>& o)
{
	out << o.Re << '\t' << o.Im;
	return out;

}