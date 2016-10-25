CFLAGS+=-std=c11
all:	atomic_lock atomic_rwlock atomic_singleton
atomic_lock:	atomic_lock.c
atomic_rwlock:	atomic_rwlock.c
atomic_singleton:	atomic_singleton.c
