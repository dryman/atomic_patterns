#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include "op_atomic.h"

a_uint32_t thread_count = 0;
static uint64_t counters[4096] = {};

void setup(int num_threads) {}

void* test(void *arg)
{
  uint64_t bound = *(uint64_t*)arg;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  printf("tid: %u\n", tid);

  for (uint64_t i = 0; i < bound; i++)
    {
      counters[tid]++;
      asm("nop");
    }

  return (void*) counters[tid];
}

