#!/bin/bash

programs=(
  atomic_wait_free_8
  pthread_mutex_8
  atomic_mutex1_8
  atomic_mutex2_8
  atomic_mutex3_8
  atomic_mutex4_8
  atomic_mutex5_8
  pthread_rwlock_8
  atomic_punch_card_8
)

for platform in c4.4xlarge c4.8xlarge; do
  case $platform in
    c4.4xlarge) t_mod=2 ;;
    c4.8xlarge) t_mod=4 ;;
  esac
  for program in ${programs[@]}
  do
    mysql -N -ufelix atomic <<SQL > $program
select thread, avg(time_elapse)
from benchmark
where
    cycle = 20 and
    fix_prob = 1 and
    program = "$program" and
    platform = "$platform" and
    thread = 1
union
select thread, avg(time_elapse)
from benchmark
where
    cycle = 20 and
    fix_prob = 1 and
    program = "$program" and
    platform = "$platform" and
    thread % $t_mod = 0
group by thread;
SQL
  done

  gnuplot -p -e "
  set t 'png' small size 720,640 enhanced;
  set output '${platform}_mutex_low_contention_8.png';
  set multiplot layout 1,1 ti 'Low contention test - $platform - 8 slots';
  set style data histogram;
  set style histogram cluster gap 2;
  plot
  'atomic_wait_free_8' u 2:xtic(1) ti 'atomic counter',
  'pthread_mutex_8' u 2:xtic(1) ti 'pthread mutex',
  'atomic_mutex1_8'u 2:xtic(1) ti 'atomic spin lock 1',
  'atomic_mutex2_8'u 2:xtic(1) ti 'atomic spin lock 2',
  'atomic_mutex3_8'u 2:xtic(1) ti 'atomic spin lock 3',
  'atomic_mutex4_8'u 2:xtic(1) ti 'atomic spin lock 4',
  'atomic_mutex5_8'u 2:xtic(1) ti 'atomic spin lock 5',
  'pthread_rwlock_8' u 2:xtic(1) ti 'pthread rwlock',
  'atomic_punch_card_8' u 2:xtic(1) ti 'punch card';
  "

  rm ${programs[@]}
done
