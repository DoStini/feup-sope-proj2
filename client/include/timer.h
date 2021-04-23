#ifndef CLIENT_INCLUDE_TIMER_H_
#define CLIENT_INCLUDE_TIMER_H_

#include <stdint.h>
#include <stdbool.h>

int start_timer(uint64_t seconds);

bool is_timeout();

#endif  // CLIENT_INCLUDE_TIMER_H_
