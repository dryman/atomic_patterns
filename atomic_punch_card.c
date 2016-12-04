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
extern uint64_t count;
a_int32_t pcard = 0;

void* test(void *arg)
{
  const int power2 = *(int*) arg;
  uint64_t bound = 1L << power2;
  uint64_t mask = (1L << 4)-1;  // 1/16 use write lock, else read lock

  for (uint64_t i = 0; i < bound; i++)
    {
      while (1)
        {
          if (!atomic_check_in(&pcard))
            continue;
          if ((i & mask) == 0)
            {
              if (!atomic_book_critical(&pcard))
                {
                  atomic_check_out(&pcard);
                  continue;
                }
              while(!atomic_enter_critical(&pcard))
                ;
              count++;
              atomic_exit_critical(&pcard);
              atomic_check_out(&pcard);
              break;
            }
          else
            {
              asm("nop");
              atomic_check_out(&pcard);
              break;
            }
        }
    }
  return NULL;
}

