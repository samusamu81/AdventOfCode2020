#pragma once
namespace smmConst      //da usare in for_each
{
	extern char separator;
	extern char trueSym;
	extern char falseSym;
	extern int not_found;
    enum direction
    {
        FAILED = -1,
        NORTH,
        EAST,
        SOUTH,
        WEST
    };
}
