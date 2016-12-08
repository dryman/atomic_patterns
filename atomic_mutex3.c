#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "op_atomic.h"

a_uint32_t thread_count = 0;
static a_uint8_t lock[SLOT] = {};
extern uint64_t counts[];

void* test(void *arg)
{
  uint64_t bound = *(uint64_t*)arg;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  uint32_t slot = tid % SLOT;
  for (uint64_t i = 0; i < bound; i++)
    {
      while (atomic_fetch_or_explicit(&lock[slot], 1, memory_order_acquire))
        ;
      counts[slot]++;
      atomic_fetch_and_explicit(&lock[slot], 0, memory_order_release);
    }
  return NULL;
}
