#!/bin/bash

for platform in c4.4xlarge c4.8xlarge; do
  case $platform in
    c4.4xlarge) t_mod=2 ;;
    c4.8xlarge) t_mod=4 ;;
  esac
  for program in nc_address nc_thread_local \
    nc_atomic_mutex1 nc_atomic_mutex2 nc_atomic_mutex3 \
    nc_atomic_mutex4 nc_atomic_mutex5 nc_pthread_mutex \
    nc_pthread_rwlock_r nc_pthread_rwlock_w \
    nc_atomic_punch_card_r nc_atomic_punch_card_w
  do
    mysql -N -ufelix atomic <<SQL > $program
select thread, avg(time_elapse)/1000000
from benchmark
where
    cycle = 20 and
    fix_prob = 0 and
    program = "$program" and
    platform = "$platform" and
    thread = 1
union
select thread, avg(time_elapse)/1000000
from benchmark
where
    cycle = 20 and
    fix_prob = 0 and
    program = "$program" and
    platform = "$platform" and
    thread % $t_mod = 0
group by thread;
SQL
  done

  gnuplot -p -e "
  set t 'png' small size 720,640 enhanced;
  set output '${platform}_op_latency_fc.png';
  set multiplot layout 1,1 ti 'No contention operation latency - $platform';
  set style data histogram;
  set style histogram cluster gap 1;
  plot
  'nc_address' u 2:xtic(1) ti 'C11 thread local variable',
  'nc_thread_local' u 2:xtic(1) ti 'Independent address',
  'nc_atomic_mutex1' u 2:xtic(1) ti 'atomic mutex 1',
  'nc_atomic_mutex2' u 2:xtic(1) ti 'atomic mutex 2',
  'nc_atomic_mutex3' u 2:xtic(1) ti 'atomic mutex 3',
  'nc_atomic_mutex4' u 2:xtic(1) ti 'atomic mutex 4',
  'nc_atomic_mutex5' u 2:xtic(1) ti 'atomic mutex 5',
  'nc_pthread_mutex' u 2:xtic(1) ti 'pthread mutex',
  'nc_pthread_rwlock_r' u 2:xtic(1) ti 'pthread rwlock read',
  'nc_pthread_rwlock_w' u 2:xtic(1) ti 'pthread rwlock write',
  'nc_atomic_punch_card_r' u 2:xtic(1) ti 'punch card read',
  'nc_atomic_punch_card_w' u 2:xtic(1) ti 'punch card write';
  "

  rm nc_address nc_thread_local \
    nc_atomic_mutex1 nc_atomic_mutex2 nc_atomic_mutex3 \
    nc_atomic_mutex4 nc_atomic_mutex5 nc_pthread_mutex \
    nc_pthread_rwlock_r nc_pthread_rwlock_w \
    nc_atomic_punch_card_r nc_atomic_punch_card_w
done
