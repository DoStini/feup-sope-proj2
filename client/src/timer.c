#include "../include/timer.h"

#include <signal.h>
#include <string.h>
#include <stdio.h>

#define NSEC_TO_USEC(x) ((x)/(1000))

static timer_t timer;

int timer_start(uint64_t seconds) {
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

void timer_get_remaining(struct timespec* time) {
    struct itimerspec timer_value;
    timer_gettime(timer, &timer_value);

    *time = timer_value.it_value;
}

void timer_get_remaining_timeval(struct timeval* time) {
    struct itimerspec timer_value;
    timer_gettime(timer, &timer_value);

    time->tv_sec = timer_value.it_value.tv_sec;
    printf("before: %ld\n ", timer_value.it_value.tv_nsec);
    time->tv_usec = NSEC_TO_USEC(timer_value.it_value.tv_nsec);
    printf("after: %ld\n ", time->tv_usec);
}
