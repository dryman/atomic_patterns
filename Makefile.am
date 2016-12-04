bin_PROGRAMS = atomic_lock atomic_rwlock atomic_singleton
atomic_lock_SOURCES = atomic_lock.c
atomic_rwlock_SOURCES = atomic_rwlock.c
atomic_singleton_SOURCES = atomic_singleton.c

if ATOMIC_HACK
atomic_lock_SOURCES += nop.c
atomic_rwlock_SOURCES += nop.c
atomic_singleton_SOURCES += nop.c
endif
