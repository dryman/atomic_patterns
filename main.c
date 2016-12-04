#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>

extern void* test(void* arg);

uint64_t count = 0;

int main(int argc, char* argv[])
{
  int num_threads = 1;
  int cycle_power = 0;

  int c;
  
  while ((c = getopt(argc, argv, "t:c:")) != -1)
    {
      switch (c)
        {
        case 't':
          num_threads = atoi(optarg);
          break;
        case 'c':
          cycle_power = atoi(optarg);
          break;
        default:
          abort();
        }
    }

  printf("num_threads: %d, cycle_power: %d\n", num_threads, cycle_power);

  pthread_t threads[num_threads];
  for (int i = 0; i < num_threads; i++)
    pthread_create(&threads[i], NULL, &test, &cycle_power);

  for (int i = 0; i < num_threads; i++)
    pthread_join(threads[i], NULL);

  printf("counter: %" PRIu64 "\n", count);

  return 0;
}
