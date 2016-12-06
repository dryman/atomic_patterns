bin_PROGRAMS = atomic_lock atomic_singleton \
no_contention1 no_contention2 \
pthread_mutex_no_contention pthread_mutex \
atomic_mutex_no_contetion atomic_mutex atomic_mutex2 \
atomic_mutex3 atomic_mutex4 atomic_mutex5 \
atomic_wait_free atomic_cas atomic_cas_handtune \
atomic_rwlock atomic_rwlock2 pthread_rwlock \
atomic_punch_card

atomic_lock_SOURCES = atomic_lock.c
atomic_singleton_SOURCES = atomic_singleton.c
no_contention1_SOURCES = no_contention1.c main.c
no_contention2_SOURCES = no_contention2.c main.c
pthread_mutex_no_contention_SOURCES = pthread_mutex_no_contention.c main.c
pthread_mutex_SOURCES = pthread_mutex.c main.c
atomic_mutex_no_contetion_SOURCES = atomic_mutex_no_contetion.c main.c
atomic_mutex_SOURCES = atomic_mutex.c main.c
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
atomic_lock_SOURCES += nop.c
atomic_mutex_no_contetion_SOURCES += nop.c
atomic_mutex_SOURCES += nop.c
atomic_mutex2_SOURCES += nop.c
atomic_rwlock_SOURCES += nop.c
endif
