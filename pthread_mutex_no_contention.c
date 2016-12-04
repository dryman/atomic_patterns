#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>

void* test(void *arg)
{
  pthread_mutex_t mutex;
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  for (uint64_t i = 0; i < bound; i++)
    {
      pthread_mutex_lock(&mutex);
      asm("nop");
      pthread_mutex_unlock(&mutex);
    }

  return NULL;
}
