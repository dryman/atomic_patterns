#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include "op_atomic.h"
#include <stdint.h>
#include <inttypes.h>

static a_uint64_t atomic_counter = 0;

void* test(void* arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  uint64_t old_val;
  for (uint64_t i = 0; i < bound; i++)
    {
      old_val = atomic_load_explicit(&atomic_counter, memory_order_relaxed);
      while(!atomic_compare_exchange_weak_explicit(
        &atomic_counter, &old_val,
        old_val + 1,
        memory_order_release,
        memory_order_relaxed))
        ;
    }

  printf("atomic counter val: %" PRIu64 "\n", atomic_counter);
  return NULL;
}
