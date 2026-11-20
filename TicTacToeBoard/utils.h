#pragma once
#include <cstdlib>

inline void clearScreen()
{

#ifdef _WIN32
    system("cls");

#else
    system("clear");

#endif
}