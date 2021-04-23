#ifndef CLIENT_INCLUDE_TIMER_H_
#define CLIENT_INCLUDE_TIMER_H_

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

int timer_start(uint64_t seconds);

bool is_timeout();

void timer_get_remaining(struct timespec* time);

void timer_get_remaining_timeval(struct timeval* time);

#endif  // CLIENT_INCLUDE_TIMER_H_
