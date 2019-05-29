#include "Timings.h"

#include <time.h>
#include <unistd.h>
#include <sys/time.h>

double getCurrentTime()
{
    struct timeval micro;
    gettimeofday(&micro, NULL);

    return micro.tv_usec / 1000;
}

void sleepmillis(int millis)
{
    usleep(millis);
}
