#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>

static __thread uint64_t counter;

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  for (uint64_t i = 0; i < bound; i++)
    {
      counter++;
      asm("nop");
    }

  return (void*) counter;
}
