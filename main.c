#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

extern void* test(void* arg);

uint64_t count = 0;
uint64_t counts[128];

int main(int argc, char* argv[])
{
  int num_threads = 1;
  int cycle_power = 0;
  bool fix_prob = false;

  int c;
  
  while ((c = getopt(argc, argv, "ft:c:")) != -1)
    {
      switch (c)
        {
        case 't':
          num_threads = atoi(optarg);
          break;
        case 'c':
          cycle_power = atoi(optarg);
          break;
        case 'f':
          fix_prob = true;
          break;
        default:
          abort();
        }
    }

  printf("num_threads: %d, cycle_power: %d\n", num_threads, cycle_power);

  pthread_t threads[num_threads];
  uint64_t cycle = 1L << cycle_power;
  if (fix_prob)
    cycle /= num_threads;

  for (int i = 0; i < num_threads; i++)
    pthread_create(&threads[i], NULL, &test, &cycle);

  for (int i = 0; i < num_threads; i++)
    pthread_join(threads[i], NULL);

  printf("count: %" PRIu64 "\n", count);
  for (int i = 0; i < 8; i++)
    printf("counts: %" PRIu64 "\n", counts[i]);

  return 0;
}
