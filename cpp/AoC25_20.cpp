#include <map>

int Aoc25_12CrackPubK(long long int goal, long long int subj = 7)
{
	const int MOD_ME = 20201227;
	long long int k = 1;
	int loopSize = 0;

	do
	{
		k = subj * k;
		k = k % MOD_ME;
		loopSize++;
	}while (k != goal);

	return loopSize;
}

long long int Aoc25_12_Calculate(long long int subj, int loopSize)
{
	const int MOD_ME = 20201227;
	long long int k = 1, i;

	for (i = 0; i < loopSize; ++i)
	{
		k = subj * k;
		k = k % MOD_ME;

	} 
	return k;
}

std::pair<size_t, size_t> AoC25_20(int pub1, int pub2)
{
	int ls1, ls2;
	long long int sk1,sk2;
	ls1 = Aoc25_12CrackPubK(pub1);
	ls2 = Aoc25_12CrackPubK(pub2);
	std::pair<long long int, long long int> myAnsw;
	sk1 = Aoc25_12_Calculate(pub1, ls2);

	sk2 = Aoc25_12_Calculate(pub2, ls1);

	if (sk1 != sk2) throw new std::exception("chiavi diverse");

	myAnsw.first = sk1;

	return myAnsw;
}


