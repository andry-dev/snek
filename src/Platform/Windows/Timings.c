#include "Timings.h"

#include <windows.h>

double getCurrentTime()
{
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);

    return (double)time.QuadPart / 1000;
}

void sleepmillis(int millis)
{
    Sleep(millis);
}
