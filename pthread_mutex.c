#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include "op_atomic.h"

a_uint32_t thread_count = 0;
extern uint64_t counts[];
static pthread_mutex_t mutex[SLOT];

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  uint32_t slot = tid % SLOT;
  for (uint64_t i = 0; i < bound; i++)
    {
      pthread_mutex_lock(&mutex[slot]);
      counts[slot]++;
      pthread_mutex_unlock(&mutex[slot]);
    }

  return NULL;
}
