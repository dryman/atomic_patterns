#!/bin/bash

for platform in c4.4xlarge c4.8xlarge; do
  for program in nc_address nc_thread_local; do
    mysql -N -ufelix atomic <<SQL > $program
select thread, avg(time_elapse)/1000000, max(time_elapse)/1000000,
  min(time_elapse)/1000000
from benchmark
where
    cycle = 20 and
    fix_prob = 0 and
    program = "$program" and
    platform = "$platform"
group by thread;
SQL
  done

  gnuplot -p -e "
  set t 'png' small size 680,480 enhanced;
  set output '${platform}_tls_fc.png';
  set multiplot layout 1,1 ti 'Thread local memory access latency - $platform';
  plot 'nc_address' using (\$1-0.25):2:3:4 with errorbars 
  ti 'C11 thread local variable',
  'nc_thread_local' using (\$1+0.25):2:3:4 with errorbars
  ti 'Independent address';"

  rm nc_address
  rm nc_thread_local
done
