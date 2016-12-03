#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>

static atomic_int rwlock = 0;
static int counter = 0;

void* reader_thread(void *arg)
{
  // int_ptr does not have to be atomic, as its visibility
  // is guarded by the atomic lock.
  for (int i = 0; i < 10; i++)
    {
      sleep(1);
      // If rwlock is INT_MIN, we are in write mode.
      // Else, we can have multiple reader thread trying to read
      // in the critical section.
      //
      // We have to use an integer instead of a single bool because
      // there can be multiple threads in the critical section.
      if (atomic_fetch_add_explicit(
        &rwlock, 1,
        memory_order_acquire) < 0)
        {   
          printf("Locked by write\n");
          atomic_fetch_sub_explicit(&rwlock, 1, memory_order_release);
          continue;
        }   
      // now we can read
      printf("Read counter %d\n", counter);
      // No memory read or write can be reordered after
      // memory_order_release.
      atomic_fetch_sub_explicit(&rwlock, 1, memory_order_release);
    }
  return NULL;
}

void* writer_thread(void *arg)
{
  // int_ptr does not have to be atomic, as its visibility
  // is guarded by the atomic lock.
  for (int i = 0; i < 5; i++)
    {
      sleep(1);
      // Set the rwlock to INT_MIN, only when the value is 0.
      // 
      // On compare exchange success, memory_order_acquire
      // ensures no memory read or write can be reordered 
      // before this point.
      // 
      // On compare exchange failure, expected_bool must
      // be reload to the expected value (which is 0).
      // No memory reordering is depending on it so we can
      // use memory_order_relazed
      int expected_rwlock = 0;
      while (!atomic_compare_exchange_weak_explicit(
        &rwlock, &expected_rwlock, INT_MIN,
        memory_order_acquire,
        memory_order_relaxed))
        {   
          expected_rwlock = 0;
        }
      // now we can perform side effects
      counter++;
      // No memory read or write can be reordered after
      // memory_order_release.
      atomic_store_explicit(&rwlock, 0, memory_order_release);
    }
  return NULL;
}

int main()
{
  pthread_t p1, p2, p3, p4;
  pthread_create(&p1, NULL, reader_thread, NULL);
  pthread_create(&p2, NULL, reader_thread, NULL);
  pthread_create(&p3, NULL, writer_thread, NULL);
  pthread_create(&p4, NULL, writer_thread, NULL);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_join(p4, NULL);

  return 0;
}

