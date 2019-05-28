#include "Timings.h"

#include <windows.h>

double getCurrentTime()
{
    LARGE_INTEGER time;
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&time);

    return ((double)time.QuadPart * 1000)/(double)freq.QuadPart;
}

void sleepmillis(int millis)
{
    Sleep(millis / 1000);
}
