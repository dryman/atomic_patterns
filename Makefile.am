bin_PROGRAMS = atomic_lock atomic_rwlock atomic_singleton \
no_contention1 no_contention2

atomic_lock_SOURCES = atomic_lock.c
atomic_rwlock_SOURCES = atomic_rwlock.c
atomic_singleton_SOURCES = atomic_singleton.c
no_contention1_SOURCES = no_contention1.c main.c
no_contention2_SOURCES = no_contention2.c main.c

if ATOMIC_HACK
atomic_lock_SOURCES += nop.c
atomic_rwlock_SOURCES += nop.c
atomic_singleton_SOURCES += nop.c
endif
