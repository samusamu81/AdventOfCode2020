#include <map>
#include "..\hpp\smmComuni.hpp"
#include "..\hpp\AoC20.hpp"
#include "..\hpp\smmMatrix.hpp"
#include "..\hpp\smmComplex.hpp"

std::pair<size_t, size_t>  AoC12_20(std::string fileName)
{
    std::ifstream myFileInp;
    std::vector<std::pair<char, int>> lista;
    char c;
    unsigned int n;
    int vert, orizz;
    smmComplex<int> currentDir;
    currentDir.Set(0, 1);   //nord
    smmComplex<int> currentPos, aComp;
    currentPos.Set(0,0), aComp.Set(0, 0);

    std::map<char, smmComplex<int>> cardinals;       //Definizione "complessa" dei punti cardinali
    std::map<char, smmComplex<int>>::iterator aDir;
    std::pair<size_t, size_t> myAnsw;

    cardinals.insert(std::make_pair('N', currentDir));
    currentDir.TurnLeft(1);
    cardinals.insert(std::make_pair('W', currentDir));
    currentDir.TurnLeft(1);
    cardinals.insert(std::make_pair('S', currentDir));
    currentDir.TurnLeft(1);
    cardinals.insert(std::make_pair('E', currentDir));
    //current is east as required
    
    myFileInp.open(fileName, std::ifstream::in);

    while (myFileInp.good())
    {
        myFileInp >> c >> n;
        lista.push_back(std::make_pair(c, n));   
    }
    myFileInp.close();
    for (n = 0; n < lista.size(); n++)
    {
        aDir = cardinals.find(lista[n].first);  //cerca la direzione
        if (aDir != cardinals.end())            //trovato
        {
            currentPos += (*aDir).second * (lista[n].second);
        }
        else
        {
            //rotazione o forward
            switch (lista[n].first)
            {
            case 'F':
                currentPos += currentDir * (lista[n].second);
                break;
            case 'R':
                currentDir.TurnRight(lista[n].second / 90);
                break;
            case 'L':
                currentDir.TurnLeft(lista[n].second / 90);
                break;
            default:
                break;
            }
        }
    }

    vert = currentPos.Im;
    orizz = currentPos.Re;
    orizz *= orizz < 0 ? -1 : 1;
    vert *= vert < 0 ? -1 : 1;
    myAnsw.first = vert + orizz;

    //fine prima parte  
    smmComplex<int> wayPoint;
    wayPoint.Set(10, 1);

    currentPos.Set(0, 0);

    for (n = 0; n < lista.size(); n++)
    {
        aDir = cardinals.find(lista[n].first);  //cerca la direzione
        if (aDir != cardinals.end())            //trovato
        {
            wayPoint += (*aDir).second * (lista[n].second);
        }
        else
        {
            //rotazione o forward
            switch (lista[n].first)
            {
            case 'F':
                currentPos += wayPoint * (lista[n].second);
                break;
            case 'R':
                wayPoint.TurnRight(lista[n].second / 90);
                break;
            case 'L':
                wayPoint.TurnLeft(lista[n].second / 90);
                break;
            default:
                break;
            }
        }
    }
    vert = currentPos.Im;
    orizz = currentPos.Re;
    myAnsw.second = (vert > 0 ? vert : -1 * vert) + (orizz > 0 ? orizz : -1 * orizz);
    return myAnsw;
}