Atomic design pattern
=====================

1. spin lock: `atomic_lock.c`
2. singleton: `atomic_singleton.c`
3. rwlock: `atomic_rwlock.c`

Compile:

```
autoreconf -vif
./configure
make
```

See comments for how it works.

Reference:
* [http://en.cppreference.com/w/c/atomic][]
