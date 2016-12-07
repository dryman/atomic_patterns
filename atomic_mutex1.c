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
ATOMIC_HACK_DECLARE
extern uint64_t count;

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  bool expected_bool = false;
  for (uint64_t i = 0; i < bound; i++)
    {
      while (!atomic_compare_exchange_weak_explicit(
        &lock, &expected_bool, true,
        memory_order_acquire,
        memory_order_relaxed))
        {
          expected_bool = false;
          ATOMIC_HACK_OP;
        }
      count++;
      atomic_store_explicit(&lock, false, memory_order_release);
    }
  return NULL;
}
