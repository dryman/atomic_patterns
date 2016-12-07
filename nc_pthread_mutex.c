#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include "op_atomic.h"

a_uint32_t thread_count = 0;
static pthread_mutex_t mutex[4096] = {};

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  for (uint64_t i = 0; i < bound; i++)
    {
      pthread_mutex_lock(&mutex[tid]);
      pthread_mutex_unlock(&mutex[tid]);
    }

  return NULL;
}
