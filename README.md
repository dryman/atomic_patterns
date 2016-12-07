Atomic design pattern
=====================

All programs below support command line flag:

1. `-c <cycles>` cycles are measured in power of 2. For example `-c 1` will
be 2 cycles, `-c 10` will be 1024 cycles.
2. `-t <threads>` number of threads

### No contention tests

The first set of tests have no contention. It measures the raw latency of
thread local variable, pthread mutex, atomic mutex, etc. User can also apply
`-t <threads>` to see how performance degrades due to context switches.

* nc_thread_local 
* nc_address
* nc_atomic_mutex1 
* nc_atomic_mutex2 
* nc_atomic_mutex3 
* nc_atomic_mutex4 
* nc_atomic_mutex5 
* nc_pthread_mutex 
* nc_pthread_rwlock_r 
* nc_pthread_rwlock_w 
* nc_atomic_rwlock_r 
* nc_atomic_rwlock_w 
* nc_atomic_punch_card_r 
* nc_atomic_punch_card_w 

### Contention tests

* atomic_wait_free 
* atomic_wait_free_8
* atomic_wait_free_16
* atomic_wait_free_32
* atomic_wait_free_64
* pthread_mutex 
* atomic_mutex1 
* atomic_mutex2 
* atomic_mutex3 
* atomic_mutex4 
* atomic_mutex5 
* pthread_mutex_8 
* atomic_mutex1_8 
* atomic_mutex2_8 
* atomic_mutex3_8 
* atomic_mutex4_8 
* atomic_mutex5_8 
* pthread_mutex_16 
* atomic_mutex1_16 
* atomic_mutex2_16 
* atomic_mutex3_16 
* atomic_mutex4_16 
* atomic_mutex5_16 
* pthread_mutex_32 
* atomic_mutex1_32 
* atomic_mutex2_32 
* atomic_mutex3_32 
* atomic_mutex4_32 
* atomic_mutex5_32 
* pthread_mutex_64 
* atomic_mutex1_64 
* atomic_mutex2_64 
* atomic_mutex3_64 
* atomic_mutex4_64 
* atomic_mutex5_64 
* pthread_rwlock 
* atomic_rwlock 
* atomic_punch_card 
* pthread_rwlock_8 
* atomic_rwlock_8 
* atomic_punch_card_8 
* pthread_rwlock_16 
* atomic_rwlock_16 
* atomic_punch_card_16 
* pthread_rwlock_32 
* atomic_rwlock_32 
* atomic_punch_card_32 
* pthread_rwlock_64 
* atomic_rwlock_64 
* atomic_punch_card_64 

### misc

* atomic_rwlock2 
* atomic_cas 
* atomic_cas_handtune

Compile:

```
autoreconf -vif
./configure
make
```

See comments for how it works.

Reference:
* [http://en.cppreference.com/w/c/atomic][]
