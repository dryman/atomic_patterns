#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>

static atomic_bool lock = false;
static int *int_ptr = NULL;

void* thread_start(void *arg)
{
  // int_ptr does not have to be atomic, as its visibility
  // is guarded by the atomic lock.
  while (int_ptr == NULL)
    {
      bool expected_bool = false;
      // On compare exchange success, memory_order_acquire
      // ensures no memory read or write can be reordered 
      // before this point.
      // 
      // On compare exchange failure, no memory reordering 
      // is depending on it so we can use memory_order_relazed.
      if (!atomic_compare_exchange_weak_explicit(
        &lock, &expected_bool, true,
        memory_order_acquire,
        memory_order_relaxed))
        {   
          continue;
        }   
      // now we can perform side effect to get singleton
      int_ptr = malloc(sizeof(int));
      *int_ptr = 5;
      // No memory read or write can be reordered after
      // memory_order_release. The side effects are "visible"
      // after memory_order_release.
      atomic_store_explicit(&lock, false, memory_order_release);
    }
  printf("singleton int_ptr addr: %p, value: %d\n", int_ptr, *int_ptr);
  return NULL;
}

int main()
{
  pthread_t p1, p2; 
  pthread_create(&p1, NULL, thread_start, NULL);
  pthread_create(&p2, NULL, thread_start, NULL);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  printf("singleton int_ptr addr: %p, value: %d\n", int_ptr, *int_ptr);
  return 0;
}

