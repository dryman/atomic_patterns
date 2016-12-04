#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include "op_atomic.h"

static a_uint64_t atomic_counter = 0;

void* test(void* arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  for (uint64_t i = 0; i < bound; i++)
    atomic_fetch_add_explicit(&atomic_counter, 1,
                              memory_order_relaxed);
  return NULL;
}
