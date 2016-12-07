bin_PROGRAMS = \
nc_thread_local \
nc_atomic_mutex1 \
nc_atomic_mutex2 \
nc_atomic_mutex3 \
nc_atomic_mutex4 \
nc_atomic_mutex5 \
nc_pthread_mutex \
nc_pthread_rwlock_r \
nc_pthread_rwlock_w \
nc_atomic_rwlock_r \
nc_atomic_rwlock_w \
nc_atomic_punch_card_r \
nc_atomic_punch_card_w \
pthread_mutex \
atomic_mutex_no_contetion atomic_mutex1 atomic_mutex2 \
atomic_mutex3 atomic_mutex4 atomic_mutex5 \
atomic_wait_free atomic_cas atomic_cas_handtune \
atomic_rwlock atomic_rwlock2 pthread_rwlock \
atomic_punch_card

nc_thread_local_SOURCES = nc_thread_local.c main.c
nc_atomic_mutex1_SOURCES = nc_atomic_mutex1.c main.c
nc_atomic_mutex2_SOURCES = nc_atomic_mutex2.c main.c
nc_atomic_mutex3_SOURCES = nc_atomic_mutex3.c main.c
nc_atomic_mutex4_SOURCES = nc_atomic_mutex4.c main.c
nc_atomic_mutex5_SOURCES = nc_atomic_mutex5.c main.c
nc_pthread_mutex_SOURCES = nc_pthread_mutex.c main.c
nc_pthread_rwlock_r_SOURCES = nc_pthread_rwlock_r.c main.c
nc_pthread_rwlock_w_SOURCES = nc_pthread_rwlock_w.c main.c
nc_atomic_rwlock_r_SOURCES = nc_atomic_rwlock_r.c main.c
nc_atomic_rwlock_w_SOURCES = nc_atomic_rwlock_w.c main.c
nc_atomic_punch_card_r_SOURCES = nc_atomic_punch_card_r.c main.c
nc_atomic_punch_card_w_SOURCES = nc_atomic_punch_card_w.c main.c
pthread_mutex_SOURCES = pthread_mutex.c main.c
atomic_mutex_no_contetion_SOURCES = atomic_mutex_no_contetion.c main.c
atomic_mutex1_SOURCES = atomic_mutex1.c main.c
atomic_mutex2_SOURCES = atomic_mutex2.c main.c
atomic_mutex3_SOURCES = atomic_mutex3.c main.c
atomic_mutex4_SOURCES = atomic_mutex4.c main.c
atomic_mutex5_SOURCES = atomic_mutex5.c main.c
atomic_wait_free_SOURCES = atomic_wait_free.c main.c
atomic_cas_SOURCES = atomic_cas.c main.c
atomic_cas_handtune_SOURCES = atomic_cas_handtune.s main.c
atomic_rwlock_SOURCES = atomic_rwlock.c main.c
atomic_rwlock2_SOURCES = atomic_rwlock2.c main.c
pthread_rwlock_SOURCES = pthread_rwlock.c main.c
atomic_punch_card_SOURCES = atomic_punch_card.c main.c

if ATOMIC_HACK
nc_atomic_mutex1_SOURCES += nop.c
nc_atomic_mutex2_SOURCES += nop.c
nc_atomic_rwlock_r_SOURCES += nop.c
nc_atomic_rwlock_w_SOURCES += nop.c
atomic_mutex1_SOURCES += nop.c
atomic_mutex2_SOURCES += nop.c
atomic_rwlock_SOURCES += nop.c
endif
