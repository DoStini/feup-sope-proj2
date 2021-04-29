#include "../include/timer.h"

#include <signal.h>
#include <string.h>

#define NSEC_TO_USEC(x) ((x) / (1000))

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

int timer_cleanup() {
    return timer_delete(timer);
}

bool is_timeout() {
    struct itimerspec timer_value;
    timer_gettime(timer, &timer_value);

    return timer_value.it_value.tv_nsec == 0 &&
           timer_value.it_value.tv_sec == 0;
}

int timer_get_remaining(struct timespec* time) {
    struct itimerspec timer_value;
    int err = timer_gettime(timer, &timer_value);
    if (err) return err;

    *time = timer_value.it_value;

    return 0;
}

int timer_get_remaining_timeval(struct timeval* time) {
    struct itimerspec timer_value;
    int err = timer_gettime(timer, &timer_value);
    if (err) return err;

    time->tv_sec = timer_value.it_value.tv_sec;
    time->tv_usec = NSEC_TO_USEC(timer_value.it_value.tv_nsec);

    return 0;
}
