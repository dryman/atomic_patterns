AC_INIT([atomic_pattern],[0.1])

AC_CONFIG_SRCDIR([atomic_lock.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR

AC_PROG_CC_C11
AC_C_INLINE
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([limits.h inttypes.h])
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MMAP

AX_CFLAGS_WARN_ALL
AX_PTHREAD

# ugly test to detect gcc and clang that pretends to be gcc
AS_IF([test "x$GCC" = "xyes"],
  [AS_IF([$CC --version | grep "clang"],
   [atomic_LIBS=""],
   [atomic_LIBS="-latomic"])],
  [atomic_LIBS=""])
AC_SUBST([atomic_LIBS])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
