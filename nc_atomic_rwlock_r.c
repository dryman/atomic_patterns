#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "op_atomic.h"
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>

ATOMIC_HACK_DECLARE
a_uint32_t thread_count = 0;
a_int32_t lock[4096] = {};

void setup(int num_threads) {}

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  for (uint64_t i = 0; i < bound; i++)
    {
      while (1)
        {
          int32_t val; 
          do
            {
              val = atomic_load_explicit(&lock[tid],
                                         memory_order_relaxed);
              if (val < 0)
                continue;
            }
          while (!atomic_compare_exchange_weak_explicit
                 (&lock[tid], &val, val + 1,
                  memory_order_acquire,
                  memory_order_relaxed));
            break;
        }
      asm("nop");
      atomic_fetch_sub_explicit(&lock[tid], 1, memory_order_release);
    }
  return NULL;
}

