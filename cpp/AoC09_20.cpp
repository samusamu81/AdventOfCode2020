#include "..\hpp\smmComuni.hpp"
#include "..\hpp\AoC20.hpp"

int AoC9_20A(std::vector<int> const & fileContent)
{
    bool found = false;
    const int PREAMBOLO = 25;
    std::deque<int> slider, coda;
    std::set<int>::iterator fwPtr;
    std::set<int>::reverse_iterator rvPtr;
    std::set <int> valoriCorrenti;
    std::ifstream myFileInp;
    int n, sum;
    /*myFileInp.open(".\\Test9_20.txt", std::ifstream::in);

    myFileInp >> n;
    while (myFileInp.good())
    {
        coda.push_back(n);
        myFileInp >> n;
    }
    myFileInp.close();*/
    coda = std::deque<int>(fileContent.begin(), fileContent.end());
    for (n = 0; n < PREAMBOLO; n++)
    {
        slider.push_back(coda.front());
        coda.pop_front();
    }
    //for (intPtr = slider.begin(); intPtr != slider.end(); ++intPtr)
    valoriCorrenti.insert(slider.begin(), slider.end());
    while (coda.size() > 0)
    {
        found = false;
        fwPtr = valoriCorrenti.begin();
        rvPtr = valoriCorrenti.rbegin();
        do
        {   //questo è un min-max: cresce il min se è basso, scende il max se è troppo
            sum = (*fwPtr) + (*rvPtr);
            if ((*fwPtr) >= (*rvPtr)) break;
            if (sum > coda.front()) ++rvPtr;
            if (sum < coda.front()) ++fwPtr;
            found = sum == coda.front();
        } while (!found);
        if (!found)
        {
            return coda.front();
        }
        //togli vecchio, da entrambi, inserisci nuovo 
        valoriCorrenti.erase(slider.front());
        slider.pop_front();
        valoriCorrenti.insert(coda.front());
        slider.push_back(coda.front());
        coda.pop_front();
    }

    return -1;
}
int AoC9_20B(int wanted, std::vector<int> const& fileContent)
{
    int l, h, sum;
    bool keepGoing;
    std::deque<int> slider, coda;
    std::deque<int>::iterator intPtr;
    std::exception e;

    coda = std::deque<int>(fileContent.begin(), fileContent.end());

    sum = 0;
    keepGoing = coda.size() > 0 && sum != wanted;
    //probabilmente era molto meglio farlo con iteratori su un vettore, ma volevo imparare la deque
    while (keepGoing)   //questo è un min_max non ordinato: se è troppo grande, lascia la punta, altrimenti cresci con la coda
    {
        while (sum < wanted)
        {
            if (coda.size() == 0) return -1;
            sum += coda.front();
            slider.push_back(coda.front());
            coda.pop_front();
        }

        while (sum > wanted)
        {
            sum -= slider.front();
            slider.pop_front();
        }
        keepGoing = coda.size() > 0 && sum != wanted;
    }

    l = slider.front();
    h = l;
    for (intPtr = slider.begin(); intPtr != slider.end(); ++intPtr)
    {
        l = l < *intPtr ? l : *intPtr;
        h = h > *intPtr ? h : *intPtr;
    }
    return l + h;
}

std::pair<size_t, size_t> AoC09_20(std::string fileName)
{
    std::pair<size_t, size_t> myAnsw;
    int x = 0;
    std::vector<int> myInput = myParser(fileName, x);
    x = AoC9_20A(myInput);
    myAnsw.first = x;
    myAnsw.second = AoC9_20B(x, myInput);
    return myAnsw;
}