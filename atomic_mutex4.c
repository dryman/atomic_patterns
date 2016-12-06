#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdatomic.h>

static atomic_flag lock = ATOMIC_FLAG_INIT;
extern uint64_t count;

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  for (uint64_t i = 0; i < bound; i++)
    {
      while (atomic_flag_test_and_set_explicit(&lock, memory_order_acquire))
        ;
      count++;
      atomic_flag_clear_explicit(&lock, memory_order_release);
    }
  return NULL;
}
