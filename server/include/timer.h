#ifndef SERVER_INCLUDE_TIMER_H_
#define SERVER_INCLUDE_TIMER_H_

#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>

/**
 * @brief Starts a no-signal timer that ends in a given number of seconds.
 *
 * @param seconds time being set.
 *
 * @return an error value.
 **/
int timer_start(uint64_t seconds);

/**
 * @brief Cleanups timer structure
 */
void timer_cleanup();

/**
 * @brief Checks if the timer has ended.
 *
 * @return an error value.
 **/
bool is_timeout(void);

/**
 * @brief Gets the remaing time on the set timer as a timespec structure.
 *
 * @param[out] time the remaining time in a timespec.
 *
 * @return an error value, if timer is not set for example.
 **/
int timer_get_remaining(struct timespec* time);

/**
 * @brief Gets the remaing time on the set timer as a timeval structure.
 *
 * @param[out] time the remaining time in a timeval.
 *
 * @return an error value, if timer is not set for example.
 **/
int timer_get_remaining_timeval(struct timeval* time);

int timer_get_absolute_timeout(struct timespec* timeout);

#endif  // SERVER_INCLUDE_TIMER_H_
