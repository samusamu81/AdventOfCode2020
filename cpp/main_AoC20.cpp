#ifndef DEBUG
#define DEBUG
#endif

#include <iostream>
#include "..\hpp\AoC20.hpp"
#include <ctime>





int main(int argc, char* argv[])
{
    std::pair <size_t, size_t> myAnsw;
    std::pair <size_t, std::string> myAnsw2;
    std::clock_t c_start, c_end;
    double time_elapsed_ms;

    c_start = std::clock();
    std::cout << "Problema 1 Anno 2020:" << std::endl;
    myAnsw = AoC01_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t';
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 2 Anno 2020:" << std::endl;
    myAnsw = AoC02_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t';
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 3 Anno 2020:" << std::endl;
    myAnsw = AoC03_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t';
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 4 Anno 2020:" << std::endl;
    myAnsw = AoC04_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 5 Anno 2020:" << std::endl;
    myAnsw = AoC05_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 6 Anno 2020:" << std::endl;
    myAnsw = AoC06_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 7 Anno 2020:" << std::endl;
    myAnsw = AoC07_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 8 Anno 2020:" << std::endl;
    myAnsw = AoC08_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 9 Anno 2020:" << std::endl;
    myAnsw = AoC09_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 10 Anno 2020:" << std::endl;
    myAnsw = AoC10_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 11 Anno 2020:" << std::endl;
    myAnsw = AoC11_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t';
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 12 Anno 2020:" << std::endl;
    myAnsw = AoC12_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 13 Anno 2020:" << std::endl;
    myAnsw = AoC13_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 14 Anno 2020:" << std::endl;
    myAnsw = AoC14_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 15 Anno 2020:" << std::endl;
    std::cout << "Ci mette molto (qualche minuto). Pazientare" << std::endl;
    myAnsw = AoC15_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 16 Anno 2020:" << std::endl;
    myAnsw = AoC16_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 17 Anno 2020:" << std::endl;
    myAnsw = AoC17_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 18 Anno 2020:" << std::endl;
    myAnsw = AoC18_20();
    c_end = std::clock();
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 19 Anno 2020:" << std::endl;
    myAnsw = AoC19_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 20 Anno 2020:" << std::endl;
    myAnsw = AoC20_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 21 Anno 2020:" << std::endl;
    myAnsw2 = AoC21_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw2.first << "\t" << myAnsw2.second << '\t';
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 22 Anno 2020:" << std::endl;
    myAnsw = AoC22_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t';
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 23 Anno 2020:" << std::endl;
    myAnsw = AoC23_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 24 Anno 2020:" << std::endl;
    myAnsw = AoC24_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    c_start = std::clock();
    std::cout << "Problema 25 Anno 2020:" << std::endl;
    myAnsw = AoC25_20();
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << myAnsw.first << "\t" << myAnsw.second << '\t'; 
    std::cout << "CPU time used: " << time_elapsed_ms << " ms" << std::endl << std::endl;

    return 0;
}
