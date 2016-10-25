#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>

static atomic_bool lock = false;
static int counter = 0;

void* thread_start(void *arg)
{
  for (int i = 0; i < 10000; i++)
    {   
      bool expected_bool = false;
      // On compare exchange success, memory_order_acquire
      // ensures no memory read or write can be reordered 
      // before this point.
      // 
      // On compare exchange failure, expected_bool must
      // be reload to the expected value (which is false).
      // No memory reordering is depending on it so we can
      // use memory_order_relazed
      while (!atomic_compare_exchange_weak_explicit(
        &lock, &expected_bool, true,
        memory_order_acquire,
        memory_order_relaxed))
        {   
          expected_bool = false;
        }   
      // now we can perform side effect on counter
      counter++;
      // No memory read or write can be reordered after
      // memory_order_release. The side effects are "visible"
      // after memory_order_release.
      atomic_store_explicit(&lock, false, memory_order_release);
    }   
  return NULL;
}

int main()
{
  pthread_t p1, p2; 
  pthread_create(&p1, NULL, thread_start, NULL);
  pthread_create(&p2, NULL, thread_start, NULL);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  // should print 20000
  printf("counter: %d\n", counter);
  return 0;
}
