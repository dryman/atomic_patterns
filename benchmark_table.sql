use atomic;
drop table if exists benchmark;
create table benchmark (
  platform char(16),
  program char(32),
  cycle smallint,
  thread smallint,
  fix_prob smallint,
  task_clock float,
  cpu_utilize float,
  ctx_switch integer,
  cpu_migration integer,
  page_fault integer,
  time_elapse double
);
load data infile 'datafile' into table `benchmark`
columns terminated by ', '
lines terminated by '\n'
;

