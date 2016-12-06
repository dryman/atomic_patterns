#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdatomic.h>

static atomic_bool lock = false;
extern uint64_t count;

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  for (uint64_t i = 0; i < bound; i++)
    {
      while (atomic_fetch_or_explicit(&lock, 1, memory_order_acquire))
        ;
      count++;
      atomic_fetch_and_explicit(&lock, 0, memory_order_release);
    }
  return NULL;
}
