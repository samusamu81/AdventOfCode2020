#include "..\hpp\smmComuni.hpp"
#include "..\hpp\AoC20.hpp"

std::pair<int, bool> testInfiniteAoC8_20( std::vector<std::pair<char, int>> const& parsedInput)
{
    int intero = 0;
    unsigned int pos;
    std::set<int> doneAlready;
    bool infLoop = false;
    for (pos = 0; pos < parsedInput.size(); pos++)
    {
        //cout << pos << endl;
        if (doneAlready.count(pos) > 0)
        {
            infLoop = true;
            break;
        }
        doneAlready.insert(pos);
        switch (parsedInput[pos].first)
        {
        case 'n':
            break;
        case 'j':
            pos += parsedInput[pos].second;
            pos--;
            break;
        case 'a':
            intero += parsedInput[pos].second;
            break;
        default:
            throw new std::exception("Stringa non riconosciuta");
        }

    }
    return std::make_pair(intero, infLoop);
}

int AoC8_20_2ndStep(std::vector<std::pair<char, int>> parsedInput)
{
     std::pair<int, bool> answ;
     unsigned int pos;
     answ.second = true;    //during 1st run might encounter troubles if left false
    for (pos = 0; pos < parsedInput.size(); pos++)
    {
         switch (parsedInput[pos].first)
        {
        case 'n':
            parsedInput[pos].first = 'j';
            answ = testInfiniteAoC8_20(parsedInput);
            parsedInput[pos].first = 'n';
            break;
        case 'j':
            parsedInput[pos].first = 'n';
            answ = testInfiniteAoC8_20(parsedInput);
            parsedInput[pos].first = 'j';
            break;
        }
        if (!answ.second) break;
    }
    return answ.first;
}

std::pair<size_t, size_t> AoC08_20(std::string fileName)
{
    std::pair<size_t, size_t> myAnsw;
    std::ifstream myFileInp;
    std::string str;
    int intero;
    char c;
    std::vector<std::pair<char, int>> parsedInput;

    myFileInp.open(fileName, std::ifstream::in);

    myFileInp >> str >> intero;
    while (myFileInp.good())
    {
        c = str.at(0);
        parsedInput.push_back(std::make_pair(c, intero));
        myFileInp >> str >> intero;
    }
    myFileInp.close();
    intero = 0;

    myAnsw.first = testInfiniteAoC8_20(parsedInput).first;
    myAnsw.second = AoC8_20_2ndStep(parsedInput);
    return myAnsw;
}