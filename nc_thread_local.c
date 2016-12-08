#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdint.h>

static __thread uint64_t counter;

void setup(int num_threads) {}

void* test(void *arg)
{
  uint64_t bound = *(uint64_t*)arg;
  for (uint64_t i = 0; i < bound; i++)
    {
      counter++;
      asm("nop");
    }

  return (void*) counter;
}
