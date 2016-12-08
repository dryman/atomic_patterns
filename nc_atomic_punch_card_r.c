#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "op_atomic.h"
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>

ATOMIC_HACK_DECLARE
a_uint32_t thread_count = 0;
static a_int32_t pcard[4096] = {};

void* test(void *arg)
{
  uint64_t bound = *(uint64_t*)arg;
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);

  for (uint64_t i = 0; i < bound; i++)
    {
      while (1)
        {
          if (!atomic_check_in(&pcard[tid]))
            continue;
          asm("nop");
          atomic_check_out(&pcard[tid]);
          break;
        }
    }
  return NULL;
}

