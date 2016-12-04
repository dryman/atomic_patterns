#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>

static pthread_mutex_t mutex;
extern uint64_t count;

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  for (uint64_t i = 0; i < bound; i++)
    {
      pthread_mutex_lock(&mutex);
      count++;
      pthread_mutex_unlock(&mutex);
    }

  return NULL;
}
