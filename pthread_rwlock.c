#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdint.h>
#include "op_atomic.h"

a_uint32_t thread_count = 0;
extern uint64_t counts[];
static pthread_rwlock_t rwlock[SLOT];

void setup(int num_threads)
{
  for (int i = 0; i < num_threads; i++)
    pthread_rwlock_init(&rwlock[i], NULL);
}

void* test(void *arg)
{
  uint64_t bound = *(uint64_t*)arg;
  uint64_t mask = (1L << 4)-1;  // 1/16 use write lock, else read lock
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  uint32_t slot = tid % SLOT;
  for (uint64_t i = 0; i < bound; i++)
    {
      if ((i & mask) == 0)
        {
          pthread_rwlock_wrlock(&rwlock[slot]);
          counts[slot]++;
          pthread_rwlock_unlock(&rwlock[slot]);
        }
      else
        {
          pthread_rwlock_rdlock(&rwlock[slot]);
          asm("nop");
          pthread_rwlock_unlock(&rwlock[slot]);
        }
    }
  return NULL;
}
