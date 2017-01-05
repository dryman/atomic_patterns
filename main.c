#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>

extern void* test(void* arg);
extern void setup(int num_threads);

uint64_t count = 0;
uint64_t counts[128];

struct timespec start, end;
double cpu_time;

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {       diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char* argv[])
{
  int num_threads = 1;
  int cycle_power = 0;
  bool fix_prob = false;

  int c;
  
  while ((c = getopt(argc, argv, "ft:c:")) != -1)
    {
      switch (c)
        {case 't':
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

  clock_gettime(CLOCK_REALTIME, &start);/* measurement: start */

  setup(num_threads);
  for (int i = 0; i < num_threads; i++)
    pthread_create(&threads[i], NULL, &test, &cycle);

  for (int i = 0; i < num_threads; i++)
    pthread_join(threads[i], NULL);

  printf("count: %" PRIu64 "\n", count);
  for (int i = 0; i < 8; i++)
    printf("counts: %" PRIu64 "\n", counts[i]);

  clock_gettime(CLOCK_REALTIME, &end); /* meansurement: end */
  cpu_time = diff_in_second(start, end);

  printf("\nexecution time: %lf sec\n", cpu_time);

  return 0;
}
