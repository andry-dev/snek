#include "Timings.h"

#include <time.h>
#include <unistd.h>

double getCurrentTime()
{
    struct timespec ret;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ret);

    return ret.tv_nsec / 1000000;
}

void sleepmillis(int millis)
{
    usleep(millis);
}
