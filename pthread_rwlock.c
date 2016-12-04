#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdint.h>

extern uint64_t count;
static pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  uint64_t mask = (1L << 4)-1;  // 1/16 use write lock, else read lock
  for (uint64_t i = 0; i < bound; i++)
    {
      if ((i & mask) == 0)
        {
          pthread_rwlock_wrlock(&rwlock);
          count++;
          pthread_rwlock_unlock(&rwlock);
        }
      else
        {
          pthread_rwlock_rdlock(&rwlock);
          asm("nop");
          pthread_rwlock_unlock(&rwlock);
        }
    }
  return NULL;
}
