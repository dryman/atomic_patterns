#!/usr/bin/env perl
use strict;
use warnings;
use 5.010;

$, = ", ";
my ($program, $cycle, $thread, $fix_prob,
$task_clock, $cpu_utilize,
$ctx_switch,
$cpu_migration,
$page_fault,
$time_elapsed
);
while(<>) {
  chomp;
  next if /^#/ or /^$/;
  if (/Performance.*'\.\/(\w+) -c (\d+) -t (\d+)( -f)?'/) {
    $program = $1;
    $cycle = $2;
    $thread = $3;
    $fix_prob = $4 ? 1 : 0;
    #say $program, $cycle, $thread, $fix_prob;
  } 
  if (/([\d.]+)\s+task-clock.+?([\d.]+) CPUs utilized/) {
    $task_clock = $1;
    $cpu_utilize = $2;
    #say $task_clock, $cpu_utilize;
  }
  if (/(\d+)\s+context-switches/) {
    $ctx_switch = $1;
  }
  if (/(\d+)\s+cpu-migrations/) {
    $cpu_migration = $1;
  }
  if (/(\d+)\s+page-faults/) {
    $page_fault = $1;
  }
  if (/([\d.]+) seconds time elapsed/) {
    $time_elapsed = $1;
    say $program, $cycle, $thread, $fix_prob,
      $task_clock, $cpu_utilize,
      $ctx_switch,
      $cpu_migration,
      $page_fault,
      $time_elapsed;
  }
}
