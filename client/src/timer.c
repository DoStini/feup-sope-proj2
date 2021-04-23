#include "../include/timer.h"

#include <time.h>
#include <signal.h>
#include <string.h>

static timer_t timer;

int start_timer(uint64_t seconds) {
    struct sigevent sevp;
    struct itimerspec spec;
    struct timespec timer_interval;
    struct timespec timer_value;

    timer_value.tv_nsec = 0;
    timer_value.tv_sec = seconds;
    timer_interval.tv_sec = timer_interval.tv_nsec = 0;

    memset(&sevp, 0, sizeof(sevp));
    sevp.sigev_notify = SIGEV_NONE;

    spec.it_interval = timer_interval;
    spec.it_value = timer_value;

    if (timer_create(CLOCK_REALTIME, &sevp, &timer)) return -1;
    return timer_settime(timer, 0, &spec, NULL);
}

bool is_timeout() {
    struct itimerspec timer_value;
    timer_gettime(timer, &timer_value);

    return timer_value.it_value.tv_nsec == 0 &&
           timer_value.it_value.tv_sec == 0;
}