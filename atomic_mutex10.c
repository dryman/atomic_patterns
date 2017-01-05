#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "op_atomic.h"
#include <immintrin.h> // For _mm_pause

a_uint32_t thread_count = 0;
static bool lock[SLOT] = {};
extern uint64_t counts[128];

void setup(int num_threads) {}

void* test(void *arg)
{
  uint64_t bound = *(uint64_t*)arg;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  uint32_t slot = tid % SLOT;
  for (uint64_t i = 0; i < bound; i++)
    {
      while (__atomic_exchange_n(&lock[slot], 1,
            __ATOMIC_ACQUIRE|__ATOMIC_HLE_ACQUIRE))
        _mm_pause();
      counts[slot]++;
      __atomic_store_n(&lock[slot], 0, __ATOMIC_RELEASE|__ATOMIC_HLE_RELEASE);
    }
  return NULL;
}
