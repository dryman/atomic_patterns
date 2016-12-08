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

// ATOMIC_HACK_DECLARE
extern uint64_t count;
a_int32_t lock = 0;
a_uint32_t tid_counter = 0;

void setup(int num_threads) {}

void* test(void *arg)
{
  uint64_t bound = *(uint64_t*)arg;
  uint64_t mask = (1L << 4)-1;  // 1/16 use write lock, else read lock
  uint32_t tid = atomic_fetch_add(&tid_counter, 1);
  char file_name [20];
  sprintf(file_name, "rwlock_%u", tid);
  FILE* file = fopen(file_name, "w");

  for (uint64_t i = 0; i < bound; i++)
    {
      if ((i & mask) == 0)
        { // write lock
          while (1)
            {
              // book write

              int32_t val = atomic_load_explicit(&lock, memory_order_acquire);
              if (val < 0)
                continue;
              fprintf(file, "%u: booking write lock: %d\n", tid, lock);
              fflush(file);
              if (atomic_fetch_or_explicit(&lock, (1<<31), memory_order_acq_rel) < 0)
                continue;
              fprintf(file, "%u: write lock booked: %d\n", tid, lock);
              fflush(file);
              val = INT32_MIN;
              while (atomic_compare_exchange_strong_explicit
                     (&lock, &val, -1,
                      memory_order_acq_rel,
                      memory_order_acquire))
                {
                  val = INT32_MIN;
                  fprintf(file, "%u: write lock waiting read: %d\n", tid, lock);
                  fflush(file);
                  // ATOMIC_HACK_OP;
                }
              break;
            }
          fprintf(file, "%u: write lock critical: %d\n", tid, lock);
          fflush(file);
          count++;
          atomic_store_explicit(&lock, 0, memory_order_release);
          fprintf(file, "%u: write lock exit: %d\n", tid, lock);
          fflush(file);
        }
      else
        { // read lock
        int count = 0;
          while (1)
            {
              if (count > 1000) exit(1);
              int32_t val = atomic_load_explicit(&lock, memory_order_acquire);
              fprintf(file, "%u: read %d, lock %d, val: %d\n", tid, count++, lock, val);
              fflush(file);
              if (val < 0)
                continue;
              if (atomic_compare_exchange_strong_explicit
                   (&lock, &val, val + 1,
                    memory_order_acquire,
                    memory_order_relaxed))
                break;
            }
          asm("nop");
          atomic_fetch_sub_explicit(&lock, 1, memory_order_release);
        }
    }
  return NULL;
}
