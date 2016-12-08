#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "op_atomic.h"

a_uint32_t thread_count = 0;
static atomic_bool lock[4096] = {};

void* test(void *arg)
{
  uint64_t bound = *(uint64_t*)arg;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  bool expected_bool = false;
  for (uint64_t i = 0; i < bound; i++)
    {
      while (1)
        {
          expected_bool = false;
          while (atomic_load_explicit(&lock[tid], memory_order_relaxed))
            ;
          if (atomic_compare_exchange_weak_explicit(
              &lock[tid], &expected_bool, true,
              memory_order_acquire,
              memory_order_relaxed))
            break;
        }
      asm("nop");
      atomic_store_explicit(&lock[tid], false, memory_order_release);
    }
  return NULL;
}

