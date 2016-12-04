AC_INIT([atomic_pattern],[0.1])

AC_CONFIG_SRCDIR([atomic_lock.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
AM_PROG_AS

AC_PROG_CC_C11
AC_C_INLINE
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([limits.h inttypes.h])
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MMAP
AX_CFLAGS_WARN_ALL
AX_PTHREAD

LIBS="$PTHREAD_LIBS $LIBS"
CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
CC="$PTHREAD_CC"

# ugly test to detect gcc and clang that pretends to be gcc
AS_IF([test "x$GCC" = "xyes"],
  [AS_IF([$CC --version | grep "clang"],
   [atomic_LIBS=""],
   [atomic_LIBS="-latomic"])],
  [atomic_LIBS=""])
AC_SUBST([atomic_LIBS])

#LIBS="$LIBS $atomic_LIBS"

AC_DEFUN([AX_ATOMIC_HACK],
[
  AC_LANG_PUSH([C])
  AC_MSG_CHECKING([for atomic data races compiles])
  AC_COMPILE_IFELSE(
   [AC_LANG_PROGRAM([$1], [$2])],
   [AC_MSG_RESULT([yes])],
   [AC_MSG_ERROR([no])])
  AC_MSG_CHECKING([for atomic data races runs])
  AC_RUN_IFELSE(
     [AC_LANG_PROGRAM([$1], [$2])],
     [
      AM_CONDITIONAL([ATOMIC_HACK],
     		[test "x$(cat conftest_atomic_race)" != "x20000"])
      AS_IF([test "x$(cat conftest_atomic_race)" = "x20000"],
       [AC_MSG_RESULT([no need to hack])
        AC_DEFINE([ATOMIC_HACK_DECLARE],[ ])
        AC_DEFINE([ATOMIC_HACK_OP],[ ])
        ],
       [
        AC_DEFINE([ATOMIC_HACK_DECLARE], [extern void nop();], [nop declare.])
        AC_DEFINE([ATOMIC_HACK_OP], [nop()], [Force nop function call.])
        AC_MSG_RESULT([hack applied])
       ])
      rm -f conftest_atomic_race
     ],
     [AC_MSG_ERROR([run failed])])
  AC_LANG_POP([C])
])


AX_ATOMIC_HACK( 
[[#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
static atomic_bool lock = false;
static int counter = 0;
void* test(void *arg)
{
  bool expected_bool = false;
  for (int i = 0; i < 10000; i++)
    {   
      while (!atomic_compare_exchange_weak_explicit(
        &lock, &expected_bool, true,
        memory_order_acquire,
        memory_order_relaxed))
        {
          expected_bool = false;
        }
      counter++;
      atomic_store_explicit(&lock, false, memory_order_release);
    }   
  return NULL;
}
]],
[[
pthread_t p1, p2; 
pthread_create(&p1, NULL, test, NULL);
pthread_create(&p2, NULL, test, NULL);
pthread_join(p1, NULL);
pthread_join(p2, NULL);
FILE *f;
f = fopen("conftest_atomic_race", "w"); if (!f) return 1;
fprintf(f, "%d\n", counter);
]])



AC_CONFIG_FILES([Makefile])

AC_OUTPUT
