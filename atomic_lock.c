#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>

static atomic_bool lock = false;
static int counter = 0;
bool global_false = true;
extern void noop();

void* thread_start(void *arg)
{
  bool expected_bool = false;
  for (int i = 0; i < 10000; i++)
    {   
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
          // gcc has a bug. It would ignore the statement above
          // unless you perform this noop().
          // asm("nop") doesn't work here.
          // writing the same algorithm in c++11 has the same problem.
          noop();
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
  global_false = false;
  pthread_t p1, p2; 
  pthread_create(&p1, NULL, thread_start, NULL);
  pthread_create(&p2, NULL, thread_start, NULL);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  // should print 20000
  printf("counter: %d\n", counter);
  return 0;
}
