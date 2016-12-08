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
static atomic_flag lock[4096] = {ATOMIC_FLAG_INIT};

void* test(void *arg)
{
  uint64_t bound = *(uint64_t*)arg;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  for (uint64_t i = 0; i < bound; i++)
    {
      while (atomic_flag_test_and_set_explicit(&lock[tid], memory_order_acquire))
        ;
      asm("nop");
      atomic_flag_clear_explicit(&lock[tid], memory_order_release);
    }
  return NULL;
}

