#pragma once
#include <map>
#include <string>
#include <sstream>
#include "smmConsts.hpp"
#include "smmMatrix.hpp"


template <class tipo> class smmTile :
    public smmMatrix<tipo>
{
public:
    std::vector<tipo> const Side(smmConst::direction d) const;
    void turnRight(void);
    void turnLeft(void);
    void Stick(void);
    template<typename tipo_2>
    friend std::ostream& operator<<(std::ostream& out, const smmTile<tipo_2>& o);
    smmConst::direction AttachTo(smmTile const & theOther);
    smmMatrix<tipo> const ConvertToSmmMatrix(void) const;
private:
    std::vector<tipo> const Top() const;
    std::vector<tipo> const Bottom() const;
    std::vector<tipo> const Right() const;
    std::vector<tipo> const Left() const;
    
    void DoMyPerim(bool forceMe = false);

    mutable int nRot = 0;
    bool isFixed = false;
    std::map<smmConst::direction, std::vector<tipo>> myPerim;
};


template<class tipo>
inline std::vector<tipo> const smmTile<tipo>::Top() const
{
    std::vector<tipo> myAnsw;
    switch (nRot % 4)
    {
    case 0:                         //R0
        myAnsw = this->getRow(0);
        break;
    case 1:
        nRot = 0;//R1, 90°
        myAnsw = this->Left();
        nRot = 1;
        break;
    case 2:                         //R2, 180°
        nRot = 0;
        myAnsw = this->Bottom();
        nRot = 2;
        break;
    case 3:                         //R3, 270°
        nRot = 0; 
        myAnsw = this->Right();
        nRot = 3;
        break;
    }
    return myAnsw;
}
template<class tipo>
inline std::vector<tipo> const smmTile<tipo>::Left() const
{
    std::vector<tipo> myAnsw;
    switch (nRot)
    {
    case 0:                         //R0
        myAnsw = this->getCol(0);
        std::reverse(myAnsw.begin(), myAnsw.end());
        break;
    case 1:                         //R1, 90°
        nRot = 0;
        myAnsw = this->Bottom();
        nRot = 1;
        break;
    case 2:                         //R2, 180°
        nRot = 0; 
        myAnsw = this->Right();
        nRot = 2;
        break;
    case 3:                         //R3, 270°
        nRot = 0;
        myAnsw = this->Top();
        nRot = 3;
        break;
    }
    return myAnsw;
}
template<class tipo>
smmMatrix<tipo> const smmTile<tipo>::ConvertToSmmMatrix(void) const
{
    //same as operator <<
    //get first line and insert vs get first line and print
    std::vector<tipo> v;
    smmMatrix<tipo> answ;

    switch (this->nRot)
    {
    case 0:
        for (long long int i = 0; i < (long long int) this->numRows(); i++)
            answ.insertRow(answ.numRows(), this->getRow(i));
        break;
    case 1:        //right once
        for (long long int i = 0; i < (long long int) this->numCols(); i++)
        {
            v = this->getCol(i);
            std::reverse(v.begin(), v.end());
            answ.insertRow(answ.numRows(), v);
        }
        break;
    case 2:        //180
        for (long long int i = (long long int) this->numRows() - 1; i >= 0; i--)
        {
            v = this->getRow(i);
            std::reverse(v.begin(), v.end());
            answ.insertRow(answ.numRows(), v);
        }
        break;
    case 3:        //left once
        for (long long int i = (long long int) this->numCols() - 1; i >= 0; i--)
            answ.insertRow(answ.numRows(), this->getCol(i));
        break;
    }
    return answ;
}
template<class tipo>
inline std::vector<tipo> const smmTile<tipo>::Bottom() const
{
    std::vector<tipo> myAnsw;
    switch (nRot)
    {
    case 0:                         //R0
        myAnsw = this->getRow(this->nR -1);
        std::reverse(myAnsw.begin(), myAnsw.end());
        break;
    case 1:                         //R1, 90°
        nRot = 0;
        myAnsw = this->Right();
        nRot = 1;
        break;
    case 2:                         //R2, 180°
        nRot = 0;
        myAnsw = this->Top();
        nRot = 2;
        break;
    case 3:                         //R3, 270°
        nRot = 0;
        myAnsw = this->Left();
        nRot = 3;
        break;
    }
    return myAnsw;
}
template<class tipo>
inline std::vector<tipo> const smmTile<tipo>::Right() const
{
    std::vector<tipo> myAnsw;
    switch (nRot)
    {
    case 0:                         //R0
        myAnsw = this->getCol(this->nC - 1);
        break;
    case 1:                         //R1, 90°
        nRot = 0;
        myAnsw = this->Top();
        nRot = 1;
        break;
    case 2:                         //R2, 180°
        nRot = 0;
        myAnsw = this->Left();
        nRot = 2;
        break;
    case 3:                         //R3, 270°
        nRot = 0;
        myAnsw = this->Bottom();
        nRot = 3;
        break;
    }
    return myAnsw;
}
template<class tipo>
inline std::vector<tipo> const smmTile<tipo>::Side(smmConst::direction d) const
{

    //skip break cause ef-it
    switch (d)
    {
    case smmConst::NORTH:
        return this->Top();
    case smmConst::EAST:
        return this->Right();
    case smmConst::SOUTH:
        return this->Bottom();
    case smmConst::WEST:
        return this->Left();
    default:
        throw new std::exception("Must specify one of 4 cardinal points! No other acceptable direction");
    }

    return this->Top(); //never executes, just shut up the compiler warnings
}
template<class tipo>
inline void smmTile<tipo>::turnRight(void)
{
    if (isFixed) throw new std::exception("Tile was fixed!");
    nRot+=3;
    nRot = nRot % 4;
}
template<class tipo>
inline void smmTile<tipo>::turnLeft(void)
{
    if (isFixed) throw new std::exception("Tile was fixed!");
    nRot++;
    nRot = nRot % 4;
}
template<class tipo>
inline void smmTile<tipo>::Stick(void)
{
    DoMyPerim(true);
    isFixed = true;
}

template<class tipo>
inline void smmTile<tipo>::DoMyPerim(bool forceMe)
{
    if (!myPerim.empty() && !forceMe) {return;}
    myPerim.insert(std::make_pair(smmConst::NORTH, this->Top()));
    myPerim.insert(std::make_pair(smmConst::EAST, this->Right()));
    myPerim.insert(std::make_pair(smmConst::SOUTH, this->Bottom()));
    myPerim.insert(std::make_pair(smmConst::WEST, this->Left()));
}


template<class tipo>
inline smmConst::direction smmTile<tipo>::AttachTo(smmTile const & theOther)
{
    //plan: always turn this ancd check the TOP against every side of theOther
    //if found, re-orient.
    //the answer refers to which side it sticks TO
    //typename std::map<smmConst::direction, std::vector<tipo>>::iterator myIter;
    smmConst::direction d; 
    int i, intDir;  //intDir, an integer to deal with smmDirection casting
    std::vector<tipo> v1, v2;

    std::map < smmConst::direction, smmConst::direction> myDirs =
    { {smmConst::NORTH,smmConst::SOUTH},
        {smmConst::WEST,smmConst::EAST},
        {smmConst::SOUTH, smmConst::NORTH},
        {smmConst::EAST,smmConst::WEST} };

    this->nRot = 0; //"sruota"
    this->isTransposed = false; //"sruota"
    this->DoMyPerim();//fai il mio perimetro

    //if (!CanAttachTo(theOther)) return smmConst::FAILED;


    for (intDir = static_cast<int> (smmConst::NORTH); intDir <= static_cast<int> (smmConst::WEST); intDir++)
    {
        d = static_cast<smmConst::direction> (intDir);
        v1 = theOther.Side(d);
        this->nRot = 0;
        for (i = 0; i < 4; i++)
        {
            v2 = this->Side(myDirs[d]);
            std::reverse(v2.begin(), v2.end());

            if (v1 == v2) return d;
            this->nRot++;   //ruotami
        }
        if (!this->isTransposed) intDir--;
        this->Transpose();

    }
    return smmConst::FAILED;
}
//template<class tipo>
//inline smmConst::direction WRONGWay(smmTile const& theOther)
//
//{
//
//    //plan: always turn this ancd check the TOP against every side of theOther
//    //if found, re-orient.
//    //the answer refers to which side it sticks TO
//    typename std::map<smmConst::direction, std::vector<tipo>>::iterator myIter;
//    smmConst::direction d;
//    int id;
//    std::vector<char> v1, v2;
//    int transLoop, nLati;
//    
//    this->nRot = 0; //"sruota"
//    this->isTransposed = false; //"sruota"
//
//    for (transLoop = 0; transLoop < 2; ++transLoop)
//    {
//        DoMyPerim(true);    //ora conosco il mio perimetro
//
//        for (nLati = 0; nLati < 4; ++nLati)
//        {       //first is NORTH
//            v2 = this->Top();  //equivalente al TOP corrente.
//
//            for (id = 0; id < 4; id++)  //0 to (4 exlude)
//            {
//                d = static_cast<smmConst::direction>(id);
//                v1 = theOther.myPerim.at(d);
//                std::reverse(v1.begin(), v1.end());
//                if (std::equal(v1.begin(), v1.end(), v2.begin()))
//                {
//                    switch (d)
//                    {
//                    case smmConst::NORTH:
//                        this->turnLeft();
//                        this->turnLeft();
//                        break;
//                    case smmConst::EAST:
//                        this->turnRight();
//                        break;
//                    case smmConst::WEST:
//                        this->turnLeft();
//                        break;
//                    case smmConst::SOUTH:       //if you go south, the other is OK
//                        break;
//                    }
//                    return d;
//                    
//                }
//            }
//            this->turnRight();
//
//        }
//        this->Transpose();
//    }
//    this->turnLeft();//reset rotation
//    return smmConst::FAILED;
//}
 template<class tipo_2>
 std::ostream& operator<<(std::ostream& out, const smmTile<tipo_2>& o)
{
     //same as ConvertToSmmMatrix! If change this, please change the other
    //get first line and insert vs get first line and print
     std::vector<tipo_2> v;
     switch (o.nRot)
     {
     case 0:
         for (long long int i = 0; i < (long long int) o.numRows(); i++)
             out << o.getRow(i)<<std::endl;
         break;
     case 1:        //right once
         for (long long int i = 0; i < (long long int) o.numCols(); i++)
         {
             v = o.getCol(i);
             std::reverse(v.begin(), v.end());
             out << v << std::endl;
         }
         break;
     case 2:        //180
         for (long long int i = (long long int) o.numRows() - 1; i >= 0; i--)
         {
             v = o.getRow(i);
             std::reverse(v.begin(), v.end());
             out << v << std::endl;
         }
         break;
     case 3:        //left once
         for (long long int i = (long long int) o.numCols() - 1; i >= 0; i--)
             out << o.getCol(i) << std::endl;
         break;
     
     }

     return out;
}
