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
extern uint64_t counts[];
a_int32_t pcard[SLOT] = {};

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  uint64_t mask = (1L << 4)-1;  // 1/16 use write lock, else read lock
  uint32_t tid = atomic_fetch_add_explicit(&thread_count, 1,
                                           memory_order_relaxed);
  uint32_t slot = tid % SLOT;

  for (uint64_t i = 0; i < bound; i++)
    {
      while (1)
        {
          if (!atomic_check_in(&pcard[slot]))
            continue;
          if ((i & mask) == 0)
            {
              if (!atomic_book_critical(&pcard[slot]))
                {
                  atomic_check_out(&pcard[slot]);
                  continue;
                }
              while(!atomic_enter_critical(&pcard[slot]))
                ;
              counts[slot]++;
              atomic_exit_critical(&pcard[slot]);
              atomic_check_out(&pcard[slot]);
              break;
            }
          else
            {
              asm("nop");
              atomic_check_out(&pcard[slot]);
              break;
            }
        }
    }
  return NULL;
}

