#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include "op_atomic.h"

a_uint32_t thread_count = 0;
static a_uint64_t atomic_counter[SLOT] = {};

void* test(void* arg)
{
  uint64_t bound = *(uint64_t*)arg;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  uint32_t slot = tid % SLOT;
  for (uint64_t i = 0; i < bound; i++)
    atomic_fetch_add_explicit(&atomic_counter[slot], 1,
                              memory_order_relaxed);
  return NULL;
}
