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
a_int32_t lock[SLOT] = {};

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
        { // write lock
          while (1)
            {
              // book write
              int32_t val = atomic_load_explicit(&lock[slot], memory_order_relaxed);
              while (!atomic_compare_exchange_weak_explicit
                     (&lock[slot], &val, val | (1<<31),
                      memory_order_acq_rel,
                      memory_order_relaxed))
                ;
                //val = atomic_load_explicit(&lock, memory_order_relaxed);
              val = INT32_MIN;
              while (atomic_compare_exchange_strong_explicit
                     (&lock[slot], &val, -1,
                      memory_order_acquire,
                      memory_order_relaxed))
                {
                  val = INT32_MIN;
                  ATOMIC_HACK_OP;
                }
              break;
            }
          counts[slot]++;
          atomic_store_explicit(&lock[slot], 0, memory_order_release);
        }
      else
        { // read lock
          while (1)
            {
              int32_t val; 
              do
                {
                  val = atomic_load_explicit(&lock[slot],
                                             memory_order_relaxed);
                  if (val < 0)
                    continue;
                }
              while (!atomic_compare_exchange_weak_explicit
                     (&lock[slot], &val, val + 1,
                      memory_order_acquire,
                      memory_order_relaxed));
                break;
            }
          asm("nop");
          atomic_fetch_sub_explicit(&lock[slot], 1, memory_order_release);
        }
    }
  return NULL;
}
