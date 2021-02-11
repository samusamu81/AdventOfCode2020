#include <iostream>
#include "..\hpp\smmComuni.hpp"
#include "..\hpp\AoC20.hpp"

std::pair<size_t, size_t> AoC10_20(std::string fileName)
{
    std::ifstream myFileInp;
    std::vector<int> jolts, dist1;
    std::vector<bool> from2, from3;
    int x = 0;
    size_t answ1, n, ones, threes, k;
    size_t pSum_BBB, pSum_BB, pSum_B, pSum;   //somma parziale_terzultima, penultima, ultima e corrente

    std::vector<unsigned long long> sums;
    jolts = myParser(fileName, x);

    jolts.push_back(0);     // aggiungi lo zero
    std::sort(jolts.begin(), jolts.end());
    jolts.push_back(jolts.back() + 3);   //aggiungi un +3
    dist1.reserve(jolts.size());
    from2.reserve(jolts.size());
    from3.reserve(jolts.size());

    for (n = 1; n < jolts.size(); n++)
    {
        k = n >= 1 ? n - 1 : n;
        dist1.push_back(jolts[n] - jolts[k]);
        k = n >= 2 ? n - 2 : n;
        from2.push_back((jolts[n] - jolts[k]) <= 3);
        k = n >= 3 ? n - 3 : n;
        from3.push_back((jolts[n] - jolts[k]) <= 3);
    }
    //inizializzazione errata: correggere
    from2[0] = false;

    from3[0] = false;
    from3[1] = false;

    ones = 0;
    threes = 0;
    for (n = 0; n < dist1.size(); n++)
    {
        //std::cout << dist1[n] << std::endl;
        ones += dist1[n] == 1 ? 1 : 0;
        threes += dist1[n] == 3 ? 1 : 0;
    }
    answ1 = ones * threes;
    pSum_BBB = 0;  //inizializzazione: finto zero
    pSum_BB = 0;
    pSum_B = 1;  //al primo posto ci può solo essere un uno
    pSum = 1; //
    //primo ciclo : non fare il 3
    //attenzione: pSum(0) "sballa" indici di 1

    for (n = 0; n < from2.size(); ++n)
    {
        //sicuramente l'ultimo
        pSum = pSum_B;
        //forse il penultimo
        pSum += from2[n] ? pSum_BB : 0;
        //forse il terzultimo
        pSum += from3[n] ? pSum_BBB : 0;
        //aggiornamento variabili:
        sums.push_back(pSum);
        pSum_BBB = pSum_BB;
        pSum_BB = pSum_B;
        pSum_B = pSum;

    }
    return std::make_pair(answ1, pSum);
}